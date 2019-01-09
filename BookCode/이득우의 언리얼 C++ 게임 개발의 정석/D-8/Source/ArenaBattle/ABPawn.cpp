// Fill out your copyright notice in the Description page of Project Settings.

#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	// Pawn에 사용할 오브젝트드들을 지정하고 에디터에서 보기 편하게 분류합니다
	
	RootComponent = Capsule;
	// 루트 컴포넌트로 캡슐을 둡니다.
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	// Mesh와 SpringArm을 Capsule의 자식으로 넣습니다
	Camera->SetupAttachment(SpringArm);
	// Camera를 SpringArm의 자식으로 넣습니다.

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	// 캡슐의 높이와 지름으 조절합니다.
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	// Mesh의 초기위치(FVector)와 회전값(FRotator)를 조절합니다
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	// 스프링암의 길이와 회전값으 조정합니다.

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOAD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOAD.Succeeded()) {
		Mesh->SetSkeletalMesh(SK_CARDBOAD.Object);
		// 사용할 SkeletaMesh 경로정보를 불러오며, 불러오는데 성공했다면, Mesh에 적용합니다.
	}
	
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	// Mesh에 AnimationBlueprint(블루프린트를 사용하는 애니메이션 조절)을 생성합니다.
	static ConstructorHelpers::FClassFinder<UAnimInstance>WARRIOR_ANIM(TEXT("/Game/Book/Animation/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded()) {
		Mesh->SetAnimInstanceClass(WARRIOR_ANIM.Class);
		// 사용할 UAnimInstance 경로정보를 불러오며, 불러오는데 성공했다면, Mesh에 적용합니다.
	}

}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();
	//Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	//Mesh에 애니메이션 노드를 생성합니다.
	//UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Book/Animation/WarriorRun.WarriorRun"));
	//UAnimationAsset인 AnimAsset에 사용할 애니메이션의 경로를 입력합니다.
	//if (AnimAsset != nullptr) {
	//	Mesh->PlayAnimation(AnimAsset, true);
	//  정상적으로 불러온 경우 애니메이션을 재생합니다.
	//}
	
}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPawn::PossessedBy(AController * NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABPawn::LeftRight);
	//BindAxis : Pawn이 레버 신호를 받을 수 있도록 함수와 연동합니다.

}

void AABPawn::UpDown(float NewAxisValue)
{
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
	//NewAxisValue : -1~1의 값을 가지며 UpDown 입력값을 줍니다.

	AddMovementInput(GetActorForwardVector(), NewAxisValue);
	//AddMovementInput : -1~1의 값을 받아 폰을 움직이게 합니다. ForwardVector방향
}

void AABPawn::LeftRight(float NewAxisValue)
{
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
	//NewAxisValue : -1~1의 값을 가지며 LeftRight 입력값을 줍니다.

	AddMovementInput(GetActorRightVector(), NewAxisValue);	
	//AddMovementInput : -1~1의 값을 받아 폰을 움직이게 합니다. RightVector방향
}

