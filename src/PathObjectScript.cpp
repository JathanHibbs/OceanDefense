// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	PathObjectSript.cpp
// Author			:	Jake Fletcher
// Creation Date	:	2017/03/21
// ---------------------------------------------------------------------------

#include "main.h"
#include "objects.h"
#include "PathObjectScript.h"
#include "Math2D.h"
#include "EnemyBehavior.h"


void EnemyCollidePath(Object_Info* enemy, Object_Info* PathBlock)
{
	TransformComponent* pathTransform = GetTransformComp(PathBlock);
	EnemyComponent* enemyComp = GetEnemyComp(enemy);
	
	if (enemyComp->CurrState != chasing)
	{
		enemyComp->isRotating = ACTIVE;
		enemyComp->rotateAngle = pathTransform->angle;
	}
}