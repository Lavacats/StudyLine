// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacter.h"


// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	// 각가의 컴포넌트 에서 새롭게 만듭니다.

	SpringArm->SetupAttachment(GetCapsuleComponent());
	// SpringArm을 Capsule의 자식으로 넣습니다.
	Camera->SetupAttachment(SpringArm);
	// Camera를 SpringArm의 자식으로 넣습니다.

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f),FRotator(0.0f,-90.0f,0.0f));
	// Mesh의 초기 위치와 회전값을 조저합니다.
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	// SpringArm의 길이와 회전값을 조정합니다.

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOAD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOAD.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_CARDBOAD.Object);
		// 사용할 SkeletaMesh 경로정보를 불러오며, 불러오는데 성공했다면, Mesh에 적용합니다.
	}
	
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	// Mesh에 AnimationBlueprint(블루프린트를 사용하는 애니메이션 조절)을 생성합니다.
	static ConstructorHelpers::FClassFinder<UAnimInstance>WARRIOR_ANIM(TEXT("/Game/Book/Animation/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
		// 사용할 UAnimInstance 경로정보를 불러오며, 불러오는데 성공했다면, Mesh에 적용합니다.
	}
	
	SetControlMode(EControlMode::DIABLO);
	// 컨트롤 모드의 초기값으로 DIABLO을 줍니다.

	ArmLengthSpeed = 3.0f;
	// 팔을 바꾸는 속도 3
	ArmRotationSpeed = 10.0f;
	// 파을 회전시키는 속도 10

	GetCharacterMovement()->JumpZVelocity = 800.0f;
	// CharacterMovement의 점프 값을 800으로 바꾸어줍니다.
	
	IsAttacking = false;
	// IsAttacking의 값을 false로 준다
	MaxCombo = 4;
	AttackEndComboState();
	// 최대 콤보는 4이며
	// 시작할 때는 콤보를 0으로 초기화 하기위해 AttackEndComboState를 사용한다.

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCharacter"));
	// ABChatacer의 캡슐컴포넌트 초기값을 ABCHaracter값으로 둡니다.

	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	//FName WeaponSocket(TEXT("hand_rSocket"));
	//// 소켓 hand_rSocket을 찾습니다

	//if (GetMesh()->DoesSocketExist(WeaponSocket)) {
	//	// WeaponSocket이 Mesh에 있다면
	//	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	//	// Waepon은 SkeletalMeshComponent의 WEAPON이라는 이름으로 생성됩니다.
	//	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));
	//	// 레퍼런스를 통해 무기를 가져오면
	//	if (SK_WEAPON.Succeeded()) {
	//		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	//		// 무기를 성공적으로 불러왔다면 SkeletalMesh에 weaopon을 장착합니다.
	//	}
	//	Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	//	// Weapon을 WaeponSocket에 넣습니다.
	//}

	CharacterStat = CreateDefaultSubobject<UABCharacterStatComponent>(TEXT("CHARCTERSTAT"));
	// 에디터에 CHARACTERSTAT라는 캐릭터 스탯 컴포넌트를 추가합니다.

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	// 에디터에 HPBARWIDGET 으로 위젯 컴포넌트를 추가합니다.

	HPBarWidget->SetupAttachment(GetMesh());
	// HPBarWidget은 GetMesh()의 자식으로 드어갑니다.

	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	// HPBarWidget의 위치는 (0,0,180)이며
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	// 항상 화면을 바라보도록 회전합니다.
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Book/UI/UI_HPBar.UI_HPBar_C"));
	// 블루프린트 계열 파일을 C++로 부를 떄는 C를 붙여야한다.
		if (UI_HUD.Succeeded()) {
			// UI_HUD를 불러오는데 성공하면
			HPBarWidget->SetWidgetClass(UI_HUD.Class);
			// HPBarWidget에 UI_HUD를 넣고
			HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
			// 크기르 150,50으로 지정합니다.
	}

		AIControllerClass = AABAIController::StaticClass();
		// AIControllerClas의 속성을 StaticClass로 잡는다
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
		// 자동적으로 만들어지는 AI 옵션을 PlacedInWorldOrSpawned로 한다.
		// 레벨(씬)에 배치되거나 새롭게 생성되는 ABCharacter마다 ABAIController가 생성된다
		// 플레이어가 조종하는 캐리을 제외한 캐릭터들은 모두 ABAIController의 지배를 받는다.
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();

	//FName WeaponSocket(TEXT("hand_rSocket"));
	//// 소켓 hand_rSocket을 찾습니다

	//auto CurWeapon = GetWorld()->SpawnActor<AABWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);\
	//// AABWapon을 World에 Spanw하고 CurWeapon으로 둡니다.

	//if (nullptr != CurWeapon) {
	//	CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	//	// CurWaepon이 생성되면 WeaponSocket의 자식으로 넣습니다.
	//}

}

