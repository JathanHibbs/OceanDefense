// --------------------------------------------------------------------------------
// Project Name		:	Project 3 - Part 1
// File Name		:	BinaryMap.c
// Author			:	Lexi Docherty
// Digipen Login	:	a.docherty
// ---------------------------------------------------------------------------------


#include "BinaryMap.h"

#pragma once
#include "AEEngine.h"


/*The number of horizontal elements*/
 int BINARY_MAP_WIDTH;

/*The number of vertical elements*/
int BINARY_MAP_HEIGHT;

/*This will contain all the data of the map, which will be retireved from a file
when the "ImportMapDataFromFile" function is called*/
int **MapData;

/*This will contain the collision dataof the binary map. It will be filled in the 
"ImportMapDataFromFile" after filling "MapData". Basically, if an array element 
in MapData is 1, it represents a collision cell, any other value is a non-collision
cell*/
int **BinaryCollisionArray;



int GetCellValue(unsigned int X, unsigned int Y)
{
	if ((X < BINARY_MAP_WIDTH) && (Y < BINARY_MAP_HEIGHT))
		return BinaryCollisionArray[X][Y];
	return 0;
}

int CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY)
{
	int flag = 0, hot1 = 0, hot2 = 0;
	//check value of points on left
	hot1 = GetCellValue((int)(PosX - (scaleX*.5)) , (int)(PosY + (scaleX*.25)));
	hot2 = GetCellValue((int)(PosX - (scaleX*.5)) , (int)(PosY - (scaleX*.25)));
	//Comapred with OR
	if (hot1 || hot2)
	{
		flag = flag | COLLISION_LEFT;
	}

	//check value of points on right
	hot1 = GetCellValue((int)(PosX + (scaleX*.5)) , (int)(PosY + (scaleX*.25)));
	hot2 = GetCellValue((int)(PosX + (scaleX*.5)) , (int)(PosY - (scaleX*.25)));
	//Comapred with OR
	if (hot1 || hot2)
	{
		flag = flag | COLLISION_RIGHT;
	}

	//check value of points on top
	hot1 = GetCellValue((int)(PosX + (scaleX*.25)) , (int)(PosY + (scaleX*.5)));
	hot2 = GetCellValue((int)(PosX - (scaleX*.25)) , (int)(PosY + (scaleX*.5)));
	//Comapred with OR
	if (hot1 || hot2)
	{
		flag = flag | COLLISION_TOP;
	}

	//check value of points on bottom
	hot1 = GetCellValue((int)(PosX + (scaleX*.25)) , (int)(PosY - (scaleX*.5)));
	hot2 = GetCellValue((int)(PosX - (scaleX*.25)) , (int)(PosY - (scaleX*.5)));
	//Comapred with OR
	if (hot1 || hot2)
	{
		flag = flag | COLLISION_BOTTOM;
	}

	return flag;
}

void SnapToCell(float *Coordinate)
{
	*Coordinate = (int)*Coordinate;
	*Coordinate += 0.5;
}

int ImportMapDataFromFile(char *FileName)
{
	char s[7];
	FILE *file;
	file = fopen(FileName, "r");
	if (file != NULL)
	{
		fscanf(file, "%s %d\n", s, &BINARY_MAP_WIDTH);
		fscanf(file, "%s %d\n", s, &BINARY_MAP_HEIGHT);

		MapData = new int*[BINARY_MAP_WIDTH];
		BinaryCollisionArray = new int*[BINARY_MAP_WIDTH];
		for (int i = 0; i < BINARY_MAP_WIDTH; i++)
		{
			MapData[i] = new int[BINARY_MAP_HEIGHT];
			BinaryCollisionArray[i] = new int[BINARY_MAP_HEIGHT];
		}

		for (int i = BINARY_MAP_HEIGHT-1; i >= 0; i--)
		{
			for (int j = 0; j < BINARY_MAP_WIDTH; j++)
			{
				fscanf(file, "%d", &MapData[j][i]);
				if (MapData[j][i] != 1)
					BinaryCollisionArray[j][i] = 0;
				else
					BinaryCollisionArray[j][i] = 1;
			}

		}

		return 1;
    }

	return 0;
}

void FreeMapData(void)
{
	for (int i = 0; i < BINARY_MAP_WIDTH; i++)
	{
		delete [] MapData[i];
		delete [] BinaryCollisionArray[i];
	}
	delete [] MapData;
	delete [] BinaryCollisionArray;
	MapData = NULL;
	BinaryCollisionArray = NULL;
	BINARY_MAP_WIDTH = 0;
	BINARY_MAP_HEIGHT = 0;
}

void PrintRetrievedInformation(void)
{
	int i, j;
	
	AESysPrintf("Width: %i\n", BINARY_MAP_WIDTH);
	AESysPrintf("Height: %i\n", BINARY_MAP_HEIGHT);

	AESysPrintf("Map Data:\n");
	for(j = BINARY_MAP_HEIGHT - 1; j >= 0; --j)
	{
		for(i = 0; i < BINARY_MAP_WIDTH; ++i)
		{
			AESysPrintf("%i ", MapData[i][j]);
		}

		AESysPrintf("\n");
	}

	AESysPrintf("\n\nBinary Collision Data:\n");
	for(j = BINARY_MAP_HEIGHT - 1; j >= 0; --j)
	{
		for(i = 0; i < BINARY_MAP_WIDTH; ++i)
		{
			AESysPrintf("%i ", BinaryCollisionArray[i][j]);
		}

		AESysPrintf("\n");
	}
}