// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileManager.generated.h"

class AMovingTile;
class UCountdown;//UI
class ALPSpawnVolume;

UCLASS()
class LOOPMAP_API ATileManager : public AActor
{
	GENERATED_BODY()

public:

	ATileManager();

	virtual void Tick(float DeltaTime) override;

	void SetFloorMoveSpeed(float InSpeed);

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

	void StartGame();//시작 카운트 다운을 위한 게임 시작 함수

	void CountdownTick();
	void RemoveCountdown();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AMovingTile>> TileClasses;//랜덤 타일 생성을 위한 타일 배열

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile|Spawn", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ALPSpawnVolume> LPSpawnVolumeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	int32 InitialTileCount = 10;//기본적으로 스폰되는 타일 개수, 매쉬 길이봐서 더 줄여도 될듯

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float TileLength = 1284.0f;//제일 중요한 변수, 여기가 안맞으면 타일이 끊어져 보임,, 매쉬 길이와 똑같게 유지

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 700.0f;//이동 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float SpawnX = 11556.0f;//매쉬에 따라 수정해야할 부분 10번째 중 9번째 타일 시작

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float DestroyX = -3000.0f;//트리거 역할, X좌표가 -1500이하로 떨어진 타일은 삭제

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	float NextSpawnX = 0.0f;//트리거 역할, X좌표가 0이하로 떨어지면 새 타일 생성

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<AMovingTile>> SpawnedTiles;//타일을 담는 배열

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "true"))
	float SpeedIncreasePerSecond = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "true"))
	float MaxMoveSpeed = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug", meta = (AllowPrivateAccess = "true"))
	float SpeedLogTimer = 0.0f;

	UPROPERTY()
	TArray<AActor*> SpawnedItems;
	UPROPERTY()
	TArray<AActor*> TotalSpawnedItems;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game", meta = (AllowPrivateAccess = "true"))
	bool bIsGameStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCountdown> CountdownClass;

	UPROPERTY()
	TObjectPtr<UCountdown> Countdown;

	int32 CountdownNumber = 3;

	FTimerHandle CountdownTimerHandle;
	FTimerHandle RemoveCountdownTimerHandle;
	FTimerHandle StartGameTimerHandle;
	//아이템 먹고 이동속도 증가한다면 여기에 AddSpeed같은 함수 추가
};
