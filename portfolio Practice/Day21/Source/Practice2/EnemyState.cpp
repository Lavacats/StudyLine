// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyState.h"


// Sets default values for this component's properties
UEnemyState::UEnemyState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	EnemyCharacter = EnemyCharacterKind::Character_Bokoblin;
	curEnemyState = EnemyCharacterState::Enemy_IDLE;
	preEnemyState = EnemyCharacterState::Enemy_SEARCH;

	IdleNumber = 1;
	IdleRange = 100.0f;
}


// Called when the game starts
void UEnemyState::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnemyState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CurrentChracterSpeed = GetOwner()->GetVelocity().Size();
	// ...
}

