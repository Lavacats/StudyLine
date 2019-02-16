// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "Weapon_Arrow.h"
#include "GameFramework/Actor.h"
#include "PlayerWeapon.generated.h"
#define ArrowNum 6
UENUM()
enum class E_Weapon : uint8 {
	Weapon_BOW			UMETA(DisplayName = "Weapon_BOW"),
	Weapon_ARROW_BAG	UMETA(DisplayName = "Weapon_ARROW_BAG"),
	Weapon_SWORD		UMETA(DisplayName = "Weapon_SWORD"),
	Weapon_SWORD_SHEATH	UMETA(DisplayName = "Weapon_SWORD_SHEATH"),
	Weapon_SHIELD		UMETA(DisplayName = "Weapon_SHIELD")
};

UCLASS()
class PRACTICE2_API APlayerWeapon : public AActor
{
	GENERATED_BODY()

	int32 ArrowCount = 6;



public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TSubclassOf<class AActor>  ArrowBagBP;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AActor*  ArrowBag;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Bow;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Sword;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Sword_Sheath;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Show_Arrow;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Shield;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TSubclassOf<class AWeapon_Arrow> Weapon_Arrows;


public:	
	APlayerWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void setWeaponComponent(E_Weapon Weapon , USkeletalMeshComponent* MeshComponent, const TCHAR * Socket);
	void FireArrow(FVector location, FRotator Rotation,FVector Forward);

	void ShowArrowLocationRotation(FVector Location, FRotator Rotation,bool aimOnOFf);

	bool getWeaponVisible(E_Weapon Weapon);
	void setWeaponVisible(E_Weapon Weapon, bool check);

	bool checkParentComponent(E_Weapon Weapon, const TCHAR * Socket);

};
