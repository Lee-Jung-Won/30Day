// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BigCoinItem.h"

ABigCoinItem::ABigCoinItem()
{
	AddScore = 30;
	ItemName = TEXT("BigCoinItem");
}

void ABigCoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}
