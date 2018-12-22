// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArenaBattle.h"
#include "WebConnection.h"
#include "ABGameInstance.generated.h"

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

	UPROPERTY()
		class UWebConnection* WebConnectionNew;

	UFUNCTION()
		void RequestTokenComplete(const FString& Token);
};
