// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "ABAnimInstance.h"
#include "ABAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "ABCharacterStatComponent.h"
#include "ABWeapon.h"
#include "ABCharacterWidget.h"
#include "Components/WidgetComponent.h"
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
	virtual float TakeDamage(
		float DamageAmount, 
		struct FDamageEvent const&DamageEvent, 
		class AController* EventInstigator, 
		AActor* DamageCauser) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UPROPERTY(VisibleAnywhere, Category = Weapon)
	//USkeletalMeshComponent* Weapon;
	//// Weapon의 SkeletalMesh선언

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	// Chractor에 사용할 SpringArm을 달아줍니다.

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	// SpringArm에 달아줄 Camera를 달아줍니다.

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;
	// 액터에 UI위젯을 부착할 수 있도록 하는 클래스 UWidgetCompont

	bool CanSetWeapon();
	// 현재 무기를 장착할 수 있는지 확인합니다.
	void SetWeapon(class AABWeapon* NewWeapon);
	// 무기를 장착합니다.
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AABWeapon* CurrentWeapon;
	// 현재 가지고있는 무기입니다.

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UABCharacterStatComponent* CharacterStat;
	// 캐릭터 스탯 컴포넌트

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);
	void Turn(float NewAixsValue);
	
	void ViewChange();
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();
	
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UABAnimInstance* ABAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;
	// 공격 범위 캡슐의 높이(원의 반지름)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;
	// 공격 범위 캡슐의 너비(캡슐의 높이)
};
