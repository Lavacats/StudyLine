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
	// Init ���� ����Ǵ� �Լ�

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;
	// �浹�� ������ �ڽ� �ݸ��� ������Ʈ
	
	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;
	// ������� ����ϴ� �ڽ� ������Ʈ

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;
	// ���ڸ� ������ �� ����Ʈ

	UPROPERTY(EditInstanceOnly, Category = Box)
	TSubclassOf<class AABWeapon> WeaponItemClass;
	// �����ۿ� ������ ������ Ž�� Ŭ����
	// TSubclassof - Ư�� Ŭ������ ��ӹ��� Ŭ������� ����� �����Ѵ�.

private:
	UFUNCTION()
		void OnCharacterOverlap(
			UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
	// ������ �Լ�

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);
	// ����Ʈ�� ������ üũ�� �Լ�
};
