// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Core/ProceduralCamera/Interfaces/Observable.h"
#include "TestVehicle.generated.h"

class UObservableActorComponent;

UENUM(BlueprintType)
enum class EVehicleMovingState
{
	Stay, Gas, Reversing
};

UCLASS()
class PROCEDURALCAMERATEMP_API ATestVehicle : public APawn, public IObservable
{
	GENERATED_BODY()

private:

	UPROPERTY()
	FVector TestVelocity = FVector::ZeroVector;

public:
	ATestVehicle();

	virtual void AddMovementInput(FVector WorldDirection, float ScaleValue = 1.0f, bool bForce = false) override;

	virtual const TObjectPtr<class UObservableActorComponent> GetObservableActorComponent() const override;
	
	FVector GetTestVelocity() const;

	EVehicleMovingState GetVehicleMovingState() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UObservableActorComponent> ObservableActorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EVehicleMovingState VehicleMovingState = EVehicleMovingState::Stay;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	double Speed = 500.0;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
