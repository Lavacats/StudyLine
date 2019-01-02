// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "ArenaBattle.h"
#include "GameFramework/RotatingMovementComponent.h"
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;
	// virtual을 통해 이 3가지 함수는 상속받았다는 사실을 알 수 있으며
	// override를 통해 3가지 함수는 상속받은 함수에 내용을 추가한다는 것을 알 수 있다.
	// 게임의 호출순서 PostInitializeComponents()->BeginPlay()-> 게임 종료 -> EndPlay();

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

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* Movement;

private:
	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	float RotateSpeed;
	// 회전값
	// 1. 언리얼 에디터에서 편집이 가능하도록 UPROPERTY에서 EditAnywhere키워드를 사용합니다
	// 2. 카테고리 분류는 Stat로 분류합니다
	// 3. 정보를 은닉하기 위해 private선언을 사용합니다
	// private선언을 사용할 경우 정보 은닉으로 인해 에디터에서 접근할 수 없으므로 EditAnywhere과 모순됩니다.
	// 데이터를 은닉할 수 있는 동시에 에디터에서도 편집할 수 있는 키워드 META를 추가합니다
	// Meta = (AllowPrivateAccess = true)를 통해 데이터가 은닉되는 동시에 에디터에서도 편집할수 있게되었습니다.(캡슐화)
};
