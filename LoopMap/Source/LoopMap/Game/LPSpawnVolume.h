#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "LPSpawnVolume.generated.h"

class USceneComponent;
class UBoxComponent;

UCLASS()
class LOOPMAP_API ALPSpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ALPSpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FVector SquareSizeInVolume;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TObjectPtr<UDataTable> ItemDataTable;

	TArray<UClass*> GetRandomItem(int32 HowMany);//랜덤아이템정의 Getter
	void SpawnItem(); //아이템정보받아서스폰만
	TArray<FVector> GetCalculatedPositionInVolume(); //좌표뭉치

	virtual void BeginPlay() override;
};
