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

	// 액터를 지정하는 게 아니라 클래스를 지정한다
	// -> 몇 명의 플레이어가 있을지 모르기 떄문에, 
	//    클래스의 정보만 저장하고, 생성할 때 마다 클래스 정보를 기반으로 생성
	//    언리어 오브젝트마다 생성된 StaticClass 함수를 통해 가져옵니다.

	PlayerControllerClass = AABPlayerController::StaticClass();

	//블루 프린트로 제작된 폰을 C++에서 불러오는 방법
	//static ConstructorHelpers::FClassFinder<APawn> BP_PAWN_C(TEXT("/Game/ThirdPersonBP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C"));
	//블루 프린트의 애셋의 클래스 정보를 넘겨줍니다.
	//클래스 정보는 애셋 경로에 '_C' 접미사를 붙여서 가져올 수 있습니다.
	//FClassFinder를 사용해 클래스의 정보를 가져옵니다.

	PlayerStateClass = AABPlayerState::StaticClass();
	// 플레이어의 스태틱 클래스에 플레이어 스테이트의 값을 가져옵니다.

	GameStateClass = AABGameState::StaticClass();
	// 게임 스테틱의 값을 변수에 넣습니다
}

void AABGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABGameState = Cast<AABGameState>(GameState);
	// ABGameState를 가져옵니다.
}

void AABGameMode::PostLogin(APlayerController * NewPlayer)
{
	//ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	// 조종할 Pawn을 생성하고 플레이어 컨트롤러가 빙의한다.
	//ABLOG(Warning, TEXT("PostLogin End"));

	auto ABPlayerState = Cast<AABPlayerState>(NewPlayer->PlayerState);
	// ABPlayerState를 AABPlayerState에서 가져옵ㄴ다
	ABCHECK(nullptr != ABPlayerState);
	// 가져오는데 실패해다면 오류 로그를 출력합니다
	ABPlayerState->InitPlayerData();
	// ABPlayerState의 InitPlayerData()함수를 실행합니다.

	// PostLogin은 플레이어 컨트롤러의 구성을 완료하는 시점의 함수이므로 이때 함께
	// ABPlayerState의 초기화도 완료해주는것이 좋다

	GameStateClass = AABGameState::StaticClass();
	// 게임 스테티트 클래스를 가져옵니다.
}

void AABGameMode::AddScore(AABPlayerController * Player)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
		// 월드에 있는 플레이어 컨트롤러 모두검사합니다

		const auto ABPlayerController = Cast<AABPlayerController>(It->Get());
		// ABPlaterConterller에
		if ((nullptr != ABPlayerController) && (Player == ABPlayerController)) {
			// ABPlayerController가 있고, 플레이어가 가지고있다면
			ABPlayerController->AddGameScore();
			// 점수를 더합니다
			break;
		}
	}
	ABGameState->AddGameScore();
	// 게임 전체 점수에 1점 가산합니다.(모든 플레이어 합계)
}
