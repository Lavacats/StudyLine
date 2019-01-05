 // Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameMode.h"

AABGameMode::AABGameMode()
{
	//DefaultPawnClass = AABPawn::StaticClass();
	DefaultPawnClass = AABCharacter::StaticClass();

	// ���͸� �����ϴ� �� �ƴ϶� Ŭ������ �����Ѵ�
	// -> �� ���� �÷��̾ ������ �𸣱� ������, 
	//    Ŭ������ ������ �����ϰ�, ������ �� ���� Ŭ���� ������ ������� ����
	//    �𸮾� ������Ʈ���� ������ StaticClass �Լ��� ���� �����ɴϴ�.

	PlayerControllerClass = AABPlayerController::StaticClass();

	//��� ����Ʈ�� ���۵� ���� C++���� �ҷ����� ���
	//static ConstructorHelpers::FClassFinder<APawn> BP_PAWN_C(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C"));
	//��� ����Ʈ�� �ּ��� Ŭ���� ������ �Ѱ��ݴϴ�.
	//Ŭ���� ������ �ּ� ��ο� '_C' ���̻縦 �ٿ��� ������ �� �ֽ��ϴ�.
	//FClassFinder�� ����� Ŭ������ ������ �����ɴϴ�.
}

void AABGameMode::PostLogin(APlayerController * NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	// ������ Pawn�� �����ϰ� �÷��̾� ��Ʈ�ѷ��� �����Ѵ�.
	ABLOG(Warning, TEXT("PostLogin End"));
}
