#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UTextBlock;
class UProgressBar;
class UImage;

UCLASS()
class LOOPMAP_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StartButtonText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ExitButtonText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TitleTextBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> TitleImage;

};
