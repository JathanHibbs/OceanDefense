//Written by Lexi Docherty
#include"TileSetFunctions.h"
#include "Vector2D.h"
#include "Matrix2D.h"

//Binarymap stuff
extern int BINARY_MAP_WIDTH;
extern int BINARY_MAP_HEIGHT;
extern int **MapData;
extern int **BinaryCollisionArray;
extern Vector2D offset;
//Tile stuff
//Pointer to the one tile mesh
AEGfxVertexList *tileMesh;
//Pointer to the tilemap texture
AEGfxTexture *tilemap;
//a list of U,V coordants for each tile type
Vector2D tileMapCoords[MAX_TILES_TYPES];
float tileU = 0, tileV = 0;

int loadTileMap(char* filename)
{
	//X
	tileMapCoords[TILE_WATER].x		= 1;
	tileMapCoords[TILE_GW_COR_UL].x	= 0;
	tileMapCoords[TILE_GW_COR_UR].x = 2;
	tileMapCoords[TILE_GW_COR_BL].x = 0;
	tileMapCoords[TILE_GW_COR_BR].x = 2;
	tileMapCoords[TILE_GW_EDGE_L].x = 0;
	tileMapCoords[TILE_GW_EDGE_R].x = 2;
	tileMapCoords[TILE_GW_EDGE_U].x = 1;
	tileMapCoords[TILE_GW_EDGE_B].x = 1;
	tileMapCoords[TILE_PATH_CORNER_UL].x = 0;
	tileMapCoords[TILE_PATH_CORNER_UR].x = 1;
	tileMapCoords[TILE_PATH_CORNER_BL].x = 0;
	tileMapCoords[TILE_PATH_CORNER_BR].x = 1;
	tileMapCoords[TILE_PATH_STRAIGHT_UB].x = 2;
	tileMapCoords[TILE_PATH_STRAIGHT_LR].x = 2;
	//Y
	tileMapCoords[TILE_WATER].y		= 1;
	tileMapCoords[TILE_GW_COR_UL].y = 0;
	tileMapCoords[TILE_GW_COR_UR].y = 0;
	tileMapCoords[TILE_GW_COR_BL].y = 2;
	tileMapCoords[TILE_GW_COR_BR].y = 2;
	tileMapCoords[TILE_GW_EDGE_L].y = 1;
	tileMapCoords[TILE_GW_EDGE_R].y = 1;
	tileMapCoords[TILE_GW_EDGE_U].y = 0;
	tileMapCoords[TILE_GW_EDGE_B].y = 2;
	tileMapCoords[TILE_PATH_CORNER_UL].y = 3;
	tileMapCoords[TILE_PATH_CORNER_UR].y = 3;
	tileMapCoords[TILE_PATH_CORNER_BL].y = 4;
	tileMapCoords[TILE_PATH_CORNER_BR].y = 4;
	tileMapCoords[TILE_PATH_STRAIGHT_UB].y = 3;
	tileMapCoords[TILE_PATH_STRAIGHT_LR].y = 4;

	return ImportMapDataFromFile(filename);
}

void loadTileMapTex(char* filename)
{
	tilemap = AEGfxTextureLoad(filename);
}

void drawTile(float tileU, float tileV)
{
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(tilemap, tileU, tileV);
	AEGfxMeshDraw(tileMesh, AE_GFX_MDM_TRIANGLES);
}

int tilePos(int type, float *outu, float *outv, float size)
{
	if (type <= MAX_TILES_TYPES)
	{
		*outu = (1 / size)*(tileMapCoords[type].x);
		*outv = (1 / size)*(tileMapCoords[type].y);
		return 1;
	}
	return 0;
}

void drawTileMap()
{
	float winLength, winWidth;
	winLength = 1200;
	winWidth = 1200;
	//AESysPrintf("%f, %f\n", winLength, winWidth);
	//draw map
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendColor(0, 0, 0, 0);
	//scale was adjusted a lot, feel free to change it again
	//translate is to match the scale
	Matrix2D scale, translate;
	Matrix2DScale(&scale, (winLength / 20.0f), (winLength / 20.0f));
	Matrix2DTranslate(&translate, -(winLength/1.3333333333f), -(winWidth/3));
	Matrix2DConcat(&scale, &translate, &scale);
	Matrix2D temp;
	//Drawing prep stuff
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	//Goes through the imported tilemap .txt and draws each tile
	for (int i = 0; i < BINARY_MAP_WIDTH; ++i)
	{
		for (int j = 0; j < BINARY_MAP_HEIGHT; ++j)
		{
			//scale and translate
			Matrix2DTranslate(&temp, i, j + 0.5);
			Matrix2DConcat(&temp, &scale, &temp);
			AEGfxSetTransform(temp.m);
			//sets the tile's U and V coords from the type of tile from mapdata (returns 0 if somethign went wrong)
			if (tilePos(MapData[i][j], &tileU, &tileV, 5) == 0)
				AESysPrintf("Tile drawing error! Something went wrong! D:\n");
			//Draws the tile using the previously changed U and V values
			drawTile(tileU, tileV);

		}
	}
}

void freeTilemap(void)
{
	
	AEGfxMeshFree(tileMesh);
}

void unloadTilemap(void)
{
	AEGfxTextureUnload(tilemap);
}