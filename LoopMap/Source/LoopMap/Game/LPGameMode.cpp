#include "Game/LPGameMode.h"
#include "Character/PlayerCharacter.h"
#include "Controller/LPPlayerController.h"
#include "Game/LPGameState.h"
ALPGameMode::ALPGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = ALPPlayerController::StaticClass();
	GameStateClass = ALPGameState::StaticClass();
}
