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
	// Mesh�� ����ƽ ������Ʈ MESH�� �����Ϳ��� Ȯ���Ҽ��ֵ����Ѵ�
	RootComponent = Mesh;
	// Mesh�� ��Ʈ������Ʈ�� ��´�

	FString AssetPath = TEXT("/Game/Book/StaticMesh/SM_SQUARE.SM_SQUARE");
	// ����� �޽��� ��θ� �Է��մϴ�
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SQUARE(*AssetPath);
	// SM_SQUARE��� �̸����� ������ �ҷ��ɴϴ�.
	if (SM_SQUARE.Succeeded()) {
		Mesh->SetStaticMesh(SM_SQUARE.Object);
		// �ҷ����µ� �����ߴٸ� ����ƽ�޽ÿ� �̹����� ����ϴ�
	}
	else {
		ABLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *AssetPath);
	}

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	// Trigger�� �����Ϳ� Trigger�� ǥ���Ѵ�.
	Trigger->SetBoxExtent(FVector(775.0f, 775.0f, 300.0f));
	// Trigger�� ����� �ڽ��� ũ��
	Trigger->SetupAttachment(RootComponent);
	// Trigger�� Root�Ʒ��� �ֽ��ϴ�.
	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	// Trigger�� ��ġ�� ���մϴ�.
	Trigger->SetCollisionProfileName(TEXT("ABTrigger"));
	// Trigger �� ����� �浹�� ABTrigger�Դϴ�.

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABSection::OnTriggerBeginOverlap);
	// Trigger�� ������(��ħ)�Ǵ� ���� OnTriggerBegin�̺�Ʈ�� �����Ѵ�.

	FString GateAssetPath = TEXT("/Game/Book/StaticMesh/SM_GATE.SM_GATE");
	// Gate�� ���۷��� ������ �Է��մϴ�.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_GATE(*GateAssetPath);
	// SM_GATE ������ �Է��� ���۷����� ���� ����ƽ �޽��� �ҷ��ɴϴ�.

	if (!SM_GATE.Succeeded()) {
		ABLOG(Error, TEXT("Failed to load staticmesh asset. : %s"), *GateAssetPath);
		// �ҷ����µ� �����ߴٸ� �α׸� ����մϴ�.
	}

	static FName GateSockets[] = { { TEXT("+XGate")},{TEXT("-XGate")},{TEXT("+YGate")},{TEXT("-YGate") } };
	// GateSockets �� ���� 4�� ���� �̸��� �з��մϴ�

	for (FName GateSocket : GateSockets) {
		// ���� ������ŭ for���� �����ϴ٤�.
		ABCHECK(Mesh->DoesSocketExist(GateSocket));
		// �޽��� ����� �ִ��� üũ�մϴ�.
		UStaticMeshComponent* NewGate = CreateDefaultSubobject<UStaticMeshComponent>(*GateSocket.ToString());
		// ����ƽ �޽� ������Ʈ�� �ҷ��ɴϴ�.
		NewGate->SetStaticMesh(SM_GATE.Object);
		// NewGate�� �޽ø� �ֽ��ϴ�.
		NewGate->SetupAttachment(RootComponent, GateSocket);
		// New ����Ʈ�� RootComponent�� �ڽ����� �ֽ��ϴ�.
		NewGate->SetRelativeLocation(FVector(0.0f, -80.5f, 0.0f));
		// ����Ʈ�� ��ġ�� ����ϴ�.(����Ʈ�� ���� GateSockets�� �̸����� SM_SQUARE���� �˻��Ͽ�
		// �̸� ������ ������ ��ġ���� 80.5�� ���� ���� ��ġ�� ���մϴ�.
		GateMeshes.Add(NewGate);
		// NewCate�� ���մϴ�

		UBoxComponent* NewGateTrigger = CreateDefaultSubobject<UBoxComponent>(*GateSocket.ToString().Append(TEXT("Trigger")));
		// ����Ʈ Trigger�� �����Ϳ��� Ȯ���� �� �ֵ��� �߰��մϴ�.
		NewGateTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 300.0f));
		// ����Ʈ Ʈ������ ũ��
		NewGateTrigger->SetupAttachment(RootComponent, GateSocket);
		// ����Ʈ Ʈ���ſ� ����Ʈ ��Ĺ�� ��Ʈ�����ʴ��� �ڽ����� ���ϴ�.
		NewGateTrigger->SetRelativeLocation(FVector(70.0f, 0.0f, 250.0f));
		// ����Ʈ Ʈ��Ŀ�� ��ġ
		NewGateTrigger->SetCollisionProfileName(TEXT("ABTrigger"));
		// ����Ʈ Ʈ���Ű� ����� �浹
		GateTriggers.Add(NewGateTrigger);

		NewGateTrigger->OnComponentBeginOverlap.AddDynamic(this, &AABSection::OnGateTriggerBeginOverlap);
		// NeGateTrigger�� Ovelap�Ǵ� ���� OnGateTriggerBeginOverlap �Լ��� ����
		NewGateTrigger->ComponentTags.Add(GateSocket);
	}

	bNoBattle = false;
	// �ʱ� NoBattle�� ���� false�� �ش�.(NPC�� �������� �ʽ��ϴ�)

	EnemySpawnTime = 2.0f;
	// ���� ù �����ð� 2��
	ItemBoxSpawnTime = 5.0f;
	// ������ �ڽ��� �����ð� 5��
}

