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
	// 플레이어가 생성되는 시점
	virtual void PossessedBy(AController* NewController) override;
	// 플레이어가 빙의하는 시점

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//-------------------폰에서 사용할 컴포넌트-----------------------
	// VisibleAnywhere : 에디터에서 확인할 수 있지만, 값을 수정할 수는 없다.
	// 각각의 카테고리로 분류
	
	UPROPERTY(VisibleAnywhere, Category = Collision)
	UCapsuleComponent* Capsule;
	// 캡슐 컴포넌트 : 충돌 , 움직임 담당

	UPROPERTY(VisibleAnywhere, Category = Visual)
	USkeletalMeshComponent* Mesh;
	// 스켈레탈 메쉬 : 비쥬얼, 애니메이션 담당

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UFloatingPawnMovement* Movement;
	// FloatingMovment : 입력에 따라 캐릭터가 움직임

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	// SpringArm : 플레이어의 입력에 따라 캐릭터가 움직이도록 한다.

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;
	// Camera : 카메라가 바라보는 화면을 출력한다.
	//-------------------폰에서 사용할 컴포넌트-----------------------

	// 입력 함수
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

};
