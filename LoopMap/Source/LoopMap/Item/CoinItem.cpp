#include "Item/CoinItem.h"

ACoinItem::ACoinItem()
{
	AddScore = 0;
	ItemName = ItemName = TEXT("CoinItem");
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	//Super::ActivateItem(Activator);
	UE_LOG(LogTemp, Warning, TEXT("CoinItem Activate"));
	if (Activator && Activator->ActorHasTag("Player"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Score Add: %d"), AddScore);

		DestroyItem();
	}
}
