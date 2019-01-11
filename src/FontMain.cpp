/******************************************************************************/
/*!
\file   Main.cpp
\author Jeremy Kings
\par    Course: GAM150
\par    Copyright © 2017 DigiPen (USA) Corporation.
\brief  AlphaEngine TextManager demo.
*/
/******************************************************************************/
/*#include <stdbool.h>
#include "AEEngine.h"
#include "TextObject.h"
#include "TextManager.h"
#include <fstream>

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

	// Initialize the system 
	AESysInitInfo sysInitInfo;
	sysInitInfo.mCreateWindow = 1;
	sysInitInfo.mAppInstance = instanceH;
	sysInitInfo.mShow = show;
	sysInitInfo.mWinWidth = 800;
	sysInitInfo.mWinHeight = 600;
	sysInitInfo.mCreateConsole = 1;
	sysInitInfo.mMaxFrameRate = 60;
	sysInitInfo.mpWinCallBack = NULL;
	sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
	sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;
	sysInitInfo.mWindowHandle = NULL;
	sysInitInfo.mHandleWindowMessages = 1;
	AESysInit(&sysInitInfo);

	// reset the system modules
	AESysReset();

	// set the background color to black: R, G, B: [0.0,1.0]
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Font nonsense - I fully expect this to catch on fire
	TextManager textManager("Fonts/");

	// Add available fonts
	TextManager::AddCharacterSet("Arial16.fnt", ARIAL_16);
	TextManager::AddCharacterSet("Arial32.fnt", ARIAL_32);
	TextManager::AddCharacterSet("Arial48.fnt", ARIAL_48);
	TextManager::AddCharacterSet("Arial64.fnt", ARIAL_64);
	TextManager::AddCharacterSet("ComicSansMS16.fnt", COMIC_SANS_MS_16);
	TextManager::AddCharacterSet("ComicSansMS32.fnt", COMIC_SANS_MS_32);
	TextManager::AddCharacterSet("ComicSansMS48.fnt", COMIC_SANS_MS_48);
	TextManager::AddCharacterSet("ComicSansMS64.fnt", COMIC_SANS_MS_64);
	TextManager::AddCharacterSet("FelixTitling16.fnt", FELIX_TITLING_16);
	TextManager::AddCharacterSet("FelixTitling32.fnt", FELIX_TITLING_32);
	TextManager::AddCharacterSet("FelixTitling48.fnt", FELIX_TITLING_48);
	TextManager::AddCharacterSet("FelixTitling64.fnt", FELIX_TITLING_64);
	TextManager::AddCharacterSet("TimesNewRoman16.fnt", TIMES_NEW_ROMAN_16);
	TextManager::AddCharacterSet("TimesNewRoman32.fnt", TIMES_NEW_ROMAN_32);
	TextManager::AddCharacterSet("TimesNewRoman48.fnt", TIMES_NEW_ROMAN_48);
	TextManager::AddCharacterSet("TimesNewRoman64.fnt", TIMES_NEW_ROMAN_64);

	TextManager::Load();

	TextObject* textObject = new TextObject("Hello World", "Greetings, humans!", FELIX_TITLING_32);
	textObject->SetPosition(-80.0f, 100.0f);
	textObject = new TextObject("Fonts1", "You can have text in several different fonts.", ARIAL_48);
	textObject->SetPosition(-400.0f, 0.0f);
	textObject = new TextObject("Fonts2", "...and different sizes.", TIMES_NEW_ROMAN_16);
	textObject->SetPosition(-50.0f, -100.0f);

	AEGfxSetTransparency(1.0f);

	// Game Loop
	bool isGameRunning = true;
	while (isGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// Update text manager
		TextManager::Update((float)AEFrameRateControllerGetFrameTime());

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if 'P' is triggered
		if (AEInputCheckTriggered('P'))
		{
			AESysPrintf("AESysPrintf: command\n");
		}

		// check if forcing the application to quit
		if (AEInputCheckTriggered(VK_ESCAPE) || (AESysDoesWindowExist() == 0))
		{
			isGameRunning = false;
		}
	}

	TextManager::Free();

	TextManager::Unload();

	// free the system
	AESysExit();

	return 0;
}*/
