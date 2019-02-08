// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerTrace.h"
#include "DrawDebugHelpers.h"

APlayerTrace::APlayerTrace()
{
 	PrimaryActorTick.bCanEverTick = false;

	TracePush = false;
	TraceForward = false;
}

void APlayerTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerTrace::PlayerTraceCheck(FVector playerLocation, FVector playerForwardVector, AActor* playerActer)
{
	PlayerForwardTrace(playerLocation, playerForwardVector, playerActer);
	PlayerPushObject(playerLocation, playerForwardVector, playerActer);
}

void APlayerTrace::PlayerForwardTrace(FVector playerLocation, FVector playerForwardVector, AActor * playerActer)
{
	FHitResult HitResult;
	float TraceRange = 10.0f;
	float TraceRadius = 5.0f;
	float StartRange = 30.0f;
	FVector StartPosition = StartRange * playerForwardVector;
	FCollisionQueryParams Params(NAME_None, false, playerActer);
	bool bResult =
		GetWorld()->SweepSingleByChannel
		(
			HitResult,
			playerLocation + StartPosition,
			playerLocation + StartPosition + playerForwardVector * TraceRange,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel2,
			FCollisionShape::MakeSphere(TraceRadius),
			Params
		);
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = playerForwardVector * TraceRange;
	FVector Center = playerLocation + TraceVec * 0.5f+ StartPosition;
	float HalfHeight = TraceRange * 0.5f;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 0.5f;

	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		TraceRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime
	);
#endif

	if (bResult) {
		TraceForward = true;
		//if (HitResult.GetActor()->ActorHasTag("PushObject") && TracePush) {
		if (TracePush) {
			//HitResult.GetActor()->SetActorLocation(HitResult.GetActor()->GetActorLocation() + playerForwardVector * HitResult.GetActor()->GetVelocity().Size()*0.1f);
			TraceCheckActor(playerActer);
		}
	}
	else {
		TraceForward = false;
	}
}

void APlayerTrace::PlayerPushObject(FVector playerLocation, FVector playerForwardVector, AActor* playerActer)
{
	FHitResult HitResult;
	float TraceRange = 10.0f;
	float TraceRadius = 5.0f;
	FCollisionQueryParams Params(NAME_None, false, playerActer);
	bool bResult =
		GetWorld()->SweepSingleByChannel
		(
			HitResult,
			playerLocation,
			playerLocation + playerForwardVector * TraceRange,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel2,
			FCollisionShape::MakeSphere(TraceRadius),
			Params
		);
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = playerForwardVector * TraceRange;
	FVector Center = playerLocation + TraceVec * 0.5f;
	float HalfHeight = TraceRange * 0.5f;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 0.5f;

	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		TraceRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime
	);
#endif

	if (bResult) {
		if (HitResult.GetActor()->ActorHasTag("PushObject")) {
			TracePush = true;
		}
	}
	else {
		TracePush = false;
	}
}

void APlayerTrace::TraceCheckActor(AActor * TraceActor)
{
	if (TraceActor->ActorHasTag("PushObject")) {
		TraceActor->SetActorLocation(TraceActor->GetActorLocation() + TraceActor->GetActorForwardVector() * TraceActor->GetVelocity().Size()*0.1f);
	}
}

