// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingTile.generated.h"

class USceneComponent;
class UStaticMeshComponent;


UCLASS()
class LOOPMAP_API AMovingTile : public AActor
{
	GENERATED_BODY()

public:

	AMovingTile();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TileMesh;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 600.0f;*/
	//만약 타일마다 속도를 다르게해 piano tile같은 게임을 만들고 싶으면 속도를 추가
};
