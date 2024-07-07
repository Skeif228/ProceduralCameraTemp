// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/ProceduralCamera/Interfaces/Observable.h"
#include "TestCharacter.generated.h"

class UObservableActorComponent;

UCLASS()
class PROCEDURALCAMERATEMP_API ATestCharacter : public ACharacter, public IObservable
{
	GENERATED_BODY()

public:
	ATestCharacter();

	UFUNCTION(BlueprintCallable, Category = "TestCharacter")
	void SetTargetVisionPoint(const FVector& NewTargetVision);

	UFUNCTION(BlueprintCallable, Category = "TestCharacter")
	void SetDistanceCameraFromTargetVisionPoint(const double NewDistanceCameraFromTargetVisionPoint);

	virtual const TObjectPtr<class UObservableActorComponent> GetObservableActorComponent() const override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TestCharacter")
	TObjectPtr<UObservableActorComponent> ObservableActorComponent;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
