// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "DestructibleComponent.h"
#include "GameFramework/Actor.h"
#include "BrokenParts.generated.h"

UCLASS()
class PRACTICE2_API ABrokenParts : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	class UDestructibleComponent* DestructibleComponent;
	// Sets default values for this actor's properties
	ABrokenParts();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
