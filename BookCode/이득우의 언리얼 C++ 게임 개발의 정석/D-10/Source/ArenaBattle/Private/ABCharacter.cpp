// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacter.h"
#include "ABAnimInstance.h"
#include "ABWeapon.h"
#include "ABCharacterStatComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "ABCharacterWidget.h"
#include "ABAIController.h"
#include "ABCharacterSetting.h"
#include "ABGameInstance.h"
#include "ABPlayerController.h"
#include "ABPlayerState.h"
#include "ABHUDWidget.h"


// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	// ������ ������Ʈ ���� ���Ӱ� ����ϴ�.

	SpringArm->SetupAttachment(GetCapsuleComponent());
	// SpringArm�� Capsule�� �ڽ����� �ֽ��ϴ�.
	Camera->SetupAttachment(SpringArm);
	// Camera�� SpringArm�� �ڽ����� �ֽ��ϴ�.

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f),FRotator(0.0f,-90.0f,0.0f));
	// Mesh�� �ʱ� ��ġ�� ȸ������ �����մϴ�.
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	// SpringArm�� ���̿� ȸ������ �����մϴ�.

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOAD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOAD.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_CARDBOAD.Object);
		// ����� SkeletaMesh ��������� �ҷ�����, �ҷ����µ� �����ߴٸ�, Mesh�� �����մϴ�.
	}
	
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	// Mesh�� AnimationBlueprint(�������Ʈ�� ����ϴ� �ִϸ��̼� ����)�� �����մϴ�.
	static ConstructorHelpers::FClassFinder<UAnimInstance>WARRIOR_ANIM(TEXT("/Game/Book/Animation/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
		// ����� UAnimInstance ��������� �ҷ�����, �ҷ����µ� �����ߴٸ�, Mesh�� �����մϴ�.
	}
	
	SetControlMode(EControlMode::DIABLO);
	// ��Ʈ�� ����� �ʱⰪ���� DIABLO�� �ݴϴ�.

	ArmLengthSpeed = 3.0f;
	// ���� �ٲٴ� �ӵ� 3
	ArmRotationSpeed = 10.0f;
	// ���� ȸ����Ű�� �ӵ� 10

	GetCharacterMovement()->JumpZVelocity = 800.0f;
	// CharacterMovement�� ���� ���� 800���� �ٲپ��ݴϴ�.
	
	IsAttacking = false;
	// IsAttacking�� ���� false�� �ش�
	MaxCombo = 4;
	AttackEndComboState();
	// �ִ� �޺��� 4�̸�
	// ������ ���� �޺��� 0���� �ʱ�ȭ �ϱ����� AttackEndComboState�� ����Ѵ�.

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCharacter"));
	// ABChatacer�� ĸ��������Ʈ �ʱⰪ�� ABCHaracter������ �Ӵϴ�.

	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	//FName WeaponSocket(TEXT("hand_rSocket"));
	//// ���� hand_rSocket�� ã���ϴ�
	//if (GetMesh()->DoesSocketExist(WeaponSocket)) {
	//	// WeaponSocket�� Mesh�� �ִٸ�
	//	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	//	// Waepon�� SkeletalMeshComponent�� WEAPON�̶�� �̸����� �����˴ϴ�.
	//	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));
	//	// ���۷����� ���� ���⸦ ��������
	//	if (SK_WEAPON.Succeeded()) {
	//		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	//		// ���⸦ ���������� �ҷ��Դٸ� SkeletalMesh�� weaopon�� �����մϴ�.
	//	}
	//	Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	//	// Weapon�� WaeponSocket�� �ֽ��ϴ�.
	//}

	CharacterStat = CreateDefaultSubobject<UABCharacterStatComponent>(TEXT("CHARCTERSTAT"));
	// �����Ϳ� CHARACTERSTAT��� ĳ���� ���� ������Ʈ�� �߰��մϴ�.

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	// �����Ϳ� HPBARWIDGET ���� ���� ������Ʈ�� �߰��մϴ�.

	HPBarWidget->SetupAttachment(GetMesh());
	// HPBarWidget�� GetMesh()�� �ڽ����� ���ϴ�.

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	// HPBarWidget�� ��ġ�� (0,0,180)�̸�
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	// �׻� ȭ���� �ٶ󺸵��� ȸ���մϴ�.
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Book/UI/UI_HPBar.UI_HPBar_C"));
	// �������Ʈ �迭 ������ C++�� �θ� ���� C�� �ٿ����Ѵ�.
		if (UI_HUD.Succeeded()) {
			// UI_HUD�� �ҷ����µ� �����ϸ�
			HPBarWidget->SetWidgetClass(UI_HUD.Class);
			// HPBarWidget�� UI_HUD�� �ְ�
			HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
			// ũ�⸣ 150,50���� �����մϴ�.
	}

	AIControllerClass = AABAIController::StaticClass();
	// AIControllerClas�� �Ӽ��� StaticClass�� ��´�
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// �ڵ������� ��������� AI �ɼ��� PlacedInWorldOrSpawned�� �Ѵ�.
	// ����(��)�� ��ġ�ǰų� ���Ӱ� �����Ǵ� ABCharacter���� ABAIController�� �����ȴ�
	// �÷��̾ �����ϴ� ĳ���� ������ ĳ���͵��� ��� ABAIController�� ���踦 �޴´�.

	auto DefaultSetting = GetDefault<UABCharacterSetting>();
	if (DefaultSetting->CharacterAssets.Num() > 0) {
		for (auto CharacterAsset : DefaultSetting->CharacterAssets) {
			ABLOG(Warning,TEXT("Chracter Asset : %s"),*CharacterAsset.ToString())
		}
	}

	AssetIndex = 4;
	// �÷��̾ ĳ���͸� �����ϴ� ��쿡�� �ӽ÷� 4�� INDEX�� ĳ���� ������ ����Ѵ�
	SetActorHiddenInGame(true);
	// ���͸� �ΰ��ӿ��� ������ �ʵ����Ѵ�.
	HPBarWidget->SetHiddenInGame(true);
	// HPBar�� �ΰ��ӿ��� ������ �ʵ����Ѵ�
	bCanBeDamaged = false;
	// ������ �Ұ��� false�� �ش�.

	DeadTimer = 5.0f;
	// ������ �� �ð��� 5�ʷ� �ش�
}

