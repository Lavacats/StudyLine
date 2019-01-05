// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacter.h"


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
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
	//EndComboState();
	MaxCombo = 4;

	// �ִ� �޺��� 4�̸�
	// ������ ���� �޺��� 0���� �ʱ�ȭ �ϱ����� AttackEndComboState�� ����Ѵ�.
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	// ��ӹ��� PostInitializeComponents�� �����մϴ�.
	{
		//auto AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
		//// AnimInstance�� ������ �ҷ��ɴϴ�.
		//ABCHECK(nullptr != AnimInstance);
		//// AnimInstanc �� �����ϴ��� üũ
		//AnimInstance->OnMontageEnded.AddDynamic(this, &AABCharacter::OnAttackMontageEnded);
		//// OnAttackMontageEnded �Լ���  OnMontageEnded�� �߰��մϴ�.
	}

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

		if (IsComboInputOn) {
			// �޺� �Է����̶��
			AttackStartComboState();
			// �޺����� �ʱ�ȭ��Ű��
			ABAnim->JumpToAttackMontageSection(CurrentCombo);
			// ���� �������� �Ѿ��.
		}
	});
}

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

	//if (IsAttacking)return;
	// IsAttacking�� True�̸� �ٷ� ��ȯ�մϴ�.(�̹� ������)

	//ABLOG_S(Warning);
	auto AnimInstance = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	// AnimInstance�� �ҷ��ɴϴ�.
	if (nullptr == AnimInstance)return;
	//���� ��� �׳� return
	AnimInstance->PlayAttackMontage();
	// Instance�� �ִٸ� ����մϴ�.

	ABAnim->PlayAttackMontage();
	// AnimInstance���� PlayAttackMontage�� �����Ų��.

	IsAttacking = true;
	//(�������� �ƴѰ��) �����ߴٴ� ���� �˸������� true���մϴ�.
}

void AABCharacter::OnAttackMontageEnded(UAnimMontage * Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	// IsAttacking�� �α׸� ����մϴ�

	IsAttacking = false;
	// IsAttacking �� ���� false�� �ش�

	ABCHECK(IsAttacking);
	// ���������� Ȯ���մϴ�
	ABCHECK(CurrentCombo > 0);
	// ���� �޺��� 0���� ū�� Ȯ���մϴ�
	IsAttacking = false;
	// ���� ���¸� false�� �Ӵϴ�
	//EndComboState();
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
	// ���� ���� �Լ��� �����մϴ�.
}


void AABCharacter::EndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
}

void AABCharacter::AttackStartComboState()
{
	// �޺� ���� ���� ����

	CanNextCombo = true;
	// ���� �޺��� �Ѿ �� ����
	IsComboInputOn = false;
	// ���� �޺����� ���´� �ƴ�
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	// ���� �޺����� �α׷� ���
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
	// Clamp�� ����� �ִ밪(MAXCOMBO)���� ���� �ø��ϴ�.
}

