// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "GameFramework/Actor.h"
#include "Weapon_Sword.generated.h"

UCLASS()
class PRACTICE2_API AWeapon_Sword : public AActor
{
	GENERATED_BODY()

private:
	bool hitEnemy;
public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* SwordMesh;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* SwordMesh_Sheath;

public:	
	// Sets default values for this actor's properties
	AWeapon_Sword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void setSwordMesh(const TCHAR * SwordMeshText, const TCHAR * SwordSheathMeshText);
	UFUNCTION()
	void SwordCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UStaticMeshComponent* getSwordMesh() {return SwordMesh;}
	UStaticMeshComponent* getSwordSheathMesh() { return SwordMesh_Sheath; }
	void setHitEnemy(bool value) { hitEnemy = value; }
};
