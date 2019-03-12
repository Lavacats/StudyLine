// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerSkill_Magnet.h"


UPlayerSkill_Magnet::UPlayerSkill_Magnet()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPlayerSkill_Magnet::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPlayerSkill_Magnet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPlayerSkill_Magnet::MagnetickCatch(FVector CameraLocation, FVector CameraForwardVector, AActor * playerActer)
{


}