void AABSection::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
	// �����Ϳ��� ���� �ٲ𶧸��� ����ɼ��ֵ����Ѵ�
}

// Called when the game starts or when spawned
void AABSection::BeginPlay()
{
	Super::BeginPlay();
	SetState(bNoBattle ? ESectionState::COMPLETE : ESectionState::READY);
	// ���� ���¸� READY�� �д�
}

void AABSection::SetState(ESectionState NewState)
{
	switch(NewState)
		// NewState�� ���¿� ���� ������ �����ȴ�.
	{
		case ESectionState::READY:
			// READY ������ ��
		{
			Trigger->SetCollisionProfileName(TEXT("ABTrigger"));
			// Trigger�� ABTrigger�� ����Ѵ�.(trigger�� �÷��̾ �濡�ִ��� �˻��ϴ� trigger�̴�)
			for (UBoxComponent* GateTrigger : GateTriggers) {
				GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
				// GateTrigger�� NoCollision �浹�� ������� �ʴ´�.(GateTrigger�� �÷��̾��� ���� �������� ���⿩��)
			}

			OperateGates(true);
			// ���� �����ϴ� �Լ��� true�� �ش�
			break;
		}
		case ESectionState::BATTLE:
		{
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			// trigger�� NoCollision�� ���� ������
			for (UBoxComponent* GateTrigger : GateTriggers) {
				GateTrigger->SetCollisionProfileName(TEXT("NoCollision"));
				// GateTrigger�� �浹�� ���� �ʴ´�
			}

			OperateGates(false);
			// ���� �����ϴ� �Լ��� false�� �ش�

			GetWorld()->GetTimerManager().SetTimer(
				SpawnNPCTimerHandle, FTimerDelegate::CreateUObject(this, &AABSection::OnNPCSpawn), 
				EnemySpawnTime, false);
			// ���忡 Ÿ�̸� ������ �ؼ� ���� �ð����� ���� ��ȯ�Ǵ� �Լ��� �����ϵ��� �մϴ�.

			GetWorld()->GetTimerManager().SetTimer(SpawnItemBoxTimerHandle, FTimerDelegate::CreateLambda([this]()->void {

				FVector2D RandXY = FMath::RandPointInCircle(600.0f);
				GetWorld()->SpawnActor<AABItemBox>(GetActorLocation() + FVector(RandXY, 30.0f), FRotator::ZeroRotator);
			}), ItemBoxSpawnTime, false);
			// ���忡 Ÿ�̸ӿ��� ������ �Ͽ�
			// ������ 600���� ������ XY��ǥ�� Itembox�� �����Ѵ�

			break;
		}
		case ESectionState::COMPLETE:
		{
			Trigger->SetCollisionProfileName(TEXT("NoCollision"));
			// Tirgger�� �浹�˻縦 �����ʴ´�.
			for (UBoxComponent* GateTrigger : GateTriggers) {
				GateTrigger->SetCollisionProfileName(TEXT("ABTrigger"));
				// GateTrigger�� ABTigger�˻縦�Ѵ�.
			}

			OperateGates(true);
			// ���� �����ϴ� �Լ��� true�� �ش�.
			break;
		}
	}
	CurrentState = NewState;
	// NewState �� ���� CurrentState�� ���� ������.
}

