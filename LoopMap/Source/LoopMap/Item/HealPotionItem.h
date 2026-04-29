#pragma once

#include "CoreMinimal.h"
#include "Item/PotionItem.h"
#include "HealPotionItem.generated.h"

UCLASS()
class LOOPMAP_API AHealPotionItem : public APotionItem
{
	GENERATED_BODY()
public:
	AHealPotionItem();
	virtual void ActivateItem(AActor* Activator) override;
};
