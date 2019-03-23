// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "GameFramework/Character.h"
#include "NPC_Shop.generated.h"

UCLASS()
class ZELDABOTW_API ANPC_Shop : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = NPC, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* NPCMesh;
	UPROPERTY(Category = NPC, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float ShopRange;
	UPROPERTY(Category = Enemy, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* DetectMark;
public:
	// Sets default values for this character's properties
	ANPC_Shop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
