#include "Game/LPSpawnVolume.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "GameUtilHeader/GameUtilComponent.h"
#include "Item/CoinItem.h"
#include "Item/PotionItem.h"
#include "Item/BoomTrapItem.h"
ALPSpawnVolume::ALPSpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = GameUtil::CreateRootComponet<USceneComponent>(this);
	BoxComponent = GameUtil::CreateComponent<UBoxComponent>(this);

	SquareSizeInVolume = FVector(50.f, 50.f, 0.f);

	ItemDataTable = nullptr;
}

TArray<UClass*> ALPSpawnVolume::GetRandomItem(int32 HowMany)
{
	TArray<UClass*> NeedToSpawnItemList;

	if (!ItemDataTable) return NeedToSpawnItemList;

	TArray<FItemSpawnRow*> AllRows;

	static const FString DebugText(TEXT("DebugTextDataTable"));
	ItemDataTable->GetAllRows(DebugText, AllRows);

	if (AllRows.IsEmpty()) return NeedToSpawnItemList;
	
	float TotalChance = 0.f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	for (int i = 0; i < HowMany; i++)
	{
		const float RandomChance = FMath::FRandRange(0.f, TotalChance);
		float AddSpawnChance = 0.f;

		for (FItemSpawnRow* Row : AllRows)
		{
			AddSpawnChance += Row->SpawnChance;
			if (RandomChance <= AddSpawnChance)
			{
				TObjectPtr<UClass> ActualClass = Row->ItemClass.Get();
				NeedToSpawnItemList.Add(ActualClass);
				break;
			}
		}
	}
	return NeedToSpawnItemList;
}

void ALPSpawnVolume::SpawnItem()
{
	//격자좌표얻기
	TArray<FVector> SpawnSpots = GetCalculatedPositionInVolume();
	//격자좌표갯수만큼 랜덤아이템 얻기
	TArray<UClass*> SpawnItemInfo = GetRandomItem(SpawnSpots.Num());

	if (SpawnItemInfo.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("List is Empty"));
		return;
	}

	for (int i = 0; i < SpawnSpots.Num(); i++)
	{
		FVector AdjustLoc = FVector::ZeroVector;
		if (SpawnItemInfo[i]->IsChildOf(ACoinItem::StaticClass()))
		{// 코인위치보정
			AdjustLoc = FVector(0.f, 0.f, 80.f);
		}
		if (SpawnItemInfo[i]->IsChildOf(APotionItem::StaticClass()))
		{// 물약위치보정
			AdjustLoc = FVector(0.f, 0.f, 80.f);
		}
		if (SpawnItemInfo[i]->IsChildOf(ABoomTrapItem::StaticClass()))
		{// 함정위치보정
			AdjustLoc = FVector(0.f, 0.f, 40.f);
		}
		GetWorld()->SpawnActor<AActor>(
			SpawnItemInfo[i],
			SpawnSpots[i] + AdjustLoc,
			FRotator::ZeroRotator
		);
	}
}

TArray<FVector> ALPSpawnVolume::GetCalculatedPositionInVolume()
{
	// volume의 x,y 크기 비교해서 들어갈크기를 확보하고
	// 확보했으면 그 사각형의 중점좌표를 TArray에 담는다
	// return array;
	//TArray<FVector> PointList;

	//FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
	//FVector BoxOrigin = BoxComponent->GetComponentLocation();

	//if (BoxExtent.X >= SquareSizeInVolume.X && BoxExtent.Y >= SquareSizeInVolume.Y)
	//{
	//	int32 PointX = FMath::TruncToInt(BoxExtent.X / SquareSizeInVolume.X);
	//	int32 PointY = FMath::TruncToInt(BoxExtent.Y / SquareSizeInVolume.Y);
	//	int32 CountPoint = PointX * PointY;
	//	if (CountPoint == 0)
	//		return PointList;

	//	FVector BoxStartPoint = GetActorLocation();
	//	BoxStartPoint.X -= BoxExtent.X; //-100
	//	BoxStartPoint.Y -= BoxExtent.Y; //-100
	//	float MoveX, MoveY;
	//	for (int i = 1; i < PointX+1; i++)
	//	{
	//		if (i == 1)
	//		MoveX = i * SquareSizeInVolume.X;
	//		else
	//		MoveX += SquareSizeInVolume.X * 2;
	//		for (int j = 1; j < PointY+1; j++)
	//		{
	//			if (j == 1)
	//				MoveY = j * SquareSizeInVolume.Y;
	//			else
	//				MoveY += SquareSizeInVolume.Y * 2;
	//			PointList.Add(FVector(BoxStartPoint.X + MoveX, BoxStartPoint.Y + MoveY, BoxStartPoint.Z));
	//		}
	//	}
	//}
	TArray<FVector> PointList;

	// TODO: BoxComponent nullptr 검사
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
	FTransform BoxTransform = BoxComponent->GetComponentTransform();

	if (BoxExtent.X >= SquareSizeInVolume.X && BoxExtent.Y >= SquareSizeInVolume.Y)
	{
		// TODO: 개수 계산식 점검
		int32 PointX = FMath::TruncToInt((BoxExtent.X) / SquareSizeInVolume.X);
		int32 PointY = FMath::TruncToInt((BoxExtent.Y) / SquareSizeInVolume.Y);
		int32 CountPoint = PointX * PointY;

		if (CountPoint == 0)
			return PointList;

		// 기존 월드 시작점 제거
		 FVector BoxStartPoint = GetActorLocation();

		// TODO: 로컬 시작점 정의
		// 첫 칸의 중심점이 되도록 반 칸만큼 안쪽에서 시작
		FVector LocalStartPoint;
		LocalStartPoint.X = -BoxExtent.X + SquareSizeInVolume.X;
		LocalStartPoint.Y = -BoxExtent.Y + SquareSizeInVolume.Y;
		LocalStartPoint.Z = 0.f;

		float MoveX = 0.f, MoveY = 0.f;

		for (int32 i = 0; i < PointX; i++)
		{
			// TODO: 현재 열의 로컬 X 좌표 계산
			 MoveX = LocalStartPoint.X + i * (SquareSizeInVolume.X * 2);

			for (int32 j = 0; j < PointY; j++)
			{
				// TODO: 현재 행의 로컬 Y 좌표 계산
				 MoveY = LocalStartPoint.Y + j * (SquareSizeInVolume.Y * 2);

				// TODO: 로컬 좌표 생성
				FVector LocalPoint;
				 LocalPoint = FVector(MoveX, MoveY, 0.f);

				// TODO: 월드 좌표로 변환
				FVector WorldPoint;
				 WorldPoint = BoxTransform.TransformPosition(LocalPoint);

				PointList.Add(WorldPoint);
			}
		}
	}
	return PointList;
}

void ALPSpawnVolume::BeginPlay()
{
	Super::BeginPlay();
}

