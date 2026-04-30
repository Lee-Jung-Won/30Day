#include "UI/InGameWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UInGameWidget::SetTimeText(float InTime)
{
	if (TimeTextBlock)
	{
		TimeTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), InTime)));
	}
}

void UInGameWidget::SetRunLengthText(int32 InLength)
{
	if (RunLengthBlock)
	{
		RunLengthBlock->SetText(FText::FromString(FString::Printf(TEXT("%03d"), InLength)));
	}
}

void UInGameWidget::SetCollectCoinText(int32 InCoinCount)
{
	if (CollectCoinTextBlock)
	{
		CollectCoinTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%02d"), InCoinCount)));
	}
}

void UInGameWidget::SetHealthProgressBar(int32 InCurrentHP, int32 MaxHP)
{
	if (HealthProgressBar && MaxHP > 0.f)
	{
		const float Percent = FMath::Clamp(static_cast<float>(InCurrentHP) / static_cast<float>(MaxHP), 0.0f, 1.0f);
		HealthProgressBar->SetPercent(Percent);
	}
}
