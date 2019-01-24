// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice1.h"
#include "GameFramework/Actor.h"
#include "PracticeItemBox.generated.h"

UCLASS()
class PRACTICE1_API APracticeItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APracticeItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;
	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;
	
	
};
