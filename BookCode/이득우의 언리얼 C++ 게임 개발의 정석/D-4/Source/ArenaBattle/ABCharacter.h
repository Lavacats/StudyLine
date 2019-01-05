// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "ABAnimInstance.h"
#include "ABAnimInstance.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

UCLASS()
class ARENABATTLE_API AABCharacter : public ACharacter
{
	// ACharacter는 APawn을 상속받아 APawn의 속성을 가지고 있습니다.
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetControlMode(int32 ControlMode);

	// 게임의 형태를 열겨형으로 정리
	enum class EControlMode {
		GTA,
		DIABLO
	};

	void SetControlMode(EControlMode NewControlMode);
	// 컨트롤러의 모드를 지정하는 함수
	EControlMode CurrentControlMode = EControlMode::GTA;
	// 현재 사용중인 게임모드 변수
	FVector DirectionToMove = FVector::ZeroVector;
	// 현재 입려된 값을 저장하는 변수(현재 입력 중인지 아닌지 판별)

	float ArmLengthTo = 0.0f;
	// 게임 모드를 전환하며 바꿀 SptrimArm의 길이
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	// SpringArm의 회전값
	float ArmLengthSpeed = 0.0f;
	// SpringArm의 이동속도
	float ArmRotationSpeed = 0.0f;
	// SpringRotation의 회전속도

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	// Chractor에 사용할 SpringArm을 달아줍니다.

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	// SpringArm에 달아줄 Camera를 달아줍니다.

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);
	void Turn(float NewAixsValue);
	
	void ViewChange();
	void Attack();
};
