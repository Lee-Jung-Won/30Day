#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LPGameState.generated.h"

UCLASS()
class LOOPMAP_API ALPGameState : public AGameState
{
	GENERATED_BODY()
public:
	ALPGameState();

	int32 CurrentLevelIndex;
	int32 MaxLevelIndex;
	int32 CurrentWaveIndex;
	int32 MaxWaveIndex;

	FTimerHandle GameStateTimer;
	int32 StateScore;
public:

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
