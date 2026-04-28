// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Countdown.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class LOOPMAP_API UCountdown : public UUserWidget
{
	GENERATED_BODY()
	


public: 
	void SetCountdownText(const FString& InText);//FName

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CountdownText;

};
