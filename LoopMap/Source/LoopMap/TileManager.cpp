// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "MovingTile.h"
#include "TimerManager.h"
#include "UI/Countdown.h"
#include "Blueprint/UserWidget.h"



// Sets default values
ATileManager::ATileManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();

	bIsGameStarted = false;//게임 시작 전
	CountdownNumber = 3;

	NextSpawnX = 0.0f;

	for (int32 i = 0; i < InitialTileCount; ++i)
	{
		SpawnTile();
	}
	if (CountdownClass)
	{
		Countdown = CreateWidget<UCountdown>(GetWorld(), CountdownClass);

		if (Countdown)
		{
			Countdown->AddToViewport();
			Countdown->SetCountdownText(TEXT("3"));//3 미리 띄워놓기
		}
	}
	GetWorldTimerManager().SetTimer( 
		CountdownTimerHandle,
		this,
		&ATileManager::CountdownTick,
		1.0f,
		true
	);
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsGameStarted)//카운트 다운 세는중
	{
		return;
	}

	MoveTiles(DeltaTime);

	NextSpawnX -= MoveSpeed * DeltaTime;//타일이 -x로 움직이기때문에 다음 생성 위치도 같이 움직여야함

	if (NextSpawnX <= SpawnX)
	{
		SpawnTile();
	}
	RemoveOldTiles();

}

void ATileManager::CountdownTick()
{
	CountdownNumber--;

	if (CountdownNumber > 0)
	{
		if (Countdown)
		{
			Countdown->SetCountdownText(FString::FromInt(CountdownNumber));
		}

		return;
	}

	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	
	if (Countdown)
	{
		Countdown->SetCountdownText(TEXT("GO!"));
	}
	StartGame();
	
	GetWorldTimerManager().SetTimer(
		RemoveCountdownTimerHandle,
		this,
		&ATileManager::RemoveCountdown,
		0.5f,
		false
	);
}

void ATileManager::StartGame()
{
	bIsGameStarted = true;
}

void ATileManager::RemoveCountdown()
{
	if (Countdown)
	{
		Countdown->RemoveFromParent();
		Countdown = nullptr;
	}
}
void ATileManager::SpawnTile()
{
	if (TileClass == nullptr)//디버깅용 출력코드
	{
		UE_LOG(LogTemp, Error, TEXT("TileClass is nullptr."))
			return;
	}

	const FVector SpawnLocation = FVector(NextSpawnX, 0.0f, 0.0f);
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMovingTile* NewTile = GetWorld()->SpawnActor<AMovingTile>(
		TileClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	if (NewTile == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed"));
		return;
	}

	SpawnedTiles.Add(NewTile);

	UE_LOG(LogTemp, Warning, TEXT("Spawn TileX: %.1f"), NextSpawnX);//스폰지점 확인용

	NextSpawnX += TileLength;
}

void ATileManager::MoveTiles(float DeltaTime)
{
	const FVector MoveOffset = FVector(-MoveSpeed * DeltaTime, 0.0f, 0.0f);

	for (AMovingTile* Tile : SpawnedTiles)
	{
		if (Tile == nullptr)
		{
			continue;
		}


		Tile->AddActorWorldOffset(MoveOffset, false);//Sweep 끔. 처음엔 켜고 했는데 끄는게 나음
	}
}
void ATileManager::RemoveOldTiles()
{
	for (int32 i = SpawnedTiles.Num() - 1; i >= 0; --i)//타일 개수만큼 반복
	{
		AMovingTile* Tile = SpawnedTiles[i];

		if (Tile == nullptr)
		{
			SpawnedTiles.RemoveAt(i);//RemoveAt은 처음봄 찾아봐야함
			continue;
		}

		if (Tile->GetActorLocation().X < DestroyX)
		{
			Tile->Destroy();
			SpawnedTiles.RemoveAt(i);
		}

	}
}


//AddSpeed(){}