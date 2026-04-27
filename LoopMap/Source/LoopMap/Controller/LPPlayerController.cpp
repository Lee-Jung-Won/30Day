#include "Controller/LPPlayerController.h"
#include "EnhancedInputSubsystems.h"
ALPPlayerController::ALPPlayerController()
	:Move_Action(nullptr)
	,Look_Action(nullptr)
	,InputMappingContext(nullptr)
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
}
