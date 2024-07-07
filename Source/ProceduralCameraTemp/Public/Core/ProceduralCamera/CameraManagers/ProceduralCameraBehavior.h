// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProceduralCameraBehavior.generated.h"

class AProceduralCameraManager;

/**
 * Класс поведения процедурной камеры. Данный абстрактный класс задает все требуемые базовые методы,
 * а наследующие классы должны их реализовать.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class PROCEDURALCAMERATEMP_API UProceduralCameraBehavior : public UObject
{
	GENERATED_BODY()
	
private:

public:

	UFUNCTION(BlueprintCallable, Category = "ProceduralCameraBehavior")
	void ConnectToProceduralCamera(AProceduralCameraManager* NewProceduralCamera);

	UFUNCTION(BlueprintCallable, Category = "ProceduralCameraBehavior")
	bool IsConnectedToProceduralCamera() const;

	/**
	* Адаптировать данные камеры на основе данных из ObservableComponent. Каждый наследник сам решает как он будет их
	* адаптировать и будет ли вообще это делать.
	*
	* @param ObservableComponent — указатель на ObservableComponent.
	*/
	virtual void AdaptDataFromObservableComponent(const TObjectPtr<class UObservableActorComponent> ObservableComponent);

	/**
	* Метод производящий стандартную для камеры процедуру — смотреть на таргет, указанный в TargetActor. В этом методе
	* должна проигрываться стандартная логика с возможностью управлять камерой от контроллера.
	*
	* @param TargetActor — указатель на актера на которого надо смотреть.
	* @param DeltaTime — время с последнего обновления.
	*/
	virtual void LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime);

	/**
	* Сфокусировать камеру на TargetActor без возможности управления игроком. Позиция камеры выбирается автоматически
	* самим методом.
	* 
	* @param TargetActor — указатель на актера на которого надо сфокусироваться.
	* @param DeltaTime — время с последнего обновления.
	* 
	*/
	virtual void FocusAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime);
	virtual void FocusAtTarget(const FVector& TargetPoint, const float DeltaTime);

	/**
	* Метод аналогичен LookAtTarget, но должен реализовывать плавную слежку за TargetActor.
	*
	* @param TargetActor — указатель на актера на которого надо смотреть.
	* @param InterpSpeed — скорость плавной слежки, если bSmoothLooking = true.
	* @param DeltaTime — время с последнего обновления.
	*
	* @see LookAtTarget
	*/
	virtual void SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime);

protected:

	UPROPERTY()
	TObjectPtr<AProceduralCameraManager> ProceduralCamera = nullptr;

	FTViewTarget& GetViewTarget() const;

	void UpdateCameraLocation(const FVector& Location);
	void UpdateCameraRotation(const FRotator& Rotation);

	FVector GetCurrentCameraLocation() const;
	FRotator GetCurrentCameraRotation() const;
};
