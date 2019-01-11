// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Actor.h"
#include "ABItemBox.generated.h"

UCLASS()
class ARENABATTLE_API AABItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	// Init 전에 실행되는 함수

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;
	// 충돌을 감지할 박스 콜리전 컴포넌트
	
	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;
	// 비쥬어을 담당하는 박스 컴포넌트

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;
	// 상자를 열었을 때 이펙트

	UPROPERTY(EditInstanceOnly, Category = Box)
	TSubclassOf<class AABWeapon> WeaponItemClass;
	// 아이템에 무기의 정보를 탐을 클래스
	// TSubclassof - 특정 클래스와 상속받은 클래스들로 목록을 한정한다.

private:
	UFUNCTION()
		void OnCharacterOverlap(
			UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
	// 오버랩 함수

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);
	// 이펙트가 끝날때 체크할 함수
};
