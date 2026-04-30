#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class LOOPMAP_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetTimeText(float InTime);
	void SetRunLengthText(int32 InLength);
	void SetCollectCoinText(int32 InCoinCount);
	void SetHealthProgressBar(int32 InCurrentHP, int32 MaxHP);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeTextBlock;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RunLengthBlock;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CollectCoinTextBlock;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

};
