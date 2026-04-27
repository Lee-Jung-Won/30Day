#include "Game/LPGameMode.h"
#include "Character/PlayerCharacter.h"
#include "Controller/LPPlayerController.h"
ALPGameMode::ALPGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = ALPPlayerController::StaticClass();

}
