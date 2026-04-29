#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class LOOPMAP_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;
	//float AccMoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintMoveSpeed;
	//float AccSprintMoveSpeed;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	int32 CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	int32 MaxHP;
	UFUNCTION(BlueprintPure, Category = "State")
	int32 GetCurrentHP() const;
	UFUNCTION(BlueprintCallable, Category = "State")
	void SetCurrentHP(int32 InCurrentHP);
	UFUNCTION(BlueprintPure, Category = "State")
	int32 GetCurrentSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "State")
	void SetCurrentSpeed(int32 InApplySpeed);

	FTimerHandle SpeedConstantTimer;
	void MaxSpeedToNormalSpeed();

	void OnDeath();
public:

	void Move_Start(const FInputActionValue& Value);
	void Move_Stop(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump_Start(const FInputActionValue& Value);
	void Jump_Stop(const FInputActionValue& Value);
	void Sprint_Start(const FInputActionValue& Value);
	void Sprint_Stop(const FInputActionValue& Value);

	UPROPERTY()
	float TargetYaw;
	UPROPERTY()
	float TargetPitch;
	UPROPERTY()
	float CurrentPitch;
	UPROPERTY()
	float CurrentYaw;


protected:
	virtual float TakeDamage(
		float Damage,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
