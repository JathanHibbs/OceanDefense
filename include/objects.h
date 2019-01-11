// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	objects.h
// Author			:	Jasper Mix
// Creation Date	:	2017/02/21
// ---------------------------------------------------------------------------
#pragma once

#include "Vector2D.h"
#include "main.h"
#include "Matrix2D.h"
#include "2DGameEngineIncludes.h"
#include "GUI_Buttons.h"
#include "TextObject.h"


#define MAXSIZE 30
#define COMPONENT_NUM			16				// number of components to allocate space for in an object
#define OBJECT_NUM_MAX			2048			// the maximum number of objects



// ---------------------------------------------------------------------------
// enums
enum OBJECT_TYPE
{
	OBJECT_PLAYER,
	OBJECT_TURRET,
	OBJECT_BULLET,
	OBJECT_TOWER,
	OBJECT_ENEMY,
	OBJECT_PATH,
	OBJECT_DEBUG,
	OBJECT_PLAYER_WEAPON,
	OBJECT_SPAWNER,
	OBJECT_BASE,
	OBJECT_TURRET_PLATFORM,
	OBJECT_MENU,
	OBJECT_HUD,
};

enum COMPONENT_TYPE
{
	COMPONENT_TRANSFORM,
	COMPONENT_PHYSICS,
	COMPONENT_MESH,
	COMPONENT_TEXTURE,
	COMPONENT_PARTICLE_EMITTER,
	COMPONENT_TOWER,
	COMPONENT_ENEMY,
	COMPONENT_BULLET,
	COMPONENT_PLAYER_WEAPON,
	COMPONENT_SPAWNER,
	COMPONENT_BASE,
	COMPONENT_TURRET_PLATFORM,
	COMPONENT_MENU
};

enum State { chasing, onPath, returning, finding }; //enemy states

enum renderLevel
{
	bottom,
	normal,
	top,
	veryTop
};

typedef struct Wave
{
	bool activeFlag = false;
	int enemyType = 0;
	int enemyCount = 0;
	float interval = 0;
}Wave;


// ---------------------------------------------------------------------------
// game object stuff
typedef struct Object_Component Object_Component;
struct Object_Component
{
	unsigned long Type;

	void (*ComponentLoad)(Object_Component* Component);
	void (*ComponentUpdate)(Object_Component* Component, float frameTime_);

	void *data;

};

typedef struct Object_Info
{
	unsigned long Type;
	Object_Component* Components[COMPONENT_NUM];
	int componentNum;
	int ActiveFlag;

}Object_Info;


//Object_Info ObjectList[OBJECT_NUM_MAX];
//Object_Info* ObjectRenderOrder[OBJECT_NUM_MAX];


// ---------------------------------------------------------------------------
// component types
typedef struct
{
	Vector2D position;
	Vector2D scale;
	Matrix2D TramsformMatrix;
	float angle;
}TransformComponent;

typedef struct
{
	Vector2D velocity;
	float rotVelocity;
}PhysicsComponent;

typedef struct
{
	AEGfxVertexList *mesh;
}MeshComponent;

typedef struct
{
	bool isVisible;
	//bool renderOnTop;
	int level;
	AEGfxTexture* texture;

	//animation stuff
	bool isAnimated;
	int frameNum;
	int framesX;
	int framesY;
	int frameCounter;
	float animSpeed;
	float animCounter;
	int startFrame;
	int endFrame;
	float texU;
	float texV;
}TextureComponent;

typedef struct
{
	unsigned long particleType;
	float ParticlesPerSec;
	float x, y, width, height;
}ParticleEmitterComponent;

typedef struct
{
	Object_Info* target;
	int type;
	float range;
	float fireSpeed;
	float expandTime;
	float damage;
	float fireCount;
	float expandCount;
	bool isExpanded;
	int expandSizeIncrease;
	
}TowerComponent;

typedef struct
{
	Object_Info* nextNode;
	int type;
	float moveSpeed;
	float tempSpeed;
	float slowedSpeed;
	float health;
	int value;
	unsigned int isRotating;
	bool hitByWeapon;
	bool hitByWeapon2;
	bool canChase;
	float rotateAngle;
	float moveAngle;
	int enemyNum;
	unsigned int CurrState;
	
}EnemyComponent;

typedef struct
{
	float damage;
}BulletComponent;

