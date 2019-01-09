// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ABPawn.generated.h"

UCLASS()
class ARENABATTLE_API AABPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AABPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	// �÷��̾ �����Ǵ� ����
	virtual void PossessedBy(AController* NewController) override;
	// �÷��̾ �����ϴ� ����

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//-------------------������ ����� ������Ʈ-----------------------
	// VisibleAnywhere : �����Ϳ��� Ȯ���� �� ������, ���� ������ ���� ����.
	// ������ ī�װ��� �з�
	
	UPROPERTY(VisibleAnywhere, Category = Collision)
	UCapsuleComponent* Capsule;
	// ĸ�� ������Ʈ : �浹 , ������ ���

	UPROPERTY(VisibleAnywhere, Category = Visual)
	USkeletalMeshComponent* Mesh;
	// ���̷�Ż �޽� : �����, �ִϸ��̼� ���

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UFloatingPawnMovement* Movement;
	// FloatingMovment : �Է¿� ���� ĳ���Ͱ� ������

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	// SpringArm : �÷��̾��� �Է¿� ���� ĳ���Ͱ� �����̵��� �Ѵ�.

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	// Camera : ī�޶� �ٶ󺸴� ȭ���� ����Ѵ�.
	//-------------------������ ����� ������Ʈ-----------------------

	// �Է� �Լ�
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

};
