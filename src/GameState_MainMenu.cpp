// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	GameState_MainMenu.cpp
// Author			:	Jasper Mix
// Creation Date	:	2017/04/10
// ---------------------------------------------------------------------------
#include "GameState_MainMenu.h"
#include "objects.h"
#include "MenuFunctions.h"

AEGfxVertexList *squareMesh;

void GameStateMainMenuLoad(void)
{
	// creat the basic square mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF00FF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFF00FF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFF00FF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFF00FF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFF00FF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFF00FF, 0.0f, 0.0f);
	squareMesh = AEGfxMeshEnd();
}

void GameStateMainMenuInit(void)
{
	Object_Info* playButton = createButton(0, 0, 100, 100);
}

void GameStateMainMenuUpdate(void)
{

}

void GameStateMainMenuDraw(void)
{

}

void GameStateMainMenuFree(void)
{

}

void GameStateMainMenuUnload(void)
{

}
