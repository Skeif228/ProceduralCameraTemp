// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProceduralCamera/CameraManagers/ProceduralCameraManager.h"
#include "Core/ProceduralCamera/Interfaces/Observable.h"
#include "Core/ProceduralCamera/Components/ObservableActorComponent.h"
#include "Core/ProceduralCamera/CameraManagers/ProceduralCameraBehavior.h"

AProceduralCameraManager::AProceduralCameraManager()
{
	ViewPitchMin = -89.0f;
	ViewPitchMax = 89.0f;
	ViewYawMin = 0.f;
	ViewYawMax = 359.0f;
	ViewRollMin = -89.0f;
	ViewRollMax = 89.0f;
}

void AProceduralCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	// Если поведение камеры не выставлено, то проигрываем стандартное поведение камеры
	if (!ProceduralCameraBehavior)
	{
		Super::UpdateViewTarget(OutVT, DeltaTime);
		return;
	}

	if (!ProceduralCameraBehavior->IsConnectedToProceduralCamera()) ProceduralCameraBehavior->ConnectToProceduralCamera(this);

	// Если TargetActor имеет свойства быть наблюдаемым, адаптируем данные из этого актера для камеры.
	// TODO: ПОКА БЫДЛОКОД, К СОЖАЛЕНИЮ ПОДПИСАТЬСЯ НА ИЗМЕНЕНИЯ ТАРГЕТА НЕВОЗМОЖНО. НАДО РЕАЛИЗОВАТЬ ЗАПОМИНАНИЕ
	// ТАРГЕТА И НЕ КАЖДЫЙ КАДР ПРЕОБРАЗОВЫВАТЬ
	if (TScriptInterface<IObservable> ObservableActor = TScriptInterface<IObservable>(OutVT.Target))
	{
		ProceduralCameraBehavior->AdaptDataFromObservableComponent(ObservableActor->GetObservableActorComponent());
	}

	if (bFocusAtPoint)
	{
		ProceduralCameraBehavior->FocusAtTarget(TargetFocusPoint, DeltaTime);
	}
	else
	{
		ProceduralCameraBehavior->LookAtTarget(OutVT.Target, DeltaTime);
	}

	// Требуется для продолжения последовательности уже из родительского класса APlayerCameraManager, которая
	// продолжает окончательную установку камеры в указанные параметры OutVT.
	ApplyCameraModifiers(DeltaTime, OutVT.POV);
	SetActorLocationAndRotation(OutVT.POV.Location, OutVT.POV.Rotation, false);
	UpdateCameraLensEffects(OutVT);
}

void AProceduralCameraManager::FocusAtPoint(const FVector& Point, const bool bInstantFocus)
{
	bFocusAtPoint = true;
	TargetFocusPoint = Point;
}

void AProceduralCameraManager::Unfocus(const bool bInstantUnfocus)
{
	bFocusAtPoint = false;
}
