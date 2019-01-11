// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	GameState_Start.cpp
// Author			:	Jasper Mix
// Creation Date	:	2017/05/12
// ---------------------------------------------------------------------------

#include "GUI_Buttons.h"
#include "AEEngine.h"
#include "AEGameStateMgr.h"
#include "GameStateList.h"
#include "fmod.hpp"
#include "main.h"

extern Button_Info ButtonList[BUTTON_NUM_MAX];
extern unsigned int gGameStateNext;
extern AEGfxVertexList* ButtonMesh;

AEGfxTexture* menuBackgroundTex;

AEGfxTexture* startButtonTex;
AEGfxTexture* quitButtonTex;
AEGfxTexture* DigiPenLogo;
Button_Info* startButton;
Button_Info* quitButton;

AEGfxVertexList* BackgroundMesh;

//sounds
FMOD::Sound * buttonClick;
FMOD::Sound * menuMusic;

FMOD::Channel* musicChannel;

extern FMOD::System *fmodSys;

bool musicPlaying = false;

float buttonBob;
Vector2D startButtonPos, quitButtonPos;
void GameStateStartLoad(void)
{
	DigiPenLogo = AEGfxTextureLoad("textures/DigiPen_WHITE.png");
	startButtonTex = AEGfxTextureLoad("textures/tmpButton.png");
	quitButtonTex = AEGfxTextureLoad("textures/tmpQuitButton.png");
	menuBackgroundTex = AEGfxTextureLoad("textures/MainMenuBackground.png");

	//load sounds
	fmodSys->createSound("sounds/bubblePop.wav", FMOD_DEFAULT, NULL, &buttonClick);

	if(musicPlaying == false)
		fmodSys->createStream("sounds/Digital Lemonade.mp3", FMOD_DEFAULT, NULL, &menuMusic);
}
void GameStateStartInit(void)
{
	buttonBob = 0.0f;
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);
	ButtonMesh = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		-600.0f, -400.0f, 0xFFFF0000, 0.0f, 1.0f,
		600.0f, -400.0f, 0xFFFF0000, 1.0f, 1.0f,
		-600.0f, 400.0f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		600.0f, -400.0f, 0xFFFF0000, 1.0f, 1.0f,
		600.0f, 400.0f, 0xFFFF0000, 1.0f, 0.0f,
		-600.0f, 400.0f, 0xFFFF0000, 0.0f, 0.0f);

	BackgroundMesh = AEGfxMeshEnd();



	

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetBlendColor(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < BUTTON_NUM_MAX; i++)
	{
		Button_Info* pButton = ButtonList + i;
		pButton->active = INACTIVE;
	}


	//create the buttons
	

	startButtonPos.x = -360.0f;
	startButtonPos.y = 50.0f;

	quitButtonPos.x = -200.0f;
	quitButtonPos.y = -160.0f;
	
	startButton = createButton(-360.0f, 50.0f, 200.0f, 200.0f);
	startButton->buttonTexture = startButtonTex;

	quitButton = createButton(-200.0f, -160.0f, 160.0f, 160.0f);
	quitButton->buttonTexture = quitButtonTex;


	//digipen splashscreen
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(DigiPenLogo, 0.0f, 0.0f);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxMeshDraw(BackgroundMesh, AE_GFX_MDM_TRIANGLES);
	for (float i = 0; i < 5000.0f; i += 0.1f)
	{
		
	}
	if (musicPlaying == false)
	{
		fmodSys->playSound(FMOD_CHANNEL_FREE, menuMusic, false, &musicChannel);
		musicPlaying = true;
	}
		
}
void GameStateStartUpdate(void)
{
	buttonUpdate();
	fmodSys->update();

	// make the buttons bob up and down
	buttonBob += 1.5f * AEFrameRateControllerGetFrameTime();
	startButton->Position.y = startButtonPos.y + (cosf(buttonBob) * 6);
	quitButton->Position.y = quitButtonPos.y + (sinf(buttonBob) * 6);

	//check if the buttons are being clicked
	if (startButton->mouseOver == ACTIVE && AEInputCheckCurr(VK_LBUTTON))
	{
		gGameStateNext = GS_LEVEL_SELECT;
		fmodSys->playSound(FMOD_CHANNEL_FREE, buttonClick, false, 0);
	}
		

	if (quitButton->mouseOver == ACTIVE && AEInputCheckCurr(VK_LBUTTON))
	{
		gGameStateNext = GS_QUIT;
		fmodSys->playSound(FMOD_CHANNEL_FREE, buttonClick, false, 0);
	}
}
void GameStateStartDraw(void)
{
	
	//draw the background
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(menuBackgroundTex, 0.0f, 0.0f);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxMeshDraw(BackgroundMesh, AE_GFX_MDM_TRIANGLES);


	//
	buttonDraw();
}
void GameStateStartFree(void)
{
	destroyButton(startButton);
	destroyButton(quitButton);
}
void GameStateStartUnload(void)
{
	AEGfxMeshFree(ButtonMesh);
	AEGfxMeshFree(BackgroundMesh);
	AEGfxTextureUnload(startButtonTex);
	AEGfxTextureUnload(quitButtonTex);
	AEGfxTextureUnload(DigiPenLogo);
}