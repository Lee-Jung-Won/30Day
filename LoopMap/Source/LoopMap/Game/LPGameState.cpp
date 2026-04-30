#include "Game/LPGameState.h"
#include "Game/LPGameInstance.h"
#include "Controller/LPPlayerController.h"
#include "Character/PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "UI/InGameWidget.h"
#include "Components/TextBlock.h"

ALPGameState::ALPGameState()
{
	CurrentLevelIndex = 1;
	MaxLevelIndex = 3;
	CurrentWaveIndex = 1;
	MaxWaveIndex = 3;
	StateScore = 0;
	RunningLengthScore = 0;
	PlayerCollectCoinCount = 0;

	GameStateMaxTime = 15.f;
}

//int32 ALPGameState::GetStateScore() const
//{
//	return StateScore;
//}

void ALPGameState::AddStateScore(int32 Amount)
{
	// �������� ������ �־ ���ھ� ���ϴ±迡 ��������
	StateScore += Amount;
	PlayerCollectCoinCount++;
}

void ALPGameState::StartLevel()
{

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (ALPPlayerController* LPPlayerController = Cast<ALPPlayerController>(PC))
		{
			LPPlayerController->ShowGameHUD();
		}
	}
	// instance����� ���� �ҷ�����
	ULPGameInstance* GameInstance = Cast<ULPGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		CurrentLevelIndex = GameInstance->GetCurrentLeve1();
	}

	GetWorldTimerManager().SetTimer(
		GameStateTimer,
		this,
		&ALPGameState::EndLevel,
		GameStateMaxTime,
		false
	);
	GetWorldTimerManager().SetTimer(
		UpdateHUDTimer,
		this,
		&ALPGameState::UpdateHUD,
		0.1f,
		true
	);
	// �ʿ��ϸ� 3��Ÿ�̸� �Ἥ true
	// tilemanager bIsGameStarted = true
}

void ALPGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(GameStateTimer);
	GetWorldTimerManager().ClearTimer(UpdateHUDTimer);
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (ALPPlayerController* LPPlayerController = Cast<ALPPlayerController>(PC))
		{

			LPPlayerController->SetPause(true);
			LPPlayerController->ShowMainMenu(true, 1);

		}
	}
}

void ALPGameState::BeginPlay()
{
	Super::BeginPlay();

	FString MapName = GetWorld()->GetName();
	if (!MapName.Contains(TEXT("MenuLevel")))
	{
		GetWorldTimerManager().SetTimer(
			ThreeSecondsTimer,
			this,
			&ALPGameState::StartLevel,
			3.f,
			false
		);
	}
	//StartLevel();
}

void ALPGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	ULPGameInstance* GameInstance = Cast<ULPGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->SetCurrentLevel(CurrentLevelIndex + 1);
		GameInstance->SetTotalScore(StateScore);
	}
}

void ALPGameState::UpdateHUD()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (ALPPlayerController* LPPlayerController = Cast<ALPPlayerController>(PC))
		{
			if (UUserWidget* HUDWidget = LPPlayerController->GetHUDWidget())
			{
				if (UInGameWidget* InGameWidget = Cast<UInGameWidget>(HUDWidget))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(GameStateTimer);
					InGameWidget->SetTimeText(RemainingTime);

					RunningLengthScore += GameStateMaxTime - RemainingTime;
					InGameWidget->SetRunLengthText(RunningLengthScore);

					InGameWidget->SetCollectCoinText(PlayerCollectCoinCount);

					if (APlayerCharacter* Player = Cast<APlayerCharacter>(LPPlayerController->GetPawn()))
					{
						InGameWidget->SetHealthProgressBar(Player->CurrentHP, Player->MaxHP);

					}
				}
			}
		}

	}
}
