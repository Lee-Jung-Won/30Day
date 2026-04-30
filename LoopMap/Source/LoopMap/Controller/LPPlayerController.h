#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LPPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UUserWidget;

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

	// UserWidget =================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> MenuWidgetInstance;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameHUD();
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowMainMenu(bool bIsRestart, int32 IsVictory = 0);
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void CStartGame();
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void CExitGame();

	UFUNCTION(BlueprintPure, Category = "HUD")
	UUserWidget* GetHUDWidget() const;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	//TSubclassOf<UUserWidget> MenuWidgetClass;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	//TObjectPtr<UUserWidget> MenuWidgetInstance;

	//void ShowMainMenu(bool IsMenuLevel);

	//UFUNCTION(BlueprintCallable, Category = "HUD")
	//void GotoGameStage();
protected:
	virtual void BeginPlay() override;
};
