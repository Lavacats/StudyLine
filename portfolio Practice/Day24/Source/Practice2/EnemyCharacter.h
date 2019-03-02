#pragma once

#include "Practice2.h"
#include "EnemyState.h"
#include "Weapon_Arrow.h"
#include "Weapon_Sword.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;
UCLASS()
class PRACTICE2_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Enemy, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* EnemyMesh;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* WeaponLocation;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UEnemyState* EnemyState;
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
	AEnemyCharacter();

	virtual void Tick(float DeltaTime) override;
	void BattleToIdle();
	void Hurt();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void getWeapon(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);


public:	
	void ShootArrow();
	FVector getWeaponLocation();
	UEnemyState* getEnemyState() { return EnemyState; }
	APawn* getPlayerCharacter() { return PlayerCharacterPawn; }
	AActor* getWeapon() { return WeaponLocation; }

	void setEnemyState(UEnemyState* state) { EnemyState = state; }
};
