#include "Game/LPGameInstance.h"

ULPGameInstance::ULPGameInstance()
{
	TotalScore = 0;
	CurrentLevel = 1;
}

void ULPGameInstance::SetTotalScore(int InStateScore)
{
	TotalScore += InStateScore;
}

int32 ULPGameInstance::GetTotalScore()
{
	return TotalScore;
}

void ULPGameInstance::SetCurrentLevel(int InStateLevel)
{
	CurrentLevel = InStateLevel;
}

int32 ULPGameInstance::GetCurrentLeve1()
{
	return CurrentLevel;
}
