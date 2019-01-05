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

	virtual void PostInitializeComponents() override;
	// Init이 실행되기전에 먼저 실행되는 함수

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	// Chractor에 사용할 SpringArm을 달아줍니다.

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	// SpringArm에 달아줄 Camera를 달아줍니다.
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsAttacking;
	// 1. 인스탄스에서 볼수 있다.
	// 2. 블루프린트에서 읽을 수만 있다
	// 3. 카테고리는 Attack
	// 4. pritvate지만 노출할 수 있도록 Meta를 사용한다.

	UPROPERTY()
		class UABAnimInstance* ABAnim;
	// AnimInstance의 전방선언

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool CanNextCombo;
	// 다음 콤보로 넘어갈수있는지에 대한 불값
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		bool IsComboInputOn;
	// 현재 콤보중인지에 대한 불값
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 CurrentCombo;
	// 현재 쌓인 콤보의 값
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		int32 MaxCombo;
	// 최대 콤보의 값
	// 1. VisibleInstanceOnly 인스탄스에서 값을 확인할 수 있다
	// 2. Blueprint에서 읽을수만 있다
	// 3. Category는 Attack
	// 4. private지만 노출을 위해 Meta를 사용한다.

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);
	void Turn(float NewAixsValue);
	
	void ViewChange();
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	// 애니메이션의 몽타주 재생이 끝나면 실행되는 델리게이트

	void AttackStartComboState();

	void EndComboState();
	// 콤보 관련 함수


};
