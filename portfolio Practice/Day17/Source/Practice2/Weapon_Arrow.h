// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "DestructibleComponent.h"
#include "DestructibleActor.h"
#include "GameFramework/Actor.h"
#include "Weapon_Arrow.generated.h"

UCLASS()
class PRACTICE2_API AWeapon_Arrow : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* ArrowMesh;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UCapsuleComponent* ArrowComponent;

	float BulletExpiry = 0;
	float gravityBullte = 20.0f;

	bool touchActor = false;
	UPROPERTY(EditAnywhere)
	FVector Velocity = FVector::ZeroVector;

	FVector CrushVec = FVector::ZeroVector;
public:	
	// Sets default values for this actor's properties
	AWeapon_Arrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UStaticMeshComponent* getRootMeshComponent()
	void setVelocity(FVector VelocityValue) { Velocity = VelocityValue; }
};