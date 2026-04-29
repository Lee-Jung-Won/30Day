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
	UPROPERTY()
	int32 CurrentLevelIndex;
	UPROPERTY()
	int32 MaxLevelIndex;
	UPROPERTY()
	int32 CurrentWaveIndex;
	UPROPERTY()
	int32 MaxWaveIndex;

	FTimerHandle GameStateTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StageTime")
	float GameStateMaxTime;

	UPROPERTY()
	int32 StateScore;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetStateScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddStateScore(int32 Amount);

public:
	void StartLevel();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
