// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProceduralCamera/CameraManagers/ProceduralCameraBehavior.h"
#include "Core/ProceduralCamera/CameraManagers/ProceduralCameraManager.h"
#include "Core/ProceduralCamera/Components/ObservableActorComponent.h"

void UProceduralCameraBehavior::ConnectToProceduralCamera(AProceduralCameraManager* NewProceduralCamera)
{
	ProceduralCamera = NewProceduralCamera;
}

bool UProceduralCameraBehavior::IsConnectedToProceduralCamera() const { return ProceduralCamera != nullptr; }

FTViewTarget& UProceduralCameraBehavior::GetViewTarget() const { return ProceduralCamera->ViewTarget; }

void UProceduralCameraBehavior::AdaptDataFromObservableComponent(const TObjectPtr<class UObservableActorComponent> ObservableComponent)
{
}

void UProceduralCameraBehavior::LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime)
{
}

void UProceduralCameraBehavior::FocusAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime)
{
}

void UProceduralCameraBehavior::FocusAtTarget(const FVector& TargetPoint, const float DeltaTime)
{
}

void UProceduralCameraBehavior::SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime)
{
}

void UProceduralCameraBehavior::UpdateCameraLocation(const FVector& Location)
{
	ProceduralCamera->ViewTarget.POV.Location = Location;
}

void UProceduralCameraBehavior::UpdateCameraRotation(const FRotator& Rotation)
{
	ProceduralCamera->ViewTarget.POV.Rotation = Rotation;
}

FVector UProceduralCameraBehavior::GetCurrentCameraLocation() const { return ProceduralCamera->ViewTarget.POV.Location; }

FRotator UProceduralCameraBehavior::GetCurrentCameraRotation() const { return ProceduralCamera->ViewTarget.POV.Rotation; }
