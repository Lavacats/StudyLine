// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice1.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "GameFramework/Actor.h"
#include "WoodBox.generated.h"


UCLASS()
class PRACTICE1_API AWoodBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWoodBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;
	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* BoxN;
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* BoxE;
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* BoxS;
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* BoxW;
	UPROPERTY(VisibleAnywhere, Category = Box)
	UPhysicsConstraintComponent* BoxPhysicsConstraintX;
	UPROPERTY(VisibleAnywhere, Category = Box)
	UPhysicsConstraintComponent* BoxPhysicsConstraintY;
private:
	UFUNCTION()
		void OnCharacterOverlap(
			UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnCharacterImpactNorth(
			UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnCharacterImpactEast(
			UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnCharacterImpactSouth(
			UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnCharacterImpactWest(
			UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
