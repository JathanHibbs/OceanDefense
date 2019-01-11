// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	PathObjectSript.cpp
// Author			:	Jake Fletcher
// Creation Date	:	2017/03/21
// ---------------------------------------------------------------------------

#include "main.h"
#include "objects.h"
#include "Vector2D.h"
#include "EnemyBehavior.h"
#include "2DGameEngineIncludes.h"
#include "GameState_Level1.h"


#define ROT_SPEED = 1.1f;
#define CHASE_RANGE 325

extern Object_Info* pPlayer;
extern int money;
AEGfxTexture* crab;
AEGfxTexture* Jelly1;
extern AEGfxTexture* sharkTex;
float enemySpeed;
int CurrEnemyCount = 1;
extern Object_Info ObjectList[OBJECT_NUM_MAX];
extern AEGfxVertexList *squareMesh;

void CreateEnemy(Vector2D pos, int type) //This function runs when a new enemy needs to be spawned
{


	Object_Info* enemy = Add_Object(OBJECT_ENEMY);
	AddComponent(enemy, COMPONENT_TRANSFORM);
	AddComponent(enemy, COMPONENT_PHYSICS);
	AddComponent(enemy, COMPONENT_MESH);
	AddComponent(enemy, COMPONENT_TEXTURE);
	AddComponent(enemy, COMPONENT_ENEMY);

	TextureComponent* textureComp = GetTextureComp(enemy);


	MeshComponent* mesh = GetMeshComp(enemy);
	mesh->mesh = squareMesh;

	ObjectSetScale(enemy, 48, 48);
	ObjectSetPosition(enemy, pos.x, pos.y);

	EnemyComponent* enemyComp = GetEnemyComp(enemy);
	enemyComp->enemyNum = CurrEnemyCount;

	TransformComponent* enemyTransform = GetTransformComp(enemy);

	CurrEnemyCount++;
	switch (type)
	{
	case basicEnemy:
		textureComp->texture = crab;
		enemyComp->health = 50;
		enemyComp->moveSpeed = 0.7f;
		enemyComp->slowedSpeed = 0.5f;
		enemyComp->value = 10;
		enemyComp->moveAngle = 6.28318;
		break;

	case basicEnemyFast:

		textureComp->texture = Jelly1;
		enemyComp->health = 40;
		enemyComp->moveSpeed = 1.1f;
		enemyComp->slowedSpeed = 0.5f;
		enemyComp->value = 10;
		enemyComp->moveAngle = 6.28318;
		break;

	case tankEnemyEasy:
		textureComp->texture = crab;
		enemyComp->health = 80;
		enemyComp->moveSpeed = 0.4f;
		enemyComp->slowedSpeed = 0.5f;
		enemyComp->value = 15;
		enemyComp->moveAngle = 6.28318;
		break;

	case tankEnemyHard: //3
		textureComp->texture = crab;
		enemyComp->health = 100;
		enemyComp->moveSpeed = 0.6f;
		enemyComp->slowedSpeed = 0.5f;
		enemyComp->value = 25;
		enemyComp->moveAngle = 6.28318;
		break;

	case enemyChaserEasy: //4
		textureComp->texture = sharkTex;
		enemyTransform->scale.x = 160;
		enemyTransform->scale.y = 96;
		enemyComp->health = 80;
		enemyComp->moveSpeed = 0.85f;
		enemyComp->slowedSpeed = 0.5f;
		enemyComp->value = 20;
		enemyComp->moveAngle = 6.28318;
		enemyComp->canChase = true;
		break;

	case enemyChaserHard: //5
		enemyTransform->scale.x = 160;
		enemyTransform->scale.y = 96;
		textureComp->texture = sharkTex;
		enemyComp->health = 120;
		enemyComp->moveSpeed = 0.7f;
		enemyComp->slowedSpeed = 0.5f;
		enemyComp->value = 30;
		enemyComp->moveAngle = 6.28318;
		enemyComp->canChase = true;
		break;
	default:
		textureComp->texture = crab;
		enemyComp->health = 20;
		enemyComp->moveSpeed = 0.7f;
		enemyComp->slowedSpeed = 0.5f;
		enemyComp->value = 10;
		enemyComp->moveAngle = 6.28318;
		break;

	}
	enemyComp->tempSpeed = enemyComp->moveSpeed;
	enemySpeed = enemyComp->moveSpeed;
	enemyComp->CurrState = onPath;
}
void EnemyUpdate(Object_Info* enemy)
{
	TransformComponent* enemyTransform = GetTransformComp(enemy);
	PhysicsComponent* enemyPhysics = GetPhysicsComp(enemy);
	EnemyComponent* enemyComp = GetEnemyComp(enemy);
	TransformComponent* playerTransform = GetTransformComp(pPlayer);
	//Moves the enemy in its "movement direction"
	Vector2DSet(&enemyPhysics->velocity, cos(enemyComp->moveAngle) * enemyComp->moveSpeed, sin(enemyComp->moveAngle) * enemyComp->moveSpeed);

	if (enemyComp->isRotating == ACTIVE) //runs the function to rotate the enemy
		EnemyRotate(enemy, enemyComp->rotateAngle);

	switch (enemyComp->CurrState)
	{
	case(chasing) :
		EnemyChase(enemy, playerTransform->position);
			break;
		case(onPath) :

			break;
		case(returning) :
			ReturnToPath(enemy, enemyComp->nextNode);
			break;

		case(finding) :
			FindPath(enemy);
	}

	//These two if statements make sure the rotation stays within -2PI and 2PI
	if (enemyComp->moveAngle > 6.28318)
		enemyComp->moveAngle -= 6.28318;
	else if (enemyComp->moveAngle <= -6.28318)
		enemyComp->moveAngle += 6.28318;

	if (enemyComp->health <= 0)
	{
		money += enemyComp->value;
		Remove_Object(enemy);
	}
	
	if (enemyComp->canChase == ACTIVE && Vector2DDistance(&enemyTransform->position, &playerTransform->position) < CHASE_RANGE)
	{
		enemyComp->CurrState = chasing;
	}
	if (enemyComp->CurrState == chasing && Vector2DDistance(&enemyTransform->position, &playerTransform->position) > CHASE_RANGE + 150)
	{
		FindPath(enemy);
	}

	//make the shark enemy face the right direction
	if (enemyComp->canChase)
	{
		if (enemyPhysics->velocity.x < 0.0f)
		{
			if (enemyTransform->scale.x > 0.0f)
				enemyTransform->scale.x = -enemyTransform->scale.x;
		}
		else
		{
			if (enemyTransform->scale.x < 0.0f)
				enemyTransform->scale.x = -enemyTransform->scale.x;
		}
	}
}

