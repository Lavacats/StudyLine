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
	// InitializeComponent ȣ���� ���ؼ��� bWantsInitializeComponent�� true�� �־�� �Ѵ�.

	Level = 1;
	// ���� ������ 1�� �ݴϴ�.
}

// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UABCharacterStatComponent::InitializeComponent()
// InitializeComponent�� ������ postInitializeComponents�� ����
// �� �Լ��� ������ postInitializeComponents �Լ��� ȣ��Ǳ� �ٷ� ���� ȣ��ȴ�.
{
	Super::InitializeComponent();
	SetNewLevel(Level);
	// �Էµ� Level�� ������ ������ �����մϴ�.
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
	// ���忡�� GameInstance�� �����ɴϴ�.

	ABCHECK(nullptr != ABGameInstance);
	// GameInstance�� ���������� �����Դ��� Ȯ���մϴ�.

	CurrentStatData = ABGameInstance->GetABCharacterData(NewLevel);
	// CurrentStatData�� GameInstance�� ABChracterData�� ������ �ֽ�����.
	if (nullptr != CurrentStatData) {
		// CurrentStatData�� ���������� �����͸� ���� ���
		Level = NewLevel;
		//Level�� NewLevel�� �ٲ��
		SetHP(CurrentStatData->MaxHP);
		//CurrentHP = CurrentStatData->MaxHP;
		// ���� ü���� �����ͻ��� �ִ�ü������ �ٲ�ϴ�.
	}
	else {
		ABLOG(Error, TEXT("Levle(%d) data doesn't exist"), NewLevel);
		// CurrentStatData�� �����͸� �������� ���
	}
}

void UABCharacterStatComponent::SetDamage(float NewDamage)
{
	ABCHECK(nullptr != CurrentStatData);
	// CurrentStatData�� �ִ��� Ȯ���Ѵ�.
	//CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP);
	// CurrentHP-NewDamage�� 0���� CurrentStatData ������ ���� ������.

	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->MaxHP));
	// SetHP�Լ��� ���� ü�°��� ����Ͽ� �Ѱ��ݴϴ�.

	//if (CurrentHP <= 0.0f) {
	//	OnHPIsZero.Broadcast();
	//	// CurrentHP�� 0�� �۾�����, OnHPIsZero ��������Ʈ�� �����Ѵ�
	//	// Broadcast�� ��ϵ� ��� �Լ��� �����Ѵٴ� ��
	//}
}

void UABCharacterStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	// ���� ü���� ������ ������ �Ӵϴ�.
	OnHPChanged.Broadcast();
	// ü�� ��ȭ (���α׷�������) �Լ��� �����մϴ�.
	if (CurrentHP < KINDA_SMALL_NUMBER) {
		// KINDA_SMALL_NUMBER�� �̼��� ������ �������� �𸮾󿡼� �����ϴ� ��ũ���Դϴ�. 0
		CurrentHP = 0.0f;
		// ��ä ü���� 0���� �۾����� ü���� 0���εӴϴ�
		OnHPIsZero.Broadcast();
		// ü���� 0�̵Ǹ� �߻��Ǵ� �Լ��� �����մϴ�.
	}
}

float UABCharacterStatComponent::GetAttack()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);
	// CurrentStatData�� ���� ����ִ��� Ȯ���մϴ�.

	return CurrentStatData->Attack;
	// CurrentStatData�� Attack���� �����մϴ�.
}

float UABCharacterStatComponent::GetHPRatio()
{
	ABCHECK(nullptr != CurrentStatData, 0.0f);

	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0f : (CurrentHP / CurrentStatData->MaxHP);
	// CurrentStatData->MaxHP  �� 0���� �۴ٸ� 0�� ��ȯ
	// 0���� ũ�ٸ� ����ü�°� �ִ�ü���� ������ ��ȯ�մϴ�.
}

int32 UABCharacterStatComponent::GetDropExp() const
{
	return CurrentStatData->DropExp;
	// ĳ���� ������ ��� EXP��ŭ ���� ��ȯ�Ѵ�.
}

