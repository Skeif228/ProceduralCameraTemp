// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ProceduralCamera/CameraManagers/ProceduralTPSCameraBehavior.h"
#include "ProceduralPlayerCameraBehavior.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROCEDURALCAMERATEMP_API UProceduralPlayerCameraBehavior : public UProceduralTPSCameraBehavior
{
	GENERATED_BODY()

public:

	virtual void AdaptDataFromObservableComponent(const TObjectPtr<class UObservableActorComponent> ObservableComponent) override;

	virtual void LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime) override;
	virtual void SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime) override;

protected:

	
};
