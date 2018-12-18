// Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Construcor Call! Start"));
	WebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("MyWebConnection"));
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Construcor Call! End"));
}

void UABGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Game Instance Init!"));
}