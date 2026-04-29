// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SmallCoinItem.h"

ASmallCoinItem::ASmallCoinItem()
{
	AddScore = 15;
	ItemName = TEXT("SmallCoinItem");
}

void ASmallCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

}
