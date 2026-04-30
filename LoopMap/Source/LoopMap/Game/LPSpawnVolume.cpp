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

	SquareSizeInVolume = FVector(100.f, 50.f, 0.f);

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

TArray<AActor*> ALPSpawnVolume::SpawnItem()
{
	//������ǥ���
	TArray<FVector> SpawnSpots = GetCalculatedPositionInVolume();
	//������ǥ������ŭ ���������� ���
	TArray<UClass*> SpawnItemInfo = GetRandomItem(SpawnSpots.Num());
	//�����Ⱦ����۳ֱ�
	
	if (SpawnItemInfo.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("List is Empty"));
		return SpawnedItemInfo;
	}

	for (int i = 0; i < SpawnSpots.Num(); i++)
	{
		FVector AdjustLoc = FVector::ZeroVector;
		if (SpawnItemInfo[i]->IsChildOf(ACoinItem::StaticClass()))
		{// ������ġ����
			AdjustLoc = FVector(0.f, 0.f, 80.f);
		}
		if (SpawnItemInfo[i]->IsChildOf(APotionItem::StaticClass()))
		{// ������ġ����
			AdjustLoc = FVector(0.f, 0.f, 80.f);
		}
		if (SpawnItemInfo[i]->IsChildOf(ABoomTrapItem::StaticClass()))
		{// ������ġ����
			AdjustLoc = FVector(0.f, 0.f, 40.f);
		}
		SpawnedItemInfo.Add(GetWorld()->SpawnActor<AActor>(
			SpawnItemInfo[i],
			SpawnSpots[i] + AdjustLoc,
			FRotator::ZeroRotator
		));
	}
	return SpawnedItemInfo;
}

TArray<FVector> ALPSpawnVolume::GetCalculatedPositionInVolume()
{
	// volume�� x,y ũ�� ���ؼ� ��ũ�⸦ Ȯ���ϰ�
	// Ȯ�������� �� �簢���� ������ǥ�� TArray�� ��´�
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

	// TODO: BoxComponent nullptr �˻�
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
	FTransform BoxTransform = BoxComponent->GetComponentTransform();

	if (BoxExtent.X >= SquareSizeInVolume.X && BoxExtent.Y >= SquareSizeInVolume.Y)
	{
		// TODO: ���� ���� ����
		int32 PointX = FMath::TruncToInt((BoxExtent.X) / SquareSizeInVolume.X);
		int32 PointY = FMath::TruncToInt((BoxExtent.Y) / SquareSizeInVolume.Y);
		int32 CountPoint = PointX * PointY;

		if (CountPoint == 0)
			return PointList;

		// ���� ���� ������ ����
		 FVector BoxStartPoint = GetActorLocation();

		// TODO: ���� ������ ����
		// ù ĭ�� �߽����� �ǵ��� �� ĭ��ŭ ���ʿ��� ����
		FVector LocalStartPoint;
		LocalStartPoint.X = -BoxExtent.X + SquareSizeInVolume.X;
		LocalStartPoint.Y = -BoxExtent.Y + SquareSizeInVolume.Y;
		LocalStartPoint.Z = 0.f;

		float MoveX = 0.f, MoveY = 0.f;

		for (int32 i = 0; i < PointX; i++)
		{
			// TODO: ���� ���� ���� X ��ǥ ���
			 MoveX = LocalStartPoint.X + i * (SquareSizeInVolume.X * 2);

			for (int32 j = 0; j < PointY; j++)
			{
				// TODO: ���� ���� ���� Y ��ǥ ���
				 MoveY = LocalStartPoint.Y + j * (SquareSizeInVolume.Y * 2);

				// TODO: ���� ��ǥ ����
				FVector LocalPoint;
				 LocalPoint = FVector(MoveX, MoveY, 0.f);

				// TODO: ���� ��ǥ�� ��ȯ
				FVector WorldPoint;
				 WorldPoint = BoxTransform.TransformPosition(LocalPoint);

				PointList.Add(WorldPoint);
			}
		}
		/*UE_LOG(LogTemp, Warning, TEXT("BoxExtent X: %.1f Y: %.1f"),
			BoxExtent.X,
			BoxExtent.Y
		);

		UE_LOG(LogTemp, Warning, TEXT("SquareSize X: %.1f Y: %.1f"),
			SquareSizeInVolume.X,
			SquareSizeInVolume.Y
		);

		UE_LOG(LogTemp, Warning, TEXT("PointX: %d PointY: %d Count: %d"),
			PointX,
			PointY,
			CountPoint
		);*/
	}
	return PointList;
}

void ALPSpawnVolume::BeginPlay()
{
	Super::BeginPlay();
}

