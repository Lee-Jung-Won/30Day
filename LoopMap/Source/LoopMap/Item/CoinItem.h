#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "CoinItem.generated.h"

UCLASS()
class LOOPMAP_API ACoinItem : public AItemBase
{
	GENERATED_BODY()
public:
	ACoinItem();
	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HPpotion")
	int32 AddScore;
};
