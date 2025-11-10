#pragma once

#include "CoreMinimal.h"
#include "PCGSettings.h"
#include "PCGElement.h"
#include "PCGPin.h"
#include "PCGSpline.generated.h"

class UPCGPointData;
class USplineComponent;

UENUM(BlueprintType)
enum class ESplineSourceMode : uint8
{
    ActorSpline     UMETA(DisplayName="Actor Spline"),
    InputSpline     UMETA(DisplayName="Input Spline Data")
};

UENUM(BlueprintType)
enum class ESplineSampleMode : uint8
{
    ByDistance      UMETA(DisplayName="By distance"),
    ByCount         UMETA(DisplayName="By count")
};

// ⚠️ sí, está deprecated, pero en 5.5 sigue siendo la forma simple
class FPCGSplinePathSamplerElement : public FSimplePCGElement
{
protected:
    virtual bool ExecuteInternal(FPCGContext* Context) const override;
};

UCLASS(BlueprintType, ClassGroup=(Procedural))
class PROJECT_ELYDRIS_API UPCGSplineSettings : public UPCGSettings
{
    GENERATED_BODY()

public:
    UPCGSplineSettings();

#if WITH_EDITOR
    virtual FName GetDefaultNodeName() const override { return TEXT("Spline Path Sampler"); }
    virtual FText GetDefaultNodeTitle() const override { return NSLOCTEXT("PCG", "SplinePathSamplerTitle", "Spline Path Sampler"); }
    virtual FText GetNodeTooltipText() const override { return NSLOCTEXT("PCG", "SplinePathSamplerTooltip", "Samples a spline and outputs PCG points"); }
#endif

    // usa un tipo real de 5.5
    virtual EPCGSettingsType GetType() const override { return EPCGSettingsType::Sampler; }

    // ----- props -----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline")
    ESplineSourceMode SplineSourceMode = ESplineSourceMode::ActorSpline;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spline", meta=(EditCondition="SplineSourceMode==ESplineSourceMode::ActorSpline"))
    FName SplineComponentName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sampling")
    ESplineSampleMode SplineSampleMode = ESplineSampleMode::ByDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sampling", meta=(EditCondition="SplineSampleMode==ESplineSampleMode::ByDistance", ClampMin="1.0"))
    float StepSize = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sampling", meta=(EditCondition="SplineSampleMode==ESplineSampleMode::ByCount", ClampMin="2"))
    int32 NumSamples = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sampling", meta=(ClampMin="0.0"))
    float StartDistance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sampling", meta=(ClampMin="0.0"))
    float EndDistance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sampling")
    bool bAlignToSpline = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sampling")
    bool bUseConstantVelocity = false;

    virtual TArray<FPCGPinProperties> InputPinProperties() const override;
    virtual TArray<FPCGPinProperties> OutputPinProperties() const override;

protected:
    virtual FPCGElementPtr CreateElement() const override
    {
        return MakeShared<FPCGSplinePathSamplerElement>();
    }
};
