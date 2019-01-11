// ---------------------------------------------------------------------------
// Project Name		:	Omega Library Test Program
// File Name		:	main.h
// Author			:	Sun Tjen Fam
// Creation Date	:	2007/04/26
// Purpose			:	main entry point for the test program
// History			:
// - 2007/04/26		:	- initial implementation
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// includes

#include "main.h"
#include "TextManager.h"
#include "FontTypes.h"
#include "fmod.hpp"
#include "2DGameEngineIncludes.h"

// ---------------------------------------------------------------------------
// Static function protoypes


// ---------------------------------------------------------------------------
// main

FMOD::System *fmodSys;
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	// Initialize the system 
	AESysInitInfo sysInitInfo;

	sysInitInfo.mAppInstance		= instanceH;
	sysInitInfo.mShow				= show;
	sysInitInfo.mWinWidth			= 1200; 
	sysInitInfo.mWinHeight			= 800;
	sysInitInfo.mCreateConsole		= 0;
	sysInitInfo.mMaxFrameRate	= 60;
	sysInitInfo.mpWinCallBack		= NULL;//MyWinCallBack;
	sysInitInfo.mClassStyle			= CS_HREDRAW | CS_VREDRAW;											
	sysInitInfo.mWindowStyle		= WS_SYSMENU;//WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW;

	sysInitInfo.mCreateWindow		= 1;
	sysInitInfo.mWindowHandle		= NULL;
	sysInitInfo.mHandleWindowMessages = 1;

	// Initialize the system
	if (0 != AESysInit(&sysInitInfo))
		return 1;

	AESysSetWindowTitle("Ocean Defense");

	// Initialize the text manager
	TextManager textManager("Fonts/");
	TextManager::AddCharacterSet("FelixTitling32.fnt", FELIX_TITLING_32);

	// Initialize fmod
	
	unsigned fmodError = FMOD::System_Create(&fmodSys);
	
	fmodSys->init(64, FMOD_INIT_NORMAL, NULL);

	if(fmodError != FMOD_OK)
	{
		AESysPrintf("\n/////////////////////////////\nFailed to create FMOD system\n");
		return 1;
	}
	//digipen splashscreen
	//////////////////////
	/*AEGfxTexture* DigiPenLogo;
	AEGfxTexture* LlamaCatsLogo;
	AEGfxVertexList* SplashScreenMesh;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-600.0f, -400.0f, 0xFFFF0000, 0.0f, 1.0f,
		600.0f, -400.0f, 0xFFFF0000, 1.0f, 1.0f,
		-600.0f, 400.0f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		600.0f, -400.0f, 0xFFFF0000, 1.0f, 1.0f,
		600.0f, 400.0f, 0xFFFF0000, 1.0f, 0.0f,
		-600.0f, 400.0f, 0xFFFF0000, 0.0f, 0.0f);

	SplashScreenMesh = AEGfxMeshEnd();

	
	DigiPenLogo = AEGfxTextureLoad("textures/DigiPen_WHITE.png");
	LlamaCatsLogo = AEGfxTextureLoad("textures/LlamaCatSplash.png");
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	
	for (float i = 0; i < 1.0f; i += AEFrameRateControllerGetFrameTime())
	{
		AESysFrameStart();
		AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 1.0f);
		AESysFrameEnd();
	}
	
	for (float i = 0; i < 4.0f; i += AEFrameRateControllerGetFrameTime())
	{
		AESysFrameStart();
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxTextureSet(DigiPenLogo, 0.0f, 0.0f);
		AEGfxSetPosition(0.0f, 0.0f);
		AEGfxMeshDraw(SplashScreenMesh, AE_GFX_MDM_TRIANGLES);

		if (i > 3.0f)
		{
			AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, i - 3.0f);
		}
		else if (i < 1.0f)
		{
			AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 1.0f - i);
		}
		else
			AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
		AESysFrameEnd();
	}
	for (float i = 0; i < 4.0f; i += AEFrameRateControllerGetFrameTime())
	{
		AESysFrameStart();
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxTextureSet(LlamaCatsLogo, 0.0f, 0.0f);
		AEGfxSetPosition(0.0f, 0.0f);
		AEGfxMeshDraw(SplashScreenMesh, AE_GFX_MDM_TRIANGLES);

		if (i > 3.0f)
		{
			AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, i - 3.0f);
		}
		else if (i < 1.0f)
		{
			AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 1.0f - i);
		}
		else
			AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);
		AESysFrameEnd();
	}
	
	AEGfxMeshFree(SplashScreenMesh);
	AEGfxTextureUnload(DigiPenLogo);
	AEGfxTextureUnload(LlamaCatsLogo);*/
	/////////////////////////////////

	GameStateMgrInit(GS_START);
	GSM_MainLoop();
	
	//unload the text manager
	TextManager::Unload();

	//unload fmod
	fmodSys->release();

	// free the system
	AESysExit();

	return 1;
}

// ---------------------------------------------------------------------------