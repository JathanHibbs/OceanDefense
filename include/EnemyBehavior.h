// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	PathObjectScript.h
// Author			:	Jake Fletcher
// Creation Date	:	2017/03/21
// ---------------------------------------------------------------------------

#pragma once

//#include "GameState_Level1.h"
enum enemyType
{
	basicEnemy,
	basicEnemyFast,
	tankEnemyEasy,
	tankEnemyHard,
	enemyChaserEasy,
	enemyChaserHard
};
void CreateEnemy(Vector2D pos, int type);
void EnemyUpdate(Object_Info* enemy);
void FindPath(Object_Info* enemy);
void ReturnToPath(Object_Info* enemy, Object_Info* path);
void EnemyChase(Object_Info* enemy, Vector2D playerPos);
void EnemyRotate(Object_Info* enemy, float PathAngle);