void AABSection::OperateGates(bool bOpen)
{
	for (UStaticMeshComponent* Gate : GateMeshes) {
		Gate->SetRelativeRotation(bOpen ? FRotator(0.0f, -90.0f, 0.0f) : FRotator::ZeroRotator);
		// Gate�� ��ο��� for���� ���� -90��ŭ ȸ����Ų��.
	}
}

void AABSection::OnTriggerBeginOverlap(UPrimitiveComponent * OverlappedCmponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (CurrentState == ESectionState::READY) {
		SetState(ESectionState::BATTLE);
		// ���� ���°� READY��� ���� �󤼸� Battle�� �ٲߴϴ�.
	}
}

void AABSection::OnGateTriggerBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool BFromSweep, const FHitResult & SweepResult)
{
	ABCHECK(OverlappedComponent->ComponentTags.Num() == 1);
	// ComponentTags�� Num()���� 1���� Ȯ���մϴ�.

	FName ComponentTag = OverlappedComponent->ComponentTags[0];
	// ������Ʈ �±׿� �浹�� ĳ���� �±׸� �Է��մϴ�.

	FName SocketName = FName(*ComponentTag.ToString().Left(2));
	// ��Ĺ �̸��� �浹�� ĳ���Ϳ��� �����ɴϴ�.

	if (!Mesh->DoesSocketExist(SocketName))
		return;
	// ��Ĺ�� ���ٸ� �Լ��� �����մϴ�.

	FVector NewLocation = Mesh->GetSocketLocation(SocketName);
	// NewLocation ���� �޽��� ��ġ���� �����ɴϴ�.

	TArray<FOverlapResult> OverlapResults;
	// �������� ����� ���� ����

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
	// ����Ʈ�κ��� ���� 775.0 �������� �ִ��� �˻��մϴ�.
	
	if (!bResult) {
		auto NewSection = GetWorld()->SpawnActor<AABSection>(NewLocation, FRotator::ZeroRotator);
		// �������ο� �ִٸ� ���ο� ���� AABSectiond�� �����մϴ�.(���ο��)
	}
	else {
		ABLOG(Warning, TEXT("New Section area is not empty"));
	}
}

void AABSection::OnNPCSpawn()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnNPCTimerHandle);
	// �۵��ϰ� �ִ� Ÿ�̸Ӹ� ��ü�մϴ�, �׸��� SpawnNPCTimerHandle �ٽ� �ֽ��ϴ�
	auto KeyNPC = GetWorld()->SpawnActor<AABCharacter>(GetActorLocation() + FVector::UpVector*88.0f, FRotator::ZeroRotator);
	// ���� ����(gate)�� �ٶ󺸴� ���⿡�� 88�Ÿ��� NPC�� ��ȯ�մϴ�(�߾�)
	if (nullptr != KeyNPC) {
		KeyNPC->OnDestroyed.AddDynamic(this, &AABSection::OnKeyNPCDestroyed);
		// Ű NPC�� desroy�ɶ� ������ OnKeyNpcDestoryed�Լ��� �ֽ��ϴ�.
	}
}

void AABSection::OnKeyNPCDestroyed(AActor * DestroyedActor)
{
	auto ABCharacter = Cast<AABCharacter>(DestroyedActor);
	ABCHECK(nullptr != ABCharacter);
	// ĳ���͸� �ҷ��ɴϴ�

	auto ABPlayerController = Cast<AABPlayerController>(ABCharacter->LastHitBy);
	ABCHECK(nullptr != ABPlayerController);
	// �÷��̾� ��Ʈ���� �ҷ��Ɉ�

	auto ABGameMode = Cast<AABGameMode>(GetWorld()->GetAuthGameMode());
	// ���� ��带 ���忡�� �ҷ��ɴϴ�
	ABCHECK(nullptr != ABGameMode);
	// ���Ӹ�尡 ���������� �ҷ��������� üũ�մϴ�
	ABGameMode->AddScore(ABPlayerController);
	// ���Ӹ�忡 ADdscore�� �����ŵ�ϴ�.

	SetState(ESectionState::COMPLETE);
	// ������ ��带 COMPLETE�� �ٲߴϴ�.
}


