// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ZeldaBOTW.h"
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

	bool AimOnOff = false;

public:

	void SetPlayerAim(bool value);
	void SetArrowCount(int count);

	bool getAimOnOff() { return AimOnOff; }
	
	
};
