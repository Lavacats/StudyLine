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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	// Chractor�� ����� SpringArm�� �޾��ݴϴ�.

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	// SpringArm�� �޾��� Camera�� �޾��ݴϴ�.

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

	void LookUp(float NewAxisValue);
	void Turn(float NewAixsValue);
	
	void ViewChange();
	void Attack();
};
