// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "P2PlayerState.h"
#include "BrokenParts.h"
#include "DestructibleComponent.h"
#include "GameFramework/Actor.h"
#include "BrokenObject.generated.h"

UCLASS()
class PRACTICE2_API ABrokenObject : public AActor
{
	GENERATED_BODY()
private:
	FTimerHandle BrokenHandler;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	class UDestructibleComponent* DestructibleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	UStaticMeshComponent* StaticComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	bool IsDestroyed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Object)
	E_PlayerState ExtraPlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Object)
	TSubclassOf<class AActor>  DropItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Object)
	AActor*  DropItem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Object)
	UStaticMesh*  DropItemMesh;
public:	
	ABrokenObject();

	UFUNCTION()
	void OnHitComponent(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void Broken();
	void setCharacterEquip(USkeletalMeshComponent* MeshComponent, const TCHAR * Socket);

	void setObjectHPDamage();
	void setBrokenColiision(bool value);
	void setExtraState(E_PlayerState value) { ExtraPlayerState = value; }
	E_PlayerState getPlayerExtraState() { return ExtraPlayerState; }
	UStaticMeshComponent* getObjectMesh() { return StaticComponent; }
};
