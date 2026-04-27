#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LPPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class LOOPMAP_API ALPPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALPPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TObjectPtr<UInputAction> Move_Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TObjectPtr<UInputAction> Look_Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TObjectPtr<UInputAction> Jump_Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TObjectPtr<UInputAction> Sprint_Action;

protected:
	virtual void BeginPlay() override;
};
