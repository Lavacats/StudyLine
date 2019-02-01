// Fill out your copyright notice in the Description page of Project Settings.

#include "P2PlayerController.h"

void AP2PlayerController::BeginPlay()
{
}

AP2PlayerController::AP2PlayerController()
{
	p2PlayerCameraManager = CreateDefaultSubobject<AP2PlayerCameraManager>(TEXT("p2PlayerCameraManager"));

}

void AP2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis(TEXT("MoveForwardBack"), this, &AP2PlayerController::ForwardBack);
	InputComponent->BindAxis(TEXT("MoveLeftRight"), this, &AP2PlayerController::LeftRight);



	/*InputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Pressed, this, &APractice1Character::RunToWalk);
	InputComponent->BindAction(TEXT("Walk"), EInputEvent::IE_Released, this, &APractice1Character::Stop);
*/
}

void AP2PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AP2PlayerController::Possess(APawn * aPawn)
{
	Super::Possess(aPawn);
	p2PlayerCharacter = Cast< APlayerCharacter>(aPawn);
	p2PlayerCameraManager->SetRootComponentSpringArm(p2PlayerCharacter->GetMesh());
	PlayerCameraManager = p2PlayerCameraManager;
}

void AP2PlayerController::ForwardBack(float NewAxisValue)
{
	p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AP2PlayerController::LeftRight(float NewAxisValue)
{
	p2PlayerCharacter->AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AP2PlayerController::LookUpDown(float NewAxisValue)
{
	p2PlayerCharacter->AddControllerPitchInput(NewAxisValue);
}

void AP2PlayerController::Turn(float NewAxisValue)
{
	p2PlayerCharacter->AddControllerYawInput(NewAxisValue);
}
