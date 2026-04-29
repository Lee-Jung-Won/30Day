#include "Item/PotionItem.h"

APotionItem::APotionItem()
{
	AddAmount = 0;
	ItemName = TEXT("PotionItem");
}

void APotionItem::ActivateItem(AActor* Activator)
{
	//Super::ActivateItem(Activator);
	UE_LOG(LogTemp, Warning, TEXT("Activate PotionItem"));
}
