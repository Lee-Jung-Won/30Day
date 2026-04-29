#include "Item/CoinItem.h"
#include "Game/LPGameState.h"
#include "Engine/World.h"
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
		if (UWorld* World = GetWorld())
		{
			if (ALPGameState* GameState = GetWorld()->GetGameState<ALPGameState>())
			{
				GameState->AddStateScore(AddScore);
			}
		}
		DestroyItem();
	}
}
