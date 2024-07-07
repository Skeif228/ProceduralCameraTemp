// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObservableActorComponent.generated.h"

/**
* Компонент для актеров за которым игрок может следить с помощью камеры (предположительно от 3-го лица).
* Все свойства с позициями исчисляются относительно владельца компонента!
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALCAMERATEMP_API UObservableActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Минимальная дистанция камеры от TargetVisionPoint
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ObservableActorComponent|Config", meta = (Units = "Centimeters", ClampMin = 0))
	double MinDistanceCameraFromTargetVisionPoint = 300.0;

	// Вектор указывающий на место куда должна смотреть камера
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ObservableActorComponent|Config")
	FVector TargetVisionPoint = FVector::ZeroVector;

	UObservableActorComponent();

protected:

	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
