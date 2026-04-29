#include "Game/LPGameState.h"
#include "Game/LPGameInstance.h"
ALPGameState::ALPGameState()
{
	CurrentLevelIndex = 1;
	MaxLevelIndex = 3;
	CurrentWaveIndex = 1;
	MaxWaveIndex = 3;
	StateScore = 0;

	GameStateMaxTime = 60.f;
}

int32 ALPGameState::GetStateScore() const
{
	return StateScore;
}

void ALPGameState::AddStateScore(int32 Amount)
{
	StateScore += Amount;
}

void ALPGameState::StartLevel()
{
	// 필요하면 3초타이머 써서 true
	// tilemanager bIsGameStarted = true
}

void ALPGameState::BeginPlay()
{
	Super::BeginPlay();
	// instance저장된 정보 불러오기
	ULPGameInstance* GameInstance = Cast<ULPGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		CurrentLevelIndex = GameInstance->GetCurrentLeve1();
	}
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
