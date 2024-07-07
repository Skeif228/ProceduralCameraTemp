// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProceduralCamera/CameraManagers/ProceduralTPSCameraBehavior.h"
#include "Core/ProceduralCamera/Components/ObservableActorComponent.h"

FVector UProceduralTPSCameraBehavior::CalcThirdPersonCameraLocation(const FVector& TargetPoint, const FRotator& RotationCamera, const double DistanceFromTargetVisionPoint) const
{
	const int8 InverseNumber = -1;

	// Получаем нормализованный вектор, который направлен в мире в сторону куда смотрит игрок, после инверсируем направление (*-1)
	// Умножаем этот нормализованный вектор на DistanceFromTargetVisionPoint и получаем вектор с длиной с которой должна камера быть отдалена
	// Прибавляем этот вектор к TargetVisionPoint и получаем вектор смещенный в нужное место.
	FVector FinalCameraLocation = UKismetMathLibrary::GetForwardVector(RotationCamera) * InverseNumber * DistanceFromTargetVisionPoint + TargetPoint;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TargetPoint, FinalCameraLocation, ECollisionChannel::ECC_Camera);

	// Если было столкновение, то обновляем FinalCameraLocation на место где оно было.
	// В ином случае все останется как посчиталось выше.
	if (HitResult.bBlockingHit) FinalCameraLocation = HitResult.Location;

	return FinalCameraLocation;
}

void UProceduralTPSCameraBehavior::AdaptDataFromObservableComponent(const TObjectPtr<class UObservableActorComponent> ObservableComponent)
{
	const FVector InversedTargetVisionPoint = GetViewTarget().Target->GetTransform().InverseTransformVector(ObservableComponent->TargetVisionPoint);
	OffsetTargetPoint = InversedTargetVisionPoint;
	
	MinDistanceFromTargetVisionPoint = ObservableComponent->MinDistanceCameraFromTargetVisionPoint;
}

void UProceduralTPSCameraBehavior::LookAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime)
{
}

void UProceduralTPSCameraBehavior::SmoothLookAtTarget(const TObjectPtr<AActor> TargetActor, const float InterpSpeed, const float DeltaTime)
{
}

void UProceduralTPSCameraBehavior::FocusAtTarget(const TObjectPtr<AActor> TargetActor, const float DeltaTime)
{
	FVector TargetVisionPoint = FVector::ZeroVector, TargetVisionScale = FVector::ZeroVector;
	GetVisionDimensions(TargetActor, TargetVisionPoint, TargetVisionScale);

	FVector FinalCameraLocation = FindDesiredLocationForCamera(TargetVisionPoint, 45.0, MinDistanceFromTargetVisionPoint);
	FinalCameraLocation = FMath::VInterpTo(GetCurrentCameraLocation(), FinalCameraLocation, DeltaTime, InterpCameraLocationSpeed);

	UpdateCameraLocation(FinalCameraLocation);
	UpdateCameraRotation(UKismetMathLibrary::FindLookAtRotation(FinalCameraLocation, TargetVisionPoint));
}

void UProceduralTPSCameraBehavior::FocusAtTarget(const FVector& TargetPoint, const float DeltaTime)
{
	FVector FinalCameraLocation = FindDesiredLocationForCamera(TargetPoint, 45.0, MinDistanceFromTargetVisionPoint);
	FinalCameraLocation = FMath::VInterpTo(GetCurrentCameraLocation(), FinalCameraLocation, DeltaTime, InterpCameraLocationSpeed);

	UpdateCameraLocation(FinalCameraLocation);
	UpdateCameraRotation(UKismetMathLibrary::FindLookAtRotation(FinalCameraLocation, TargetPoint));
}

FVector UProceduralTPSCameraBehavior::FindDesiredLocationForCamera(const FVector& TargetPoint, const double AngleInDegree, const double DistanceFromTargetVisionPoint, const int32 NumberOfIterations) const
{
	checkf(NumberOfIterations != 0, L"NumberOfIterations equal 0 in %s!", *GetFullName());

	TArray<FHitResult> HitResults; HitResults.SetNum(NumberOfIterations);

	const FVector HorizontalAxis = FVector { 0.0, 1.0, 0.0 };
	const FVector VerticalAxis = FVector{ 0.0, 0.0, 1.0 };

	FVector MaxVector = FVector::ZeroVector;
	double MaxDistance = 0.0;

	for (int32 x = 0; x < HitResults.Num(); ++x)
	{
		FHitResult& HitResult = HitResults[x];

		const FVector DirectionCamera = (FVector::ForwardVector * DistanceFromTargetVisionPoint).
			RotateAngleAxis(-AngleInDegree, HorizontalAxis).RotateAngleAxis(360.0 / NumberOfIterations * (x+1), VerticalAxis);

		FVector FinalCameraLocation = TargetPoint + DirectionCamera;
		GetWorld()->LineTraceSingleByChannel(HitResult, TargetPoint, FinalCameraLocation, ECollisionChannel::ECC_Camera);
		if (HitResult.bBlockingHit) FinalCameraLocation = HitResult.Location;

		double DistanceCamera = FVector::Distance(TargetPoint, FinalCameraLocation);
		if (DistanceCamera > MaxDistance)
		{
			MaxDistance = DistanceCamera;
			MaxVector = FinalCameraLocation;
		}
	}

	return MaxVector;
}

void UProceduralTPSCameraBehavior::GetVisionDimensions(const TObjectPtr<AActor> TargetActor, FVector& TargetVisionCenterPoint, FVector& TargetVisionScale) const
{
	// Получаем центр таргет актера, чтобы легко адаптироваться под любых актеров
	TargetActor->GetActorBounds(true, TargetVisionCenterPoint, TargetVisionScale);

	TargetVisionCenterPoint += OffsetTargetPoint;
}

double UProceduralTPSCameraBehavior::GetScaledDistanceFromTargetVisionPoint(const FVector& TargetVisionScale) const
{
	const double SumLength = TargetVisionScale.X + TargetVisionScale.Y + TargetVisionScale.Z;

	// Дополнительная дистанция
	const double ExtraDistance = SumLength * FactorCameraDistanceToTargetSize - MinDistanceFromTargetVisionPoint;

	// Если ExtraDistance равен или меньше 0, то значит добавлять нечего и возвращаем минимум
	if (ExtraDistance <= 0) return MinDistanceFromTargetVisionPoint;

	return MinDistanceFromTargetVisionPoint + ExtraDistance;
}
