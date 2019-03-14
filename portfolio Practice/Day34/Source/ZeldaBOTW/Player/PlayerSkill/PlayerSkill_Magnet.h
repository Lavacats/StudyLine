// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerSkill_Magnet.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZELDABOTW_API UPlayerSkill_Magnet : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerSkill_Magnet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MagnetickCatch(FVector CameraLocation, FVector CameraForwardVector, AActor* playerActer);

	
};
