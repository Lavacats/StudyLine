// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "GameFramework/Actor.h"
#include "Weapon_Shield.generated.h"

UCLASS()
class ZELDABOTW_API AWeapon_Shield : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* ShieldMesh;

public:	
	// Sets default values for this actor's properties
	AWeapon_Shield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setShieldMesh(const TCHAR * ShieldMeshText);
	UFUNCTION()
	void ShieldCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UStaticMeshComponent* getShieldMesh() { return ShieldMesh; }

	
};
