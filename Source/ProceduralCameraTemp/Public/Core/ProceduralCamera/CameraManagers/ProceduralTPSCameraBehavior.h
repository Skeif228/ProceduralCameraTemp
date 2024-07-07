// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ProceduralCamera/CameraManagers/ProceduralCameraBehavior.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ProceduralTPSCameraBehavior.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class PROCEDURALCAMERATEMP_API UProceduralTPSCameraBehavior : public UProceduralCameraBehavior
{
	GENERATED_BODY()
	
public:

	virtual void AdaptDataFromObservableComponent(const TObjectPtr<class UObservableActorComponent> ObservableComponent) override;

	virtual void LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime) override;
	virtual void SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime) override;

	virtual void FocusAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime);
	virtual void FocusAtTarget(const FVector& TargetPoint, const float DeltaTime);

protected:

	// Смещение с точки фокуса, которая обновляется в AdaptDataFromObservableComponent, получая точку из ObservableComponent
	UPROPERTY()
	FVector OffsetTargetPoint = FVector::ZeroVector;

	// Минимальная дистанция между точкой фокуса и камеры
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProceduralCameraManager|ThirdPersonCamera", meta = (Units = "Centimeters", ClampMin = 0))
	double MinDistanceFromTargetVisionPoint = 300.0;

	// Множитель дистанции камеры к таргету (чем больше, тем дальше камера будет отдаляться)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProceduralCameraManager|ThirdPersonCamera", meta = (Units = "Times", ClampMin = 0))
	double FactorCameraDistanceToTargetSize = 1.0;

	// Скорость слежки камера за таргетом
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ProceduralCameraManager|ThirdPersonCamera", meta = (Units = "Times", ClampMin = 0))
	float InterpCameraLocationSpeed = 2.0f;

	/**
	* Посчитать позицию камеры от третьего лица, которая должна находиться позади TargetPoint и смотреть под углом указанным в Rotation,
	* находясь на дистанции указанной в DistanceFromTargetVisionPoint. Данный метод учитывает окружение и если камера будет упираться в
	* поверхность, то камера будет смещена насколько это возможно, чтобы не пробивать поверхность.
	* 
	* @param TargetPoint — вектор указывающий на место куда должна смотреть камера.
	* @param RotationCamera — ротатор указывающий угол с которого должна смотреть камера. Уточнение: Сначала камера ставится на TargetPoint
	* и поворачивается на основе этого параметра, а потом просто сдвигается назад на DistanceFromTargetVisionPoint.
	* @param DistanceFromTargetVisionPoint — дистанция камеры от TargetPoint.
	* 
	* @return Вектор позиции для камеры.
	*/
	FVector CalcThirdPersonCameraLocation(const FVector& TargetPoint, const FRotator& RotationCamera, const double DistanceFromTargetVisionPoint) const;

	/**
	* Найти желательную (красивую, комфортную) для камеры относительно TargetPoint.
	* 
	* @param TargetPoint — вектор указывающий на место куда должна смотреть камера.
	* @param AngleInDegree — вертикальный угол с которого камера должна смотреть на TargetPoint. Если 0, то камера будет на уровне
	* самого TargetPoint; Если 90, то камера будет прямо над TargetPoint; Если -90, то снизу TargetPoint;
	* @param DistanceFromTargetVisionPoint — дистанция камеры от TargetPoint.
	* @param NumberOfIterations — количество итераций для проверок позиции. Чем больше, тем больше шансов на нахождении лучшей позиции,
	* но в тоже время и производительнее.
	* 
	* @return Вектор позиции для камеры.
	*/
	FVector FindDesiredLocationForCamera(const FVector& TargetPoint, const double AngleInDegree, const double DistanceFromTargetVisionPoint, const int32 NumberOfIterations = 8) const;

	/**
	* Получить габариты актера, указанного в TargetActor, которые можно использовать для корректной
	* установки камеры (удобный вид). Желательно ОБЯЗАТЕЛЬНО получать данные по центру точки из этого метода,
	* потому что он учитывает все свойства смещения, например OffsetTargetPoint.
	* 
	* @param TargetActor — указатель на актера у которого нужно найти центр
	* @param TargetVisionCenterPoint — вектор в который метод запишет центр актера
	* @param TargetVisionScale — вектор в котором метод запишет размеры границ в виде куба.
	*/
	void GetVisionDimensions(const TObjectPtr<AActor> TargetActor, FVector& TargetVisionCenterPoint, FVector& TargetVisionScale) const;

	/**
	* Получить масштабированную дистанцию камеры от TargetVisionPoint.
	* 
	* @param TargetVisionScale — вектор указывающий на края актера в виде куба
	* 
	* @return Масштабированную дистанцию камеры от TargetVisionPoint 
	*/
	double GetScaledDistanceFromTargetVisionPoint(const FVector& TargetVisionScale) const;
};
