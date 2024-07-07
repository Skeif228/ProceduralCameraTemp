// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Characters/TestCharacter.h"
#include "Core/ProceduralCamera/Components/ObservableActorComponent.h"

ATestCharacter::ATestCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ObservableActorComponent = CreateDefaultSubobject<UObservableActorComponent>("ObservableActorComponent");
}

void ATestCharacter::SetTargetVisionPoint(const FVector& NewTargetVision)
{
	ObservableActorComponent->TargetVisionPoint = NewTargetVision;
}

void ATestCharacter::SetDistanceCameraFromTargetVisionPoint(const double NewDistanceCameraFromTargetVisionPoint)
{
	ObservableActorComponent->MinDistanceCameraFromTargetVisionPoint = NewDistanceCameraFromTargetVisionPoint;
}

const TObjectPtr<UObservableActorComponent> ATestCharacter::GetObservableActorComponent() const { return ObservableActorComponent; }

void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

