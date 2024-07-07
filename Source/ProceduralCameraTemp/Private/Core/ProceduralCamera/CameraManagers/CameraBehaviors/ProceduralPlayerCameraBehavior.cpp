// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProceduralCamera/CameraManagers/CameraBehaviors/ProceduralPlayerCameraBehavior.h"

void UProceduralPlayerCameraBehavior::AdaptDataFromObservableComponent(const TObjectPtr<class UObservableActorComponent> ObservableComponent)
{
	Super::AdaptDataFromObservableComponent(ObservableComponent);

}

void UProceduralPlayerCameraBehavior::LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime)
{
	Super::LookAtTarget(TargetActor, DeltaTime);

	FVector TargetVisionPoint = FVector::ZeroVector, TargetVisionScale = FVector::ZeroVector;
	GetVisionDimensions(TargetActor, TargetVisionPoint, TargetVisionScale);

	const double ScaledDistanceCamera = GetScaledDistanceFromTargetVisionPoint(TargetVisionScale);

	// Очевидно что контроллер у нас будет только один и возможности играть несколькими за одним пк не будет
	const TObjectPtr<APlayerController> PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const FRotator ControlRotation = PlayerController->GetControlRotation();

	FVector FinalCameraLocation = CalcThirdPersonCameraLocation(TargetVisionPoint, ControlRotation, ScaledDistanceCamera);
	UpdateCameraLocation(FinalCameraLocation);
	UpdateCameraRotation(UKismetMathLibrary::FindLookAtRotation(FinalCameraLocation, TargetVisionPoint));
}

void UProceduralPlayerCameraBehavior::SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime)
{
	Super::SmoothLookAtTarget(TargetActor, InterpSpeed, DeltaTime);

}
