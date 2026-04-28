// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileManager.generated.h"

class AMovingTile;

UCLASS()
class LOOPMAP_API ATileManager : public AActor
{
	GENERATED_BODY()

public:

	ATileManager();

	virtual void Tick(float DeltaTime) override;



	//아래는 나중에 아이템 먹었을때 이속 변경에 쓸 함수
	/*UFUNCTION(BluprintCallable, Category = "Tile")
	void SetMoveSpeed(float NewMoveSpeed);

	UFUNCTION(BluprintCallable, Category = "Tile")
	float GetMoveSpeed() const;*/

protected:

	virtual void BeginPlay() override;

private:
	void SpawnTile(); //타일 생성하는 함수
	void MoveTiles(float DeltaTime); //타일 움직이는 함수
	void RemoveOldTiles(); //타일 없애는 함수

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMovingTile> TileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	int32 InitialTileCount = 6;//기본적으로 유지되는 타일 개수, 매쉬 길이봐서 더 줄여도 될듯

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float TileLength = 1284.0f;//제일 중요한 변수, 여기가 안맞으면 타일이 끊어져 보임,, 매쉬 길이와 똑같게 유지

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 600.0f;//이동 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float SpawnX = 6420.0f;//매쉬에 따라 수정해야할 부분 6번째 중 5번째 타일 시작

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float DestroyX = -1500.0f;//트리거 역할, X좌표가 -1500이하로 떨어진 타일은 삭제

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float NextSpawnX = 0.0f;//트리거 역할, X좌표가 0이하로 떨어지면 새 타일 생성

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AMovingTile>> SpawnedTiles;

	//아이템 먹고 이동속도 증가한다면 여기에 AddSpeed같은 함수 추가
};
