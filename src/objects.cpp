// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	objects.c
// Author			:	Jasper Mix
// Creation Date	:	2017/02/21
// ---------------------------------------------------------------------------

#include "objects.h"
#include "TowerBehavior.h"
#include "main.h"

extern Object_Info ObjectList[OBJECT_NUM_MAX];


AEGfxVertexList *squareMesh;
// ---------------------------------------------------------------------------
// component functions
void TransformComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(TransformComponent));
	TransformComponent* tmpTransform = (TransformComponent*)Component->data;

	// initialize all the transform data
	tmpTransform->angle = 0;
	Vector2DZero(&tmpTransform->position);
	Vector2DZero(&tmpTransform->scale);

	Matrix2DIdentity(&tmpTransform->TramsformMatrix);
}
void TransformComponentUpdate(Object_Component * Component, float frameTime_)
{
	
}


void PhysicsComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(PhysicsComponent));

	// Initialize all the physics data
	PhysicsComponent* tmpPhysics = (PhysicsComponent*)Component->data;
	Vector2DZero(&tmpPhysics->velocity);
	tmpPhysics->rotVelocity = 0.0f;
}
void PhysicsComponentUpdate(Object_Component * Component, float frameTime_)
{

}

void MeshComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(MeshComponent));
}
void MeshComponentUpdate(Object_Component * Component, float frameTime_)
{

}

void TextureComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(TextureComponent));
	TextureComponent* tmpText = (TextureComponent*)Component->data;
	tmpText->isVisible = true;
	tmpText->level = normal;
	
	//animation
	tmpText->animCounter = 0.0f;
	tmpText->animSpeed = 1.0f;
	tmpText->endFrame = 0;
	tmpText->frameCounter = 0;
	tmpText->frameNum = 0;
	tmpText->framesX = 1;
	tmpText->framesY = 1;
	tmpText->isAnimated = false;
	tmpText->startFrame = 0;
	tmpText->texU = 0.0f;
	tmpText->texV = 0.0f;
}
void TextureComponentUpdate(Object_Component * Component, float frameTime_)
{

}

void ParticleEmitterComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(ParticleEmitterComponent));
	ParticleEmitterComponent* tmpParticleEmitter = (ParticleEmitterComponent*)Component->data;
	tmpParticleEmitter->ParticlesPerSec = 0;
	tmpParticleEmitter->height = 0;
	tmpParticleEmitter->width = 0;
	tmpParticleEmitter->x = 0;
	tmpParticleEmitter->y = 0;
	tmpParticleEmitter->particleType = NULL;
}
void ParticleEmitterComponentUpdate(Object_Component * Component, float frameTime_)
{

}

void TowerComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(TowerComponent));
	TowerComponent* tempTower = (TowerComponent*)Component->data;
	tempTower->target = NULL;
	tempTower->type = standardTower;
	tempTower->range = 250;
	tempTower->fireSpeed = 1;
	tempTower->damage = 10;
	tempTower->fireCount = tempTower->fireSpeed * 100;
}
void TowerComponentUpdate(Object_Component * Component, float frameTime_)
{
}

void EnemyComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(EnemyComponent));
	EnemyComponent* tempEnemy = (EnemyComponent*)Component->data;
	tempEnemy->nextNode = NULL;
	tempEnemy->moveSpeed = 3;
	tempEnemy->tempSpeed = 3;
	tempEnemy->slowedSpeed = 1;
	tempEnemy->isRotating = INACTIVE;
	tempEnemy->hitByWeapon = INACTIVE;
	tempEnemy->hitByWeapon2 = INACTIVE;
	tempEnemy->canChase = false;
	tempEnemy->moveAngle = 0.0f;
	tempEnemy->rotateAngle = 0.0f;
	tempEnemy->value = 20;
	tempEnemy->enemyNum = 0;
	tempEnemy->CurrState = onPath;
}
void EnemyComponentUpdate(Object_Component * Component, float frameTime_)
{
}

void BulletComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(EnemyComponent));
	BulletComponent* tempBullet = (BulletComponent*)Component->data;
	tempBullet->damage = 0;
}
void BulletComponentUpdate(Object_Component * Component, float frameTime_)
{
}



void PlayerWeaponComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(PlayerWeaponComponent));
	PlayerWeaponComponent* tmpWeaponComp = (PlayerWeaponComponent*)Component->data;
	tmpWeaponComp->attackDuration = 0.0f;
	tmpWeaponComp->damage = 15;
}
void PlayerWeaponComponentUpdate(Object_Component * Component, float frameTime_)
{

}

void SpawnerLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(SpawnerComponent));
	SpawnerComponent* tmpSpawnerComp = (SpawnerComponent*)Component->data;
	
	tmpSpawnerComp->CurrDelayTime = 0;
	tmpSpawnerComp->CurrWait = 0;
	tmpSpawnerComp->TotalWaves = 0;
	tmpSpawnerComp->CurrWave = 1;
	tmpSpawnerComp->CurrEnemy = 1;
}

void SpawnerUpdate(Object_Component * Component, float frameTime_)
{

}


void BaseLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(BaseComponent));
	BaseComponent* tmpSpawnerComp = (BaseComponent*)Component->data;

	tmpSpawnerComp->health = 20;
}

void BaseUpdate(Object_Component * Component, float frameTime_)
{

}

void TurretPlatformLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(TurretPlatformComponent));
	TurretPlatformComponent* tmpTurretPlatformComp = (TurretPlatformComponent*)Component->data;

	tmpTurretPlatformComp->hasTower = false;
	tmpTurretPlatformComp->tower = NULL;

	tmpTurretPlatformComp->upgrade1 = 0;
	tmpTurretPlatformComp->upgrade2 = 0;
	tmpTurretPlatformComp->upgrade3 = 0;
}

void TurretPlatformUpdate(Object_Component * Component, float frameTime_)
{

}

void MenuLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(MenuComponent));
	MenuComponent* tmpMenuComp = (MenuComponent*)Component->data;

	tmpMenuComp->menu_type = 0;
	tmpMenuComp->option1 = NULL;
	tmpMenuComp->option2 = NULL;
	tmpMenuComp->option3 = NULL;
	tmpMenuComp->option1Price = NULL;
	tmpMenuComp->option2Price = NULL;
	tmpMenuComp->option3Price = NULL;
	tmpMenuComp->upgrade1Text = NULL;
	tmpMenuComp->upgrade2Text = NULL;
	tmpMenuComp->upgrade3Text = NULL;
}

void MenuUpdate(Object_Component * Component, float frameTime_)
{

}

void SpawnerComponentLoad(Object_Component * Component)
{
	Component->data = malloc(sizeof(SpawnerComponent));
	SpawnerComponent* tmpMenuComp = (SpawnerComponent*)Component->data;

	tmpMenuComp->WaveInfo = new Wave[MAXSIZE];
}

void SpawnerComponentLoadUpdate(Object_Component * Component, float frameTime_)
{

}
// ---------------------------------------------------------------------------
// functions for handling components

void AddComponent(Object_Info * object_, unsigned long compType)
{
	// return if the component array is full
	if (object_->componentNum >= COMPONENT_NUM)
	{
		AESysPrintf("\n////////////////////////\nTo many object components\n////////////////////////\n");
		return;
	}
	object_->Components[object_->componentNum] = /*malloc(sizeof(Object_Component))*/ new Object_Component;
	switch (compType)
	{
	case COMPONENT_TRANSFORM:
		object_->Components[object_->componentNum]->ComponentLoad = TransformComponentLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = TransformComponentUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_TRANSFORM;
		break;

	case COMPONENT_PHYSICS:
		object_->Components[object_->componentNum]->ComponentLoad = PhysicsComponentLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = PhysicsComponentUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_PHYSICS;
		break;

	case COMPONENT_MESH:
		object_->Components[object_->componentNum]->ComponentLoad = MeshComponentLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = MeshComponentUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_MESH;
		break;

	case COMPONENT_TEXTURE:
		object_->Components[object_->componentNum]->ComponentLoad = TextureComponentLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = TextureComponentUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_TEXTURE;
		break;

	case COMPONENT_PARTICLE_EMITTER:
		object_->Components[object_->componentNum]->ComponentLoad = ParticleEmitterComponentLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = ParticleEmitterComponentUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_PARTICLE_EMITTER;
		break;

	case COMPONENT_TOWER:
		object_->Components[object_->componentNum]->ComponentLoad = TowerComponentLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = TowerComponentUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_TOWER;
		break;

	case COMPONENT_ENEMY:
		object_->Components[object_->componentNum]->ComponentLoad = EnemyComponentLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = EnemyComponentUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_ENEMY;
		break;

	case COMPONENT_BULLET:
		object_->Components[object_->componentNum]->ComponentLoad = BulletComponentLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = BulletComponentUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_BULLET;
		break;

	case COMPONENT_PLAYER_WEAPON:
		object_->Components[object_->componentNum]->ComponentLoad = PlayerWeaponComponentLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = PlayerWeaponComponentUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_PLAYER_WEAPON;
		break;


	case COMPONENT_SPAWNER:
		object_->Components[object_->componentNum]->ComponentLoad =SpawnerLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = SpawnerUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_SPAWNER;
		break;


	case COMPONENT_BASE:
		object_->Components[object_->componentNum]->ComponentLoad = BaseLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = BaseUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_BASE;
		break;

	case COMPONENT_TURRET_PLATFORM:
		object_->Components[object_->componentNum]->ComponentLoad = TurretPlatformLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = TurretPlatformUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_TURRET_PLATFORM;
		break;

	case COMPONENT_MENU:
		object_->Components[object_->componentNum]->ComponentLoad = MenuLoad;
		object_->Components[object_->componentNum]->ComponentUpdate = MenuUpdate;

		object_->Components[object_->componentNum]->Type = COMPONENT_MENU;
		break;
	}
	object_->Components[object_->componentNum]->ComponentLoad(object_->Components[object_->componentNum]);
	object_->componentNum++;
	
}


