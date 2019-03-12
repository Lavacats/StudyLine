// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
#include "Components/Image.h"
#include "Components/WrapBox.h"
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
	UPROPERTY()
		class UImage* PlayerAimImage;
	UPROPERTY()
		class UTextBlock* PlayerArrowCountText;
	UPROPERTY()
		class UWrapBox* HeartBox;
	UPROPERTY()
		class UVerticalBox* MessageBox;

	bool AimOnOff = false;
	FTimerHandle Font1_TimerHandle;
	FTimerHandle Font2_TimerHandle;
	FTimerHandle Font3_TimerHandle;
public:
	UPlayerUIWidget(const FObjectInitializer& ObjectInitializer);
	void SetPlayerAim(bool value);
	void SetArrowCount(int count);
	void SetHP(int maxHP,int curHP);
	void SetPontAlpha(int index);


	UTexture2D* getTexture(int num);
	bool getAimOnOff() { return AimOnOff; }
	
	
};
