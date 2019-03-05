#pragma once

#include "ZeldaBOTW.h"
#include "GameFramework/Actor.h"
#include "Weapon_Sword.generated.h"

UCLASS()
class ZELDABOTW_API AWeapon_Sword : public AActor
{
	GENERATED_BODY()
	
private:
	bool hitEnemy;
	bool hitPlayer;

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* SwordMesh;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* SwordMesh_Sheath;

protected:
	virtual void BeginPlay() override;

public:
	AWeapon_Sword();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SwordCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void setSwordMesh(const TCHAR * SwordMeshText, const TCHAR * SwordSheathMeshText);
	void setCharacterEquip(USkeletalMeshComponent* MeshComponent, const TCHAR * Socket, int charactorNum = 0);

	UStaticMeshComponent* getSwordMesh() { return SwordMesh; }
	UStaticMeshComponent* getSwordSheathMesh() { return SwordMesh_Sheath; }
	
	void setHitEnemy(bool value) { hitEnemy = value; }
	void setHitPlayer(bool value) { hitPlayer = value; }
};
