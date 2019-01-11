// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	TowerBehavior.c
// Author			:	Jathan Hibbs
// Editted       : Jake Fletcher
// Creation Date	:	2017/03/03
// ---------------------------------------------------------------------------

#include "main.h"
#include "objects.h"
#include "TowerBehavior.h"
#include "GameState_Level1.h"
#include "currency.h"
#include "animation.h"

#include <math.h>

#define BULLET_SPEED 5.0f
#define EXPAND_DURATION 1.0f
int isLoaded;
extern int money;
extern Object_Info ObjectList[OBJECT_NUM_MAX];


extern AEGfxVertexList *squareMesh;
AEGfxTexture* bullet;
AEGfxTexture* towerTexture;
AEGfxTexture* circle;
extern AEGfxTexture* PufferTowerTex;

//sound stuff
extern FMOD::System *fmodSys;
extern FMOD::Sound * squidTowerAttackSound;

Object_Info* createTowerPos(Vector2D pos, int type)
{
	Object_Info* tower = Add_Object(OBJECT_TOWER);
	AddComponent(tower, COMPONENT_TRANSFORM);
	AddComponent(tower, COMPONENT_PHYSICS);
	AddComponent(tower, COMPONENT_MESH);
	AddComponent(tower, COMPONENT_TOWER);
	AddComponent(tower, COMPONENT_TEXTURE);

	MeshComponent* mesh = GetMeshComp(tower);
	mesh->mesh = squareMesh;

	TextureComponent* towTex = GetTextureComp(tower);
	towTex->texture = towerTexture;

	ObjectSetScale(tower, 100, 100);
	ObjectSetPosition(tower, pos.x, pos.y);

	TowerComponent* towerComp = GetTowerComp(tower);
	switch (type)
	{
		case standardTower:
			towerComp->target = NULL;
			towerComp->type = type;
			towerComp->range = 175;
			towerComp->fireSpeed = 2;
			towerComp->damage = 10;
			towerComp->fireCount = towerComp->fireSpeed * 100;
			break;

		case pufferTower:
			towerComp->target = NULL;
			towerComp->type = type;
			towerComp->range = 150;
			towerComp->fireSpeed = 2;
			towerComp->expandTime = 1;
			towerComp->damage = 10;
			towerComp->fireCount = towerComp->fireSpeed * 100;
			towerComp->expandCount = towerComp->expandTime * 100;
			towerComp->isExpanded = false;
			towerComp->expandSizeIncrease = 200;

			//texture and animation stuff
			towTex->texture = PufferTowerTex;
			towTex->isAnimated = true;
			towTex->framesX = 2;
			towTex->framesY = 2;
			towTex->startFrame = 1;
			towTex->endFrame = 3;
			towTex->animSpeed = 0.0f;
			towTex->frameCounter = 1;

			mesh->mesh = NULL;
			loadAnimation(tower);
			break;

		default:
			towerComp->target = NULL;
			towerComp->type = type;
			towerComp->range = 175;
			towerComp->fireSpeed = 2; //delay between expansions
			towerComp->expandTime = 1; //time expanded
			towerComp->damage = 10;
			towerComp->expandSizeIncrease = 150;
			towerComp->fireCount = towerComp->fireSpeed * 100;
			towerComp->expandCount = towerComp->expandTime * 100;
			break;
	}
	//debug circle
	/*Object_Info* rangeCircle = Add_Object(OBJECT_DEBUG);
	AddComponent(rangeCircle, COMPONENT_TRANSFORM);
	AddComponent(rangeCircle, COMPONENT_MESH);
	AddComponent(rangeCircle, COMPONENT_TEXTURE);
	AddComponent(rangeCircle, COMPONENT_PHYSICS);

	MeshComponent* debugMesh = GetMeshComp(rangeCircle);
	debugMesh->mesh = squareMesh;

	TextureComponent* debugTex = GetTextureComp(rangeCircle);
	debugTex->texture = circle;

	TowerComponent* towComp = GetTowerComp(tower);

	ObjectSetScale(rangeCircle, towComp->range*2.0, towComp->range*2.0);
	ObjectSetPosition(rangeCircle, pos.x, pos.y);*/

	return tower;
}

