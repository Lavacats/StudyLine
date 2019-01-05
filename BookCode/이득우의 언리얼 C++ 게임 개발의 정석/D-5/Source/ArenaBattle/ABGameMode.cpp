 // Fill out your copyright notice in the Description page of Project Settings.

#include "ABGameMode.h"

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
}

void AABGameMode::PostLogin(APlayerController * NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	// 조종할 Pawn을 생성하고 플레이어 컨트롤러가 빙의한다.
	ABLOG(Warning, TEXT("PostLogin End"));
}
