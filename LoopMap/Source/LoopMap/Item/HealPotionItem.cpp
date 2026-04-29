#include "Item/HealPotionItem.h"

AHealPotionItem::AHealPotionItem()
{
	AddAmount = 25;
	ItemName = TEXT("HealPotionItem");
}

void AHealPotionItem::ActivateItem(AActor* Activator)
{
	//Super::ActivateItem(Activator);
	UE_LOG(LogTemp, Warning, TEXT("Activate HPpotionItem"));
	if (Activator && Activator->ActorHasTag("Player"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Destoryed"));
		DestroyItem();
	}
}