void updateTower(Object_Info* tower)
{
	updateTarget(tower);

	TransformComponent* towPos = GetTransformComp(tower);
	TowerComponent *tow = GetTowerComp(tower);
	TextureComponent* towTex = GetTextureComp(tower);

	if (tow->target != NULL && tow->type != pufferTower)
	{
		TransformComponent *towTarget = GetTransformComp(tow->target);
		//AESysPrintf("%f\n", towPos->angle);
		Vector2D direction;
		Vector2DSub(&direction, &towTarget->position, &towPos->position);

		Vector2D vec2;
		Vector2DSet(&vec2, cosf(towPos->angle ), sinf(towPos->angle ));
		Vector2DNormalize(&vec2, &vec2);
		float angleDirection = Vector2DDotProduct(&direction, &vec2);
		if (angleDirection > 15)
		{
			towPos->angle += 0.15f;
		}
		else if (angleDirection < -15)
		{
			towPos->angle -= 0.15f;
		}
	}
		
	towerFire(tower);
}

void updateTarget(Object_Info* tower)
{
	TowerComponent* towComp = GetTowerComp(tower);
	//not closest anymore, i just dont want to change the variable names
	Object_Info* closestEnemy = NULL;

	TransformComponent* towPos = GetTransformComp(tower);

	float distance = towComp->range;
	int currEnemyNum = 100;
	for (int i = 0; i < OBJECT_NUM_MAX; i++)
	{
		Object_Info* pObject = ObjectList + i;

		if (pObject->ActiveFlag == INACTIVE)
			continue;

		if (pObject->Type == OBJECT_ENEMY)
		{
			TransformComponent* enemyPos = GetTransformComp(pObject);
			EnemyComponent* enemyEnemy = GetEnemyComp(pObject);
			if (Vector2DDistance(&towPos->position, &enemyPos->position) < distance && enemyEnemy->enemyNum < currEnemyNum)
			{
				closestEnemy = pObject;
				currEnemyNum = enemyEnemy->enemyNum;
			}
		}
	}

	if (closestEnemy != NULL)
	{
		towComp->target = closestEnemy;
		//AESysPrintf("%f\n", distance);
	}
	else
	{
		towComp->target = NULL;
	}
}

