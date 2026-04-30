#include "Item/BoomTrapItem.h"
#include "Components/SphereComponent.h"
//#include "NiagaraFunctionLibrary.h"
//#include "Kismet/GameplayStatics.h"
ABoomTrapItem::ABoomTrapItem()
{
	DmgAmount = 50;
	BoomInterval = 2.f;
	ItemName = TEXT("BoomTrapItem");
}

void ABoomTrapItem::OnMagnetBoundOverLap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("MagnetBoundOverLapped: %s"), *OtherActor->GetName());
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GetWorldTimerManager().SetTimer(
			ExplodeTimerHandle,
			this,
			&ABoomTrapItem::Explode,
			BoomInterval,
			false
		);
	}
}

void ABoomTrapItem::OnItemOverLap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GetWorldTimerManager().ClearTimer(ExplodeTimerHandle);
		Explode();
	}
}

void ABoomTrapItem::Explode()
{

	TArray<AActor*> OverlappingActors;
	MagnetSphereComponent->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Boom Take Dmg: %d"), DmgAmount);
			ActivateItem(Actor);
		}
	}
	// �����ȿ� ��Ӱ��������� activateItem���� detroy1��
	// ���⼭ detroy2��
	DestroyItem();

}

void ABoomTrapItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	//explosioncollision = MagnetSphereComponent

}
