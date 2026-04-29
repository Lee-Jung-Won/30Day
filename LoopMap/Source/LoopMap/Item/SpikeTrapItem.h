#pragma once

#include "CoreMinimal.h"
#include "Item/TrapItem.h"
#include "SpikeTrapItem.generated.h"

UCLASS()
class LOOPMAP_API ASpikeTrapItem : public ATrapItem
{
	GENERATED_BODY()

public:
	ASpikeTrapItem();

protected:

	virtual void ActivateItem(AActor* Activator) override;
};
