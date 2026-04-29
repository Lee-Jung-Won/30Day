#include "Item/TrapItem.h"
#include "Kismet/GameplayStatics.h"
ATrapItem::ATrapItem()
{
	PrimaryActorTick.bCanEverTick = false;

	DmgAmount = 30;
	ItemName = TEXT("TrapItem");
}

void ATrapItem::OnMagnetBoundOverLap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	//None Move

}

void ATrapItem::ActivateItem(AActor* Activator)
{
	//Super::ActivateItem(Activator);
	UE_LOG(LogTemp, Warning, TEXT("TrapItem Activate"));
	if (Activator && Activator->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(
			Activator,
			DmgAmount,
			nullptr,
			this,
			UDamageType::StaticClass()
		);
	}
	DestroyItem();
}
