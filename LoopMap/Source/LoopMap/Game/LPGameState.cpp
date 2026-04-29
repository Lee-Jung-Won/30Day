#include "Game/LPGameState.h"
#include "Game/LPGameInstance.h"
ALPGameState::ALPGameState()
{
	CurrentLevelIndex = 1;
	MaxLevelIndex = 3;
	CurrentWaveIndex = 1;
	MaxWaveIndex = 3;
	StateScore = 0;

}

void ALPGameState::BeginPlay()
{
	Super::BeginPlay();
	ULPGameInstance* GameInstance = Cast<ULPGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		CurrentLevelIndex = GameInstance->GetCurrentLeve1();
	}
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
