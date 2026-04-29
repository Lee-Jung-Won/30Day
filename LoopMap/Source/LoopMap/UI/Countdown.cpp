#include "UI/Countdown.h"
#include "Components/TextBlock.h"

void UCountdown::SetCountdownText(const FString& InText)
{
	if (CountdownText)
	{
		CountdownText->SetText(FText::FromString(InText));
	}
}

