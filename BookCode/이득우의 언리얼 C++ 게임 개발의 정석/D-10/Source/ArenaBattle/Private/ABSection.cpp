// Fill out your copyright notice in the Description page of Project Settings.

#include "ABSection.h"
#include "ABCharacter.h"
#include "ABItemBox.h"
#include "ABPlayerController.h"
#include "ABGameMode.h"
#include "ABGameMode.h"
#include "ABPlayerController.h"

// Sets default values
AABSection::AABSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	// Mesh에 스테틱 컴포넌트 MESH로 에디터에서 확인할수있도록한다
	RootComponent = Mesh;
	// Mesh를 루트오브젝트로 삼는다

	FString AssetPath = TEXT("/Game/Book/StaticMesh/SM_SQUARE.SM_SQUARE");
	// 사용할 메쉬의 경로를 입력합니다
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SQUARE(*AssetPath);
	// SM_SQUARE라는 이름으로 정보를 불러옵니다.
	if (SM_SQUARE.Succeeded()) {
		Mesh->SetStaticMesh(SM_SQUARE.Object);
		// 불러오는데 성공했다면 스태틱메시에 이미지를 씌웁니다
	}
	else {
		ABLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *AssetPath);
	}

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	// Trigger를 에디터에 Trigger라 표시한다.
	Trigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	// Trigger에 사용할 박스의 크기
	Trigger->SetupAttachment(RootComponent);
	// Trigger를 Root아래로 넣습니다.
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	// Trigger의 위치를 정합니다.
	Trigger->SetCollisionProfileName(TEXT("ABTrigger"));
	// Trigger 가 사용할 충돌은 ABTrigger입니다.

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABSection::OnTriggerBeginOverlap);
	// Trigger가 오버랩(겹침)되는 순가 OnTriggerBegin이벤트를 실행한다.

	FString GateAssetPath = TEXT("/Game/Book/StaticMesh/SM_GATE.SM_GATE");
	// Gate의 레퍼런스 정보를 입력합니다.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GATE(*GateAssetPath);
	// SM_GATE 변수에 입력한 레퍼런스를 통해 스태틱 메쉬를 불러옵니다.

	if (!SM_GATE.Succeeded()) {
		ABLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *GateAssetPath);
		// 불러오는데 실패했다면 로그를 출력합니다.
	}

	static FName GateSockets[] = { { TEXT("+XGate")},{TEXT("-XGate")},{TEXT("+YGate")},{TEXT("-YGate") } };
	// GateSockets 를 통해 4개 문의 이름을 분류합니다

	for (FName GateSocket : GateSockets) {
		// 문의 개수만큼 for문을 돌립니다ㅏ.
		ABCHECK(Mesh->DoesSocketExist(GateSocket));
		// 메쉬가 제대로 있는지 체크합니다.
		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		// 스태틱 메쉬 컴포넌트를 불러옵니다.
		NewGate->SetStaticMesh(SM_GATE.Object);
		// NewGate에 메시를 넣습니다.
		NewGate->SetupAttachment(RootComponent, GateSocket);
		// New 게이트는 RootComponent의 자식으로 넣습니다.
		NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
		// 게이트의 위치를 잡습니다.(게이트는 각각 GateSockets의 이름으로 SM_SQUARE에서 검색하여
		// 미리 정해진 소켓의 위치에서 80.5의 값을 더해 위치를 정합니다.
		GateMeshes.Add(NewGate);
		// NewCate를 더합니다

		UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>(*GateSocket.ToString().Append(TEXT("Trigger")));
		// 게이트 Trigger를 에디터에서 확인할 수 있도록 추가합니다.
		NewGateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		// 게이트 트리거의 크기
		NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
		// 게이트 트리거와 게이트 소캣은 루트컴포너느의 자식으로 들어갑니다.
		NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		// 게이트 트리커의 위치
		NewGateTrigger->SetCollisionProfileName(TEXT("ABTrigger"));
		// 게이트 트리거가 사용할 충돌
		GateTriggers.Add(NewGateTrigger);

		NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABSection::OnGateTriggerBeginOverlap);
		// NeGateTrigger가 Ovelap되는 순간 OnGateTriggerBeginOverlap 함수를 실행
		NewGateTrigger->ComponentTags.Add(GateSocket);
	}

	bNoBattle = false;
	// 초기 NoBattle의 값은 false를 준다.(NPC가 공격하지 않습니다)

	EnemySpawnTime = 2.0f;
	// 적의 첫 스폰시간 2초
	ItemBoxSpawnTime = 5.0f;
	// 아이템 박스의 스폰시간 5초
}

void AABSection::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
	// 에ㄷ터에서 값이 바뀔때마다 실행될수있도록한다
}

// Called when the game starts or when spawned
void AABSection::BeginPlay()
{
	Super::BeginPlay();
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
	// 시작 상태를 READY로 둔다
}