void AABCharacter::SetControlMode(int32 ControlMode)
{
	if (ControlMode == 0) {
		// SpringArm : 카메라 지지대에 관한 설정
		SpringArm->TargetArmLength = 450.0f;
		// SpringArm의 타겟으로 부터의 거리 450
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		// SpringArm의 초기 회전값 Zero
		SpringArm->bUsePawnControlRotation = true;
		// SpringArm의 Pawn에서의 회전 사용여부 true
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		// Roll = X축 , Pitch = Y축, Yaw = Z축 회전값 사용 여부 모두 True
		SpringArm->bDoCollisionTest = true;
		// SPringArm이 충돌시 카메라를 장애물 앞으로 줌인한다.
		bUseControllerRotationYaw = false;
		// 컨트롤러의 Z출 회전을 사용하지않습니다.

		GetCharacterMovement()->bOrientRotationToMovement = true;
		// 캐릭터를 자동으로 회전시켜주는 OrientRotationToMovement를 사용합니다.
		GetCharacterMovement()->RotationRate = FRotator(0.0f,720.0f, 0.0f);
		// 캐릭터를 회전할 속도
	}
}

void AABCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;
	// CurrentControlMode에 입력된 값을 저장합니다.
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		/*SpringArm->TargetArmLength = 450.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);*/
		ArmLengthTo = 450.0f;
		// 팔의 길이를 450으로 바꿉니다.
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;

		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		// bUseControllerDesiredRotation 를 체크하면 컨트롤 회전이 가리키는 방향으로 부드럽게 회전한다.
		// GTA모드에서는 별도의 회전값을 가지기 떄문에 체크하지 않는다.
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::DIABLO:
		/*SpringArm->TargetArmLength = 800.0f;
		SpringArm->SetRelativeRotation(FRotator(-45.0f,0.0f,0.0f));*/
		ArmLengthTo = 800.0f;
		//팔의 길이를 800으로 바꿉니다
		ArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		// 팔의 회전 초기값을 -45로 잡습니다.
		SpringArm->bUsePawnControlRotation = false;
		// SpringArm의 Pawn에서의 회전 사용여부 false
		SpringArm->bInheritRoll = false;
		SpringArm->bInheritPitch = false;
		SpringArm->bInheritYaw = false;
		// Roll = X축 , Pitch = Y축, Yaw = Z축 회전값 사용 여부 모두 false
		SpringArm->bDoCollisionTest = false;
		// SPringArm이 충돌시 카메라를 장애물 앞으로 줌인하지않는다.
		bUseControllerRotationYaw = false;
		// 컨트롤러의 Z출 회전을 사용하지 않습니다

		GetCharacterMovement()->bOrientRotationToMovement = false;
		// 캐릭터를 자동으로 회전시켜주는 OrientRotationToMovement를 사용하지 않는다.
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		// bUseControllerDesiredRotation 를 체크해제하면 컨트롤 회전이 가리키는 방향으로 부드럽게 회전한다.
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
		// 회전속도를 지정해줍니다.
		break;
	case EControlMode::NPC:
		// NPC 모드일 경우
		bUseControllerRotationYaw = false;
		// 컨트롤러의 Z출 회전을 사용하지 않습니다
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		// bUseControllerDesiredRotation 를 체크해제하면 컨트롤 회전이 가리키는 방향으로 부드럽게 회전한다.
		GetCharacterMovement()->bOrientRotationToMovement = true;
		// 캐릭터를 자동으로 회전시켜주는 OrientRotationToMovement를 사용하지 않는다.
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
		// 회전속도를 480으로 지정해줍니다.
		break;
	}
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);
	//SrpingArm의 길이는 현재 SpringArm의 길이부터 ArmLengthTo의 길이까지 DeltaTime주기로 바뀐다.

	switch (CurrentControlMode) {
	case EControlMode::DIABLO:
		SpringArm->RelativeRotation = FMath::RInterpTo(SpringArm->RelativeRotation, ArmRotationTo, DeltaTime, ArmRotationSpeed);
		// SptringArm의 회전값은 DIABLO모드일때만 회전하며, 현재 SpringArm의 회전갑셍서 ArmRotationTo의 값으로
		// DeltaTime에 따라 서서히 바뀐다.
		break;
	}

	switch (CurrentControlMode) {
	case EControlMode::DIABLO:
		if (DirectionToMove.SizeSquared() > 0.0f) {
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
			// 디아브로 모드 일때
			// DirectionToMove.SizeSquared() => 입력값의 크기가 0보다 크다면
			// DirectionToMove에 캐릭터의 이동 벡터를 담고
			// 카메라가 DirectionToMode를 향해 움직입니다.
		}
		break;
	}
	
	//// Pawn에서 instance를 통해 애니메이션을 조절하는 방법
	//auto ABAnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	//if (nullptr != ABAnimInstance) {
	//	ABAnimInstance->SetPawnSpeed(GetVelocity().Size());
	//	// 인스탄스에 Pawn의 정보를 넘긴다.
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
	// ABAnim의 정보를 불러오고 nullptr의 값을 가지지않는지 확인합니다.

	ABAnim->OnMontageEnded.AddDynamic(this, &AABCharacter::OnAttackMontageEnded);
	// OnMontageEnded(몽타주 마지막에 실행되는 함수)에 OnAttackMontageEnded를 추가합니다.

	// 람다식을 사용해 OnNextAttackCheck 델리게이트에 ABCharactor을 선언한다.
	ABAnim->OnNextAttackCheck.AddLambda([this]()->void {
		ABLOG(Warning, TEXT("OnNextAttackCheck"));
		// OnNextAttackCheck 델리게이트 정보를 로그로 출력한다.
		CanNextCombo = false;
		// 콤보진행 여부에 false를 준다
		if (IsComboInputOn){	
			// 콤보 입력중이라면
			AttackStartComboState();
			// 콤보값으 초기화시키고
			ABAnim->JumpToAttackMontageSection(CurrentCombo);
			// 다음 세션으로 넘어간다.
	}
	});
	ABAnim->OnAttackHitCheck.AddUObject(this, &AABCharacter::AttackCheck);
	// OnAttackHit 무기를 휘두르는 순간 발생하는 함수에 AttackCheck를 추가한다.

	CharacterStat->OnHPIsZero.AddLambda([this]()->void {
		// 캐릭터 스탯의 OnHpIsZeor에 함수를 람다로 추가합니다(딜리게이트)
		ABLOG(Warning, TEXT("OnHPIsZero"));
		ABAnim->SetDeadAnim();
		// AnAnim 에 죽는 애니메이션을 추가합니다
		SetActorEnableCollision(false);
		// 캐릭터의 충돌을 끕니다.
	});

	auto CharacterWidget = Cast<UABCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	// HPWidget에서 UserWidgetObject를 가져옵니다.
	if (nullptr != CharacterWidget) {
		// CharacterWidget이 읽는데 성공했다면
		CharacterWidget->BindCharacterStat(CharacterStat);
		// ChracterWidget과 CharacteStat을 연결합니다.
	}
}

float AABCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// 상속받은 TakeDamage에 인자를 전달해주고 최종값을 flot형으로 받아옵니다
	ABLOG(Warning, TEXT("Actor: %s took Damage : %f"), *GetName(), FinalDamage);
	// 준 피해만큼 로그로출력합니다

	//if (FinalDamage > 0.0f) {
		// 받은 피해가 0보다 크다면
		//ABAnim->SetDeadAnim();
		// SetDeadANim()함수를 실행합니다.
		//SetActorEnableCollision(false);
		// 충돌을 종료합니다.collision을 끕니다
	//}

	CharacterStat->SetDamage(FinalDamage);
	// 캐릭터 스뎃에 FinalDamage만큼 데미지를 줍니다.(피해를 줍니다)
	return FinalDamage;
	// 피해값을 반환합니다.
}

void AABCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	if (IsPlayerControlled()) {
		// 컨트롤러가 존재한다면
		SetControlMode(EControlMode::DIABLO);
		// 캐릭터는 디아브로 모드가 됩니다.
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		// 이때 걷는 속도는 600이됩니다.
	}
	else {
		SetControlMode(EControlMode::NPC);
		// 컨트롤러가 없다면 NPC몯가 되며
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		// 걷는속도는 300이됩니다.
	}
}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &AABCharacter::ViewChange);
	// 버튼이 눌렀는지(IE_Pressed)안 눌렀는지(IE_Released)에 대한 체크를 할 수 있다.

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AABCharacter::Jump);
	// 액션 이벤트에 존재하는 점프를 검사합니ㅏ.

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AABCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABCharacter::LeftRight);
	// InputComponent의 값을 AABCharactor의 UpDown과 LeftRight 함수에 준다.

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::Turn);
	// InputComponent의 값을 AABCharacter의 LookUp과 Turn에 줍니다.
}

