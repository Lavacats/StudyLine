// Fill out your copyright notice in the Description page of Project Settings.


#include "ABItemBox.h"
#include "ABWeapon.h"
#include "ABCharacter.h"

// Sets default values
AABItemBox::AABItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	// �ڽ��� �浹�� ����� Trigger
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	// �ڽ��� ������� ����ϴ� Box
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	// ����Ʈ�� ����ϴ� EFECT�� �����մϴ�.


	RootComponent = Trigger;
	// Trigger�� ��Ʈ ������Ʈ�� �Ӵϴ�.
	Box->SetupAttachment(RootComponent);
	// Box�� ��Ʈ ������Ʈ�� �ڽ����� ���ϴ�.
	Effect->SetupAttachment(RootComponent);
	// EFECT���� ��Ʈ ������Ʈ�� �ڽ����� �Ӵϴ�.

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	// Trigger�� �ڽ�ũ�� (40,42,30)�� �ڽ��� ������ �Ӵϴ�.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if(SM_BOX.Succeeded()) {
		Box->SetStaticMesh(SM_BOX.Object);
		// Box�� ���������Ÿƽ�޽��� ����ϴ�.
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (P_CHESTOPEN.Succeeded()) {
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
		//EFfect�� �ҷ��� ��ƼŬ �ý����� �����
		// autoACtive�ڵ��ߵ��� �����ϴ�.
	}



	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	// Box�� ��ġ�� �����մϴ�.

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	// Trigger�� Collsion �̸��� ItemBox�� �д�
	Box->SetCollisionProfileName(TEXT("NoCollision"));
	// Box�� ����� ����ϹǷ� NoCollision �浹�� ������� �ʴ´�.

	WeaponItemClass = AABWeapon::StaticClass();
	// Weapon�� ������ ���� �������� Ŭ������ Weapon Ŭ������ �ֽ��ϴ�.
}

// Called when the game starts or when spawned
void AABItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBox::OnCharacterOverlap);
	// ������Ʈ�� ��������(Overlap) OnCharacterOverlap �Լ��� ����ǵ��� AddDynamic�� ����մϴ�.
	// Overlap�Լ��� �浹�� ���� �ѹ��� ����˴ϴ�.
}

// Called every frame
void AABItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABItemBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ABLOG_S(Warning);

	auto ABCharacter = Cast<AABCharacter>(OtherActor);
	// ABCharacter Ŭ������ ���ͷ� ���� �����ɴϴ�.
	ABCHECK(nullptr != ABCharacter);
	// ABCharacet�� �ִ���Ȯ���Ѵ�.

	if (nullptr != ABCharacter && nullptr != WeaponItemClass) {
		// ĳ���Ϳ� ���� ũ���� ��� �ִٸ�
		if (ABCharacter->CanSetWeapon()) {
			// ABCharacter�� CanSetWeapon�� ����Ѵ�.
			auto NewWeapon = GetWorld()->SpawnActor<AABWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			// NewWeapon�� World�� Spawn �Ѵ�.
			ABCharacter->SetWeapon(NewWeapon);
			// ABCharacter�� NewWeapon�� �����Ѵ�.
			Effect->Activate(true);
			// ����Ʈ�� �ߵ��մϴ�.
			Box->SetHiddenInGame(true, true);
			// �ڽ��� �����Ϳ����� ����������, ȭ�鿡���� ��������� �մϴ�.
			SetActorEnableCollision(false);
			// �ڽ� ������ �浹�� ���ϴ�false
			Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
			// ����Ʈ�� ���� ��  OnEffectFinished �Լ��� �ǝ�ǵ��� AddDynamic���� �߰��մϴ�.
		}
		else
		{
			ABLOG(Warning, TEXT("%s can't equip waepon currently."), *ABCharacter->GetName());
			// �����Ҽ����� ��� ���޼����� ����.
		}
	}
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent * PSystem)
{
	Destroy();
	// ����Ʈ�� ������ ���͸� �ı��մϴ�.
}

