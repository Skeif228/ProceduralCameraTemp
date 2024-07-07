// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProceduralCamera/CameraManagers/CameraBehaviors/ProceduralVehicleCameraBehavior.h"
#include "Core/Vehicles/TestVehicle.h"
#include "Core/ProceduralCamera/CameraManagers/ProceduralCameraManager.h"

void UProceduralVehicleCameraBehavior::AdaptDataFromObservableComponent(const TObjectPtr<class UObservableActorComponent> ObservableComponent)
{
	Super::AdaptDataFromObservableComponent(ObservableComponent);

}

void UProceduralVehicleCameraBehavior::LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime)
{
	Super::LookAtTarget(TargetActor, DeltaTime);
	
	FVector TargetVisionPoint = FVector::ZeroVector, TargetVisionScale = FVector::ZeroVector;
	GetVisionDimensions(TargetActor, TargetVisionPoint, TargetVisionScale);

	TObjectPtr<ATestVehicle> TestVehicle = Cast<ATestVehicle>(TargetActor);
	if (!TestVehicle)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Red, "ViewTarget isn't TestVehicle!");
		return;
	}
	
	switch (TestVehicle->GetVehicleMovingState())
	{
		case EVehicleMovingState::Gas:
		{
			ConcentrationControllerOnDirection(TestVehicle->GetActorForwardVector(), 2.0f, DeltaTime);
			break;
		}
		case EVehicleMovingState::Reversing:
		{
			ConcentrationControllerOnDirection(TestVehicle->GetActorForwardVector() * -1, 2.0f, DeltaTime);
			break;
		}
	}
	
	if (HighVelocityCameraShakeClass)
	{
		const double VehicleSpeed = TestVehicle->GetTestVelocity().Length();
		if (VehicleSpeed > HighVelocityValue)
		{
			ProceduralCamera->StartCameraShake(HighVelocityCameraShakeClass, VehicleSpeed / 500.0);
		}
	}
	
	const double ScaledDistanceCamera = GetScaledDistanceFromTargetVisionPoint(TargetVisionScale);

	// Очевидно что контроллер у нас будет только один и возможности играть несколькими за одним пк не будет
	const TObjectPtr<APlayerController> PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const FRotator ControlRotation = PlayerController->GetControlRotation();

	FVector FinalCameraLocation = CalcThirdPersonCameraLocation(TargetVisionPoint, ControlRotation, ScaledDistanceCamera);
	UpdateCameraLocation(FinalCameraLocation);
	UpdateCameraRotation(UKismetMathLibrary::FindLookAtRotation(FinalCameraLocation, TargetVisionPoint));
}

void UProceduralVehicleCameraBehavior::SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime)
{
	Super::SmoothLookAtTarget(TargetActor, InterpSpeed, DeltaTime);

}

void UProceduralVehicleCameraBehavior::ConcentrationControllerOnDirection(const FVector& Direction, const float ConcentrationSpeed, const float DeltaTime)
{
	const TObjectPtr<APlayerController> PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const FRotator ControlRotation = PlayerController->GetControlRotation();
	const FRotator TargetRotation = Direction.ToOrientationRotator();

	const FRotator ResutlRotation = FMath::RInterpTo(ControlRotation, TargetRotation, DeltaTime, ConcentrationSpeed);
	PlayerController->SetControlRotation(ResutlRotation);
}
