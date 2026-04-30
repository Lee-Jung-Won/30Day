#include "Character/PlayerCharacter.h"
#include "GameUtilHeader/GameUtilComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Controller/LPPlayerController.h"
#include "Game/LPGameState.h"
#include "EnhancedInputComponent.h"

#include "TileManager.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	NormalSpringArmLength = 350.0f;
	SpringArmComponent = GameUtil::CreateComponent<USpringArmComponent>(this);
	SpringArmComponent->TargetArmLength = NormalSpringArmLength;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	//===========================================================================================
	MoveSpeed = 600.f;
	SprintMoveSpeed = 600.f; // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	GetCharacterMovement()->AirControl = 2.0f;
	//===========================================================================================
	MaxHP = 100;
	CurrentHP = MaxHP;

	bIsZoomOutLogic = false;
	bIsZoomInLogic = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
<<<<<<< HEAD

=======
	FixedX = GetActorLocation().X;
>>>>>>> EditCode
}

int32 APlayerCharacter::GetCurrentHP() const
{
	return CurrentHP;
}

void APlayerCharacter::SetCurrentHP(int32 InCurrentHP)
{
	CurrentHP = FMath::Clamp(CurrentHP + InCurrentHP, 0, MaxHP);
}

int32 APlayerCharacter::GetCurrentSpeed() const
{
	return GetCharacterMovement()->MaxWalkSpeed;
}

void APlayerCharacter::SetCurrentSpeed(int32 InApplySpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed + InApplySpeed;
<<<<<<< HEAD
	// TileManager.cpp > TileSpeed = MoveSpeed + InApplySpeed º¯°æ·ÎÁ÷
	ATileManager* TileManager = Cast<ATileManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ATileManager::StaticClass()));
	if (!TileManager) return;
	TileManager->SetFloorMoveSpeed(MoveSpeed + InApplySpeed);
=======
	// TileManager.cpp > TileSpeed = MoveSpeed + InApplySpeed ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	//
>>>>>>> EditCode
	// ==========================================================

	// =================================== camera zoom out
	bIsZoomOutLogic = true;
	// ===================================
	GetWorldTimerManager().SetTimer(
		SpeedConstantTimer,
		this,
		&APlayerCharacter::MaxSpeedToNormalSpeed,
		1.5f,
		false
	);
}

void APlayerCharacter::ZoomOutLogic(float DeltaTime)
{// ZoomOutLogic in Tick()
	if (bIsZoomOutLogic)
	{
		float CurrnetSpringArmLength = SpringArmComponent->TargetArmLength;
		float TargetSpringArmLength = NormalSpringArmLength + 350.f;
		
		CurrnetSpringArmLength = FMath::FInterpTo(
			CurrnetSpringArmLength,
			TargetSpringArmLength,
			DeltaTime,
			6.f
		);
		SpringArmComponent->TargetArmLength = CurrnetSpringArmLength;
		if (FMath::IsNearlyEqual(CurrnetSpringArmLength, TargetSpringArmLength, 1.f))
		{
			bIsZoomOutLogic = false;
			bIsZoomInLogic = true;
			SpringArmComponent->TargetArmLength = TargetSpringArmLength;
		}
	}

	else if (bIsZoomInLogic)
	{
		float CurrnetSpringArmLength = SpringArmComponent->TargetArmLength;
		float TargetSpringArmLength = NormalSpringArmLength;

		CurrnetSpringArmLength = FMath::FInterpTo(
			CurrnetSpringArmLength,
			TargetSpringArmLength,
			DeltaTime,
			6.f
		);
		SpringArmComponent->TargetArmLength = CurrnetSpringArmLength;

		if (FMath::IsNearlyEqual(CurrnetSpringArmLength, TargetSpringArmLength, 1.f))
		{
			SpringArmComponent->TargetArmLength = NormalSpringArmLength;
		}
	}
}

void APlayerCharacter::MaxSpeedToNormalSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
<<<<<<< HEAD
	// TileManager.cpp > TileSpeed = MoveSpeed Á¤»óÈ­ ·ÎÁ÷
	ATileManager* TileManager = Cast<ATileManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ATileManager::StaticClass()));
	if (!TileManager) return;
	TileManager->SetFloorMoveSpeed(MoveSpeed);
=======
	// TileManager.cpp > TileSpeed = MoveSpeed ï¿½ï¿½ï¿½ï¿½È­ ï¿½ï¿½ï¿½ï¿½
	//
>>>>>>> EditCode
	// ==========================================================
	bIsZoomOutLogic = false;
	bIsZoomInLogic = false;
}

