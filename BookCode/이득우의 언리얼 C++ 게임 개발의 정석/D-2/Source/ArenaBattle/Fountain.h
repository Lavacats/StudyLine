// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "ArenaBattle.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class ARENABATTLE_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	// UPROPERTY : 언리얼 실행 환경에서 언리얼 엔진이 자동으로 객체를 관리하는 선언
	// VisibleAnywhere : 객체를 에디터에서 볼 수 있도록 한다.
	UStaticMeshComponent *Body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *Water;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent *Light;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent *Splash;

	UPROPERTY(EditAnywhere, Category=ID)
	// EditAnywhere : 언리얼 에디터에서 속성의 데이터를 변경하도록 한다.
	// Category=분류명 : 지정된 분류값으로 분류한다.
	int32 ID;
};
