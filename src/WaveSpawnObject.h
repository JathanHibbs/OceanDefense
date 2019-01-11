// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	PathObjectScript.h
// Author			:	Jake Fletcher
// Creation Date	:	2017/04/24
// ---------------------------------------------------------------------------

#pragma once


#include "GameState_Level1.h"
#include "objects.h"



void SpawnerInitialize(Object_Info* Spawner, int waveAmount, int spawnerNum);

void SpawnerUpdate(Object_Info* Spawner, float frameTime);

void Spawning(Object_Info* Spawner, Wave* waveInfo, float frameTime);

