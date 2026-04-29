#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LPItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class ULPItemInterface : public UInterface
{
	GENERATED_BODY()
};

class LOOPMAP_API ILPItemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnItemOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;
	UFUNCTION()
	virtual void OnItemEndOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;

	UFUNCTION()
	virtual void OnMagnetBoundOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;

	virtual void ActivateItem(AActor* Activator) = 0;

};
