// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "MovingTile.h"
#include "TimerManager.h"
#include "UI/Countdown.h"
#include "Blueprint/UserWidget.h"

#include "Game/LPSpawnVolume.h"

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

	//GameState로 넘겨서 GameState의 시간을 적용해야할 타이머 =============

	GetWorldTimerManager().SetTimer( 
		CountdownTimerHandle,
		this,
		&ATileManager::CountdownTick,
		1.0f,
		true
	);
	//=======================================
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsGameStarted)//카운트 다운 세는중
	{
		return;
	}

	MoveSpeed += SpeedIncreasePerSecond * DeltaTime;
	MoveSpeed = FMath::Clamp(MoveSpeed, 0.0f, MaxMoveSpeed);
	
	SpeedLogTimer += DeltaTime;
	if (SpeedLogTimer >= 1.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current MoveSpeed: %.1f / Max: %.1f"),
			MoveSpeed,
			MaxMoveSpeed
		);

		SpeedLogTimer = 0.0f;
	}
	
	MoveTiles(DeltaTime);

	NextSpawnX -= MoveSpeed * DeltaTime;

	if (NextSpawnX <= SpawnX)
	{
		SpawnTile();
	}

	RemoveOldTiles();//타일이 -x로 움직이기때문에 다음 생성 위치도 같이 움직여야함
}

void ATileManager::SetFloorMoveSpeed(float InSpeed)
{
	MoveSpeed = InSpeed;
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
	// bIsGameStarted = true ========================
	StartGame();
	// ==============================================
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
	UE_LOG(LogTemp, Warning, TEXT("[%s] SpawnTile Called. NextSpawnX: %.1f"),
		*GetName(),
		NextSpawnX
	);



const FVector SpawnLocation = FVector(NextSpawnX, 0.0f, 0.0f);
const FRotator SpawnRotation = FRotator::ZeroRotator;

FActorSpawnParameters SpawnParams;
SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

if (TileClasses.IsEmpty())
{
	UE_LOG(LogTemp, Error, TEXT("TileClasses is empty. Set tile blueprints in BP_TileManager."));
	return;
}

const int32 RandomIndex = FMath::RandRange(0, TileClasses.Num() - 1); //랜덤 타일
TSubclassOf<AMovingTile> SelectedTileClass = TileClasses[RandomIndex];

AMovingTile* NewTile = GetWorld()->SpawnActor<AMovingTile>( //랜덤 타일 호출
	SelectedTileClass,
	SpawnLocation,
	SpawnRotation,
	SpawnParams
);
// SpawnVolumeTile Spawn ===========================
ALPSpawnVolume* SpawnTile = GetWorld()->SpawnActor<ALPSpawnVolume>(
	LPSpawnVolumeClass,
	SpawnLocation + FVector(0.f, 0.f, 500.f), // 다리메쉬 높이이슈 위치보정
	SpawnRotation + FRotator(0.f, 90.f, 0.f), // 다리메쉬 회전값 적용
	SpawnParams
);

// ==================================================
if (NewTile == nullptr || SpawnTile == nullptr)
{
	UE_LOG(LogTemp, Error, TEXT("NewTile, SpawnTile: Failed"));
	return;
}
// Spawn Item In SpawnVolumeTile ====================
SpawnedItems = SpawnTile->SpawnItem();
/*UE_LOG(LogTemp, Warning, TEXT("[%s] SpawnVolume spawned %d items"),
	*GetName(),
	SpawnedItems.Num()
);*/
SpawnedTiles.Add(NewTile);

// ====================================================
for (const auto SpawnedItem : SpawnedItems)
{
	TotalSpawnedItems.Add(SpawnedItem); //생성된 아이템 전부 넣기
}
SpawnTile->Destroy(); // SpawnTile지우기
// ====================================================

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
		// Moveing Tile Logic ======================
		Tile->AddActorWorldOffset(MoveOffset, false);//Sweep 끔. 처음엔 켜고 했는데 끄는게 나음
	}
	// Item Moveing Logic Need =================
	for (AActor* Items : TotalSpawnedItems)
	{
		if (!Items) continue;
		Items->AddActorWorldOffset(MoveOffset, false);
	}
	//==========================================
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
		// Remove Item Need =======================
		for (AActor* Items : TotalSpawnedItems)
		{
			if (Items->GetActorLocation().X < DestroyX)
			{
				if (!Items)	continue;
				Items->Destroy();
			}
		}
		TotalSpawnedItems.RemoveAll([](AActor* Actor) // TArray에서 지워진요소에 대한 인덱스를 지우는 로직
			{
				return !IsValid(Actor);
			});
		//=========================================
	}
}


