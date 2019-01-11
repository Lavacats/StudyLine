// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacterStatComponent.h"
#include "ABGameInstance.h"


// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
	// InitializeComponent 호출을 위해서는 bWantsInitializeComponent를 true로 주어야 한다.

	Level = 1;
	// 시작 레벨을 1로 줍니다.
}

// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UABCharacterStatComponent::InitializeComponent()
// InitializeComponent은 액터의 postInitializeComponents와 같다
// 이 함수는 액터의 postInitializeComponents 함수가 호출되기 바로 전에 호출된다.
{
	Super::InitializeComponent();
	SetNewLevel(Level);
	// 입력된 Level의 값으로 레벨을 세팅합니다.
}

// Called every frame
void UABCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UABCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto ABGameInstance = Cast<UABGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// 월드에서 GameInstance를 가져옵니다.

	ABCHECK(nullptr != ABGameInstance);
	// GameInstance르 정상적으로 가져왔는지 확인합니다.

	CurrentStatData = ABGameInstance->GetABCharacterData(NewLevel);
	// CurrentStatData에 GameInstance의 ABChracterData를 가져와 넣습ㄴ다.
	if (nullptr != CurrentStatData) {
		// CurrentStatData가 성공적으로 데이터를 읽은 경우
		Level = NewLevel;
		//Level은 NewLevel로 바뀌며
		SetHP(CurrentStatData->MaxHP);
		//CurrentHP = CurrentStatData->MaxHP;
		// 현재 체력은 데이터상의 최대체력으로 바뀝니다.
	}
	else {
		ABLOG(Error, TEXT("Levle(%d) data doesn't exist"), NewLevel);
		// CurrentStatData가 데이터를 읽지못한 경우
	}
}

void UABCharacterStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStatData);
	// CurrentStatData가 있는지 확인한다.
	//CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP);
	// CurrentHP-NewDamage는 0부터 CurrentStatData 사이의 값으 가진다.

	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
	// SetHP함수에 현재 체력값을 계산하여 넘겨줍니다.

	//if (CurrentHP <= 0.0f) {
	//	OnHPIsZero.Broadcast();
	//	// CurrentHP가 0볻 작아지면, OnHPIsZero 델리게이트를 실행한다
	//	// Broadcast는 등록된 모든 함수를 실행한다는 뜻
	//}
}

void UABCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	// 현재 체력을 계산받은 값으로 둡니다.
	OnHPChanged.Broadcast();
	// 체력 변화 (프로그래스바쪽) 함수를 실행합니다.
	if (CurrentHP < KINDA_SMALL_NUMBER) {
		// KINDA_SMALL_NUMBER은 미세한 오차를 막기위해 언리얼에서 제공하는 매크로입니다. 0
		CurrentHP = 0.0f;
		// 현채 체력이 0보다 작아지면 체력을 0으로둡니다
		OnHPIsZero.Broadcast();
		// 체력이 0이되면 발생되는 함수를 실행합니다.
	}
}

float UABCharacterStatComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);
	// CurrentStatData의 값이 비어있는지 확인합니다.

	return CurrentStatData->Attack;
	// CurrentStatData의 Attack값을 전달합니다.
}

float UABCharacterStatComponent::GetHPRatio()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
	// CurrentStatData->MaxHP  가 0보다 작다면 0을 반환
	// 0보다 크다면 현재체력과 최대체력의 비율을 반환합니다.
}

int32 UABCharacterStatComponent::GetDropExp() const
{
	return CurrentStatData->DropExp;
	// 캐릭터 정보의 드랍 EXP만큼 값을 반환한다.
}

