#include "Item/HealPotionItem.h"
#include "Character/PlayerCharacter.h"
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
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(Activator))
		{
			Player->SetCurrentHP(AddAmount);
		}
		DestroyItem();
	}
}
