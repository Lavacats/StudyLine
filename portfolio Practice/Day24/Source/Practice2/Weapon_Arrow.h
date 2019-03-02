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
private:
	bool hitEnemy;
	bool hitPlayer;
public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* ArrowMesh;

	UPROPERTY(EditAnywhere, Category = Weapon)
	FVector Velocity = FVector::ZeroVector;
	
	FTimerHandle ArrowTimeHandler;
	FVector CrushVec;
	float gravityBullte = 20.0f;
	bool touchActor = false;

public:	
	AWeapon_Arrow();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void hitComponent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void Tick(float DeltaTime) override;
	void setVelocity(FVector VelocityValue) { Velocity = VelocityValue; }
	void setHitEnemy(bool value) { hitEnemy = value; }
	void setHitPlayer(bool value) { hitPlayer = value; }
};