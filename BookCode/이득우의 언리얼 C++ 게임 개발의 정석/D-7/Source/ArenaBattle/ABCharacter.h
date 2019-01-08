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
	// ACharacter�� APawn�� ��ӹ޾� APawn�� �Ӽ��� ������ �ֽ��ϴ�.
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetControlMode(int32 ControlMode);

	// ������ ���¸� ���������� ����
	enum class EControlMode {
		GTA,
		DIABLO
	};

	void SetControlMode(EControlMode NewControlMode);
	// ��Ʈ�ѷ��� ��带 �����ϴ� �Լ�
	EControlMode CurrentControlMode = EControlMode::GTA;
	// ���� ������� ���Ӹ�� ����
	FVector DirectionToMove = FVector::ZeroVector;
	// ���� �Է��� ���� �����ϴ� ����(���� �Է� ������ �ƴ��� �Ǻ�)

	float ArmLengthTo = 0.0f;
	// ���� ��带 ��ȯ�ϸ� �ٲ� SptrimArm�� ����
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	// SpringArm�� ȸ����
	float ArmLengthSpeed = 0.0f;
	// SpringArm�� �̵��ӵ�
	float ArmRotationSpeed = 0.0f;
	// SpringRotation�� ȸ���ӵ�

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
	//// Weapon�� SkeletalMesh����

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	// Chractor�� ����� SpringArm�� �޾��ݴϴ�.

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	// SpringArm�� �޾��� Camera�� �޾��ݴϴ�.

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;
	// ���Ϳ� UI������ ������ �� �ֵ��� �ϴ� Ŭ���� UWidgetCompont

	bool CanSetWeapon();
	// ���� ���⸦ ������ �� �ִ��� Ȯ���մϴ�.
	void SetWeapon(class AABWeapon* NewWeapon);
	// ���⸦ �����մϴ�.
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AABWeapon* CurrentWeapon;
	// ���� �������ִ� �����Դϴ�.

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UABCharacterStatComponent* CharacterStat;
	// ĳ���� ���� ������Ʈ

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
	// ���� ���� ĸ���� ����(���� ������)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;
	// ���� ���� ĸ���� �ʺ�(ĸ���� ����)
};
