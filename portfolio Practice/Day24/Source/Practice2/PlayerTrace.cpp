// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerTrace.h"
#include "DrawDebugHelpers.h"
#include "P2PlayerState.h"
#include "BrokenObject.h"
#include "P2PlayerController.h"

APlayerTrace::APlayerTrace()
{
 	PrimaryActorTick.bCanEverTick = false;

	TraceClose = false;
	TraceForward = false;
	TraceClimming = false;
	TracePush = false;
	TraceHeights = false;
	ThrowValue = false;
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
	PlayerCloseForwardTrace(playerLocation, playerForwardVector, playerActer);
	PlayerHeightTrace(playerLocation, playerForwardVector, playerActer);
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
	static bool CarryNow = false;
	auto Controller = GetWorld()->GetFirstPlayerController();
	ABrokenObject* Object = Cast< ABrokenObject>(HitResult.GetActor());
	AP2PlayerController* PlayerController = Cast<AP2PlayerController>(Controller);
	APlayerCharacter* playerCharactor = PlayerController->getPlayerCharacter();

	if (bResult) {
		TraceForward = true;
		TraceCheckActor(HitResult, playerActer);

		if (HitResult.GetComponent()->ComponentHasTag(FName("ExtraObject"))) {
			if (IsValid(Object)) {
				if (IsValid(PlayerController)) {
					PlayerController->getPlayerState()->setExtraState(Object->getPlayerExtraState());
					//Object->setExtraState(E_PlayerState::Player_NONE);
				}
			}
		}
		if (IsValid(playerCharactor) && !CarryNow) {
			if (PlayerController->getPlayerState()->CheckCurState(E_PlayerState::Player_Carry)) {
				Object->setCharacterEquip(playerCharactor->getPlayerMeshComponent()->getRootMesh(),TEXT("PlayerForwardSocket"));
				PlayerController->getPlayerState()->setExtraState(E_PlayerState::Player_NONE);
				CarryNow = true;
				Object->setBrokenColiision(false);
			}
		}
		if (ThrowValue) {
			//Object->setCharacterEquip(playerCharactor->getPlayerMeshComponent()->getRootMesh(), TEXT("RightHandSocket"));

			PlayerController->getPlayerState()->setPlayerState(E_PlayerState::Player_IDLE);
			PlayerController->getPlayerState()->setThrowObject(true);
			Object->getObjectMesh()->DetachFromParent();
			Object->getObjectMesh()->SetSimulatePhysics(true);
			Object->setBrokenColiision(true);
			Object->setObjectHPDamage();
			ThrowValue = false;
		}
	}
	else {
		CarryNow = false;
		PlayerController->getPlayerState()->setExtraState(E_PlayerState::Player_NONE);
		TraceForward = false;
		TraceClimming = false;
		TracePush = false;
		TraceHeights = false;
	}
}

void APlayerTrace::PlayerCloseForwardTrace(FVector playerLocation, FVector playerForwardVector, AActor* playerActer)
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
		TraceClose = true;
	}
	else {
		TraceClose = false;
	}
}

void APlayerTrace::PlayerHeightTrace(FVector playerLocation, FVector playerForwardVector, AActor * playerActer)
{
	FHitResult HitResult;
	float TraceRange = 10.0f;
	float TraceRadius = 5.0f;
	float StartRange = 30.0f;
	float TraceHeight =80.0f;
	//FVector StartPosition = StartRange * playerForwardVector + FVector(0,0, TraceHeight);
	FVector StartPosition =  FVector(0, 0, TraceHeight) + playerForwardVector* StartRange;
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
	TraceHeights = bResult;
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = playerForwardVector * TraceRange;
	FVector Center = playerLocation + TraceVec * 0.5f+ StartPosition;
	float HalfHeight = TraceRange * 0.5f;
	//FQuat CapsuleRot = FRotationMatrix::Identity.ToQuat();
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
}

void APlayerTrace::TraceCheckActor(FHitResult TraceActorHitResult, AActor* PlayerActor)
{
	if (TraceActorHitResult.GetActor()->ActorHasTag("PushObject")) {
		if (TraceClose) {
			TracePush = true;
		}
	}
	if (TraceActorHitResult.GetActor()->ActorHasTag("Climing")) {
		if (TraceClose) {
			if (!TraceClimming && TraceHeights && TraceForward && TraceClose) {
				auto Character = Cast<ACharacter>(PlayerActor);
				auto PlayerController = GetWorld()->GetFirstPlayerController();
				auto playerState = Cast< AP2PlayerController>(PlayerController)->getPlayerState();
				if (playerState->getCurPlayerState() !=E_PlayerState::Player_CLIMING)
				{
					FRotator playerRo = TraceActorHitResult.Normal.Rotation();
					Character->SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, playerRo.Yaw - 180.0f, GetActorRotation().Roll));
					Character->SetActorRelativeLocation(FVector(TraceActorHitResult.Normal.X*30.0f + TraceActorHitResult.Location.X, TraceActorHitResult.Normal.Y*30.0f + TraceActorHitResult.Location.Y, TraceActorHitResult.Location.Z));
				}
			}
			TraceClimming = true;
		}
	}
}

void APlayerTrace::ThrowObject()
{
	//auto Controller = GetWorld()->GetFirstPlayerController();
	//AP2PlayerController* PlayerController = Cast<AP2PlayerController>(Controller);
	//APlayerCharacter* playerCharactor = PlayerController->getPlayerCharacter();
	//if (!IsValid(playerCharactor))return;
	//ABrokenObject* Object = Cast< ABrokenObject>(playerCharactor);
	//if (IsValid(Object)) {
	//	Object->getObjectMesh()->DetachFromParent();
	//	Object->getObjectMesh()->SetSimulatePhysics(true);
	//}
	ThrowValue = true;
}

