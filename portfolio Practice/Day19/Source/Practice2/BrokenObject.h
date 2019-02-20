// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "DestructibleComponent.h"
#include "GameFramework/Actor.h"
#include "BrokenObject.generated.h"

UCLASS()
class PRACTICE2_API ABrokenObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrokenObject();

	UFUNCTION()
	void Damage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void Destroy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	class UDestructibleComponent* DestructibleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	UStaticMeshComponent* StaticComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	bool IsTriggerEnabled;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	bool IsDestroyed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	float CurrentHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	float DefaultDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Object)
	float DefaultImpulse;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
