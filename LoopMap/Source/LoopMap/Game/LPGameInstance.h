#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LPGameInstance.generated.h"

UCLASS()
class LOOPMAP_API ULPGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	ULPGameInstance();

	void SetTotalScore(int InStateScore);
	int32 GetTotalScore();

	void SetCurrentLevel(int InStateLevel);
	int32 GetCurrentLeve1();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TotalState")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TotalState")
	int32 CurrentLevel;
};
