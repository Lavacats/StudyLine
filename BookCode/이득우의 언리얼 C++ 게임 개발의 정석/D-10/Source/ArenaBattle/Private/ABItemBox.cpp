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
	// 박스의 충돌을 담당할 Trigger
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));
	// 박스의 비쥬어을 담당하는 Box
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	// 이펙트를 담당하는 EFECT를 생성합니다.


	RootComponent = Trigger;
	// Trigger를 루트 컴포넌트로 둡니다.
	Box->SetupAttachment(RootComponent);
	// Box는 루트 컴포넌트의 자식으로 들어갑니다.
	Effect->SetupAttachment(RootComponent);
	// EFECT역시 루트 컴포넌트의 자식으로 둡니다.

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	// Trigger에 박스크기 (40,42,30)의 박스를 가져다 둡니다.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/InfinityBladeGrassLands/Environments/Breakables/StaticMesh/Box/SM_Env_Breakables_Box1.SM_Env_Breakables_Box1"));
	if(SM_BOX.Succeeded()) {
		Box->SetStaticMesh(SM_BOX.Object);
		// Box에 비쥬얼을스타틱메쉬를 씌웁니다.
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Treasure/Chest/P_TreasureChest_Open_Mesh.P_TreasureChest_Open_Mesh"));
	if (P_CHESTOPEN.Succeeded()) {
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
		//EFfect에 불러온 파티클 시스템을 씌우고
		// autoACtive자동발동을 막습니다.
	}



	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
	// Box의 위치를 조정합니다.

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	// Trigger의 Collsion 이름을 ItemBox로 둔다
	Box->SetCollisionProfileName(TEXT("NoCollision"));
	// Box는 비쥬얼만 담당하므로 NoCollision 충돌을 사용하지 않는다.

	WeaponItemClass = AABWeapon::StaticClass();
	// Weapon의 정보를 담을 아이템의 클래스에 Weapon 클래스를 넣습니다.
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
	// 컴포넌트가 겹쳐질떄(Overlap) OnCharacterOverlap 함수가 실행되도록 AddDynamic을 사용합니다.
	// Overlap함수는 충돌한 순간 한번만 실행됩니다.
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
	// ABCharacter 클래스를 액터로 부터 가져옵니다.
	ABCHECK(nullptr != ABCharacter);
	// ABCharacet가 있느지확인한다.

	if (nullptr != ABCharacter && nullptr != WeaponItemClass) {
		// 캐릭터와 무기 크래스 모두 있다면
		if (ABCharacter->CanSetWeapon()) {
			// ABCharacter의 CanSetWeapon을 사용한다.
			auto NewWeapon = GetWorld()->SpawnActor<AABWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			// NewWeapon을 World에 Spawn 한다.
			ABCharacter->SetWeapon(NewWeapon);
			// ABCharacter에 NewWeapon을 세팅한다.
			Effect->Activate(true);
			// 이펙트를 발동합니다.
			Box->SetHiddenInGame(true, true);
			// 박스가 에디터에서는 남아있으나, 화면에서는 사라지도록 합니다.
			SetActorEnableCollision(false);
			// 박스 액터의 충돌을 끕니다false
			Effect->OnSystemFinished.AddDynamic(this, &AABItemBox::OnEffectFinished);
			// 이펙트가 끝날 때  OnEffectFinished 함수가 실앻되도록 AddDynamic으로 추가합니다.
		}
		else
		{
			ABLOG(Warning, TEXT("%s can't equip waepon currently."), *ABCharacter->GetName());
			// 세팅할수없을 경우 경고메세지를 띄운다.
		}
	}
}

void AABItemBox::OnEffectFinished(UParticleSystemComponent * PSystem)
{
	Destroy();
	// 이펙트가 끝나면 액터를 파괴합니다.
}

