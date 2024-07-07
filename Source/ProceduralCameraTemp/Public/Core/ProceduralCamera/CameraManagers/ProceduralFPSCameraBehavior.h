// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ProceduralCamera/CameraManagers/ProceduralCameraBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ProceduralFPSCameraBehavior.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROCEDURALCAMERATEMP_API UProceduralFPSCameraBehavior : public UProceduralCameraBehavior
{
	GENERATED_BODY()
	
public:

	virtual void LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime) override;
	virtual void SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime) override;

	virtual void FocusAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime) override;
	virtual void FocusAtTarget(const FVector& TargetPoint, const float DeltaTime) override;
};
