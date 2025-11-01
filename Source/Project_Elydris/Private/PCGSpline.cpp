#include "PCGSpline.h"

#include "Data/PCGPointData.h"
#include "Data/PCGSplineData.h"
#include "PCGContext.h"
#include "PCGPin.h"
#include "PCGComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Internationalization/Text.h"

UPCGSplineSettings::UPCGSplineSettings()
{
}

TArray<FPCGPinProperties> UPCGSplineSettings::InputPinProperties() const
{
    TArray<FPCGPinProperties> Pins;
    // entrada de spline (si no llega y el modo es ActorSpline, usamos el spline del actor)
    Pins.Emplace(PCGPinConstants::DefaultInputLabel, EPCGDataType::Spline, /*bAllowMultipleConnections=*/false);
    return Pins;
}

TArray<FPCGPinProperties> UPCGSplineSettings::OutputPinProperties() const
{
    TArray<FPCGPinProperties> Pins;
    Pins.Emplace(PCGPinConstants::DefaultOutputLabel, EPCGDataType::Point);
    return Pins;
}

static USplineComponent* FindSplineOnActor(const AActor* Actor, const FName& WantedName)
{
    if (!Actor)
    {
        return nullptr;
    }

    if (!WantedName.IsNone())
    {
        TArray<USplineComponent*> SplineComponents;
        Actor->GetComponents<USplineComponent>(SplineComponents);
        for (USplineComponent* SC : SplineComponents)
        {
            if (SC && SC->GetFName() == WantedName)
            {
                return SC;
            }
        }
    }

    return Actor->FindComponentByClass<USplineComponent>();
}

bool FPCGSplinePathSamplerElement::ExecuteInternal(FPCGContext* Context) const
{
    const UPCGSplineSettings* Settings = Context->GetInputSettings<UPCGSplineSettings>();
    if (!Settings)
    {
        return true;
    }

    USplineComponent* SplineComponent = nullptr;
    const UPCGSplineData* InputSplineData = nullptr;

    // --- 1. Resolver fuente ---
    if (Settings->SplineSourceMode == ESplineSourceMode::InputSpline)
    {
        const TArray<FPCGTaggedData>& Inputs = Context->InputData.GetInputs();
        for (const FPCGTaggedData& Input : Inputs)
        {
            if (const UPCGSplineData* SplineData = Cast<UPCGSplineData>(Input.Data))
            {
                InputSplineData = SplineData;
                break;
            }
        }

        if (!InputSplineData)
        {
            PCGE_LOG(Warning, GraphAndLog, FText::FromString(TEXT("Spline Path Sampler: no llegó spline por el pin de entrada.")));
            return true;
        }
    }
    else
    {
        UPCGComponent* PCGComp = Context->SourceComponent.Get();
        AActor* SourceActor = PCGComp ? PCGComp->GetOwner() : nullptr;
        if (!SourceActor)
        {
            PCGE_LOG(Warning, GraphAndLog, FText::FromString(TEXT("Spline Path Sampler: no hay Actor fuente.")));
            return true;
        }

        SplineComponent = FindSplineOnActor(SourceActor, Settings->SplineComponentName);
        if (!SplineComponent)
        {
            PCGE_LOG(Warning, GraphAndLog, FText::FromString(TEXT("Spline Path Sampler: el Actor no tiene USplineComponent.")));
            return true;
        }
    }

    // --- 2. Crear salida ---
    UPCGComponent* SourcePCG = Context->SourceComponent.Get();
    UObject* Outer = SourcePCG ? static_cast<UObject*>(SourcePCG) : static_cast<UObject*>(GetTransientPackage());
    UPCGPointData* OutPointData = NewObject<UPCGPointData>(Outer);
    TArray<FPCGPoint>& OutPoints = OutPointData->GetMutablePoints();

    // --- 3. Muestrear ---
    const bool bAlign = Settings->bAlignToSpline;
    const bool bConstVel = Settings->bUseConstantVelocity;

    auto SampleAt = [&](float Distance) -> FTransform
    {
        if (InputSplineData)
        {
            return InputSplineData->GetTransformAtDistance(Distance, /*bWorldSpace=*/true, bConstVel);
        }
        else
        {
            return SplineComponent->GetTransformAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World, bConstVel);
        }
    };

    // --- calcular la longitud del spline ---
    auto GetPCGSplineDataLength = [](const UPCGSplineData* SplineData) -> float
    {
        if (!SplineData)
        {
            return 0.f;
        }

        const int32 NumSegments = SplineData->GetNumSegments();
        float Total = 0.f;
        for (int32 i = 0; i < NumSegments; ++i)
        {
            Total += SplineData->GetSegmentLength(i);
        }
        return Total;
    };

    // ✅ aquí SOLO UNA VEZ
    float SplineLength = 0.0f;
    if (InputSplineData)
    {
        SplineLength = GetPCGSplineDataLength(InputSplineData);
    }
    else
    {
        SplineLength = SplineComponent->GetSplineLength();
    }

    const float StartDist = FMath::Clamp(Settings->StartDistance, 0.0f, SplineLength);
    const float EndDist   = (Settings->EndDistance > StartDist)
        ? FMath::Clamp(Settings->EndDistance, StartDist, SplineLength)
        : SplineLength;

    if (Settings->SplineSampleMode == ESplineSampleMode::ByDistance)
    {
        const float Step = FMath::Max(Settings->StepSize, 1.0f);
        for (float D = StartDist; D <= EndDist + KINDA_SMALL_NUMBER; D += Step)
        {
            FTransform T = SampleAt(D);
            if (!bAlign)
            {
                T.SetRotation(FQuat::Identity);
            }

            OutPoints.Emplace_GetRef(T, 1.0f, 0);
        }
    }
    else // ByCount
    {
        const int32 Count = FMath::Max(Settings->NumSamples, 2);
        const float Segment = (EndDist - StartDist) / (Count - 1);

        for (int32 i = 0; i < Count; ++i)
        {
            const float D = StartDist + Segment * i;
            FTransform T = SampleAt(D);
            if (!bAlign)
            {
                T.SetRotation(FQuat::Identity);
            }

            OutPoints.Emplace_GetRef(T, 1.0f, 0);
        }
    }

    // --- 4. Registrar salida ---
    FPCGTaggedData& Output = Context->OutputData.TaggedData.Emplace_GetRef();
    Output.Data = OutPointData;
    Output.Pin  = PCGPinConstants::DefaultOutputLabel;

    return true;
}
