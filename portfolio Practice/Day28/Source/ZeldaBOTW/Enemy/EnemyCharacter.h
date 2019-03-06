// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Enemy/EnemyCharacterState.h"
#include "Weapon/Weapon_Arrow.h"
#include "Weapon/Weapon_Equip.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;
UCLASS()
class ZELDABOTW_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = Enemy, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* EnemyMesh;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		AActor* WeaponLocation;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UEnemyCharacterState* EnemyState;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		APawn* PlayerCharacterPawn;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float MaxSpeed;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		TSubclassOf<class AWeapon_Arrow> Weapon_Arrows;

	float AttackTimer;
	FTimerHandle AttackTimerHandle;
	UPawnSensingComponent* pawnSensing;
	class UWidgetComponent* DetectMark;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void getWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void BattleToIdle();
	void Hurt();
	
public:
	void ShootArrow();
	FVector getWeaponLocation();
	UEnemyCharacterState* getEnemyState() { return EnemyState; }
	APawn* getPlayerCharacter() { return PlayerCharacterPawn; }
	AActor* getWeapon() { return WeaponLocation; }

	void setEnemyState(UEnemyCharacterState* state) { EnemyState = state; }
};