typedef struct
{
	float damage;
	float attackDuration;
}PlayerWeaponComponent;

typedef struct
{
	Wave* WaveInfo;
	float CurrDelayTime;
	float CurrWait;
	int TotalWaves;
	int     CurrWave;
	int    CurrEnemy;
}SpawnerComponent;

typedef struct
{
	int health;
	int healingPerSecond;
}BaseComponent;

typedef struct
{
	bool hasTower;
	Object_Info* tower;
	int upgrade1;
	int upgrade2;
	int upgrade3;
}TurretPlatformComponent;

typedef struct
{
	Button_Info* option1;
	Button_Info* option2;
	Button_Info* option3;

	TextObject* option1Price;
	TextObject* option2Price; 
	TextObject* option3Price;

	TextObject* upgrade1Text;
	TextObject* upgrade2Text;
	TextObject* upgrade3Text;

	int menu_type;
}MenuComponent;


// ---------------------------------------------------------------------------
// Componant function prototypes
void TransformComponentLoad(Object_Component * Component);
void TransformComponentUpdate(Object_Component * Component, float frameTime_);

void PhysicsComponentLoad(Object_Component * Component);
void PhysicsComponentUpdate(Object_Component * Component, float frameTime_);

void MeshComponentLoad(Object_Component * Component);
void MeshComponentUpdate(Object_Component * Component, float frameTime_);

void TextureComponentLoad(Object_Component * Component);
void TextureComponentUpdate(Object_Component * Component, float frameTime_);

void ParticleEmitterComponentLoad(Object_Component * Component);
void ParticleEmitterComponentUpdate(Object_Component * Component, float frameTime_);

void TowerComponentLoad(Object_Component * Component);
void TowerComponentUpdate(Object_Component * Component, float frameTime_);

void EnemyComponentLoad(Object_Component * Component);
void EnemyComponentUpdate(Object_Component * Component, float frameTime_);

void BulletComponentLoad(Object_Component * Component);
void BulletComponentUpdate(Object_Component * Component, float frameTime_);

void PlayerWeaponComponentLoad(Object_Component * Component);
void PlayerWeaponComponentUpdate(Object_Component * Component, float frameTime_);

void SpawnerComponentLoad(Object_Component * Component);
void SpawnerComponentUpdate(Object_Component * Component, float frameTime_);

void BaseComponentLoad(Object_Component * Component);
void BaseComponentUpdate(Object_Component * Component, float frameTime_);

void TurretPlatformComponentLoad(Object_Component * Component);
void TurretPlatformComponentUpdate(Object_Component * Component, float frameTime_);

void MenuComponentLoad(Object_Component * Component);
void MenuComponentUpdate(Object_Component * Component, float frameTime_);

// ---------------------------------------------------------------------------
// functions for handling components
void AddComponent(Object_Info * object_, unsigned long compType);


// ---------------------------------------------------------------------------
// functions for getting components
Object_Component* GetComponent(Object_Info* object_, unsigned long compType);

TransformComponent* GetTransformComp(Object_Info* object_);
PhysicsComponent* GetPhysicsComp(Object_Info* object_);
MeshComponent* GetMeshComp(Object_Info* object_);
TextureComponent* GetTextureComp(Object_Info* object_);
ParticleEmitterComponent* GetParticleEmitterComp(Object_Info* object_);
TowerComponent* GetTowerComp(Object_Info* object_);
BulletComponent* GetBulletComp(Object_Info* object_);
EnemyComponent* GetEnemyComp(Object_Info* object_);
PlayerWeaponComponent* GetPlayerWeaponComp(Object_Info* object_);
SpawnerComponent* GetSpawnerComp(Object_Info* object_);
BaseComponent* GetBaseComp(Object_Info* object_);
TurretPlatformComponent* GetTurretPlatformComp(Object_Info* object_);
MenuComponent* GetMenuComp(Object_Info* object_);


// ---------------------------------------------------------------------------
// functions setting components
void ObjectSetPosition(Object_Info* object_, float x, float y);
void ObjectSetVelocity(Object_Info* object_, float x, float y);
void ObjectSetScale(Object_Info* object_, float x, float y);

// ---------------------------------------------------------------------------
// functions for adding and removing objects
Object_Info* Add_Object(unsigned long ObjectType);							// creates an object with all the transform/physics valus set to null.
void Remove_Object(Object_Info* object_);									// removes an object
