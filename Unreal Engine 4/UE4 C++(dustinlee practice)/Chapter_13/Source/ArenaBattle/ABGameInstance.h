// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArenaBattle.h"
#include "WebConnection.h"
#include "ABGameInstance.generated.h"

class FHouse
{
public:
	TSharedPtr<FHouse> OthersDead;
	TWeakPtr<FHouse>AccessHouse;
	int32 Size = 10;
};
/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UABGameInstance();
	virtual void Init() override;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="WebService")
		class UWebConnection* WebConnection;

	//**step6**
	//UPROPERTY()
		class UWebConnection* WebConnectionNew;

	UFUNCTION()
		void RequestTokenComplete(const FString& Token);

	FTimerHandle ObjectCheckTimer;

	UFUNCTION()
		void CheckUObjectAlive();
};
