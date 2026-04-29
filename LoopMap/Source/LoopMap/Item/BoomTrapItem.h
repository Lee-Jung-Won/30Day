#pragma once

#include "CoreMinimal.h"
#include "Item/TrapItem.h"
#include "BoomTrapItem.generated.h"



UCLASS()
class LOOPMAP_API ABoomTrapItem : public ATrapItem
{
	GENERATED_BODY()
public:
	ABoomTrapItem();


	virtual void OnMagnetBoundOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	virtual void OnItemOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	FTimerHandle ExplodeTimerHandle;
	void Explode();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boom")
	float BoomInterval;

protected:

	virtual void ActivateItem(AActor* Activator) override;
};