void AABCharacter::SetChracterState(ECharacterState NewState)
{
	ABCHECK(CurrentState != NewState);
	CurrentState = NewState;
	// ���� ĳ���� ���¸� NewState���·� �Ӵϴ�.

	switch (CurrentState) {
		// ���� ���¿� ���� ����ġ���Դϴ�.
		case ECharacterState::LOADING:
			// LOADING ���´� ���� ĳ���͸� �д� ���� �����Դϴ�.
		{
			if (bIsPlayer) {
				DisableInput(ABPlayerController);
				// �÷��̾� ��Ʈ�ѷ��� �ִٸ� Input�� �Ҽ� ������ �Ӵϴ�.

				ABPlayerController->GetHUDWidget()->BindCharacterStat(CharacterStat);
				// �÷��̾� ��Ʈ�ѷ��� ������ ĳ���� ������ �����մϴ�.

				auto ABPlayerState = Cast<AABPlayerState>(PlayerState);
				// AABPlayerSTate���� PalyerState�� ���� �����ɴϴ�.
				ABCHECK(nullptr != ABPlayerState);
				// ABPlayerState�� ���ٸ� �����α׸� ����մϴ�.
				CharacterStat->SetNewLevel(ABPlayerState->GetCharacterLevel());
				// ĳ���� ������ ���� ĳ������ ���� ���� ������ ���� ����ϴ�
			}
			SetActorHiddenInGame(true);
			HPBarWidget->SetHiddenInGame(true);
			bCanBeDamaged = false;
			break;
			// LOADING ������ ���
			// ���͸� �ΰ��ӿ��� ����ϴ�
			// HP�ٸ� ����ϴ�
			// ������ �Ұ��� 0���� �ݴϴ�
		}
		case ECharacterState::READY:
			// READY ���´� �ε��� ��ģ ĳ���Ͱ� ���� ���ӿ� �ִ� �����Դϴ�
		{
			SetActorHiddenInGame(false);
			HPBarWidget->SetHiddenInGame(false);
			bCanBeDamaged = true;
			// READY������ ���
			// ĳ���͸� �ΰ��ӿ��� �����݈�
			// HP Bar�� �ΰ��ӿ��� �����ݴϴ�
			// ������ �Ұ��� ���� �ݴϴ�.

			CharacterStat->OnHPIsZero.AddLambda([this]()->void {
				SetChracterState(ECharacterState::DEAD);
			});
			// ĳ���� ������ OnHPIsZero�� �Ŵ� ���� ĳ���� �������ͽ��� DEAD�� �ٲܼ��ֵ��� �Լ��� �߰��մϴ�

			auto CharacterWidget = Cast<UABCharacterWidget>(HPBarWidget->GetUserWidgetObject());
			// ĳ���� ����(HP��) �� ã���ϴ�
			ABCHECK(nullptr != CharacterWidget);
			// HP�ٰ� ���ٸ� ���� �α׸� ����մϴ�.
			CharacterWidget->BindCharacterStat(CharacterStat);
			// ĳ���� ������ ĳ���� ������ �����մϴ�.

			if (bIsPlayer) {
				SetControlMode(EControlMode::DIABLO);
				GetCharacterMovement()->MaxWalkSpeed = 600.0f;
				EnableInput(ABPlayerController);
				// �÷��̾� ��Ʈ�ѷ��� �ִٸ�
				// ���Ӹ��� ��ƺ�� ��带 ����ϸ�
				// �ȴ� �ӵ� �ִ밪�� 600
				// Input�� �����ϵ��� �����
			}
			else {
				SetControlMode(EControlMode::NPC);
				GetCharacterMovement()->MaxWalkSpeed = 400.0f;
				ABAIController->RunAI();
				// �÷��̾� ��Ʈ�ѷ��� ���ٸ�
				// ���Ӹ��� NPC�� �ϸ�
				// �ִ� �̵��ӵ��� 400
				// AICONTROLLER �� RUNAI()�� �����մϴ�.
			}
			break;
		}
		case ECharacterState::DEAD:
			// ĳ���Ͱ� ü���� ��� �ٵǾ� DEAD ���·� �� �� �Դϴ�.
		{
			SetActorEnableCollision(false);
			GetMesh()->SetHiddenInGame(false);
			HPBarWidget->SetHiddenInGame(true);
			// DEAD ������ ����
			// ĳ������ �浹 ������ ���ϴ�
			// ĳ���ʹ� �ΰ��ӿ��� ���Դϴ�
			//  HP�� �ΰ��ӿ��� ������ �ʽ��ϴ�
			ABAnim->SetDeadAnim();
			// DeadAnimation�� ����մϴ�.
			bCanBeDamaged = false;
			// Damage �Ұ��� false�� �ݴϴ�.

			if (bIsPlayer) {
				DisableInput(ABPlayerController);
				// Dead������ �� �÷��̾� ��Ʈ�ѷ��� �ִٸ� Input�� ����������ϰ� �մϴ�.
			}
			else {
				ABAIController->StopAI();
				// Dead ������ �� AI��� StopAI�Լ��� �����մϴ�.
			}
			
			GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([this]()->void {
				// World���� DeadTimerHandle��ŭ�� �ð��� ����Ǹ� �Ʒ��� �Լ��� �����մϴ�.
				if (bIsPlayer) {
					ABPlayerController->RestartLevel();
					// �÷��̾� ��Ʈ�ѷ��� �ִٸ� levle�� �ٽý����մϴ�(�÷��̾ ����߱⶧��)
				}
				else {
					Destroy();
					// AI�� ����ߴٸ� AI�� ����ϴ�
				}
			}), DeadTimer, false);

			break;
		}
	}
}

