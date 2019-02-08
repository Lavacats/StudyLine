// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice2.h"
#include "GameFramework/Actor.h"
#include "PlayerTrace.generated.h"

UCLASS()
class PRACTICE2_API APlayerTrace : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(Category = Trace, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool TracePush = false;
	UPROPERTY(Category = Trace, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool TraceForward = false;
public:	
	APlayerTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void PlayerTraceCheck(FVector playerLocation, FVector playerForwardVector, AActor* playerActer);
	void PlayerForwardTrace(FVector playerLocation, FVector playerForwardVector, AActor* playerActer);
	void PlayerPushObject(FVector playerLocation, FVector playerForwardVector, AActor* playerActer);

	void TraceCheckActor(AActor* TraceActor);



	bool getTracePush() { return TracePush; }
	bool getTraceForward() { return TraceForward; }
};
