 // Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameMode.h"
#include "ABCharacter.h"
#include "ABPlayerController.h"
#include "ABPlayerState.h"
#include "ABGameState.h"

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

	PlayerStateClass = AABPlayerState::StaticClass();
	// �÷��̾��� ����ƽ Ŭ������ �÷��̾� ������Ʈ�� ���� �����ɴϴ�.

	GameStateClass = AABGameState::StaticClass();
	// ���� ����ƽ�� ���� ������ �ֽ��ϴ�
}

void AABGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABGameState = Cast<AABGameState>(GameState);
	// ABGameState�� �����ɴϴ�.
}

void AABGameMode::PostLogin(APlayerController * NewPlayer)
{
	//ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	// ������ Pawn�� �����ϰ� �÷��̾� ��Ʈ�ѷ��� �����Ѵ�.
	//ABLOG(Warning, TEXT("PostLogin End"));

	auto ABPlayerState = Cast<AABPlayerState>(NewPlayer->PlayerState);
	// ABPlayerState�� AABPlayerState���� �����ɤ���
	ABCHECK(nullptr != ABPlayerState);
	// �������µ� �����شٸ� ���� �α׸� ����մϴ�
	ABPlayerState->InitPlayerData();
	// ABPlayerState�� InitPlayerData()�Լ��� �����մϴ�.

	// PostLogin�� �÷��̾� ��Ʈ�ѷ��� ������ �Ϸ��ϴ� ������ �Լ��̹Ƿ� �̶� �Բ�
	// ABPlayerState�� �ʱ�ȭ�� �Ϸ����ִ°��� ����

	GameStateClass = AABGameState::StaticClass();
	// ���� ����ƼƮ Ŭ������ �����ɴϴ�.
}

void AABGameMode::AddScore(AABPlayerController * Player)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
		// ���忡 �ִ� �÷��̾� ��Ʈ�ѷ� ��ΰ˻��մϴ�

		const auto ABPlayerController = Cast<AABPlayerController>(It->Get());
		// ABPlaterConterller��
		if ((nullptr != ABPlayerController) && (Player == ABPlayerController)) {
			// ABPlayerController�� �ְ�, �÷��̾ �������ִٸ�
			ABPlayerController->AddGameScore();
			// ������ ���մϴ�
			break;
		}
	}
	ABGameState->AddGameScore();
	// ���� ��ü ������ 1�� �����մϴ�.(��� �÷��̾� �հ�)
}
