

#include "MovingTile.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


AMovingTile::AMovingTile()
{

	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetupAttachment(SceneRoot);

}

void AMovingTile::BeginPlay()
{
	Super::BeginPlay();

}

