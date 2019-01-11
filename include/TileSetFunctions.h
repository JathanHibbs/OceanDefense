//Written by Lexi Docherty
#pragma once

#include "AEEngine.h"
#include "BinaryMap.h"
#include "Vector2D.h"

#define MAX_TILES_TYPES 25

//enum for objects to use in an object .txt file
typedef enum objectType
{
	OBJ_EMPTY,
	TILE_SOLID,
	TILE_PATH,
	OBJ_PLAYER
}objectType;

//The tile types (used in the tileMapCoords array to find the U and V coords for the type of tile
//Will have ACTUAL names (ex, TILE_GRASS or TILE_PATH_L)
typedef enum tileType
{
	TILE_WATER,
	TILE_GW_COR_UL,
	TILE_GW_COR_UR,
	TILE_GW_COR_BL,
	TILE_GW_COR_BR,
	TILE_GW_EDGE_L,
	TILE_GW_EDGE_R,
	TILE_GW_EDGE_U,
	TILE_GW_EDGE_B,
	TILE_PATH_CORNER_UL,
	TILE_PATH_CORNER_UR,
	TILE_PATH_CORNER_BL,
	TILE_PATH_CORNER_BR,
	TILE_PATH_STRAIGHT_UB,
	TILE_PATH_STRAIGHT_LR,

}tileType;

//Sets each tile to its corresponding posistion on the tile map and imports the tilemap;
int loadTileMap(char* filename);
//loads the tilemap texture
void loadTileMapTex(char* filename);
//draws a tile with the given U and V posistion
void drawTile(float tileU, float tileV);
//Translate the x,y coordants from the tileMapCoord array to the proper U,V posistion
int tilePos(int type, float *outu, float *outv, float size);
//Draw function for the tilemap
void drawTileMap();

void freeTilemap(void);
void unloadTilemap(void);