ECharacterState AABCharacter::GetChracterState() const
{
	return CurrentState;
	// ���� ĳ���� ���¸� ��ȯ�մϴ�.
}

int32 AABCharacter::GetExp() const
{
	return CharacterStat->GetDropExp();
	
	// ĳ���� ������ �������ġ�� ��ȯ�Ѵ�.
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();

	//FName WeaponSocket(TEXT("hand_rSocket"));
	//// ���� hand_rSocket�� ã���ϴ�
	//auto CurWeapon = GetWorld()->SpawnActor<AABWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);\
	//// AABWapon�� World�� Spanw�ϰ� CurWeapon���� �Ӵϴ�.
	//if (nullptr != CurWeapon) {
	//	CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	//	// CurWaepon�� �����Ǹ� WeaponSocket�� �ڽ����� �ֽ��ϴ�.
	//}

	bIsPlayer = IsPlayerControlled();
	// bIsPlayer : �÷��̾ ��Ʈ���ϴ��� ���� IsPlayerControler Ŭ������ ���翩��
	if (bIsPlayer) {
		ABPlayerController = Cast<AABPlayerController>(GetController());
		// �÷��̾� ��Ʈ�ѷ��� �ִٸ� ABPlayerController�� �޾ƿɴϴ�.
		ABCHECK(nullptr != ABPlayerController);
	}
	else {
		ABAIController = Cast<AABAIController>(GetController());
		// �÷��̾� ��Ʈ�ѷ��� ���ٸ�, AABAIControoler�� �ִٸ� ABAAIController�� �޾ƿɴϴ�.
		ABCHECK(nullptr != ABAIController);
	}

	auto DefaultSetting = GetDefault<UABCharacterSetting>();
	// ĳ���� ���� Ŭ������ ����Ʈ ���� �޾ƿ��� ����Ʈ ������ �����մϴ�

	if (bIsPlayer) {
		AssetIndex = 4;
		// �÷��̾ ��Ʈ���Ұ�� 4���� �ε��� ĳ���� ������ ����մϴ�.
	}
	else {
		AssetIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
		// �÷��̾ ��Ʈ������ ���� ��� ������ �ε����� ĳ���� ������ ����մϴ�.
	}
	CharacterAssetToLoad = DefaultSetting->CharacterAssets[AssetIndex];
	// �ε��� ���� ���� ������ �н��ϴ� (LOAD)
	auto ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	// ���� ������ ���� �ν�ź���� �ҷ��ɴϴ�.
	ABCHECK(nullptr != ABGameInstance);
	// �ν�ź���� ���ٸ� ������ ���ϴ�.
	AssetStreamingHandle = ABGameInstance->StreamableManager.RequestAsyncLoad(
		CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &AABCharacter::OnAssetLoadCompleted));
	// ���� , ABGameInstance�� StreamableManager�� ���� CharacterAssetToLoad ������ ���´�
	// �׸��� ABCharacter�� OnAssetLoadCompleted�� �����Ѵ�.
	// CreateUObject ����� ����� �Ｎ���� ��������Ʈ�� ���������ν� �Լ��� �����Ѵ�.
	SetChracterState(ECharacterState::LOADING);
	// ĳ������ ���°����� LOADING���·� �Ӵϴ�.

	//if (!IsPlayerControlled()) {
	//	// �÷��̾ ��Ʈ������ �ʴ� ĳ���Ͷ�� NPC
	//	auto DefaultSetting = GetDefault<UABCharacterSetting>();
	//	// DefaultSetting�� ĳ���� ���� ������ �����ɴϴ�.
	//	int32 RandIndex = FMath::RandRange(0, DefaultSetting->CharacterAssets.Num() - 1);
	//	// ĳ���� ������ �� �߿��� ������ �� �ϳ��� �����ɴϴ�.
	//	CharacterAssetToLoad = DefaultSetting->CharacterAssets[RandIndex];
	//	// FSoftObjectPath Ŭ���� CharacterAssetToLoad�� ĳ���� ���� ������ �ҷ��ɴϴ�.
	//	auto ABGameInstance = Cast<UABGameInstance>(GetGameInstance());
	//	// ���� �ν��Ͻ��� �о�ɴϴ�.
	//	if (nullptr != ABGameInstance) {
	//		AssetStreamingHandle = ABGameInstance->StreamableManager.RequestAsyncLoad(
	//			CharacterAssetToLoad, FStreamableDelegate::CreateUObject(this, &AABCharacter::OnAssetLoadCompleted));
	//		// ���� , ABGameInstance�� StreamableManager�� ���� CharacterAssetToLoad ������ ���´�
	//		// �׸��� ABCharacter�� OnAssetLoadCompleted�� �����Ѵ�.
	//		// CreateUObject ����� ����� �Ｎ���� ��������Ʈ�� ���������ν� �Լ��� �����Ѵ�.
	//	}
	//}


}

