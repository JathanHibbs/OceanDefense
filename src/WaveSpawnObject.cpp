// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	PathObjectSript.cpp
// Author			:	Jake Fletcher
// Creation Date	:	2017/03/21
// ---------------------------------------------------------------------------
#include "main.h"
#include "WaveSpawnObject.h"
#include "EnemyBehavior.h"
#include "GameState_Level1.h"
#include <string>


float WaveLength = 0;
extern float WaveTime;
bool newWaveStart = true;
int GlobalTotalWaves = 0;
int CurrWave = 0;
void SpawnerInitialize(Object_Info* Spawner, int waveAmount, int spawnerNum)
{
	AESysPrintf("spawnerNum: %i\n", spawnerNum);
	int waveNum = 0;
	FILE *file;
	std::string fileName = "Spawner" + std::to_string(spawnerNum) + ".txt";
	const char* fileName2TTemp = fileName.c_str();
	
	file = fopen(fileName2TTemp, "r");
	SpawnerComponent* spawnerComp = GetSpawnerComp(Spawner);
	spawnerComp->WaveInfo = new Wave[waveAmount];
	if (file != NULL)
	{
		fscanf(file, "%i\n\n", &spawnerNum);
		while (!feof(file))
		{
			fscanf(file, "%i \n", &waveNum);
			spawnerComp->WaveInfo[waveNum].activeFlag = true;
			fscanf(file, "%i \n", &spawnerComp->WaveInfo[waveNum].enemyType);
			fscanf(file, "%i \n", &spawnerComp->WaveInfo[waveNum].enemyCount);
			fscanf(file, "%f \n\n", &spawnerComp->WaveInfo[waveNum].interval);
			spawnerComp->TotalWaves++;
			GlobalTotalWaves++;
		}
	}
}
void SpawnerUpdate(Object_Info* Spawner, float frameTime)
{
	SpawnerComponent* spawnerComp = GetSpawnerComp(Spawner);
	if (spawnerComp->CurrDelayTime <= 0)
	{
		if (spawnerComp->WaveInfo[spawnerComp->CurrWave].activeFlag)
		{

			Spawning(Spawner, &spawnerComp->WaveInfo[spawnerComp->CurrWave], frameTime);
			if (newWaveStart == true)
			{
				WaveLength = (spawnerComp->WaveInfo[spawnerComp->CurrWave].enemyCount + 1) * spawnerComp->WaveInfo[spawnerComp->CurrWave].interval + WAVE_DELAY;
				WaveTime = WaveLength;
				newWaveStart = false;
				CurrWave = spawnerComp->CurrWave;
			}
		}
	}
	if (spawnerComp->CurrDelayTime > 0)
	{
		newWaveStart = true;
		spawnerComp->CurrDelayTime -= frameTime;
	}

	WaveTime -= frameTime;
}


void Spawning(Object_Info* Spawner, Wave* waveInfo, float frameTime)
{
	//TO DO 5/2/17 Use waveInfo to spawn the specified amount of enemies, with their delay
	SpawnerComponent* spawnerComp = GetSpawnerComp(Spawner);
	if (spawnerComp->CurrWait <= 0) //checks the delay between each spawn
	{
		if (waveInfo->enemyCount > 0) //middle of current wave
		{
			TransformComponent* spawnerTransform = GetTransformComp(Spawner);
			CreateEnemy(spawnerTransform->position, waveInfo->enemyType);
			spawnerComp->CurrWait = waveInfo->interval;
			waveInfo->enemyCount--;

		}
		else //end of current wave
		{
			spawnerComp->CurrDelayTime = WAVE_DELAY;
			spawnerComp->CurrWave++;
		}
	}
	
	spawnerComp->CurrWait -= frameTime;
	
}

