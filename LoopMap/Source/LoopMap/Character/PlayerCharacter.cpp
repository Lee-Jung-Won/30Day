#include "Character/PlayerCharacter.h"
#include "GameUtilHeader/GameUtilComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Controller/LPPlayerController.h"
#include "EnhancedInputComponent.h"
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = GameUtil::CreateComponent<USpringArmComponent>(this);
	SpringArmComponent->TargetArmLength = 300.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	//===========================================================================================
	MoveSpeed = 300.f;
	SprintMoveSpeed = 600.f;
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AccMoveSpeed = MoveSpeed * DeltaTime;
	//AccSprintMoveSpeed = SprintMoveSpeed * DeltaTime;
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
		AddMovementInput(GetActorForwardVector(), Movevalue.X);
		AddMovementInput(GetActorRightVector(), Movevalue.Y);
	}
}

void APlayerCharacter::Move_Stop(const FInputActionValue& Value)
{
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D Lookvalue = Value.Get<FVector2D>();

	if (!Lookvalue.IsNearlyZero())
	{
		AddControllerYawInput(Lookvalue.X);
		AddControllerPitchInput(Lookvalue.Y);
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