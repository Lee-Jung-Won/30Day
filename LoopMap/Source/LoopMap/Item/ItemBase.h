#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/LPItemInterface.h"
#include "ItemBase.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class USphereComponent;
class UNiagaraSystem;
class USoundWave;

UCLASS()
class LOOPMAP_API AItemBase 
	: public AActor
	, public ILPItemInterface
{
	GENERATED_BODY()
	
public:
	AItemBase();
	FName ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USphereComponent> MagnetSphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UNiagaraSystem> NiagaraSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USoundWave> SoundWave;

	//======================================================================
	UPROPERTY()
	FVector SpawnLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spin")
	float UpDownSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spin")
	float UpDownRange;

protected:

	virtual void OnItemOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	virtual void OnItemEndOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	 
	//=============================================
	//Magnatic
	virtual void OnMagnetBoundOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	FTimerHandle MoveToActorTick;
	AActor* TargetOneActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
	float MoveToActorSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
	float AccMoveToActorSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magnet")
	float MaxMoveToActorSpeed;
	bool setgo;

	void MoveToActorMagneticLogic(float DeltaSeconds);
	//=============================================

	void UpDown_RotateMoveLogic(float DeltaSeconds);
	//=============================================

	virtual void ActivateItem(AActor* Activator) override;
	virtual void DestroyItem();

	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
};
