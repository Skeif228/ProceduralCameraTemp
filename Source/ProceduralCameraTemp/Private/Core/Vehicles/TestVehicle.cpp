// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Vehicles/TestVehicle.h"
#include "Core/ProceduralCamera/Components/ObservableActorComponent.h"

ATestVehicle::ATestVehicle()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	ObservableActorComponent = CreateDefaultSubobject<UObservableActorComponent>("ObservableActorComponent");
}

void ATestVehicle::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	WorldDirection *= ScaleValue;

	if (WorldDirection.X == 1.0)
	{
		VehicleMovingState = EVehicleMovingState::Gas;
	}
	else if (WorldDirection.X == -1.0)
	{
		VehicleMovingState = EVehicleMovingState::Reversing;
	}
	else if (WorldDirection.X == 0.0)
	{
		VehicleMovingState = EVehicleMovingState::Stay;
	}

	TestVelocity = WorldDirection * Speed;
}

const TObjectPtr<class UObservableActorComponent> ATestVehicle::GetObservableActorComponent() const { return ObservableActorComponent; }

FVector ATestVehicle::GetTestVelocity() const { return TestVelocity; }

EVehicleMovingState ATestVehicle::GetVehicleMovingState() const { return VehicleMovingState; }

void ATestVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const FVector StartLocation = GetActorLocation() + FVector{ 0.0,0.0,50.0 };
	DrawDebugLine(GetWorld(), StartLocation, StartLocation + TestVelocity, FColor::Red);
}

void ATestVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

