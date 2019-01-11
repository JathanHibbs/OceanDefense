//Written by Lexi Docherty
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EnemyMapFunctions.h"
#include "objects.h"
#include "WaveSpawnObject.h"
#include "EnemyBehavior.h"
#include "GameState_Level1.h"

#define PI 3.141592654

extern int BINARY_MAP_WIDTH;
extern int BINARY_MAP_HEIGHT;
extern AEGfxVertexList *squareMesh;
extern TransformComponent *baseLocation;
extern BaseComponent *baseBase;
extern unsigned int selectedLevel;
extern enum LEVEL { LEVEL1, LEVEL2, LEVEL3 };
//holds all the information from the enemy map file
int **EnemyMapData;

int spawnerCount = 0;
int pixelXY(int a, float win, float map)
{
	//return a*(win / (map/ 1.5)) - (win / 2.0f);
	float tileSize = win / 20;
	return (a*tileSize) - ((tileSize * map) / 2.0f);
}


//Translates all the information in the enemy map file to a enemyMapData array
int ImportEnemyMapDataFromFile(char *fileName)
{
	char s[7];
	FILE *file;
	file = fopen(fileName, "r");
	if (file != NULL)
	{
		EnemyMapData = (int**)malloc(BINARY_MAP_WIDTH*sizeof(int*));
		for (int i = 0; i < BINARY_MAP_WIDTH; i++)
		{
			EnemyMapData[i] = (int*)malloc(BINARY_MAP_HEIGHT*sizeof(int));
		}

		for (int i = BINARY_MAP_HEIGHT - 1; i >= 0; i--)
		{
			for (int j = 0; j < BINARY_MAP_WIDTH; j++)
			{
				fscanf(file, "%d", &EnemyMapData[j][i]);
			}

		}
		fclose(file);
		return 1;
	}

	return 0;
}
//creates all the objects using the enemy map file
void createObjFromEnemyMap(AEGfxTexture* node, AEGfxTexture* spawner, AEGfxTexture* base, AEGfxTexture* tower)
{
	float winY, winX;
	winX = 1200;
	winY = 1200;
	float a = 1.6f;
	for (int i = 0; i < BINARY_MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < BINARY_MAP_WIDTH; ++j)
		{
			switch (EnemyMapData[j][i])
			{
				case EM_EMPTY:
					break;
				case EM_TOWER_SPOT:
				{
					//test turret platform
					Object_Info* towPlatform = Add_Object(OBJECT_TURRET_PLATFORM);

					AddComponent(towPlatform, COMPONENT_TRANSFORM);
					AddComponent(towPlatform, COMPONENT_PHYSICS);
					AddComponent(towPlatform, COMPONENT_MESH);
					AddComponent(towPlatform, COMPONENT_TEXTURE);
					AddComponent(towPlatform, COMPONENT_TURRET_PLATFORM);

					MeshComponent* towPlatformMesh = GetMeshComp(towPlatform);
					towPlatformMesh->mesh = squareMesh;
					// get the texture component
					TextureComponent* towPlatformTexComp = GetTextureComp(towPlatform);
					towPlatformTexComp->texture = tower;
					towPlatformTexComp->level = bottom;
					ObjectSetScale(towPlatform, 64, 64);
					ObjectSetPosition(towPlatform, pixelXY(j, winX, BINARY_MAP_WIDTH), pixelXY(i, winY, BINARY_MAP_HEIGHT/a));
				  break;
				}
				case EM_BASE:
				{
					////////////////////////////////////////////////
					// Base Object
					// 
					Object_Info* BaseObject = Add_Object(OBJECT_BASE);

					// add components to the Player object
					AddComponent(BaseObject, COMPONENT_TRANSFORM);
					AddComponent(BaseObject, COMPONENT_PHYSICS);
					AddComponent(BaseObject, COMPONENT_MESH);
					AddComponent(BaseObject, COMPONENT_TEXTURE);
					AddComponent(BaseObject, COMPONENT_BASE);

					// Create an ObjectMesh pointer then set it to the BaseObject mesh component
					MeshComponent* BaseMesh = GetMeshComp(BaseObject);
					BaseMesh->mesh = squareMesh;
					// get the texture component
					TextureComponent* BaseTexture = GetTextureComp(BaseObject);

					BaseTexture->texture = base;
					BaseTexture->level = bottom;

					// Create an ObjectTransform pointer then set it to the BaseObject Transform component

					baseLocation = GetTransformComp(BaseObject);
					baseBase = GetBaseComp(BaseObject);         

					// set the position and scale of the player
					baseLocation->position.x = a + pixelXY(j, winX, BINARY_MAP_WIDTH);
					baseLocation->position.y = a + pixelXY(i, winY, BINARY_MAP_HEIGHT / a);

					baseLocation->scale.x = 450.0f;
					baseLocation->scale.y = 450.0f;

					break;
				}
				case EM_SPAWNER:
				{

					Object_Info* Spawner1 = Add_Object(OBJECT_SPAWNER);
					
					// add components to the Player object
					AddComponent(Spawner1, COMPONENT_TRANSFORM);
					AddComponent(Spawner1, COMPONENT_PHYSICS);
					AddComponent(Spawner1, COMPONENT_MESH);
					AddComponent(Spawner1, COMPONENT_TEXTURE);
					AddComponent(Spawner1, COMPONENT_SPAWNER);

					TransformComponent* SpawnerTransform1 = GetTransformComp(Spawner1);

					// Creat an ObjectMesh pointer then set it to the PlayerObject mesh component
					MeshComponent* SpawnerMesh1;
					SpawnerMesh1 = GetMeshComp(Spawner1);

					SpawnerMesh1->mesh = squareMesh;

					// get the texture component
					TextureComponent* SpawnerTexture1;
					SpawnerTexture1 = GetTextureComp(Spawner1);

					SpawnerTexture1->texture = spawner;

					//PhysicsComponent* PathTransform2 = GetPhysicsComp(Spawner1);
					//PathTransform2->angle = 4.71f;
					ObjectSetScale(Spawner1, 100, 100);
					ObjectSetPosition(Spawner1, pixelXY(j, winX, BINARY_MAP_WIDTH), a + pixelXY(i, winY, BINARY_MAP_HEIGHT / a));
					spawnerCount++;
					switch (selectedLevel)
					{
						case LEVEL1:
						{
							SpawnerInitialize(Spawner1, 5, 1);
							break;
						}

						case LEVEL2:
						case LEVEL3:
						{
							SpawnerInitialize(Spawner1, 5, (selectedLevel + spawnerCount));
							AESysPrintf("%i \n", selectedLevel + spawnerCount);
							AESysPrintf("%f \n", SpawnerTransform1->position.x);
							break;
						}
					}
					
					break;
				}
				case EM_NODE_DOWN:
				case EM_NODE_UP:
				case EM_NODE_RIGHT:
				case EM_NODE_LEFT:
				{
					Object_Info* PathObject = Add_Object(OBJECT_PATH);

					// add components to the Player object
					AddComponent(PathObject, COMPONENT_TRANSFORM);
					AddComponent(PathObject, COMPONENT_PHYSICS);
					AddComponent(PathObject, COMPONENT_MESH);
					AddComponent(PathObject, COMPONENT_TEXTURE);


					// Creat an ObjectMesh pointer then set it to the PlayerObject mesh component
					MeshComponent* PathMesh;
					PathMesh = GetMeshComp(PathObject);

					PathMesh->mesh = squareMesh;

					// get the texture component
					TextureComponent* PathTexture;
					PathTexture = GetTextureComp(PathObject);

					PathTexture->texture = node;
					PathTexture->isVisible = false;

					TransformComponent* PathTransform = GetTransformComp(PathObject);

					float angle = EnemyMapData[j][i] - 2;
					angle *= (0.5f * PI);
					PathTransform->angle = angle;
					ObjectSetScale(PathObject, 100, 100);
					float tmp = winX / BINARY_MAP_WIDTH;
					float tmp2 = winY / BINARY_MAP_HEIGHT;
					ObjectSetPosition(PathObject, pixelXY(j, winX, BINARY_MAP_WIDTH), a + pixelXY(i, winY, BINARY_MAP_HEIGHT / a));
					break;
				}
			}
		}
	}
}

void FreeEnemyMap(void)
{
	for (int i = 0; i < BINARY_MAP_WIDTH; i++)
	{
		free(EnemyMapData[i]);
	}
	free(EnemyMapData);
}