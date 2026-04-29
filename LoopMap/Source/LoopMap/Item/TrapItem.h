#pragma once

#include "CoreMinimal.h"
#include "Item/ItemBase.h"
#include "TrapItem.generated.h"

UCLASS()
class LOOPMAP_API ATrapItem : public AItemBase
{
	GENERATED_BODY()
public:
	ATrapItem();

	virtual void OnMagnetBoundOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	
	virtual void ActivateItem(AActor* Activator) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrapItemInfo")
	int32 DmgAmount;


};
