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

	GameStateMaxTime = 60.f;
}

//int32 ALPGameState::GetStateScore() const
//{
//	return StateScore;
//}

void ALPGameState::AddStateScore(int32 Amount)
{
	// 동전에만 점수가 있어서 스코어 더하는김에 갯수까지
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
	// instance저장된 정보 불러오기
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
	// 필요하면 3초타이머 써서 true
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
			
			LPPlayerController->ShowMainMenu(true);
		}
	}
}

void ALPGameState::BeginPlay()
{
	Super::BeginPlay();

	// 게임시작
	StartLevel();
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
