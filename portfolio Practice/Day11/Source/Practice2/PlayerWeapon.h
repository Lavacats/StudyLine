// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "GameFramework/Actor.h"
#include "PlayerWeapon.generated.h"

UENUM()
enum class E_Weapon : uint8 {
	Weapon_BOW			UMETA(DisplayName = "Weapon_BOW"),
	Weapon_ARROW_BAG	UMETA(DisplayName = "Weapon_ARROW_BAG"),
	Weapon_SWORD		UMETA(DisplayName = "Weapon_SWORD")
};

UCLASS()
class PRACTICE2_API APlayerWeapon : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AActor* ArrowBag;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Bow;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TSubclassOf<class UStaticMeshComponent> Arrows;
public:	
	// Sets default values for this actor's properties
	APlayerWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent* getBow() { return Bow; }
	void setWeaponComponent(E_Weapon Weapon , USkeletalMeshComponent* MeshComponent, const TCHAR * Socket);
	bool getWeaponVisible(E_Weapon Weapon);
	void setWeaponVisible(E_Weapon Weapon,bool check);
	bool checkParentComponent(E_Weapon Weapon, const TCHAR * Socket);
};