void AABSection::SetState(ESectionState NewState)
{
	switch(NewState)
		// NewState의 상태에 따라 세션이 결정된다.
	{
		case ESectionState::READY:
			// READY 상태일 떄
		{
			Trigger->SetCollisionProfileName(TEXT("ABTrigger"));
			// Trigger는 ABTrigger를 사용한다.(trigger는 플레이어가 방에있는지 검사하는 trigger이다)
			for (UBoxComponent* GateTrigger : GateTriggers) {
				GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
				// GateTrigger은 NoCollision 충돌을 사용하지 않는다.(GateTrigger는 플레이어의 다음 방으로의 진출여부)
			}

			OperateGates(true);
			// 문을 조정하는 함수에 true를 준다
			break;
		}
		case ESectionState::BATTLE:
		{
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			// trigger는 NoCollision의 값을 가진다
			for (UBoxComponent* GateTrigger : GateTriggers) {
				GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
				// GateTrigger는 충돌을 하지 않는다
			}

			OperateGates(false);
			// 문을 조정하는 함수에 false를 준다

			GetWorld()->GetTimerManager().SetTimer(
				SpawnNPCTimerHandle, FTimerDelegate::CreateUObject(this, &AABSection::OnNPCSpawn), 
				EnemySpawnTime, false);
			// 월드에 타이머 세팅을 해서 세팅 시간마다 적이 소환되는 함수를 실행하도록 합니다.

			GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle, FTimerDelegate::CreateLambda([this]()->void {

				FVector2D RandXY = FMath::RandPointInCircle(600.0f);
				GetWorld()->SpawnActor<AABItemBox>(GetActorLocation() + FVector(RandXY, 30.0f), FRotator::ZeroRotator);
			}), ItemBoxSpawnTime, false);
			// 월드에 타이머에서 세팅을 하여
			// 무작위 600범위 내부의 XY좌표에 Itembox를 스폰한다

			break;
		}
		case ESectionState::COMPLETE:
		{
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			// Tirgger는 충돌검사를 하지않는다.
			for (UBoxComponent* GateTrigger : GateTriggers) {
				GateTrigger->SetCollisionProfileName(TEXT("ABTrigger"));
				// GateTrigger은 ABTigger검사를한다.
			}

			OperateGates(true);
			// 문으 조정하는 함수에 true를 준다.
			break;
		}
	}
	CurrentState = NewState;
	// NewState 의 값을 CurrentState의 값에 덮어씌운다.
}

void AABSection::OperateGates(bool bOpen)
{
	for (UStaticMeshComponent* Gate : GateMeshes) {
		Gate->SetRelativeRotation(bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::ZeroRotator);
		// Gate들 모두에게 for문을 통해 -90만큼 회전시킨다.
	}
}

void AABSection::OnTriggerBeginOverlap(UPrimitiveComponent * OverlappedCmponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (CurrentState == ESectionState::READY) {
		SetState(ESectionState::BATTLE);
		// 현재 상태가 READY라면 현재 상ㅌ를 Battle로 바꿉니다.
	}
}

void AABSection::OnGateTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool BFromSweep, const FHitResult & SweepResult)
{
	ABCHECK(OverlappedComponent->ComponentTags.Num() == 1);
	// ComponentTags의 Num()값이 1인지 확인합니다.

	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	// 컴포넌트 태그에 충돌한 캐릭의 태그를 입력합니다.

	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	// 소캣 이름을 충돌한 캐릭터에서 가져옵니다.

	if (!Mesh->DoesSocketExist(SocketName))
		return;
	// 소캣이 없다면 함수를 종료합니다.

	FVector NewLocation = Mesh->GetSocketLocation(SocketName);
	// NewLocation 값에 메쉬의 위치값을 가져옵니다.

	TArray<FOverlapResult> OverlapResults;
	// 오버랩의 결과를 담을 변수

	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	FCollisionObjectQueryParams ObjectQueryParam(FCollisionObjectQueryParams::InitType::AllObjects);
	bool bResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		NewLocation,
		FQuat::Identity,
		ObjectQueryParam,
		FCollisionShape::MakeSphere(775.0f),
		CollisionQueryParam
	);
	// 게이트로부터 원형 775.0 범위내에 있는지 검사합니다.
	
	if (!bResult) {
		auto NewSection = GetWorld()->SpawnActor<AABSection>(NewLocation, FRotator::ZeroRotator);
		// 범위내부에 있다면 새로운 액터 AABSectiond르 스폰합니다.(새로운방)
	}
	else {
		ABLOG(Warning, TEXT("New Section area is not empty"));
	}
}

void AABSection::OnNPCSpawn()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle);
	// 작동하고 있는 타이머를 해체합니다, 그리고 SpawnNPCTimerHandle 다시 넣습니다
	auto KeyNPC = GetWorld()->SpawnActor<AABCharacter>(GetActorLocation() + FVector::UpVector*88.0f, FRotator::ZeroRotator);
	// 현재 액터(gate)가 바라보는 방향에서 88거리에 NPC를 소환합니다(중앙)
	if (nullptr != KeyNPC) {
		KeyNPC->OnDestroyed.AddDynamic(this, &AABSection::OnKeyNPCDestroyed);
		// 키 NPC가 desroy될때 실행할 OnKeyNpcDestoryed함수를 넣습니다.
	}
}

void AABSection::OnKeyNPCDestroyed(AActor * DestroyedActor)
{
	auto ABCharacter = Cast<AABCharacter>(DestroyedActor);
	ABCHECK(nullptr != ABCharacter);
	// 캐릭터를 불러옵니다

	auto ABPlayerController = Cast<AABPlayerController>(ABCharacter->LastHitBy);
	ABCHECK(nullptr != ABPlayerController);
	// 플레이어 컨트롤을 불러옵닏

	auto ABGameMode = Cast<AABGameMode>(GetWorld()->GetAuthGameMode());
	// 게임 모드를 월드에서 불러옵니다
	ABCHECK(nullptr != ABGameMode);
	// 게임모드가 정상적으로 불러와졌느지 체크합니다
	ABGameMode->AddScore(ABPlayerController);
	// 게임모드에 ADdscore을 실행시킵니다.

	SetState(ESectionState::COMPLETE);
	// 세션의 모드를 COMPLETE로 바꿉니다.
}


