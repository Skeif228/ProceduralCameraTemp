// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ProceduralCameraManager.generated.h"

class UProceduralCameraBehavior;

/**
 * Абстрактный класс процедурной камеры. Задает важные методы, которые должны обязательно быть реализованы в
 * налседующих классах.
 */
UCLASS()
class PROCEDURALCAMERATEMP_API AProceduralCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

private:

	// Фокусируется ли щас камера на точку, а не актера?
	bool bFocusAtPoint = false;

	// Точка фокуса для камеры
	UPROPERTY()
	FVector TargetFocusPoint = FVector::ZeroVector;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProceduralCameraManager")
	TObjectPtr<UProceduralCameraBehavior> ProceduralCameraBehavior = nullptr;

	AProceduralCameraManager();

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override final;

	/**
	* Сфокусировать камеру на точку, указанную в Point. Данный метод "временно" отцепляет камеру от основно TargetActor и
	* заставляет следить какой-то точкой. Например, чтобы показать место куда игроку надо идти.
	* 
	* @param Point — точка на которую нужно сфокусировать камеру.
	* @param bInstantFocus — если true, то фокус произойдет моментально в ином случае плавно.
	*/
	UFUNCTION(BlueprintCallable, Category = "ProceduralCameraManager")
	void FocusAtPoint(const FVector& Point, const bool bInstantFocus = false);

	/**
	* Расфокусировать камеру с точки и вернуть на TargetActor.
	* 
	* @param bInstantUnfocus — если true, то возврат будет моментальный, если false, то плавным.
	*/
	UFUNCTION(BlueprintCallable, Category = "ProceduralCameraManager")
	void Unfocus(const bool bInstantUnfocus = false);

protected:

};