void EnemyChase(Object_Info* enemy, Vector2D playerPos)
{
		Vector2D direction;
		TransformComponent* enemyTransform = GetTransformComp(enemy);
		PhysicsComponent* enemyPhysicsComp = GetPhysicsComp(enemy);
		EnemyComponent* enemyComp = GetEnemyComp(enemy);
		Vector2DSub(&direction, &playerPos, &enemyTransform->position);
		//Vector2DNormalize(&direction, &direction);
		Vector2D V1;
		Vector2DSet(&V1, enemyPhysicsComp->velocity.y * -1, enemyPhysicsComp->velocity.x);
		Vector2DNormalize(&V1, &V1);
		float dotToTarget = Vector2DDotProduct(&direction, &V1);
		//AESysPrintf("dot: %i, direction: (%f, %f) \n", dotToTarget, direction.x, direction.y);
		if (dotToTarget != 0)
		{
			if (dotToTarget > 0)
			{
				enemyComp->moveAngle += 0.1;// *frameTime;
			}
			else
			{
				enemyComp->moveAngle -= 0.1;// *frameTime;
			}
		}
}



//this function finds the nearest node to the enemy and angles towards it

void FindPath(Object_Info* enemy)
{
	Object_Info* closestEnemy = NULL;

	TransformComponent* enemyPos = GetTransformComp(enemy);
	EnemyComponent* enemyComp = GetEnemyComp(enemy);
	float closestDistance = 10000;
	for (int i = 0; i < OBJECT_NUM_MAX; i++)
	{
		Object_Info* pObject = ObjectList + i;

		if (pObject->ActiveFlag == INACTIVE)
			continue;

		if (pObject->Type == OBJECT_PATH)
		{
			TransformComponent* pathPos = GetTransformComp(pObject);
			if (Vector2DDistance(&enemyPos->position, &pathPos->position) < closestDistance)
			{
				enemyComp->nextNode = pObject;
				closestDistance = Vector2DDistance(&enemyPos->position, &pathPos->position);
			}
		}
		if (enemyComp->nextNode != NULL)
		{
			enemyComp->CurrState = returning;
		}
	}
	
}

