// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "GameFramework/Actor.h"
#include "Weapon_Bow.generated.h"

UCLASS()
class PRACTICE2_API AWeapon_Bow : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* BowMesh;
public:	
	// Sets default values for this actor's properties
	AWeapon_Bow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setShieldMesh(const TCHAR * ShieldMeshText);
	UStaticMeshComponent* getBowMesh() { return BowMesh; }
};
