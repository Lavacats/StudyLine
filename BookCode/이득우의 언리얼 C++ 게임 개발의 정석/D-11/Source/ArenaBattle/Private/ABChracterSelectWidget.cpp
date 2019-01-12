// Fill out your copyright notice in the Description page of Project Settings.

#include "ABChracterSelectWidget.h"
#include "ABCharacterSetting.h"
#include "ABGameInstance.h"
#include "EngineUtils.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "ABSaveGame.h"
#include "ABPlayerState.h"

void UABChracterSelectWidget::NextCharacter(bool bForward)
{
	bForward ? CurrentIndex++ : CurrentIndex--;
	// bForward가 ture이면 CurrentIndex값을 1더하고 false이면 1을 뺀다.

	if (CurrentIndex == -1)CurrentIndex = MaxIndex - 1;
	// CurrentIndex가 -1이라면 CurrnetIndex는 최대 인덱스 -1의 값을 가진다
	if (CurrentIndex == MaxIndex)CurrentIndex = 0;
	// CurrentIndex가 MaxIndex라면 CurrentIndex를 0으로 바꾸어준다.

	auto CharacterSetting = GetDefault<UABCharacterSetting>();
	// 캐릭터 세팅의 값을 부러옵니다.
	auto AssetRef = CharacterSetting->CharacterAssets[CurrentIndex];
	// AssetRef 캐릭터 에셋의 값을 인덱스에 따라 불러옵니다.

	auto ABGameInstance = GetWorld()->GetGameInstance<UABGameInstance>();
	// 월드 에서 게임인스탄스 클래스 값을 가져옵니다.
	ABCHECK(nullptr != ABGameInstance);
	ABCHECK(TargetComponent.IsValid());
	// GameInstance값이 있는지 확인하고, 타겟이 있는지 확인합니다.

	USkeletalMesh* Asset = ABGameInstance->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);
	// Asset에 불러온 스켈레탈 메시를 저장합니다.
	if (nullptr != Asset) {
		TargetComponent->SetSkeletalMesh(Asset);
		// Asset이 정상적으로 불렀다면 타겟에 스켈레탈 메시를 Asset으로 바꿉니다
	}
}

void UABChracterSelectWidget::NativeConstruct()
{
	Super:: NativeConstruct();

	CurrentIndex = 0;
	// 인덱스값을 0으로 줍니다.
	auto CharacterSetting = GetDefault<UABCharacterSetting>();
	// 캐릭터 세팅 클래스를 부러옵니다
	MaxIndex = CharacterSetting->CharacterAssets.Num();
	// 최대 인덱스는 캐릭터 세팅의 값에서 가져옵니다

	for (TActorIterator<ASkeletalMeshActor>It(GetWorld()); It; ++It) {
		TargetComponent = It->GetSkeletalMeshComponent();
		// 타겟 컴포넌트를 결정합니다.
		// 월드의 Actor를 확인하여 발견하면 break
		break;
	}

	PrevButton = Cast<UButton>(GetWidgetFromName(TEXT("btnPrev")));
	ABCHECK(nullptr != PrevButton);

	NextButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNext")));
	ABCHECK(nullptr != NextButton);

	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("edtPlayerName")));
	ABCHECK(nullptr != TextBox);

	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("btnConfirm")));
	ABCHECK(nullptr != ConfirmButton);
	// 각각의 버튼클래스르 불러온뒤 제대로 불러와졌는지 확인합니다.

	PrevButton->OnClicked.AddDynamic(this, &UABChracterSelectWidget::OnPrevClicked);
	NextButton->OnClicked.AddDynamic(this, &UABChracterSelectWidget::OnNextClicked);
	ConfirmButton->OnClicked.AddDynamic(this, &UABChracterSelectWidget::OnConfirmClicked);
	// 버튼 클릭함수에 함수를 추가합니다.
}

void UABChracterSelectWidget::OnPrevClicked()
{
	NextCharacter(false);
}

void UABChracterSelectWidget::OnNextClicked()
{
	NextCharacter(true);
}

void UABChracterSelectWidget::OnConfirmClicked()
{
	FString CharacterName = TextBox->GetText().ToString();
	// 캐릭터 이름을 텍스트 박스에서 가져옵니다.
	if (CharacterName.Len() <= 0 || CharacterName.Len() > 10)return;
	// 캐릭터이름이 0보다 자거나 같거나 10보다 클경우 함수를 종료합니다.

	UABSaveGame* NewPlayerData = NewObject<UABSaveGame>();
	NewPlayerData->PlayerName = CharacterName;
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->HighScore = 0;
	NewPlayerData->CharacterIndex = CurrentIndex;
	// 플레이어 세이브 데이터 변수를 만들어 초기 값을 입력합니다.

	auto ABPlayerState = GetDefault<AABPlayerState>();
	// ABPlayerState값을 불러옵니다.
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, ABPlayerState->SaveSlotName, 0)){
		// 슬롯 이름에 있는 슬롯에 저장되있는 값을 불러옵니다.
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Gameplay"));
		// Gameplay 레벨을 불러와 엽니다.
	}
	else{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
}