void ReturnToPath(Object_Info* enemy, Object_Info* path)
{
	Vector2D direction;
	TransformComponent* enemyTransform = GetTransformComp(enemy);
	TransformComponent* pathTransform = GetTransformComp(path);
	PhysicsComponent* enemyPhysicsComp = GetPhysicsComp(enemy);
	EnemyComponent* enemyComp = GetEnemyComp(enemy);
	Vector2DSub(&direction, &pathTransform->position, &enemyTransform->position);
	//Vector2DNormalize(&direction, &direction);
	Vector2D V1;
	Vector2DSet(&V1, enemyPhysicsComp->velocity.y * -1, enemyPhysicsComp->velocity.x);
	Vector2DNormalize(&V1, &V1);
	float dotToTarget = Vector2DDotProduct(&direction, &V1);
	//AESysPrintf("dot: %i, direction: (%f, %f) \n", dotToTarget, direction.x, direction.y);
	if (dotToTarget != 0)
	{
		if (dotToTarget > 0)
		{
			enemyComp->moveAngle += 0.1;// *frameTime;
		}
		else
		{
			enemyComp->moveAngle -= 0.1;// *frameTime;
		}
	}

}
void EnemyRotate(Object_Info* enemy, float PathAngle)
{
	frameTime = AEFrameRateControllerGetFrameTime();
	//AESysPrintf("FrameTime is: %f\n", frameTime);
	TransformComponent* enemyTransform = GetTransformComp(enemy);
	EnemyComponent* enemyComp = GetEnemyComp(enemy);
	enemyComp->CurrState = onPath;
	if (PathAngle == 0)
		PathAngle = PI * 2;

	if (enemyComp->moveAngle == 0)
		enemyComp->moveAngle = PI * 2;

	float angleDiff = enemyComp->moveAngle - PathAngle; //angleDiff is the difference(angle) between the enemies movement rotation

	if (angleDiff <= -6.28318) //keeps above -2PI
		enemyComp->moveAngle += 6.28318;

	if (enemyComp->moveAngle != PathAngle)
	{
		if (fabs(angleDiff) < 1.0f) //snaps when the angles are close
		{
			enemyComp->moveAngle = PathAngle;
			enemyComp->isRotating = INACTIVE; //stops this function
			enemyComp->moveSpeed = enemyComp->tempSpeed;
		}
		else
		{
			enemyComp->moveSpeed = enemyComp->slowedSpeed; //slows the enemies movement for the duration of the rotation

														   //different cases for which way to rotate
			if (angleDiff < 0 && angleDiff > -2.0f)
				enemyComp->moveAngle += 0.02f * (frameTime * 60.0f);
			else if (angleDiff < 3.14 && angleDiff > 0.0f)
				enemyComp->moveAngle -= 0.02f * (frameTime * 60.0f);
			else if (angleDiff < -3.14)
				enemyComp->moveAngle -= 0.1f * (frameTime * 60.0f);
			else if (angleDiff > 3.14)
				enemyComp->moveAngle += 0.02f * (frameTime * 60.0f);
			else //if unknown rotation then snap
			{
				enemyComp->moveAngle = PathAngle;
				enemyComp->isRotating = INACTIVE;
				enemyComp->moveSpeed = enemyComp->tempSpeed;
			}

		}

	}
}