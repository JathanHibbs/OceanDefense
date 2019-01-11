#pragma once
// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	GameState_LevelSelect.cpp
// Author			:	Jasper Mix
// Creation Date	:	2017/05/23
// ---------------------------------------------------------------------------
enum LEVEL
{
	LEVEL1,
	LEVEL2,
	LEVEL3
};

unsigned int selectedLevel;
// ---------------------------------------------------------------------------

#include "GUI_Buttons.h"
#include "AEEngine.h"
#include "AEGameStateMgr.h"
#include "GameStateList.h"
#include "fmod.hpp"


extern Button_Info ButtonList[BUTTON_NUM_MAX];
extern unsigned int gGameStateNext;
extern AEGfxVertexList* ButtonMesh;

AEGfxVertexList* backgroundMesh;
AEGfxTexture* LevelSelectBackgroundTex;

float ButtonBob;
//button textures
AEGfxTexture* level1ButtonTex;
AEGfxTexture* level2ButtonTex;
AEGfxTexture* level3ButtonTex;

AEGfxTexture* BackArrowTex;

//buttons
Button_Info* level1Button;
Button_Info* level2Button;
Button_Info* level3Button;

Button_Info* BackArrow;

//button positions
Vector2D level1ButtonPos, level2ButtonPos, level3ButtonPos;

//sound
FMOD::Sound * levelSelect_buttonClick;

extern FMOD::System *fmodSys;

void GameStateLevelSelectLoad(void)
{
	level1ButtonTex = AEGfxTextureLoad("textures/Level1Button.png");
	level2ButtonTex = AEGfxTextureLoad("textures/Level2Button.png");
	level3ButtonTex = AEGfxTextureLoad("textures/Level3Button.png");
	BackArrowTex = AEGfxTextureLoad("textures/BackArrow.png");

	LevelSelectBackgroundTex = AEGfxTextureLoad("textures/LevelSelectBackground.png");

	//load sounds
	fmodSys->createSound("sounds/bubblePop.wav", FMOD_DEFAULT, NULL, &levelSelect_buttonClick);
}
void GameStateLevelSelectInit(void)
{
	//create the meshes
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
	backgroundMesh = AEGfxMeshEnd();


	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	

	for (int i = 0; i < BUTTON_NUM_MAX; i++)
	{
		Button_Info* pButton = ButtonList + i;
		pButton->active = INACTIVE;
	}

	//create the buttons
	Vector2DSet(&level1ButtonPos, -150.0f, 50.0f);
	Vector2DSet(&level2ButtonPos, 0.0f, -100.0f);
	Vector2DSet(&level3ButtonPos, 150.0f, 30.0f);

	level1Button = createButton(-150.0f, -100.0f, 170.0f, 170.0f);
	level2Button = createButton(0.0f, 60.0f, 150.0f, 150.0f);
	level3Button = createButton(150.0f, -115.0f, 130.0f, 130.0f);

	level1Button->buttonTexture = level1ButtonTex;
	level2Button->buttonTexture = level2ButtonTex;
	level3Button->buttonTexture = level3ButtonTex;

	BackArrow = createButton(-540.0f, 340.0f, 70.0f, 70.0f);
	BackArrow->buttonTexture = BackArrowTex;
}
void GameStateLevelSelectUpdate(void)
{
	//button bob
	ButtonBob += 1.5f * AEFrameRateControllerGetFrameTime();
	level1Button->Position.y = level1ButtonPos.y + (cosf(ButtonBob) * 7);
	level2Button->Position.y = level2ButtonPos.y + (sinf(ButtonBob) * 6);
	level3Button->Position.y = level3ButtonPos.y + (cosf(ButtonBob) * 5);

	// check for button clicks
		//back arrow
	if (BackArrow->mouseOver == ACTIVE && AEInputCheckCurr(VK_LBUTTON))
	{
		gGameStateNext = GS_START;
	}
		// level 1
	if (level1Button->mouseOver == ACTIVE && AEInputCheckCurr(VK_LBUTTON))
	{
		fmodSys->createSound("sounds/bubblePop.wav", FMOD_DEFAULT, NULL, &levelSelect_buttonClick);
		selectedLevel = LEVEL1;
		gGameStateNext = GS_LEVEL1;
	}

		//level 2
	if (level2Button->mouseOver == ACTIVE && AEInputCheckCurr(VK_LBUTTON))
	{
		fmodSys->createSound("sounds/bubblePop.wav", FMOD_DEFAULT, NULL, &levelSelect_buttonClick);
		selectedLevel = LEVEL2;
		gGameStateNext = GS_LEVEL1;
	}

		//level 3
	if (level3Button->mouseOver == ACTIVE && AEInputCheckCurr(VK_LBUTTON))
	{
		fmodSys->createSound("sounds/bubblePop.wav", FMOD_DEFAULT, NULL, &levelSelect_buttonClick);
		selectedLevel = LEVEL3;
		gGameStateNext = GS_LEVEL1;
	}


	buttonUpdate();
}
void GameStateLevelSelectDraw(void)
{
	//draw the background
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(LevelSelectBackgroundTex, 0.0f, 0.0f);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxMeshDraw(backgroundMesh, AE_GFX_MDM_TRIANGLES);



	buttonDraw();
}
void GameStateLevelSelectFree(void)
{

}
void GameStateLevelSelectUnload(void)
{
	destroyButton(level1Button);
	destroyButton(level2Button);
	destroyButton(level3Button);
	destroyButton(BackArrow);
}

// ---------------------------------------------------------------------------