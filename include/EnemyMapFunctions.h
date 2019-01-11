//Written by Lexi Docherty
#pragma once

#include "AEEngine.h"
#include "BinaryMap.h"
#include "Vector2D.h"

//Functions to control and read from the enemy map file
typedef enum EnemyMap
{
	EM_EMPTY,
	EM_BASE,
	EM_SPAWNER,
	EM_NODE_UP,
	EM_NODE_LEFT,
	EM_NODE_DOWN,
	EM_NODE_RIGHT,
	EM_TOWER_SPOT

}EnemyMap;

//Translates all the information in the enemy map file to a enemyMapData array
int ImportEnemyMapDataFromFile(char *fileName);
//creates all the objects using the enemy map file
void createObjFromEnemyMap(AEGfxTexture* node, AEGfxTexture* spawner, AEGfxTexture* base, AEGfxTexture* tower);
//Frees map
void FreeEnemyMap(void);
