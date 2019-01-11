#pragma once
// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	GameState_Lose.cpp
// Author			:	Jasper Mix
// Creation Date	:	2017/05/19
// ---------------------------------------------------------------------------

#include "GUI_Buttons.h"
#include "AEEngine.h"
#include "AEGameStateMgr.h"
#include "GameStateList.h"

// ---------------------------------------------------------------------------

Button_Info* LquitButton;
AEGfxTexture* LquitButtonTex;

extern unsigned int gGameStateNext;
extern AEGfxVertexList* ButtonMesh;

void GameStateLoseLoad(void)
{
	LquitButtonTex = AEGfxTextureLoad("textures/tmpQuitButton.png");
}
void GameStateLoseInit(void)
{

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


	AEGfxSetBackgroundColor(0.7f, 0.2f, 0.2f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	LquitButton = createButton(0.0f, 0.0f, 200.0f, 100.0f);
	LquitButton->buttonTexture = LquitButtonTex;
}
void GameStateLoseUpdate(void)
{
	buttonUpdate();
}
void GameStateLoseDraw(void)
{
	if (LquitButton->mouseOver == ACTIVE && AEInputCheckCurr(VK_LBUTTON))
		gGameStateNext = GS_QUIT;

	buttonDraw();
}
void GameStateLoseFree(void)
{
	destroyButton(LquitButton);
}
void GameStateLoseUnload(void)
{
	AEGfxMeshFree(ButtonMesh);
	AEGfxTextureUnload(LquitButtonTex);
}

// ---------------------------------------------------------------------------