// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProceduralCamera/Components/ObservableActorComponent.h"

UObservableActorComponent::UObservableActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UObservableActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UObservableActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

