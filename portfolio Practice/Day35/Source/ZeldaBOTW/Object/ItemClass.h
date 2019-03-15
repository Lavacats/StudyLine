// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Components/Image.h"
#include "GameFramework/Actor.h"
#include "ItemClass.generated.h"


UENUM()
enum class ItemTypeValue : uint8 {
	ItemType_Weapon		UMETA(DisplayName = "ItemType_Weapon"),
	ItemType_Arrow		UMETA(DisplayName = "ItemType_Arrow"),
	ItemType_Food		UMETA(DisplayName = "ItemType_Food"),
	ItemType_Material	UMETA(DisplayName = "ItemType_Material")
};

UCLASS()
class ZELDABOTW_API AItemClass : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(Category = Item, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName ItemName;
	UPROPERTY(Category = Item, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FSlateBrush ItemImage;
	UPROPERTY(Category = Item, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString ItemInformation;
	UPROPERTY(Category = Item, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ItemTypeValue ItmeType;
	UPROPERTY(Category = Item, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ItemPrice;
	
public:	
	// Sets default values for this actor's properties
	AItemClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FName getItmeName() { return ItemName; }
	FSlateBrush getItemImage() { return ItemImage; }
	FString getItemInformation() { return ItemInformation; }
	ItemTypeValue getItmeTypeValue() { return ItmeType; }
	float getItemPrice() { return ItemPrice; }
	
};
