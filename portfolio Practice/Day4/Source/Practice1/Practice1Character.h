// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Practice1.h"
#include "GameFramework/Character.h"
#include "Practice1Character.generated.h"

UENUM()
enum class E_PlayerState : uint8 {
	Player_IDLE		UMETA(DisplayName="Player_IDLE"),
	Player_WALK		UMETA(DisplayName="Player_WALK"),
	Player_JUMP		UMETA(DisplayName="Player_JUMP"),
	Player_RUN		UMETA(DisplayName="Player_RUN"),
	Player_COLLECT  UMETA(DisplayName="Player_COLLECT"), 
	Player_CROUCH	UMETA(DisplayName="Player_CROUCH")
};

UCLASS()
class PRACTICE1_API APractice1Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APractice1Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* hairMesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* upperMesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* underMesh;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, Category = MoveSpeed)
	float characterMoveSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerState)
	E_PlayerState EplayerState;

	E_PlayerState PreState;

public:
	float getMoveSpeed() { return characterMoveSpeed; }
	void RunToWalk();
private:
	bool inPlayerOnAir;

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void WalkToRun();

	void Stop();
	void PlayerMovement(E_PlayerState State);

	void OnJumpCheck();
	void PlayerCrouch();
	void PlayerUnCrouch();
public:
	void SetCollectAnimation(int Collect);
	void EndCollect();
	void MoveObject(UBoxComponent* objcet);
};