// ---------------------------------------------------------------------------
// functions for getting components
Object_Component* GetComponent(Object_Info* object_, unsigned long compType)
{
	int i;
	Object_Component* ObjectComponent;
	for (i = 0; i < object_->componentNum; i++)
	{
		if (object_->Components[i]->Type == compType)
			break;

		else if (i == object_->componentNum - 1)
		{
			("\n////////////////////////\nObject Component not found\n////////////////////////\n");
		}
	}
	ObjectComponent = object_->Components[i];
	return ObjectComponent;
}


// ---------------------------------------------------------------------------
// functions setting components
void ObjectSetPosition(Object_Info* object_, float x, float y)
{
	TransformComponent* tmpComponent = GetTransformComp(object_);
	tmpComponent->position.x = x;
	tmpComponent->position.y = y;
}

void ObjectSetVelocity(Object_Info* object_, float x, float y)
{
	PhysicsComponent* tmpComponent = GetPhysicsComp(object_);
	tmpComponent->velocity.y = y;
	tmpComponent->velocity.x = x;
}

void ObjectSetScale(Object_Info* object_, float x, float y)
{
	TransformComponent* tmpComponent = GetTransformComp(object_);
	tmpComponent->scale.x = x;
	tmpComponent->scale.y = y;
}

// these functions use the "GetComponent" function to find a specific component, then returns the "data" component
TransformComponent* GetTransformComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	TransformComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_TRANSFORM);
	ObjectComponent = (TransformComponent*)TmpComp->data;

	return ObjectComponent;
}

PhysicsComponent* GetPhysicsComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	PhysicsComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_PHYSICS);
	ObjectComponent = (PhysicsComponent*)TmpComp->data;

	return ObjectComponent;
}

MeshComponent* GetMeshComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	MeshComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_MESH);
	ObjectComponent = (MeshComponent*)TmpComp->data;

	return ObjectComponent;
}

TextureComponent* GetTextureComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	TextureComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_TEXTURE);
	ObjectComponent = (TextureComponent*)TmpComp->data;

	return ObjectComponent;
}

ParticleEmitterComponent* GetParticleEmitterComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	ParticleEmitterComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_PARTICLE_EMITTER);
	ObjectComponent = (ParticleEmitterComponent*)TmpComp->data;

	return ObjectComponent;
}

TowerComponent* GetTowerComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	TowerComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_TOWER);
	ObjectComponent = (TowerComponent*)TmpComp->data;

	return ObjectComponent;
}

EnemyComponent* GetEnemyComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	EnemyComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_ENEMY);
	ObjectComponent = (EnemyComponent*)TmpComp->data;

	return ObjectComponent;
}

BulletComponent* GetBulletComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	BulletComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_BULLET);
	ObjectComponent = (BulletComponent*)TmpComp->data;

	return ObjectComponent;
}

PlayerWeaponComponent* GetPlayerWeaponComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	PlayerWeaponComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_PLAYER_WEAPON);
	ObjectComponent = (PlayerWeaponComponent*)TmpComp->data;

	return ObjectComponent;
}

BaseComponent* GetBaseComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	BaseComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_BASE);
	ObjectComponent = (BaseComponent*)TmpComp->data;

	return ObjectComponent;
}

TurretPlatformComponent* GetTurretPlatformComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	TurretPlatformComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_TURRET_PLATFORM);
	ObjectComponent = (TurretPlatformComponent*)TmpComp->data;

	return ObjectComponent;
}

MenuComponent* GetMenuComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	MenuComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_MENU);
	ObjectComponent = (MenuComponent*)TmpComp->data;

	return ObjectComponent;
}

SpawnerComponent* GetSpawnerComp(Object_Info* object_)
{
	Object_Component* TmpComp;
	SpawnerComponent* ObjectComponent;

	TmpComp = GetComponent(object_, COMPONENT_SPAWNER);
	ObjectComponent = (SpawnerComponent*)TmpComp->data;

	return ObjectComponent;
}

// ---------------------------------------------------------------------------
// functions for adding and removing objects

Object_Info* Add_Object(unsigned long ObjectType)
{
	Object_Info* newObject;

	// find a free spot in the Object list
	for (int i = 0; i < OBJECT_NUM_MAX; i++)
	{
		Object_Info* pObject = ObjectList + i;

		if (pObject->ActiveFlag == INACTIVE)
		{
			newObject = pObject;
			break;
		}

	}

	newObject->Type = ObjectType;
	newObject->componentNum = 0;
	newObject->ActiveFlag = ACTIVE;


	return newObject;
}

void Remove_Object(Object_Info* object_)
{
	//free all the data in the objects components
	for (int i = 0; i < COMPONENT_NUM; i++)
	{
		if (object_->Components[i] != NULL)
		{
			free(object_->Components[i]->data);
			object_->Components[i]->data = NULL;
		}
	}

	//free all of the objects components
	/*(for (int i = 0; i < object_->componentNum; i++)
	{
		if (object_->Components[i] != NULL)
		{
			free(object_->Components[i]);
			object_->Components[i] = NULL;
		}
	}(*/
	
	object_->ActiveFlag = INACTIVE;
	object_->componentNum = 0;
}