void towerFire(Object_Info* tower)
{
	TowerComponent* towComp = GetTowerComp(tower);
	TransformComponent* towerPos = GetTransformComp(tower);
	TextureComponent* towTex = GetTextureComp(tower);
	switch (towComp->type)
	{
		case standardTower:
		{
			

			if (towComp->target != NULL)
			{
				TransformComponent* towTarget = GetTransformComp(towComp->target);
				Vector2D direction;
				Vector2DSub(&direction, &towTarget->position, &towerPos->position);
			
				Vector2D vec2;
				Vector2DSet(&vec2, cosf(towerPos->angle + PI), sinf(towerPos->angle + PI));
				Vector2DNormalize(&vec2, &vec2);
				float angleDirection = Vector2DDotProduct(&direction, &vec2);

				if (towComp->fireCount <= 0 && (angleDirection < 2 && angleDirection > -2))
				{
					//play sound
					fmodSys->playSound(FMOD_CHANNEL_FREE, squidTowerAttackSound, false, 0);

					Object_Info* tmpBullet = Add_Object(OBJECT_BULLET);

					AddComponent(tmpBullet, COMPONENT_TRANSFORM);
					AddComponent(tmpBullet, COMPONENT_PHYSICS);
					AddComponent(tmpBullet, COMPONENT_MESH);
					AddComponent(tmpBullet, COMPONENT_TEXTURE);
					AddComponent(tmpBullet, COMPONENT_BULLET);

					TransformComponent* bulletTransform = GetTransformComp(tmpBullet);
					PhysicsComponent* bulletPhysics = GetPhysicsComp(tmpBullet);
					MeshComponent* bulletMesh = GetMeshComp(tmpBullet);
					TextureComponent* bulletTex = GetTextureComp(tmpBullet);
					BulletComponent* bulletComp = GetBulletComp(tmpBullet);
					bulletComp->damage = towComp->damage;

					bulletMesh->mesh = squareMesh;
					bulletTex->texture = bullet;

					//sets bullet pos
					bulletTransform->position = towerPos->position;
					//set scale
					Vector2DSet(&bulletTransform->scale, 25, 25);

					//gets target
					TransformComponent* targetPos = GetTransformComp(towComp->target);
					PhysicsComponent* targetVel = GetPhysicsComp(towComp->target);

					//predict where to shoot
					Vector2D posPrediction;
					Vector2DSet(&posPrediction, targetPos->position.x, targetPos->position.y);
					Vector2DScaleAdd(&posPrediction, &targetVel->velocity, &posPrediction, BULLET_SPEED);

					//Vector2DSet(&bulletPhysics->velocity, cos(bulletTransform->angle) * BULLET_SPEED, sin(bulletTransform->angle) * BULLET_SPEED);
					Vector2DSub(&bulletPhysics->velocity, &posPrediction, &towerPos->position);
					Vector2DNormalize(&bulletPhysics->velocity, &bulletPhysics->velocity);
					Vector2DScale(&bulletPhysics->velocity, &bulletPhysics->velocity, BULLET_SPEED);

					towComp->fireCount = towComp->fireSpeed * 100;
				}
			}
			break;
		}
		case pufferTower:
		{
			if (towComp->target != NULL && towComp->isExpanded == false && towComp->fireCount <= 0) //expands it
			{
				towComp->isExpanded = true;
				TransformComponent* towTarget = GetTransformComp(towComp->target);
				
				towComp->expandCount = towComp->expandTime * 100;

				towTex->animSpeed = 1.0f;
			}

			else if (towComp->isExpanded == true && towComp->expandCount <= 0.0f) //when it should unexpand
			{
				towComp->isExpanded = false;
				towerPos->scale.x -= towComp->expandSizeIncrease;
				towerPos->scale.y -= towComp->expandSizeIncrease;
				towComp->fireCount = towComp->fireSpeed * 100;

				towTex->animSpeed = 0.0f;
				towTex->frameCounter = 1;
			}
			else if (towComp->isExpanded == true) //already expanded
			{
				//towComp->expandCount -= 1;
				if (towTex->frameCounter == 2)
				{
					if (towTex->animSpeed != 0.0f)
					{
						towerPos->scale.x += towComp->expandSizeIncrease;
						towerPos->scale.y += towComp->expandSizeIncrease;
						towTex->animSpeed = 0.0f;
					}
				}
			}
			break;
		}
	}
}

void towerUpgrade(Object_Info* towerPlatform, int type)
{
	TurretPlatformComponent* platform = GetTurretPlatformComp(towerPlatform);
	Object_Info* tower = GetTurretPlatformComp(towerPlatform)->tower;
	TowerComponent* towerTower = GetTowerComp(tower);

	switch (type)
	{
		case damage:
				towerTower->damage += 5;
			break;
		case fireRate:
				towerTower->fireSpeed -= 0.25;
			break;
		case changeTower:
				Vector2D pos = GetTransformComp(tower)->position;
				int towerType = GetTowerComp(tower)->type;
				Remove_Object(tower);
				if (towerType == 0)
					platform->tower = createTowerPos(pos, 1);
				if (towerType == 1)
					platform->tower = createTowerPos(pos, 0);
			break;
	}
}