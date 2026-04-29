#pragma once

#include "CoreMinimal.h"
#include "Item/PotionItem.h"
#include "SpeedPotionItem.generated.h"

UCLASS()
class LOOPMAP_API ASpeedPotionItem : public APotionItem
{
	GENERATED_BODY()
public:
	ASpeedPotionItem();
	virtual void ActivateItem(AActor* Activator) override;

};
