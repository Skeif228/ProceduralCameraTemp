// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ProceduralCamera/CameraManagers/ProceduralTPSCameraBehavior.h"
#include "ProceduralVehicleCameraBehavior.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROCEDURALCAMERATEMP_API UProceduralVehicleCameraBehavior : public UProceduralTPSCameraBehavior
{
	GENERATED_BODY()
	
public:

	virtual void AdaptDataFromObservableComponent(const TObjectPtr<class UObservableActorComponent> ObservableComponent) override;

	virtual void LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime) override;
	virtual void SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime) override;

protected:

	// Класс тряски камеры для высоких скоростей
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProceduralCameraManager|Vehicle")
	TSubclassOf<UCameraShakeBase> HighVelocityCameraShakeClass;

	// Скорость при которой начинается тряска камеры
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProceduralCameraManager|Vehicle|Config")
	double HighVelocityValue = 500.0;

	/**
	* Концентрирует поворот на направление указанное в Direction. ЭТО НЕ ПОВОРАЧИВАЕТ КАМЕРУ, а просто
	* плавно изменяет поворот ControlRotation у контроллера. Направление исчесляется от TargetActor.
	*
	* @param TargetActor — указатель на таргет актера от которого начинается направление.
	* @param Direction — вектор, указывающий направление.
	* @param ConcentrationSpeed — скорость плавной смены направления.
	* @param DeltaTime — время с последнего обновления.
	*/
	void ConcentrationControllerOnDirection(const FVector& Direction, const float ConcentrationSpeed, const float DeltaTime);
};
