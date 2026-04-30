#include "Controller/LPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Game/LPGameState.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Game/LPGameInstance.h"
ALPPlayerController::ALPPlayerController()
	:Move_Action(nullptr)
	,Look_Action(nullptr)
	,InputMappingContext(nullptr)
	,HUDWidgetClass(nullptr)
	,HUDWidgetInstance(nullptr)
	,MenuWidgetClass(nullptr)
	,MenuWidgetInstance(nullptr)
{

}

void ALPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	//if (HUDWidgetClass)
	//{	// �ν��Ͻ��� �������ִ� createwidget
	//	HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
	//	if (HUDWidgetInstance)
	//	{
	//		HUDWidgetInstance->AddToViewport();
	//	}
	//}

	ALPGameState* LPGameStae = GetWorld() ? GetWorld()->GetGameState<ALPGameState>() : nullptr;
	if (LPGameStae)
	{
		LPGameStae->UpdateHUD();
	}

	FString CuurentMapName = GetWorld()->GetName();
	if (CuurentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}
}
// ShowMainMenu�� ����
// �ν��Ͻ� ������� ��� show
void ALPPlayerController::ShowGameHUD()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->RemoveFromParent();
		MenuWidgetInstance = nullptr;
	}
	// =====================================================
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}

		ALPGameState* LPGameState = GetWorld() ? GetWorld()->GetGameState<ALPGameState>() : nullptr;
		if (LPGameState)
		{
			LPGameState->UpdateHUD();
		}
	}
}

void ALPPlayerController::ShowMainMenu(bool bIsRestart)
{
	// bIsRestart�� ���� � ��ư���ڷ� �ٲ��� ����
	// �ϴ� ������ �� ��
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (MenuWidgetInstance)
	{
		MenuWidgetInstance->RemoveFromParent();
		MenuWidgetInstance = nullptr;
	}
	// =====================================================
	if (MenuWidgetClass)
	{
		MenuWidgetInstance = CreateWidget<UUserWidget>(this, MenuWidgetClass);
		if (MenuWidgetInstance)
		{
			MenuWidgetInstance->AddToViewport();
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MenuWidgetInstance->GetWidgetFromName(TEXT("StartButton"))))
		{// Menu button text �ٲٱ� restart/start
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString("Restart"));
			}
			else
			{
				ButtonText->SetText(FText::FromString("Start"));
			}
		}

	}
}

void ALPPlayerController::CStartGame()
{ // ������ ���ο� ���� = GameInstance�� ��������ֱ⶧���� ���� ����
	if (ULPGameInstance* LPGameInstance = Cast<ULPGameInstance>(
		UGameplayStatics::GetGameInstance(this)))
	{
		LPGameInstance->CurrentLevel = 0;
		LPGameInstance->TotalScore = 0;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("PlayGround"));

}

UUserWidget* ALPPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}


//void ALPPlayerController::ShowMainMenu(bool IsMenuLevel)
//{
//	if (IsMenuLevel)
//	{
//		// ����â UI?
//
//	}
//	else
//	{
//		FInputModeUIOnly InputMode;
//		SetInputMode(InputMode);
//		bShowMouseCursor = true;
//		SetPause(true);
//
//		if (MenuWidgetInstance)
//		{
//			MenuWidgetInstance->RemoveFromParent();
//			MenuWidgetInstance = nullptr;
//		}
//
//		if (MenuWidgetClass)
//		{
//			MenuWidgetInstance = CreateWidget<UUserWidget>(this, MenuWidgetClass);
//			if (MenuWidgetInstance)
//			{
//				MenuWidgetInstance->AddToViewport();
//			}
//		}
//	}
//}
//
//void ALPPlayerController::GotoGameStage()
//{
//
//	FInputModeGameOnly InputMode;
//	SetInputMode(InputMode);
//	bShowMouseCursor = false;
//	SetPause(false);
//
//	UGameplayStatics::OpenLevel(GetWorld(), FName("PlayGround"));
//}