void APlayerCharacter::OnDeath()
{
	//end logic
}

float APlayerCharacter::TakeDamage(
	float Damage,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	CurrentHP = FMath::Clamp(CurrentHP - Damage, 0.f, MaxHP);
	UE_LOG(LogTemp, Warning, TEXT("Take Damaged: CurrentHP: %d"), CurrentHP);
	if (CurrentHP <= 0)
	{
		OnDeath();
	}
	return ActualDamage;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
<<<<<<< HEAD
	// CharacterMoveLogic =============================================================
	AddMovementInput(GetActorForwardVector(), 1.0f);
	//AccMoveSpeed = MoveSpeed * DeltaTime;
	//AccSprintMoveSpeed = SprintMoveSpeed * DeltaTime;
	// ================================================================================
	
	// SpringSoftMoveLogic ============================================================
=======
	//AddMovementInput(GetActorForwardVector(), 1.0f);
	//AccMoveSpeed = MoveSpeed * DeltaTime;
	//AccSprintMoveSpeed = SprintMoveSpeed * DeltaTime;

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.X = FixedX;
	SetActorLocation(CurrentLocation);

>>>>>>> EditCode
	CurrentPitch = FMath::FInterpTo(
		CurrentPitch,
		TargetPitch,
		DeltaTime,
		8.f
	);

	CurrentYaw = FMath::FInterpTo(
		CurrentYaw,
		TargetYaw,
		DeltaTime,
		8.f
	);
	SpringArmComponent->SetRelativeRotation(FRotator(CurrentPitch, CurrentYaw, 0.f));
	// ================================================================================

	// SpringArmSoftLogic :: WithSpeedItem ============================================
	ZoomOutLogic(DeltaTime);
	// ================================================================================

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ALPPlayerController* PController = Cast<ALPPlayerController>(GetController()))
		{
			if (PController->Move_Action)
			{
				InputComp->BindAction(
					PController->Move_Action,
					ETriggerEvent::Triggered,
					this,
					&APlayerCharacter::Move_Start
				);
				InputComp->BindAction(
					PController->Move_Action,
					ETriggerEvent::Completed,
					this,
					&APlayerCharacter::Move_Stop
				);
			}

			if (PController->Look_Action)
			{
				InputComp->BindAction(
					PController->Look_Action,
					ETriggerEvent::Triggered,
					this,
					&APlayerCharacter::Look
				);
			}

			if (PController->Jump_Action)
			{
				InputComp->BindAction(
					PController->Jump_Action,
					ETriggerEvent::Triggered,
					this,
					&APlayerCharacter::Jump_Start
				);
				InputComp->BindAction(
					PController->Jump_Action,
					ETriggerEvent::Completed,
					this,
					&APlayerCharacter::Jump_Stop
				);
			}

			if (PController->Sprint_Action)
			{
				InputComp->BindAction(
					PController->Sprint_Action,
					ETriggerEvent::Triggered,
					this,
					&APlayerCharacter::Sprint_Start
				);
				InputComp->BindAction(
					PController->Sprint_Action,
					ETriggerEvent::Completed,
					this,
					&APlayerCharacter::Sprint_Stop
				);
			}
		}
	}
}


void APlayerCharacter::Move_Start(const FInputActionValue& Value)
{
	if (!Controller) return;
	
	const FVector2D Movevalue = Value.Get<FVector2D>();
	if (!Movevalue.IsNearlyZero())
	{
		//AddMovementInput(GetActorForwardVector(), Movevalue.X);
		AddMovementInput(GetActorRightVector(), Movevalue.Y);
	}
}

void APlayerCharacter::Move_Stop(const FInputActionValue& Value)
{
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D Lookvalue = Value.Get<FVector2D>();
	//AddControllerYawInput(Lookvalue.X);
	//AddControllerPitchInput(Lookvalue.Y);
	if (!FMath::IsNearlyZero(Lookvalue.X))
	{
		TargetYaw += Lookvalue.X;
	}
	if (!FMath::IsNearlyZero(Lookvalue.Y))
	{
		TargetPitch += -Lookvalue.Y;
		TargetPitch = FMath::Clamp(TargetPitch, -50, 20);
	}
}

void APlayerCharacter::Jump_Start(const FInputActionValue& Value)
{
	Jump();
}

void APlayerCharacter::Jump_Stop(const FInputActionValue& Value)
{
	StopJumping();
}

void APlayerCharacter::Sprint_Start(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMoveSpeed;
}

void APlayerCharacter::Sprint_Stop(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}