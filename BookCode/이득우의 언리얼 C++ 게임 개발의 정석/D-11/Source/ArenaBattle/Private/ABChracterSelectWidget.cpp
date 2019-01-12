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
	// bForward�� ture�̸� CurrentIndex���� 1���ϰ� false�̸� 1�� ����.

	if (CurrentIndex == -1)CurrentIndex = MaxIndex - 1;
	// CurrentIndex�� -1�̶�� CurrnetIndex�� �ִ� �ε��� -1�� ���� ������
	if (CurrentIndex == MaxIndex)CurrentIndex = 0;
	// CurrentIndex�� MaxIndex��� CurrentIndex�� 0���� �ٲپ��ش�.

	auto CharacterSetting = GetDefault<UABCharacterSetting>();
	// ĳ���� ������ ���� �η��ɴϴ�.
	auto AssetRef = CharacterSetting->CharacterAssets[CurrentIndex];
	// AssetRef ĳ���� ������ ���� �ε����� ���� �ҷ��ɴϴ�.

	auto ABGameInstance = GetWorld()->GetGameInstance<UABGameInstance>();
	// ���� ���� �����ν�ź�� Ŭ���� ���� �����ɴϴ�.
	ABCHECK(nullptr != ABGameInstance);
	ABCHECK(TargetComponent.IsValid());
	// GameInstance���� �ִ��� Ȯ���ϰ�, Ÿ���� �ִ��� Ȯ���մϴ�.

	USkeletalMesh* Asset = ABGameInstance->StreamableManager.LoadSynchronous<USkeletalMesh>(AssetRef);
	// Asset�� �ҷ��� ���̷�Ż �޽ø� �����մϴ�.
	if (nullptr != Asset) {
		TargetComponent->SetSkeletalMesh(Asset);
		// Asset�� ���������� �ҷ��ٸ� Ÿ�ٿ� ���̷�Ż �޽ø� Asset���� �ٲߴϴ�
	}
}

void UABChracterSelectWidget::NativeConstruct()
{
	Super:: NativeConstruct();

	CurrentIndex = 0;
	// �ε������� 0���� �ݴϴ�.
	auto CharacterSetting = GetDefault<UABCharacterSetting>();
	// ĳ���� ���� Ŭ������ �η��ɴϴ�
	MaxIndex = CharacterSetting->CharacterAssets.Num();
	// �ִ� �ε����� ĳ���� ������ ������ �����ɴϴ�

	for (TActorIterator<ASkeletalMeshActor>It(GetWorld()); It; ++It) {
		TargetComponent = It->GetSkeletalMeshComponent();
		// Ÿ�� ������Ʈ�� �����մϴ�.
		// ������ Actor�� Ȯ���Ͽ� �߰��ϸ� break
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
	// ������ ��ưŬ������ �ҷ��µ� ����� �ҷ��������� Ȯ���մϴ�.

	PrevButton->OnClicked.AddDynamic(this, &UABChracterSelectWidget::OnPrevClicked);
	NextButton->OnClicked.AddDynamic(this, &UABChracterSelectWidget::OnNextClicked);
	ConfirmButton->OnClicked.AddDynamic(this, &UABChracterSelectWidget::OnConfirmClicked);
	// ��ư Ŭ���Լ��� �Լ��� �߰��մϴ�.
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
	// ĳ���� �̸��� �ؽ�Ʈ �ڽ����� �����ɴϴ�.
	if (CharacterName.Len() <= 0 || CharacterName.Len() > 10)return;
	// ĳ�����̸��� 0���� �ڰų� ���ų� 10���� Ŭ��� �Լ��� �����մϴ�.

	UABSaveGame* NewPlayerData = NewObject<UABSaveGame>();
	NewPlayerData->PlayerName = CharacterName;
	NewPlayerData->Level = 1;
	NewPlayerData->Exp = 0;
	NewPlayerData->HighScore = 0;
	NewPlayerData->CharacterIndex = CurrentIndex;
	// �÷��̾� ���̺� ������ ������ ����� �ʱ� ���� �Է��մϴ�.

	auto ABPlayerState = GetDefault<AABPlayerState>();
	// ABPlayerState���� �ҷ��ɴϴ�.
	if (UGameplayStatics::SaveGameToSlot(NewPlayerData, ABPlayerState->SaveSlotName, 0)){
		// ���� �̸��� �ִ� ���Կ� ������ִ� ���� �ҷ��ɴϴ�.
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Gameplay"));
		// Gameplay ������ �ҷ��� ���ϴ�.
	}
	else{
		ABLOG(Error, TEXT("SaveGame Error!"));
	}
}