void AABCharacter::SetControlMode(int32 ControlMode)
{
	if (ControlMode == 0) {
		// SpringArm : ī�޶� �����뿡 ���� ����
		SpringArm->TargetArmLength = 450.0f;
		// SpringArm�� Ÿ������ ������ �Ÿ� 450
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		// SpringArm�� �ʱ� ȸ���� Zero
		SpringArm->bUsePawnControlRotation = true;
		// SpringArm�� Pawn������ ȸ�� ��뿩�� true
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		// Roll = X�� , Pitch = Y��, Yaw = Z�� ȸ���� ��� ���� ��� True
		SpringArm->bDoCollisionTest = true;
		// SPringArm�� �浹�� ī�޶� ��ֹ� ������ �����Ѵ�.
		bUseControllerRotationYaw = false;
		// ��Ʈ�ѷ��� Z�� ȸ���� ��������ʽ��ϴ�.

		GetCharacterMovement()->bOrientRotationToMovement = true;
		// ĳ���͸� �ڵ����� ȸ�������ִ� OrientRotationToMovement�� ����մϴ�.
		GetCharacterMovement()->RotationRate = FRotator(0.0f,720.0f, 0.0f);
		// ĳ���͸� ȸ���� �ӵ�
	}
}

void AABCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;
	// CurrentControlMode�� �Էµ� ���� �����մϴ�.
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		/*SpringArm->TargetArmLength = 450.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);*/
		ArmLengthTo = 450.0f;
		// ���� ���̸� 450���� �ٲߴϴ�.
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		// bUseControllerDesiredRotation �� üũ�ϸ� ��Ʈ�� ȸ���� ����Ű�� �������� �ε巴�� ȸ���Ѵ�.
		// GTA��忡���� ������ ȸ������ ������ ������ üũ���� �ʴ´�.
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::DIABLO:
		/*SpringArm->TargetArmLength = 800.0f;
		SpringArm->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f));*/
		ArmLengthTo = 800.0f;
		//���� ���̸� 800���� �ٲߴϴ�
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		// ���� ȸ�� �ʱⰪ�� -45�� ����ϴ�.
		SpringArm->bUsePawnControlRotation = false;
		// SpringArm�� Pawn������ ȸ�� ��뿩�� false
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = false;
		// Roll = X�� , Pitch = Y��, Yaw = Z�� ȸ���� ��� ���� ��� false
		SpringArm->bDoCollisionTest = false;
		// SPringArm�� �浹�� ī�޶� ��ֹ� ������ ���������ʴ´�.
		bUseControllerRotationYaw = false;
		// ��Ʈ�ѷ��� Z�� ȸ���� ������� �ʽ��ϴ�

		GetCharacterMovement()->bOrientRotationToMovement = false;
		// ĳ���͸� �ڵ����� ȸ�������ִ� OrientRotationToMovement�� ������� �ʴ´�.
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		// bUseControllerDesiredRotation �� üũ�����ϸ� ��Ʈ�� ȸ���� ����Ű�� �������� �ε巴�� ȸ���Ѵ�.
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		// ȸ���ӵ��� �������ݴϴ�.
		break;
	case EControlMode::NPC:
		// NPC ����� ���
		bUseControllerRotationYaw = false;
		// ��Ʈ�ѷ��� Z�� ȸ���� ������� �ʽ��ϴ�
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		// bUseControllerDesiredRotation �� üũ�����ϸ� ��Ʈ�� ȸ���� ����Ű�� �������� �ε巴�� ȸ���Ѵ�.
		GetCharacterMovement()->bOrientRotationToMovement = true;
		// ĳ���͸� �ڵ����� ȸ�������ִ� OrientRotationToMovement�� ������� �ʴ´�.
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
		// ȸ���ӵ��� 480���� �������ݴϴ�.
		break;
	}
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
	//SrpingArm�� ���̴� ���� SpringArm�� ���̺��� ArmLengthTo�� ���̱��� DeltaTime�ֱ�� �ٲ��.

	switch (CurrentControlMode) {
	case EControlMode::DIABLO:
		SpringArm->RelativeRotation = FMath::RInterpTo(SpringArm->RelativeRotation, ArmRotationTo, DeltaTime, ArmRotationSpeed);
		// SptringArm�� ȸ������ DIABLO����϶��� ȸ���ϸ�, ���� SpringArm�� ȸ�����ļ� ArmRotationTo�� ������
		// DeltaTime�� ���� ������ �ٲ��.
		break;
	}

	switch (CurrentControlMode) {
	case EControlMode::DIABLO:
		if (DirectionToMove.SizeSquared() > 0.0f) {
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
			// ��ƺ�� ��� �϶�
			// DirectionToMove.SizeSquared() => �Է°��� ũ�Ⱑ 0���� ũ�ٸ�
			// DirectionToMove�� ĳ������ �̵� ���͸� ���
			// ī�޶� DirectionToMode�� ���� �����Դϴ�.
		}
		break;
	}
	
	//// Pawn���� instance�� ���� �ִϸ��̼��� �����ϴ� ���
	//auto ABAnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	//if (nullptr != ABAnimInstance) {
	//	ABAnimInstance->SetPawnSpeed(GetVelocity().Size());
	//	// �ν�ź���� Pawn�� ������ �ѱ��.
	//}

}

void AABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//auto AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	//ABCHECK(nullptr != AnimInstance);
	//AnimInstance->OnMontageEnded.AddDynamic(this, &AABCharacter::OnAttackMontageEnded);

	ABAnim = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(nullptr != ABAnim);
	// ABAnim�� ������ �ҷ����� nullptr�� ���� �������ʴ��� Ȯ���մϴ�.

	ABAnim->OnMontageEnded.AddDynamic(this, &AABCharacter::OnAttackMontageEnded);
	// OnMontageEnded(��Ÿ�� �������� ����Ǵ� �Լ�)�� OnAttackMontageEnded�� �߰��մϴ�.

	// ���ٽ��� ����� OnNextAttackCheck ��������Ʈ�� ABCharactor�� �����Ѵ�.
	ABAnim->OnNextAttackCheck.AddLambda([this]()->void {
		ABLOG(Warning, TEXT("OnNextAttackCheck"));
		// OnNextAttackCheck ��������Ʈ ������ �α׷� ����Ѵ�.
		CanNextCombo = false;
		// �޺����� ���ο� false�� �ش�
		if (IsComboInputOn){	
			// �޺� �Է����̶��
			AttackStartComboState();
			// �޺����� �ʱ�ȭ��Ű��
			ABAnim->JumpToAttackMontageSection(CurrentCombo);
			// ���� �������� �Ѿ��.
	}
	});
	ABAnim->OnAttackHitCheck.AddUObject(this, &AABCharacter::AttackCheck);
	// OnAttackHit ���⸦ �ֵθ��� ���� �߻��ϴ� �Լ��� AttackCheck�� �߰��Ѵ�.

	CharacterStat->OnHPIsZero.AddLambda([this]()->void {
		// ĳ���� ������ OnHpIsZeor�� �Լ��� ���ٷ� �߰��մϴ�(��������Ʈ)
		ABLOG(Warning, TEXT("OnHPIsZero"));
		ABAnim->SetDeadAnim();
		// AnAnim �� �״� �ִϸ��̼��� �߰��մϴ�
		SetActorEnableCollision(false);
		// ĳ������ �浹�� ���ϴ�.
	});

	auto CharacterWidget = Cast<UABCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	// HPWidget���� UserWidgetObject�� �����ɴϴ�.
	if (nullptr != CharacterWidget) {
		// CharacterWidget�� �дµ� �����ߴٸ�
		CharacterWidget->BindCharacterStat(CharacterStat);
		// ChracterWidget�� CharacteStat�� �����մϴ�.
	}
}

float AABCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// ��ӹ��� TakeDamage�� ���ڸ� �������ְ� �������� flot������ �޾ƿɴϴ�
	ABLOG(Warning, TEXT("Actor: %s took Damage : %f"), *GetName(), FinalDamage);
	// �� ���ظ�ŭ �α׷�����մϴ�

	//if (FinalDamage > 0.0f) {
		// ���� ���ذ� 0���� ũ�ٸ�
		//ABAnim->SetDeadAnim();
		// SetDeadANim()�Լ��� �����մϴ�.
		//SetActorEnableCollision(false);
		// �浹�� �����մϴ�.collision�� ���ϴ�
	//}

	CharacterStat->SetDamage(FinalDamage);
	// ĳ���� ������ FinalDamage��ŭ �������� �ݴϴ�.(���ظ� �ݴϴ�)
	if (CurrentState == ECharacterState::DEAD) {
		// ���� ���°� DEAD�ϋ�
		if (EventInstigator->IsPlayerController()) {
			// ������ �ʿ��� (�������� NPC) �÷��̾� ��Ʈ�ѷ��� �ִٸ�
			auto ABPlayerController = Cast<AABPlayerController>(EventInstigator);
			ABCHECK(nullptr != ABPlayerController, 0.0f);
			ABPlayerController->NPCKill(this);
			// ������ �÷��̾���Ʈ�ѿ� NPCKILL�Լ��� �� ĳ������ ���� �Ѱ��ݴϴ�.
		}
	}
	return FinalDamage;
	// ���ذ��� ��ȯ�մϴ�.
}

//void AABCharacter::PossessedBy(AController * NewController)
//{
//	Super::PossessedBy(NewController);
//
//	if (IsPlayerControlled()) {
//		// ��Ʈ�ѷ��� �����Ѵٸ�
//		SetControlMode(EControlMode::DIABLO);
//		// ĳ���ʹ� ��ƺ�� ��尡 �˴ϴ�.
//		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
//		// �̶� �ȴ� �ӵ��� 600�̵˴ϴ�.
//	}
//	else {
//		SetControlMode(EControlMode::NPC);
//		// ��Ʈ�ѷ��� ���ٸ� NPC���� �Ǹ�
//		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
//		// �ȴ¼ӵ��� 300�̵˴ϴ�.
//	}
//}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AABCharacter::ViewChange);
	// ��ư�� ��������(IE_Pressed)�� ��������(IE_Released)�� ���� üũ�� �� �� �ִ�.

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AABCharacter::Jump);
	// �׼� �̺�Ʈ�� �����ϴ� ������ �˻��մϤ�.

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AABCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABCharacter::LeftRight);
	// InputComponent�� ���� AABCharactor�� UpDown�� LeftRight �Լ��� �ش�.

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::Turn);
	// InputComponent�� ���� AABCharacter�� LookUp�� Turn�� �ݴϴ�.
}

