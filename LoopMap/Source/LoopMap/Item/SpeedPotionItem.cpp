#include "Item/SpeedPotionItem.h"

ASpeedPotionItem::ASpeedPotionItem()
{
	AddAmount = 50;
	ItemName = TEXT("SpeedPotionItem");
}

void ASpeedPotionItem::ActivateItem(AActor* Activator)
{
	//Super::ActivateItem(Activator);
	UE_LOG(LogTemp, Warning, TEXT("Activate SpeedpotionItem"));
	if (Activator && Activator->ActorHasTag("Player"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Speed ++ , %d"), AddAmount);

		DestroyItem();
	}
}