bool AABCharacter::CanSetWeapon()
{
	return (nullptr==CurrentWeapon);
}

void AABCharacter::SetWeapon(AABWeapon * NewWeapon)
{
	ABCHECK(nullptr != NewWeapon && nullptr == CurrentWeapon);
	// 새로 바꿀 무기와, 현재 무기가 모두 있는지 확인합니다.

	FName WeaponSocket(TEXT("hand_rSocket"));
	if (nullptr != NewWeapon) {
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		NewWeapon->SetOwner(this);
		CurrentWeapon = NewWeapon;
		// NewWeapon이 존재한다면 WeaponSocket의 자식으로 두고
		// CurrentWeapon을 NewWeapon으로 바꿉니다.
	}
}

void AABCharacter::UpDown(float NewAxisValue)
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
		// 입력받은 NewAxisVlaue의 값으로 캐릭터의 전, 후 방향으로 움직입니다.
		// 캐릭터의 이동방향 ControlRotation의 값을 사용해
		// 마우스의 회전값을 계산하여 캐릭터를 이동벡터를 회전시킵니다.(캐릭터 모델은 회전하지 않습니다)
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X = NewAxisValue;
		// 입력받은 NewXisValue의 값을 DirectionToMove.X에게 줍니다
		break;
	}
}

void AABCharacter::LeftRight(float NewAxisValue)
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
		// 입력받은 NewAxisValue의 값으로 캐릭터의 좌우 방향으로 움직입니다.
		// 캐릭터의 이동방향 ControlRotation의 값을 사용해
		// 마우스의 회전값을 계산하여 캐릭터를 이동벡터를 회전시킵니다.(캐릭터 모델은 회전하지 않습니다)
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y = NewAxisValue;
		// 입력받은 NewXisValue의 값을 DirectionToMove.Y에게 줍니다
		break;
	}
}

void AABCharacter::LookUp(float NewAxisValue)
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		// 컨트롤러에 NewAxisValue의 값을 줍니다.
		break;
	}
}

void AABCharacter::Turn(float NewAixsValue)
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		AddControllerYawInput(NewAixsValue);
		// 컨트롤러에 newAxisValue의 값을 주어 회전시킵니다.
		break;
	}
}

void AABCharacter::ViewChange()
{
	switch (CurrentControlMode) {
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		// GTA에서 DIABLO모드로 바뀌는 경우
		// 컨트롤러의 회전값을 Actor의 회전값으로 바꾼다.
		SetControlMode(EControlMode::DIABLO);
		// 현재 게임모드가 GTA일 경우 DIABLO로 바꾼다.
		break;
	case EControlMode::DIABLO:
		GetController()->SetControlRotation(SpringArm->RelativeRotation);
		// DIABLO에서 GTA로 바꾸는 경우
		// 컨트롤러의 회전값을 SpringArm의 회전값으로 바꿉니다.
		SetControlMode(EControlMode::GTA);
		// 현재 게임모드가 DIABLO일경우 GTA로 바꾼다.
		break;
	}
}

void AABCharacter::Attack()
{
	//if (IsAttacking)return;
	////ABLOG_S(Warning);
	////auto AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	////// AnimInstance를 불러옵니다.
	////if (nullptr == AnimInstance)return;
	//////없을 경우 그냥 return
	////AnimInstance->PlayAttackMontage();
	//// Instance가 있다면 재생합니다.
	//ABAnim->PlayAttackMontage();
	//IsAttacking = true;
	if (IsAttacking) {
		//공격중이라면
		ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		// CurrentCombo가 MaxCombo보다 큰지 확인한다.
		if (CanNextCombo) {
			// 다음 콤보가 가능하다면
			IsComboInputOn = true;
			// 콤보중인 걸로 처리된다.
		}
	}
	else {
		ABCHECK(CurrentCombo == 0);
		// 현재 콤보가 0인지 확인한다.
		AttackStartComboState();
		// 콤보함수를 초기화한다
		ABAnim->PlayAttackMontage();
		// 몽타주를 시작한다
		ABAnim->JumpToAttackMontageSection(CurrentCombo);
		// 다음세션으로 넘어갈수있는 정보를 몽타주의 함수에 넘깁니다
		IsAttacking = true;
		// 현재 공격중
	}
}

void AABCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	// IsAttacking이 true인지 확인합니다.
	ABCHECK(CurrentCombo > 0);
	// 현재 콤보가 0보다 큰지 확인합니다
	IsAttacking = false;
	// 공격 상태를 false로 둡니다
	AttackEndComboState();
	// 공격 끝냄 함수를 실행합니다.

	OnAttackEnd.Broadcast();
	// 공격이 끝나면 딜리게이트를 실행합니다.
}

void AABCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	// 다음 콤보로 넘어갈 수 있음
	IsComboInputOn = false;
	// 현재 콤보중인 상태는 아님
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	// 현재콤보수가 0보다 크고 MaxCombo-1보다 작은지 체크합니다.
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
	// Clamp를 사용해 최대값(MAXCOMBO)까지 값을 올립니다.
}

void AABCharacter::AttackEndComboState()
{
	// 콤보가 종료되므로 초기화를 해줍니다.
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void AABCharacter::AttackCheck()
{
	FHitResult HitResult;
	// FHitResult 구조체를 변수로 생성합니다.

	FCollisionQueryParams Params(NAME_None, false, this);
	// 충돌 기능에 전달된 매개변수의 정의

	bool bResult =
		GetWorld()->SweepSingleByChannel
		// 기본 도형을 인자로 받은 후 (Sphere)
		// 시작 지점에서 끝 지점까지(GetActorLocation(), GetActorLocation()+ GetActorForwardVector()*200.0f)
		// 쓸며 (Sweep)
		// 해당 영역 내에서 무리 판정이 일어났는지를 조사한다.
		(
			HitResult,
			// 충돌 결과값을 담을 구조체
			GetActorLocation(),
			// 시작점
			GetActorLocation() + GetActorForwardVector()*200.0f,
			// 끝점
			FQuat::Identity,
			// 회전 (Identity는 회전없음)
			ECollisionChannel::ECC_GameTraceChannel2,
			// 물리 출돌에 사용할 트레이스 채널의 정보
			FCollisionShape::MakeSphere(50.0f),
			// 탐색에 사용할 구체의 크기와 모양
			Params
			// 탐색 방법에 대한 설정 값을 모아둔 구조체
		);

	#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector()*AttackRange;
	// Actor의 방향 * 공격 범위 => 움직일 벡터 길이
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	// 중심점 => 액터의 위치 + 벡터 길이의 절반
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	// 반지름 => 캡슐의 끝부터 중심까지의 거리
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	// 캡슐의 회전
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	// 색상 초록 or 빨강
	float DebugLifeTime = 5.0f;
	// 디버그 라인 생성 시간 5초

	DrawDebugCapsule(
		GetWorld(),
		// 캡슐을 World에 생성하며
		Center,
		// Center를 중심으로
		HalfHeight,
		// HalfHeight의 높이와
		AttackRadius,
		// AttackRadius의 반지름을 가지며
		CapsuleRot,
		// CapsuleRot만큼 회전한
		DrawColor,
		// DrawColor 색의
		false,
		DebugLifeTime
		// DebugLifeTime동안 생성한다.
	);

	#endif

	if (bResult) {
		// 무언가에 충돌했다면
		if (HitResult.Actor.IsValid()) {
			// 충돌한 Actor가 있다면
			ABLOG(Warning, TEXT("Hit Actor Name: %s"), *HitResult.Actor->GetName());
			// Actor의 정보를 출력합니다.

			FDamageEvent DamageEvent;
			// DamageEvnet는 데미지의 종류를 나타낸다
			HitResult.Actor->TakeDamage(CharacterStat->GetAttack(), DamageEvent, GetController(), this);
			// 피해 값을 캐리거 스탯에서 가져옵니다.

			// 충돌한 Actor에 TakeDamage함수를 사용해
			// 전달할 데미지의 세기 50
			// 데미지의 종류 DamageEvent
			// 공격을 내린 가해자
			// 데미지 전달을 위해 사용한 도구(피해자)
		}
	}
}
