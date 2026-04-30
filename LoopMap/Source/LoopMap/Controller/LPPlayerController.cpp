#include "Controller/LPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Game/LPGameState.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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
	//{	// 인스턴스로 생성해주는 createwidget
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
// ShowMainMenu와 동일
// 인스턴스 다지우고 허드 show
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

void ALPPlayerController::ShowMainMenu(bool bIsRestart, int32 IsVictory)
{
	// bIsRestart에 따라 어떤 버튼글자로 바꿀지 정함
	// 일단 위젯을 다 꺼
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

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{// Menu button text 바꾸기 restart/start
			if (bIsRestart)
			{
				if (UImage* GetImageBox = Cast<UImage>(MenuWidgetInstance->GetWidgetFromName(TEXT("TitleImage"))))
				{
					if (IsVictory == 1)
					{
						UTexture2D* NewTexture = LoadObject<UTexture2D>(
							nullptr,
							TEXT("/Game/30Days/Blueprint/UI/Gemini_Generated_Image_s9sthzs9sthzs9st.Gemini_Generated_Image_s9sthzs9sthzs9st")
						);
						if (NewTexture)
						{
							GetImageBox->SetBrushFromTexture(NewTexture);
						}

						if (UTextBlock* TitleText = Cast<UTextBlock>(MenuWidgetInstance->GetWidgetFromName(TEXT("TitleTextBox"))))
						{
							TitleText->SetText(FText::FromString(FString::Printf(TEXT("!!! Victory !!!"))));
						}
					}
					else if (IsVictory == 0)
					{
						//UTexture2D* NewTexture = LoadObject<UTexture2D>(
						//	nullptr,
						//	TEXT("/Game/30Days/Blueprint/UI/Gemini_Generated_Image_113d2b113d2b113d.Gemini_Generated_Image_113d2b113d2b113d")
						//);
						//if (NewTexture)
						//{
						//	GetImageBox->SetBrushFromTexture(NewTexture);
						//}

						//if (UTextBlock* TitleText = Cast<UTextBlock>(MenuWidgetInstance->GetWidgetFromName(TEXT("TitleTextBox"))))
						//{
						//	TitleText->SetText(FText::FromString(FString::Printf("Running Puppy")));
						//}
					}
					else if (IsVictory == -1)
					{
						UTexture2D* NewTexture = LoadObject<UTexture2D>(
							nullptr,
							TEXT("/Game/30Days/Blueprint/UI/Gemini_Generated_Image_xg53nsxg53nsxg53.Gemini_Generated_Image_xg53nsxg53nsxg53")
						);
						if (NewTexture)
						{
							GetImageBox->SetBrushFromTexture(NewTexture);
						}

						if (UTextBlock* TitleText = Cast<UTextBlock>(MenuWidgetInstance->GetWidgetFromName(TEXT("TitleTextBox"))))
						{
							TitleText->SetText(FText::FromString(FString::Printf(TEXT("... Defeated ..."))));
						}
					}
				}
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
{ // 끝난후 새로운 시작 = GameInstance가 아직살아있기때문에 값이 있음
	if (ULPGameInstance* LPGameInstance = Cast<ULPGameInstance>(
		UGameplayStatics::GetGameInstance(this)))
	{
		LPGameInstance->CurrentLevel = 0;
		LPGameInstance->TotalScore = 0;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("PlayGround"));

}

void ALPPlayerController::CExitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

UUserWidget* ALPPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}


//void ALPPlayerController::ShowMainMenu(bool IsMenuLevel)
//{
//	if (IsMenuLevel)
//	{
//		// 상태창 UI?
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
