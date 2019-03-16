// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Components/Image.h"
#include "Components/WrapBox.h"
#include "Object/ItemClass.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZELDABOTW_API UPlayerUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, Meta = (AllowPrivateAccess = true))
		class UImage* PlayerAimImage;					   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, Meta = (AllowPrivateAccess = true))
		class UTextBlock* PlayerArrowCountText;			   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, Meta = (AllowPrivateAccess = true))
		class UWrapBox* HeartBox;						   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, Meta = (AllowPrivateAccess = true))
		class UVerticalBox* MessageBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, Meta = (AllowPrivateAccess = true),Meta = (MultiLine = true))
		class UTextBlock* InfomationText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, Meta = (AllowPrivateAccess = true), Meta = (MultiLine = true))
		class UTextBlock* MoneyText;
	ItemTypeValue curInventoryItemType;
	bool AimOnOff = false;
	bool InventoryActive = false;
	FTimerHandle Font1_TimerHandle;
	FTimerHandle Font2_TimerHandle;
	FTimerHandle Font3_TimerHandle;
public:
	UPlayerUIWidget(const FObjectInitializer& ObjectInitializer);
	void SetPlayerAim(bool value);
	void SetArrowCount(int count);
	void SetHP(int maxHP,int curHP);

	void SetPontAlpha(UVerticalBox* MessageBox);
	void FontHide();
	void ShowInventory();
	void PrintMessageBox(FString Message);
	void setInventoryButtonImage();
	void setInventoryImage(TArray<UTexture2D*> ImageList);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void changeItemType(ItemTypeValue typeValue,int num);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void IventoryButton(UImage* image);

	UTexture2D* getTexture(int num);
	bool getAimOnOff() { return AimOnOff; }
	bool getInvenrotyActive() { return InventoryActive; }
};
