// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProceduralCamera/CameraManagers/ProceduralFPSCameraBehavior.h"

void UProceduralFPSCameraBehavior::LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime)
{
	const TObjectPtr<APlayerController> PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const FRotator ControlRotation = PlayerController->GetControlRotation();

	UpdateCameraLocation(TargetActor->GetActorLocation());
	UpdateCameraRotation(ControlRotation);
}

void UProceduralFPSCameraBehavior::SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime)
{

}

void UProceduralFPSCameraBehavior::FocusAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime)
{
	

}

void UProceduralFPSCameraBehavior::FocusAtTarget(const FVector& TargetPoint, const float DeltaTime)
{
	const FVector CameraLocation = GetViewTarget().Target->GetActorLocation();

	FRotator CameraRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, TargetPoint);
	CameraRotation = FMath::RInterpTo(GetCurrentCameraRotation(), CameraRotation, DeltaTime, 2.0f);

	UpdateCameraLocation(CameraLocation);
	UpdateCameraRotation(CameraRotation);
}
