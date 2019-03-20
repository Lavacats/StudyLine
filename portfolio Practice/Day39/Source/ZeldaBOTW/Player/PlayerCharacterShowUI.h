// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Player/PlayerMesh.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Weapon/Weapon_Equip.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacterShowUI.generated.h"

UCLASS()
class ZELDABOTW_API APlayerCharacterShowUI : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* PlayerUICamera;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USceneCaptureComponent2D* playerCaputre;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* faceMesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* hairMesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* upperMesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* underMesh;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		UStaticMeshComponent*  Weapon_Bow;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		UStaticMeshComponent*  Weapon_Shield;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		UStaticMeshComponent* Weapon_Sword;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		UStaticMeshComponent*  ArrowBag;


public:
	// Sets default values for this pawn's properties
	APlayerCharacterShowUI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSkeletalMeshComponent(USkeletalMeshComponent* skeletalMesh, const TCHAR* Channel);
	void SetAnimClass(const TCHAR * AnimChannel);
	void SetMeshPosition(float X, float Y, float Z);
	
	void SetWeaponUI();
	void SetWeaponPlayerUI(UStaticMeshComponent* weapon, AWeapon_Equip* playerWeapon);
};
