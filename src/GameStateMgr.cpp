// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	GameStateMgr.cpp
// Author			:	Jasper Mix
// Creation Date	:	2017/02/21
// ---------------------------------------------------------------------------

#include "GameStateMgr.h"
#include "GameState_Level1.h"
#include "GameState_Start.h"
#include "GameState_Lose.h"
#include "GameState_LevelSelect.h"

// ---------------------------------------------------------------------------
// globals

// variables to keep track the current, previous and next game state
static unsigned int	gGameStateInit;
static unsigned int	gGameStateCurr;
static unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

// pointer to functions for game state life cycles functions
void (*GameStateLoad)(void)		= 0;
void (*GameStateInit)(void)		= 0;
void (*GameStateUpdate)(void)	= 0;
void (*GameStateDraw)(void)		= 0;
void (*GameStateFree)(void)		= 0;
void (*GameStateUnload)(void)	= 0;

// ---------------------------------------------------------------------------
// Functions implementations

void GameStateMgrInit(unsigned int gameStateInit)
{
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr = gGameStateInit;
	gGameStatePrev = gGameStateInit;
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GameStateMgrUpdate();
}

// ---------------------------------------------------------------------------

void GameStateMgrUpdate()
{
	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
	case GS_LEVEL1:
		GameStateLoad = GameStateLevel1Load;
		GameStateInit = GameStateLevel1Init;
		GameStateUpdate = GameStateLevel1Update;
		GameStateDraw = GameStateLevel1Draw;
		GameStateFree = GameStateLevel1Free;
		GameStateUnload = GameStateLevel1Unload;
		break;

	case GS_START:
		GameStateLoad = GameStateStartLoad;
		GameStateInit = GameStateStartInit;
		GameStateUpdate = GameStateStartUpdate;
		GameStateDraw = GameStateStartDraw;
		GameStateFree = GameStateStartFree;
		GameStateUnload = GameStateStartUnload;
		break;

	case GS_LOSE:
		GameStateLoad = GameStateLoseLoad;
		GameStateInit = GameStateLoseInit;
		GameStateUpdate = GameStateLoseUpdate;
		GameStateDraw = GameStateLoseDraw;
		GameStateFree = GameStateLoseFree;
		GameStateUnload = GameStateLoseUnload;
		break;

	case GS_LEVEL_SELECT:
		GameStateLoad = GameStateLevelSelectLoad;
		GameStateInit = GameStateLevelSelectInit;
		GameStateUpdate = GameStateLevelSelectUpdate;
		GameStateDraw = GameStateLevelSelectDraw;
		GameStateFree = GameStateLevelSelectFree;
		GameStateUnload = GameStateLevelSelectUnload;
		break;

	default:
		AE_FATAL_ERROR("invalid state!!");
	}
}

// ---------------------------------------------------------------------------


void GSM_MainLoop(void)
{
	while (gGameStateCurr != GS_QUIT)
	{
		// reset the system modules
		AESysReset();
		// If not restarting, load the gamestate
		if (gGameStateCurr != GS_RESTART)
		{
			GameStateMgrUpdate();
			GameStateLoad();
		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;

		// Initialize the gamestate
		GameStateInit();

		while (gGameStateCurr == gGameStateNext)
		{
			AESysFrameStart();

			AEInputUpdate();

			GameStateUpdate();

			GameStateDraw();

			AESysFrameEnd();

			// check if forcing the application to quit
			if ((0 == AESysDoesWindowExist()) || (AEInputCheckCurr(VK_ESCAPE) && AEInputCheckCurr(VK_SHIFT)))
				gGameStateNext = GS_QUIT;

		}

		GameStateFree();

		if (gGameStateNext != GS_RESTART)
			GameStateUnload();

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}
}


// ---------------------------------------------------------------------------
