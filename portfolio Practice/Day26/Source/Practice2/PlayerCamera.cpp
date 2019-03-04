// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCamera.h"
#include "DrawDebugHelpers.h"
#include "P2PlayerController.h"
#include "PlayerUIWidget.h"
#include "Components/WidgetComponent.h"

void UPlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	AIM_UI = CreateWidget<UPlayerUIWidget>(Cast< AP2PlayerController>(GetWorld()->GetFirstPlayerController()), HDWidgetClass);
	AIM_UI->AddToViewport();
}

UPlayerCamera::UPlayerCamera()
{
	PrimaryComponentTick.bCanEverTick = true;

	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));


	this->SetupAttachment(SpringArm);
	SpringArm->TargetArmLength =150.0f;
	ArmLengthTo = SpringArm->TargetArmLength;
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = false;
	ViewState = PlayerViewState::View_IDLE;
	ArmRotationSpeed = 5.0f;

	static ConstructorHelpers::FClassFinder<UPlayerUIWidget> UI_AIM(TEXT("/Game/UI/UI_AIM.UI_AIM_C"));
	if (UI_AIM.Succeeded()) {
		HDWidgetClass = UI_AIM.Class;
	}

}

void UPlayerCamera::setSpringArmCameraInRoot(UCapsuleComponent * root)
{
	SpringArm->SetupAttachment(root);

}

void UPlayerCamera::ChangeView(PlayerViewState view)
{
	switch (view) {
	case PlayerViewState::View_IDLE:
		ArmLengthTo = 150.0f;
		ViewState = PlayerViewState::View_IDLE;
		SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = false;
		break;
	case PlayerViewState::View_SHOT:
		ArmLengthTo = 30.0f;
		ViewState = PlayerViewState::View_SHOT;
		SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		SpringArm->SetRelativeLocation(FVector(37.5f, 0.0f, 30.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = false;
		break;
	case PlayerViewState::View_SHIELD:
		ArmLengthTo = 110.0f;
		ViewState = PlayerViewState::View_SHOT;
		SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		SpringArm->SetRelativeLocation(FVector(26.0f, 0.0f,43.0f));
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritPitch = true;
		SpringArm->bInheritRoll = true;
		SpringArm->bInheritYaw = true;
		SpringArm->bDoCollisionTest = false;
		break;
	}
}

void UPlayerCamera::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmRotationSpeed);

}

void UPlayerCamera::CameraVector()
{
	FHitResult* HitResult = new FHitResult();
	float TraceRange = 10.0f;
	float TraceRadius = 5.0f;
	
	FVector StartTrace = this->GetComponentLocation();
	FVector ForwardVector = this->GetForwardVector();
	FVector EndTrace = ((ForwardVector*5000.0f) + StartTrace);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams)){
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true);
	}

}

void UPlayerCamera::PlayerAimOnOff(bool value)
{
	AIM_UI->SetPlayerAim(value);
}
