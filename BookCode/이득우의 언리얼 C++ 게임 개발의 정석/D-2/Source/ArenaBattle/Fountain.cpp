// Fill out your copyright notice in the Description page of Project Settings.

#include "Fountain.h"


// Sets default values
AFountain::AFountain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	Splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));
	// C++에서 new와 같은 역할을 하는 CreateDefaultSubobject
	// 스태틱메시 컴포넌트를 실제로 생성한다.<UStaticMeshComponent>
	// 조명 기능에 UPointLightComponent
	// 이펙트 기능 UParticleSystemComponent

	RootComponent = Body;
	Water->SetupAttachment(Body);
	// 분수대 구조담당을 Body를 루트로 삼는다.
	// water(물)을 구조의 자식으로 넣는다.

	Light->SetupAttachment(Body);
	Splash->SetupAttachment(Body);
	// Light를 Body의 자식으로 넣는다
	// Splash를 Body의 자식으로 넣습니다.

	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f));
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));
	Splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f));
	// 초기 위치를 잡아줍니다

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_BODY(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	// 레퍼런스 정보를 통해 StaticMesh정보를 불러와 SM_BODY에 저장합니다
	// StaticMesh 와 같이 경로정보를 바꿀일이 없다면 Static으로 선언해 한번만 초기화합니다.

	if (SM_BODY.Succeeded()) // StaticMesh를 불러오는데 성공하면
	{
		Body->SetStaticMesh(SM_BODY.Object);
		//Body에 StaticMesh를 입힙니다.
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_WATER(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Meshes/Env/SM_Plains_Fountain_02.SM_Plains_Fountain_02"));
	// 레퍼런스 정보를 통해 StaticMesh정보를 불러와 SM_WATER에 저장합니다

	if (SM_WATER.Succeeded())
	{
		Water->SetStaticMesh(SM_WATER.Object);
		//Water에 StaticMesh를 입힙니다.
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		PS_SPLASH(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_Base_01.P_Water_Fountain_Splash_Base_01"));
	// 레퍼런스 정보를 통해 UParticleSystem정보를 불러와 PS_SPLASH에 저장합니다

	if (PS_SPLASH.Succeeded())
	{
		Splash->SetTemplate(PS_SPLASH.Object);
		//Splash에 PS_SPLASH를 입힙니다.
	}
}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(ArenaBattle, Warning, TEXT("Actor Name : %s, ID: %d,Locationn X: %.3f"),*GetName(), ID, GetActorLocation().X);
	//ABLOG_S(Waring);
	//ABLOG(Warning, TEXT("Actor Name : %s, ID: %d, Location X: %.3f"), *GetName(), ID, GetActorLocation().X);
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

