// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SpikeTrapItem.h"

ASpikeTrapItem::ASpikeTrapItem()
{
	DmgAmount = 20;
	ItemName = TEXT("SpikeTrapItem");
}

void ASpikeTrapItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

}
