#include "Item/ItemBase.h"
#include "GameUtilHeader/GameUtilComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
//#include "NiagaraComponent.h"

#include "LoopMap.h"
AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = GameUtil::CreateRootComponet<USceneComponent>(this);
	StaticMeshComponent = GameUtil::CreateComponent<UStaticMeshComponent>(this);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

	SphereComponent = GameUtil::CreateComponent<USphereComponent>(this);
	//overlapFname = alldynamic
	MagnetSphereComponent = GameUtil::CreateComponent<USphereComponent>(this);
	MagnetSphereComponent->SetSphereRadius(90.f);

	//NiagaraComponent = GameUtil::CreateComponent<UNiagaraSystem>(this);
	//NiagaraComponent->SetAutoActivate(false);
	//overlap�� �Ķ���Ϳ� �����ؾ� ���ε� ������
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemOverLap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnItemEndOverLap);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetGenerateOverlapEvents(true);

	MagnetSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnMagnetBoundOverLap);
	MagnetSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MagnetSphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MagnetSphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MagnetSphereComponent->SetGenerateOverlapEvents(true);
	//===========================================================================================

	ItemName = TEXT("ItemBase");

	UpDownSpeed = 2.f;
	UpDownRange = 0.1f;
	MoveToActorSpeed = 200.f;
	AccMoveToActorSpeed = 50.f;
	MaxMoveToActorSpeed = 800.f;
	TargetOneActor = nullptr;
	setgo = false;
}

void AItemBase::OnItemOverLap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	//player�ۿ� ���� >> �ڼ��̵������� �ٸ����͵� ����
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		ActivateItem(OtherActor);
		setgo = false;
	}
}

void AItemBase::OnItemEndOverLap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{

}

void AItemBase::OnMagnetBoundOverLap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	//�ڼ�(Player�±� �϶���)
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		TargetOneActor = OtherActor;
		setgo = true;
	}

}

void AItemBase::MoveToActorMagneticLogic(float DeltaSeconds)
{
	MoveToActorSpeed += AccMoveToActorSpeed;
	FVector CurrentLocation = GetActorLocation();
	FVector OneTargetLocation = TargetOneActor->GetActorLocation();
	float CalculateSpeed = FMath::Clamp(MoveToActorSpeed * DeltaSeconds, MoveToActorSpeed, MaxMoveToActorSpeed);
	FVector MoveDir = OneTargetLocation - CurrentLocation;
	MoveDir.Normalize();
	FVector ItemToActorLocation = MoveDir * CalculateSpeed * DeltaSeconds;
	SetActorLocation(CurrentLocation + ItemToActorLocation);
}

void AItemBase::UpDown_RotateMoveLogic(float DeltaSeconds)
{
	AddActorWorldRotation(FRotator(0.f, 60.f * DeltaSeconds, 0.f));
	float UpDownValue = FMath::Sin(GetWorld()->GetTimeSeconds() * UpDownSpeed) * UpDownRange;
	//SpawnLocation.Z += UpDownValue;
	AddActorWorldOffset(FVector(0.f, 0.f, UpDownValue));
}

void AItemBase::ActivateItem(AActor* Activator)
{
	UE_LOG(LogTemp, Warning, TEXT("Activate Item"));


}

void AItemBase::DestroyItem()
{
	if (NiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			NiagaraSystem,
			GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1.f),
			true,
			true
		);
	}
	if (SoundWave)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			GetWorld(),
			SoundWave,
			GetActorLocation()
		);
	}
	UE_LOG(LogTemp, Warning, TEXT("Destroy Item"));
	Destroy();
}

void AItemBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpDown_RotateMoveLogic(DeltaSeconds);
	if (setgo)
	{
		MoveToActorMagneticLogic(DeltaSeconds);
	}

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = GetActorLocation();
}

