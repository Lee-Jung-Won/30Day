#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "PotionItem.generated.h"

UCLASS()
class LOOPMAP_API APotionItem : public AItemBase
{
	GENERATED_BODY()
public:
	APotionItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HPpotion")
	int32 AddAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
