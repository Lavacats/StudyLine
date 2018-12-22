// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WebConnection.generated.h"

//DECLARE_DELEGATE_OneParam(FTokenCompleteSignature, const FString&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTokenCompleteSignature, const FString&, Token);

/**
 * 
 */
UCLASS()
class WEBSERVICE_API UWebConnection : public UObject
{
	GENERATED_BODY()
public:
	UWebConnection();

	UPROPERTY()
		FString Host;

	UPROPERTY()
		FString URI;

	UFUNCTION()
		void RequestToken(const FString& UserID);

	UPROPERTY(BlueprintAssignable,Category="WebService")
		FTokenCompleteSignature TokenCompleteDelegate;
};

DECLARE_LOG_CATEGORY_EXTERN(WebConnection, Log, All);