bool AABCharacter::CanSetWeapon()
{
	return (nullptr==CurrentWeapon);
}

void AABCharacter::SetWeapon(AABWeapon * NewWeapon)
{
	ABCHECK(nullptr != NewWeapon && nullptr == CurrentWeapon);
	// ���� �ٲ� �����, ���� ���Ⱑ ��� �ִ��� Ȯ���մϴ�.

	FName WeaponSocket(TEXT("hand_rSocket"));
	if (nullptr != NewWeapon) {
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
		// NewWeapon�� �����Ѵٸ� WeaponSocket�� �ڽ����� �ΰ�
		// CurrentWeapon�� NewWeapon���� �ٲߴϴ�.
	}
}

void AABCharacter::UpDown(float NewAxisValue)
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		// �Է¹��� NewAxisVlaue�� ������ ĳ������ ��, �� �������� �����Դϴ�.
		// ĳ������ �̵����� ControlRotation�� ���� �����
		// ���콺�� ȸ������ ����Ͽ� ĳ���͸� �̵����͸� ȸ����ŵ�ϴ�.(ĳ���� ���� ȸ������ �ʽ��ϴ�)
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		// �Է¹��� NewXisValue�� ���� DirectionToMove.X���� �ݴϴ�
		break;
	}
}

void AABCharacter::LeftRight(float NewAxisValue)
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		// �Է¹��� NewAxisValue�� ������ ĳ������ �¿� �������� �����Դϴ�.
		// ĳ������ �̵����� ControlRotation�� ���� �����
		// ���콺�� ȸ������ ����Ͽ� ĳ���͸� �̵����͸� ȸ����ŵ�ϴ�.(ĳ���� ���� ȸ������ �ʽ��ϴ�)
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		// �Է¹��� NewXisValue�� ���� DirectionToMove.Y���� �ݴϴ�
		break;
	}
}

void AABCharacter::LookUp(float NewAxisValue)
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		// ��Ʈ�ѷ��� NewAxisValue�� ���� �ݴϴ�.
		break;
	}
}

void AABCharacter::Turn(float NewAixsValue)
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		AddControllerYawInput(NewAixsValue);
		// ��Ʈ�ѷ��� newAxisValue�� ���� �־� ȸ����ŵ�ϴ�.
		break;
	}
}

void AABCharacter::ViewChange()
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		// GTA���� DIABLO���� �ٲ�� ���
		// ��Ʈ�ѷ��� ȸ������ Actor�� ȸ�������� �ٲ۴�.
		SetControlMode(EControlMode::DIABLO);
		// ���� ���Ӹ�尡 GTA�� ��� DIABLO�� �ٲ۴�.
		break;
	case EControlMode::DIABLO:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		// DIABLO���� GTA�� �ٲٴ� ���
		// ��Ʈ�ѷ��� ȸ������ SpringArm�� ȸ�������� �ٲߴϴ�.
		SetControlMode(EControlMode::GTA);
		// ���� ���Ӹ�尡 DIABLO�ϰ�� GTA�� �ٲ۴�.
		break;
	}
}

void AABCharacter::Attack()
{
	//if (IsAttacking)return;
	////ABLOG_S(Warning);
	////auto AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	////// AnimInstance�� �ҷ��ɴϴ�.
	////if (nullptr == AnimInstance)return;
	//////���� ��� �׳� return
	////AnimInstance->PlayAttackMontage();
	//// Instance�� �ִٸ� ����մϴ�.
	//ABAnim->PlayAttackMontage();
	//IsAttacking = true;
	if (IsAttacking) {
		//�������̶��
		ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		// CurrentCombo�� MaxCombo���� ū�� Ȯ���Ѵ�.
		if (CanNextCombo) {
			// ���� �޺��� �����ϴٸ�
			IsComboInputOn = true;
			// �޺����� �ɷ� ó���ȴ�.
		}
	}
	else {
		ABCHECK(CurrentCombo == 0);
		// ���� �޺��� 0���� Ȯ���Ѵ�.
		AttackStartComboState();
		// �޺��Լ��� �ʱ�ȭ�Ѵ�
		ABAnim->PlayAttackMontage();
		// ��Ÿ�ָ� �����Ѵ�
		ABAnim->JumpToAttackMontageSection(CurrentCombo);
		// ������������ �Ѿ���ִ� ������ ��Ÿ���� �Լ��� �ѱ�ϴ�
		IsAttacking = true;
		// ���� ������
	}
}

void AABCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	// IsAttacking�� true���� Ȯ���մϴ�.
	ABCHECK(CurrentCombo > 0);
	// ���� �޺��� 0���� ū�� Ȯ���մϴ�
	IsAttacking = false;
	// ���� ���¸� false�� �Ӵϴ�
	AttackEndComboState();
	// ���� ���� �Լ��� �����մϴ�.

	OnAttackEnd.Broadcast();
	// ������ ������ ��������Ʈ�� �����մϴ�.
}

void AABCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	// ���� �޺��� �Ѿ �� ����
	IsComboInputOn = false;
	// ���� �޺����� ���´� �ƴ�
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	// �����޺����� 0���� ũ�� MaxCombo-1���� ������ üũ�մϴ�.
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
	// Clamp�� ����� �ִ밪(MAXCOMBO)���� ���� �ø��ϴ�.
}

void AABCharacter::AttackEndComboState()
{
	// �޺��� ����ǹǷ� �ʱ�ȭ�� ���ݴϴ�.
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void AABCharacter::AttackCheck()
{
	FHitResult HitResult;
	// FHitResult ����ü�� ������ �����մϴ�.

	FCollisionQueryParams Params(NAME_None, false, this);
	// �浹 ��ɿ� ���޵� �Ű������� ����

	bool bResult =
		GetWorld()->SweepSingleByChannel
		// �⺻ ������ ���ڷ� ���� �� (Sphere)
		// ���� �������� �� ��������(GetActorLocation(), GetActorLocation()+ GetActorForwardVector()*200.0f)
		// ���� (Sweep)
		// �ش� ���� ������ ���� ������ �Ͼ������ �����Ѵ�.
		(
			HitResult,
			// �浹 ������� ���� ����ü
			GetActorLocation(),
			// ������
			GetActorLocation() + GetActorForwardVector()*200.0f,
			// ����
			FQuat::Identity,
			// ȸ�� (Identity�� ȸ������)
			ECollisionChannel::ECC_GameTraceChannel2,
			// ���� �⵹�� ����� Ʈ���̽� ä���� ����
			FCollisionShape::MakeSphere(50.0f),
			// Ž���� ����� ��ü�� ũ��� ���
			Params
			// Ž�� ����� ���� ���� ���� ��Ƶ� ����ü
		);

	#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector()*AttackRange;
	// Actor�� ���� * ���� ���� => ������ ���� ����
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	// �߽��� => ������ ��ġ + ���� ������ ����
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	// ������ => ĸ���� ������ �߽ɱ����� �Ÿ�
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	// ĸ���� ȸ��
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	// ���� �ʷ� or ����
	float DebugLifeTime = 5.0f;
	// ����� ���� ���� �ð� 5��

	DrawDebugCapsule(
		GetWorld(),
		// ĸ���� World�� �����ϸ�
		Center,
		// Center�� �߽�����
		HalfHeight,
		// HalfHeight�� ���̿�
		AttackRadius,
		// AttackRadius�� �������� ������
		CapsuleRot,
		// CapsuleRot��ŭ ȸ����
		DrawColor,
		// DrawColor ����
		false,
		DebugLifeTime
		// DebugLifeTime���� �����Ѵ�.
	);

	#endif

	if (bResult) {
		// ���𰡿� �浹�ߴٸ�
		if (HitResult.Actor.IsValid()) {
			// �浹�� Actor�� �ִٸ�
			ABLOG(Warning, TEXT("Hit Actor Name: %s"), *HitResult.Actor->GetName());
			// Actor�� ������ ����մϴ�.

			FDamageEvent DamageEvent;
			// DamageEvnet�� �������� ������ ��Ÿ����
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
			// ���� ���� ĳ���� ���ȿ��� �����ɴϴ�.

			// �浹�� Actor�� TakeDamage�Լ��� �����
			// ������ �������� ���� 50
			// �������� ���� DamageEvent
			// ������ ���� ������
			// ������ ������ ���� ����� ����(������)
		}
	}
}

void AABCharacter::OnAssetLoadCompleted()
{
	AssetStreamingHandle->ReleaseHandle();
	TSoftObjectPtr<USkeletalMesh> LoadedAssetPath(CharacterAssetToLoad);
	ABCHECK(LoadedAssetPath.IsValid());
	// ������ ��θ� ���������� �о����� �Ǵ��մϴ�.

	GetMesh()->SetSkeletalMesh(LoadedAssetPath.Get());
	SetChracterState(ECharacterState::READY);
	//ĳ���� ���¸� READY�� �Ӵϴ�

	//if (LoadedAssetPath.IsValid()) {
	//	GetMesh()->SetSkeletalMesh(LoadedAssetPath.Get());
	//	// ĳ������ �޽��� �Է¹��� ������ �޽��� �ٲߴϴ�.
	//}
}
