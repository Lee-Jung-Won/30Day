#include "Item/SpeedPotionItem.h"
#include "Character/PlayerCharacter.h"
ASpeedPotionItem::ASpeedPotionItem()
{
	AddAmount = 200;
	ItemName = TEXT("SpeedPotionItem");
}

void ASpeedPotionItem::ActivateItem(AActor* Activator)
{
	//Super::ActivateItem(Activator);
	UE_LOG(LogTemp, Warning, TEXT("Activate SpeedpotionItem"));
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(Activator))
		{
			Player->SetCurrentSpeed(AddAmount);
		}
		DestroyItem();
	}
}
