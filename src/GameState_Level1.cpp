// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	GameState_Level1.c
// Author			:	Jasper Mix
// Edited           :   Jake Fletcher
// Also Edited      :   Jathan Hibbs
// Creation Date	:	2017/02/21
// ---------------------------------------------------------------------------

#include "main.h"

#include "Math2d.h"
#include "Matrix2D.h"
#include "Vector2D.h"

#include "objects.h"
#include "PlayerBehavior.h"
#include "TowerBehavior.h"
#include "Particles.h"
#include "2DGameEngineIncludes.h"
#include "PathObjectScript.h"
#include "currency.h"
#include "EnemyBehavior.h"
#include "WaveSpawnObject.h"
#include "TileSetFunctions.h"
#include "EnemyMapFunctions.h"
#include "GUI_Buttons.h"
#include "GameState_LevelSelect.h"
#include "BinaryMap.h"
#include "popupMenu.h"
#include "animation.h"

//for text
#include <stdbool.h>
#include "AEEngine.h"
#include "TextObject.h"
#include "TextManager.h"
#include <fstream>

// ---------------------------------------------------------------------------
//defines
#define BULLET_SPEED					20.0f
// ---------------------------------------------------------------------------
// mesh declarations
static AEGfxVertexList *Mesh;
extern AEGfxVertexList *squareMesh;
extern Object_Info* PlayerWeapon;
extern AEGfxVertexList *tileMesh;
extern AEGfxVertexList* ButtonMesh;
AEGfxVertexList *leftScrollMesh;
AEGfxVertexList *rightScrollMesh;
AEGfxVertexList *midScrollMesh;
AEGfxVertexList *heartMesh;

// make a pointer to the player
Object_Info* pPlayer;
Object_Info* ObjectRenderOrder[OBJECT_NUM_MAX];
Object_Info ObjectList[OBJECT_NUM_MAX];

// textures
AEGfxTexture* playerBaseTex;
AEGfxTexture* playerTurretTex;
AEGfxTexture* BulletTex;
AEGfxTexture* scrollTex;
AEGfxTexture* scrollMidTex;
AEGfxTexture* turretPlatform;
AEGfxTexture* heartTex;
AEGfxTexture* heartEmptyTex;
AEGfxTexture* BaseTex;
AEGfxTexture* sharkTex;
AEGfxTexture* pauseScreenTex;
AEGfxTexture* pauseMenuButtonTex;
AEGfxTexture* pauseQuitButtonTex;
AEGfxTexture* caveTex;
AEGfxTexture* PufferTowerTex;
extern AEGfxTexture* PlayerWeaponTex;
extern AEGfxTexture* Jelly1;
extern AEGfxTexture* crab;
extern AEGfxTexture* towerTexture;
extern AEGfxTexture* PopupMenuTex;
extern AEGfxTexture* bullet;
extern AEGfxTexture* circle;
AEGfxTexture* pufferSprite;
AEGfxTexture* sword;
AEGfxTexture* watch;
AEGfxTexture* meter;

extern int spawnerCount;
extern int TotalWaves;
extern int CurrWave;
extern float WaveLength;
extern int GlobalTotalWaves;
float WaveTime = 1;
//pause menu stuff
Button_Info* menuPauseButton;
Button_Info* quitPauseButton;

Vector2D menuPauseButtonPos, quitPauseButtonPos;

AEGfxVertexList* pauseScreenMesh;

//level select stuff
extern unsigned int selectedLevel;
extern enum LEVEL
{
	LEVEL1,
	LEVEL2,
	LEVEL3
};

//sound stuff
extern FMOD::System *fmodSys;
FMOD::Sound * enemyDamageSound;
FMOD::Sound * playerAttackSound;
FMOD::Sound * squidTowerAttackSound;

//music
extern FMOD::Channel * musicChannel;
FMOD::Sound * gameMusic;
extern FMOD::Sound * menuMusic;
extern bool musicPlaying;


//player health stuff
AEGfxTexture* health1;
AEGfxTexture* health2;
AEGfxTexture* health3;
AEGfxTexture* health4;
AEGfxTexture* health5;

float turretAngle = 0;
float counter = 0;
int money = STARTMONEY;
extern int health;
bool playerIsColliding = false;
bool dynamicCamera = false;
extern bool isDead;
bool isPaused = false;
extern int BINARY_MAP_WIDTH;
extern int BINARY_MAP_HEIGHT;
Object_Info* enemyCollidingWith = NULL;
TextObject* goldText;
TextObject* baseHealth;
TextObject* textObject;

TextObject* waveText;

TransformComponent* baseLocation;
BaseComponent* baseBase;

Vector2D offset;
Vector2D offsetVelocity;
Vector2D cameraLead;

extern unsigned int	gGameStateNext;
extern bool menuExists;
float updateLoopNum;
void GameStateLevel1Load(void)
{
	AESysPrintf("\n------------------------\nLoading level 1\n");

	// creat the basic square mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);
	squareMesh = AEGfxMeshEnd();

	//button mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFF0000, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFF0000, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);
	ButtonMesh = AEGfxMeshEnd();

	// pause screen mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-600.0f, -600.0f, 0xFFFF0000, 0.0f, 1.0f,
		600.0f, -600.0f, 0xFFFF0000, 1.0f, 1.0f,
		-600.0f, 600.0f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		600.0f, -600.0f, 0xFFFF0000, 1.0f, 1.0f,
		600.0f, 600.0f, 0xFFFF0000, 1.0f, 0.0f,
		-600.0f, 600.0f, 0xFFFF0000, 0.0f, 0.0f);
	pauseScreenMesh = AEGfxMeshEnd();



	AEGfxMeshStart();
	AEGfxTriAdd(
		-25.0f, -25.0f, 0xFFFF0000, 0.0f, 1.0f,
		25.0f, -25.0f, 0xFFFF0000, 1.0f, 1.0f,
		-25.0f, 25.0f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		25.0f, -25.0f, 0xFFFF0000, 1.0f, 1.0f,
		25.0f, 25.0f, 0xFFFF0000, 1.0f, 0.0f,
		-25.0f, 25.0f, 0xFFFF0000, 0.0f, 0.0f);
	heartMesh = AEGfxMeshEnd();

	//Scroll HUD stuff -Jathan
	AEGfxMeshStart();
	AEGfxTriAdd(
		-40.0f, -50.0f, 0xFFFF0000, 0.0f, 1.0f,
		-40.0f, 50.0f, 0xFFFF0000, 1.0f, 1.0f,
		40.0f, -50.0f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		-40.0f, 50.0f, 0xFFFF0000, 1.0f, 1.0f,
		40.0f, 50.0f, 0xFFFF0000, 1.0f, 0.0f,
		40.0f, -50.0f, 0xFFFF0000, 0.0f, 0.0f);
	leftScrollMesh = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		40.0f, -50.0f, 0xFFFF0000, 0.0f, 1.0f,
		40.0f, 50.0f, 0xFFFF0000, 1.0f, 1.0f,
		-40.0f, -50.0f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		40.0f, 50.0f, 0xFFFF0000, 1.0f, 1.0f,
		-40.0f, 50.0f, 0xFFFF0000, 1.0f, 0.0f,
		-40.0f, -50.0f, 0xFFFF0000, 0.0f, 0.0f);
	rightScrollMesh = AEGfxMeshEnd();

	AEGfxMeshStart();
	AEGfxTriAdd(
		60.0f, -36.0f, 0xFFFF0000, 0.0f, 1.0f,
		60.0f, 36.0f, 0xFFFF0000, 1.0f, 1.0f,
		-60.0f, -36.0f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		60.0f, 36.0f, 0xFFFF0000, 1.0f, 1.0f,
		-60.0f, 36.0f, 0xFFFF0000, 1.0f, 0.0f,
		-60.0f, -36.0f, 0xFFFF0000, 0.0f, 0.0f);
	midScrollMesh = AEGfxMeshEnd();

	// load textures
	playerBaseTex = AEGfxTextureLoad("textures/MainCharacterRotate.png");
	playerTurretTex = AEGfxTextureLoad("textures/BoatTurret.png");
	BulletTex = AEGfxTextureLoad("textures/Bullet.png");
	Jelly1 = AEGfxTextureLoad("textures/JELLIES.png");
	PlayerWeaponTex = AEGfxTextureLoad("textures/PlayerWeaponTmp.png");
	scrollTex = AEGfxTextureLoad("textures/ScrollBottom.png");
	scrollMidTex = AEGfxTextureLoad("textures/ScrollAddOn.png");
	turretPlatform = AEGfxTextureLoad("textures/tempPlatform.png");
	crab = AEGfxTextureLoad("textures/crabbie.png");
	heartTex = AEGfxTextureLoad("textures/HealthBarFull.png");
	heartEmptyTex = AEGfxTextureLoad("textures/HealthBarEmpty.png");
	BaseTex = AEGfxTextureLoad("textures/base.png");
	sharkTex = AEGfxTextureLoad("textures/shark.png");
	pauseScreenTex = AEGfxTextureLoad("textures/PauseScreen.png");
	pauseMenuButtonTex = AEGfxTextureLoad("textures/MenuButton.png");
	pauseQuitButtonTex = AEGfxTextureLoad("textures/QuitButton.png");
	caveTex = AEGfxTextureLoad("textures/CAVE.png");
	PufferTowerTex = AEGfxTextureLoad("textures/PufferSpriteSheet.png");
	towerTexture = AEGfxTextureLoad("textures/squiddddddddddddddddddd.png");
	pufferSprite = AEGfxTextureLoad("textures/PufferSingle.png");
	PopupMenuTex = AEGfxTextureLoad("textures/menuTemp.png");
	bullet = AEGfxTextureLoad("textures/BoatBase.png");
	circle = AEGfxTextureLoad("textures/debugCircle.png");
	sword = AEGfxTextureLoad("textures/sword +.png");
	watch = AEGfxTextureLoad("textures/watch +.png");
	meter = AEGfxTextureLoad("textures/squareButtonBase.png");


	//load sounds
	fmodSys->createSound("sounds/hit.wav", FMOD_DEFAULT, NULL, &enemyDamageSound);
	fmodSys->createSound("sounds/Sword.wav", FMOD_DEFAULT, NULL, &playerAttackSound);
	fmodSys->createSound("sounds/slime-squish.wav", FMOD_DEFAULT, NULL, &squidTowerAttackSound);

	fmodSys->createStream("sounds/Pookatori and Friends.mp3", FMOD_DEFAULT, NULL, &gameMusic);



	health1 = heartTex;
	health2 = heartTex;
	health3 = heartTex;
	health4 = heartTex;
	health5 = heartTex;

	
	TextManager::Load();
	/*vvvtileMap Stuffvvvvvvvvvvvvvvvvvvvvvvv*/
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFF000000, 0.0f, 0.2f,
		0.5f, -0.5f, 0xFF000000, 0.2f, 0.2f,
		-0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f);

	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFF000000, 0.2f, 0.2f,
		0.5f, 0.5f, 0xFF000000, 0.2f, 0.0f);

	tileMesh = AEGfxMeshEnd();

	spawnerCount = 0;

	//load map .txt and texture
	switch (selectedLevel)
	{
	case LEVEL1:
		loadTileMap("Tilemap.txt");
		/*^^^tileMap Stuff^^^^^^^^^^^^^^^^^^^^^^^*/
		//enemy map stuff
		if (!(ImportEnemyMapDataFromFile("Enemymap.txt")))
			AESysPrintf("EnemyMapFile Not Found or Broken");
		break;

	case LEVEL2:
		loadTileMap("Tilemap2.txt");
		/*^^^tileMap Stuff^^^^^^^^^^^^^^^^^^^^^^^*/
		//enemy map stuff
		if (!(ImportEnemyMapDataFromFile("Enemymap2.txt")))
			AESysPrintf("EnemyMapFile Not Found or Broken");
		break;

	case LEVEL3:
		loadTileMap("Tilemap3.txt");
		/*^^^tileMap Stuff^^^^^^^^^^^^^^^^^^^^^^^*/
		//enemy map stuff
		if (!(ImportEnemyMapDataFromFile("Enemymap3.txt")))
			AESysPrintf("EnemyMapFile Not Found or Broken");
		break;
	}
	loadTileMapTex("textures/tileMapFinished.png");

	ParticleLoad();

	health = 5;
	money = STARTMONEY;
	CurrWave = 1;
}


void GameStateLevel1Init(void)
{
	AESysPrintf("\n------------------------\nInitializing level 1\n");
	isPaused = false;
	// set all the objects ActiveFlags to 0;
	for (int i = 0; i < OBJECT_NUM_MAX; i++)
	{
		Object_Info* pObject = ObjectList + i;
		pObject->ActiveFlag = INACTIVE;
	}

	AEGfxSetBackgroundColor(0.9f, 0.9f, 0.6f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// creat a player object
	Object_Info* PlayerObject = Add_Object(OBJECT_PLAYER);

	// add components to the Player object
	AddComponent(PlayerObject, COMPONENT_TRANSFORM);
	AddComponent(PlayerObject, COMPONENT_PHYSICS);
	AddComponent(PlayerObject, COMPONENT_MESH);
	AddComponent(PlayerObject, COMPONENT_TEXTURE);

	// set the pPlayer pointer to the PlayerObject so it can be accessed later
	pPlayer = PlayerObject;


	// Creat an ObjectMesh pointer then set it to the PlayerObject mesh component
	MeshComponent* PlayerMesh;
	PlayerMesh = GetMeshComp(PlayerObject);

	PlayerMesh->mesh = squareMesh;

	// get the texture component
	TextureComponent* PlayerTexture;
	PlayerTexture = GetTextureComp(PlayerObject);

	PlayerTexture->texture = playerBaseTex;
	PlayerTexture->level = normal;
	PlayerTexture->isAnimated = true;
	PlayerTexture->framesX = 4;
	PlayerTexture->framesY = 1;
	PlayerTexture->animSpeed = 0.0f;
	PlayerTexture->startFrame = 1;
	PlayerTexture->endFrame = 4;
	PlayerTexture->frameCounter = 2;
	
	loadAnimation(PlayerObject);
	
	// Creat an ObjectTransform pointer then set it to the PlayerObject Transform component
	TransformComponent* ObjectTransform;
	ObjectTransform = GetTransformComp(PlayerObject);

	// set the position and scale of the player
	Vector2DZero(&ObjectTransform->position);

	ObjectTransform->scale.x = 64;
	ObjectTransform->scale.y = 64;

	//Creates Spawners, nodes, tower spots and the player base
	createObjFromEnemyMap(playerTurretTex, caveTex, BaseTex, turretPlatform);
	
	//gold display
	textObject = new TextObject("goldLabel", "GOLD: ", FELIX_TITLING_32);
	textObject->SetColor(0, 0, 0, 1);
	textObject->SetPosition(-565.0f, 390.0f);

	goldText = new TextObject("gold", std::to_string(money), FELIX_TITLING_32);
	goldText->SetColor(0, 0, 0, 1);
	goldText->SetPosition(-470.0f, 390.0f);


	//wave info display
	Object_Info* WaveBarObject = Add_Object(OBJECT_HUD);

	// add components to the Player object
	AddComponent(WaveBarObject, COMPONENT_TRANSFORM);
	AddComponent(WaveBarObject, COMPONENT_PHYSICS);
	AddComponent(WaveBarObject, COMPONENT_MESH);
	AddComponent(WaveBarObject, COMPONENT_TEXTURE);

	MeshComponent* WaveBarMesh;
	WaveBarMesh = GetMeshComp(WaveBarObject);

	WaveBarMesh->mesh = squareMesh;

	// get the texture component
	TextureComponent* WaveBarTexture;
	WaveBarTexture = GetTextureComp(WaveBarObject);

	WaveBarTexture->texture = meter;
	WaveBarTexture->level = veryTop;


	// Creat an ObjectTransform pointer then set it to the PlayerObject Transform component
	TransformComponent* WaveBarTransform;
	WaveBarTransform = GetTransformComp(WaveBarObject);

	// set the position and scale of the player
	Vector2DSet(&WaveBarTransform->position, 300.0f, 300.0f);

	WaveBarTransform->scale.x = 400;
	WaveBarTransform->scale.y = 80;



	baseHealth = new TextObject("baseHealth", "X "+std::to_string(20), FELIX_TITLING_32);
	baseHealth->SetColor(0, 0, 0, 1);
	baseHealth->SetPosition(baseLocation->position.x - 20, baseLocation->position.y + 100);

	ParticleInit();

	Vector2DSet(&offsetVelocity, 0, 0);

	waveText = new TextObject("waveText", std::to_string(CurrWave) + "/" + std::to_string(GlobalTotalWaves), FELIX_TITLING_32);
	waveText->SetColor(0, 0, 0, 1);
	waveText->SetPosition(470.0f, 390.0f);

	//create pause menu buttons
	quitPauseButton = createButton(-400.0f, 0.0f, 256.0f, 64.0f);
	menuPauseButton = createButton(-400.0f, 100.0f, 256.0f, 64.0f);

	menuPauseButtonPos.x = 150.0f;
	menuPauseButtonPos.y = -330.0f;

	quitPauseButtonPos.x = -150.0f;
	quitPauseButtonPos.y = -330.0f;

	quitPauseButton->buttonTexture = pauseQuitButtonTex;
	menuPauseButton->buttonTexture = pauseMenuButtonTex;
	menuPauseButton->Position.x = 1000;
	menuPauseButton->Position.y = 1000;

	quitPauseButton->Position.x = 1000;
	quitPauseButton->Position.y = 1000;

	baseBase->health = 20;
	fmodSys->playSound(FMOD_CHANNEL_REUSE, gameMusic, false, &musicChannel);
}


void GameStateLevel1Update(void)
{
	if (isPaused)
	{
		if (AEInputCheckTriggered(VK_ESCAPE))
		{
			isPaused = false;
			menuPauseButton->Position.x = 1000;
			menuPauseButton->Position.y = 1000;

			quitPauseButton->Position.x = 1000;
			quitPauseButton->Position.y = 1000;
		}

		if (quitPauseButton->mouseOver && AEInputCheckCurr(VK_LBUTTON))
			gGameStateNext = GS_QUIT;

		if (menuPauseButton->mouseOver && AEInputCheckCurr(VK_LBUTTON))
		{
			AEGfxSetCamPosition(0.0f, 0.0f);
			gGameStateNext = GS_START;
		}
		buttonUpdate();
	}
	else
	{
		//pause stuff
		if (AEInputCheckTriggered(VK_ESCAPE))
		{
			isPaused = true;
			menuPauseButton->Position.x = offset.x + menuPauseButtonPos.x;
			menuPauseButton->Position.y = offset.y + menuPauseButtonPos.y;

			quitPauseButton->Position.x = offset.x + quitPauseButtonPos.x;
			quitPauseButton->Position.y = offset.y + quitPauseButtonPos.y;
		}
		//camera types
		if (dynamicCamera)
		{
			offset.x += offsetVelocity.x;
			offset.y += offsetVelocity.y;
		}
		else if (!isDead)
		{
			offset.x = GetTransformComp(pPlayer)->position.x;
			offset.y = GetTransformComp(pPlayer)->position.y;
		}

		//sound update
		fmodSys->update();

		offsetVelocity.x *= 0.95f;
		offsetVelocity.y *= 0.95f;

		Vector2D* playerPos = &GetTransformComp(pPlayer)->position;
		Vector2D* playerScale = &GetTransformComp(pPlayer)->scale;
		if (!isDead)
		{
			if (offset.x + 330 > (BINARY_MAP_WIDTH * 40) / 2)
				offset.x = ((BINARY_MAP_WIDTH * 40) / 2) - 330;

			if (offset.x - 300 < (BINARY_MAP_WIDTH * 40) / -2)
				offset.x = ((BINARY_MAP_WIDTH * 40) / -2) + 300;

			if (offset.y + 200 > (BINARY_MAP_WIDTH * 40) / 2)
				offset.y = ((BINARY_MAP_WIDTH * 40) / 2) - 200;

			if (offset.y - 600 < (BINARY_MAP_WIDTH * 40) / -2)
				offset.y = ((BINARY_MAP_WIDTH * 40) / -2) + 600;

			if (playerPos->x - (playerScale->x / 2) < offset.x - 600.0f)
				playerPos->x = offset.x - 600.0f + (playerScale->x / 2.0f);

			if (playerPos->x + (playerScale->x / 2) > offset.x + 600.0f)
				playerPos->x = offset.x + 600.0f - (playerScale->x / 2.0f);

			if (playerPos->y - (playerScale->y / 2.0f) < offset.y - 380.0f)
				playerPos->y = offset.y - 380.0f + (playerScale->y / 2.0f);

			if (playerPos->y + (playerScale->y / 2.0f) > offset.y + 380.0f)
				playerPos->y = offset.y + 380.0f - (playerScale->y / 2.0f);
		}


		//
		animationUpdate();

		//
		health1 = heartTex;
		health2 = heartTex;
		health3 = heartTex;
		health4 = heartTex;
		health5 = heartTex;

		switch (health)
		{
		case -1:
		case 0:
			health1 = heartEmptyTex;
		case 1:
			health2 = heartEmptyTex;
		case 2:
			health3 = heartEmptyTex;
		case 3:
			health4 = heartEmptyTex;
		case 4:
			health5 = heartEmptyTex;
		}

		//AESysPrintf("Level 1: update\n");
		frameTime = (float)AEFrameRateControllerGetFrameTime();
		//AESysPrintf("%d", health);
		//mouse stuff -Jathan
		long mousex, mousey;
		AEInputGetCursorPosition(&mousex, &mousey);
		//Convert mouse's screen coordinates to world coordinates
		Vector2D mouseWorld;
		AEGfxConvertScreenCoordinatesToWorld((float)mousex, (float)mousey, &mouseWorld.x, &mouseWorld.y);

		// ---------------------------------------------------------------------------
		// Player properties
		PlayerMovement(pPlayer);
		buttonUpdate();


		if (AEInputCheckTriggered('U'))
		{
			for (int i = 0; i < OBJECT_NUM_MAX; i++)
			{
				Object_Info* pObject = ObjectList + i;
				if (pObject->ActiveFlag == INACTIVE)
					continue;

				if (pObject->Type == OBJECT_PATH || pObject->Type == OBJECT_SPAWNER)
				{
					TextureComponent* objectTexture = GetTextureComp(pObject);
					if (objectTexture->isVisible == true)
						objectTexture->isVisible = false;
					else
						objectTexture->isVisible = true;

				}
			}
		}

		//K for kamera
		if (AEInputCheckTriggered('K'))
		{
			if (dynamicCamera)
				dynamicCamera = false;
			else
				dynamicCamera = true;
		}

		for (int i = 0; i < OBJECT_NUM_MAX; i++)
		{
			Object_Info* pObject = ObjectList + i;

			// skip non-active object
			if (pObject->ActiveFlag == INACTIVE)
				continue;
			TransformComponent* objectTransform = GetTransformComp(pObject);
			if (objectTransform != NULL)
			{
				if (objectTransform->angle >= 6.28318)
				{
					objectTransform->angle - 6.28318;
				}
			}
			if (pObject->Type == OBJECT_BULLET)
			{
				TransformComponent* bulletTransform = GetTransformComp(pObject);
				//void ParticleEmit(unsigned long type, float x, float y, float width, float height, float particlesPerSec);
				ParticleEmit(PARTICLE_BULLET_TRAIL, bulletTransform->position.x, bulletTransform->position.y, 5, 5, 400);

				if (bulletTransform->position.x > 1000 || bulletTransform->position.x < -1000)
					pObject->ActiveFlag = INACTIVE;

				if (bulletTransform->position.y > 1000 || bulletTransform->position.y < -1000)
					pObject->ActiveFlag = INACTIVE;
			}

			if (pObject->Type == OBJECT_TOWER)
			{
				//updateTarget(pObject);
				TowerComponent* towComp = GetTowerComp(pObject);
				towComp->fireCount -= 1;
				if (towComp->isExpanded == true) //decrement expand timer only if expanded
					towComp->expandCount--;
				updateTower(pObject);
			}

			if (AEInputCheckReleased(VK_RBUTTON) || AEInputCheckReleased(VK_LBUTTON))
			{
				if (pObject->Type == OBJECT_TURRET_PLATFORM)
				{
					TransformComponent* pos = GetTransformComp(pObject);
					TurretPlatformComponent* TP = GetTurretPlatformComp(pObject);
					int result = StaticPointToStaticRect(&mouseWorld, &pos->position, pos->scale.x, pos->scale.x);
					//AESysPrintf("(%f, %f) %d\n", mouseWorld.x, mouseWorld.y, result);
					if (StaticPointToStaticRect(&mouseWorld, &pos->position, pos->scale.x, pos->scale.x) && menuExists == false)
					{
						if (!TP->hasTower)
						{
							CreatePopupMenu(pObject, newTower);
						}
						else
						{
							CreatePopupMenu(pObject, upgradeTower);
						}
						
					}
					
				}
				if (pObject->Type == OBJECT_MENU)
				{
					TransformComponent* pos = GetTransformComp(pObject);
					if (StaticPointToStaticRect(&mouseWorld, &pos->position, pos->scale.x, pos->scale.x) && menuExists)
					{
						popupMenuClick(mouseWorld.x, mouseWorld.y);
					}
					else if(menuExists)
					{
						DeletePopupMenu();
					}
				}
			}

			if (pObject->Type == OBJECT_PATH)
			{
				TransformComponent* pathTransform = GetTransformComp(pObject);
				for (int i = 0; i < OBJECT_NUM_MAX; i++)
				{
					Object_Info* pObject2 = ObjectList + i;

					// skip non-active object
					if (pObject2->ActiveFlag == INACTIVE)
						continue;

					if (pObject2->Type == OBJECT_ENEMY)
					{
						TransformComponent* enemyTransform = GetTransformComp(pObject2);
						if (StaticPointToStaticRect(&pathTransform->position, &enemyTransform->position, enemyTransform->scale.x, enemyTransform->scale.y))
						{
							//AESysPrintf("Player Path Collision Registered \n");
							EnemyCollidePath(pObject2, pObject);
						}
					}
				}
			} //end pathobject
			if (pObject->Type == OBJECT_SPAWNER)
			{
				SpawnerUpdate(pObject, frameTime);
			}
			if (pObject->Type == OBJECT_ENEMY)
			{
				EnemyUpdate(pObject);
				EnemyComponent* enemyComp = GetEnemyComp(pObject);
				if (enemyComp != NULL && enemyComp->health <= 0.0f)
				{
					AESysPrintf("ENEMY DELETE 1");
					money += enemyComp->value;
					Remove_Object(pObject);
					continue;
				}

				for (int i = 0; i < OBJECT_NUM_MAX; i++)
				{
					Object_Info* pObject2 = ObjectList + i;

					// skip non-active object
					if (pObject2->ActiveFlag == INACTIVE)
						continue;



					if (pObject2->Type == OBJECT_PLAYER)
					{
						TransformComponent* enemyPos = GetTransformComp(pObject);
						TransformComponent* playerPos = GetTransformComp(pObject2);
						if (enemyPos != NULL && StaticRectToStaticRect(&enemyPos->position, enemyPos->scale.x, enemyPos->scale.y, &playerPos->position, playerPos->scale.x, playerPos->scale.y))
						{
							if (playerIsColliding == false)
							{
								health--;
								playerIsColliding = true;

								Vector2D knockBack;
								Vector2DSub(&knockBack, &enemyPos->position, &playerPos->position);
								Vector2DNormalize(&knockBack, &knockBack);
								knockBack.x *= -8;
								knockBack.y *= -8;
								Vector2DAdd(&GetPhysicsComp(pObject2)->velocity, &GetPhysicsComp(pObject2)->velocity, &knockBack);

								enemyCollidingWith = pObject;
							}
						}
						else if (enemyCollidingWith == pObject)
							playerIsColliding = false;
					}
					if (pObject2->Type == OBJECT_BASE)
					{
						TransformComponent* enemyPos = GetTransformComp(pObject);
						TransformComponent* basePos = GetTransformComp(pObject2);
						if (enemyPos != NULL && StaticRectToStaticRect(&enemyPos->position, enemyPos->scale.x, enemyPos->scale.y, &basePos->position, basePos->scale.x, basePos->scale.y))
						{
							BaseComponent* baseBase = GetBaseComp(pObject2);
							EnemyComponent* enemyEnemy = GetEnemyComp(pObject);
							baseBase->health--;
							enemyEnemy->health = 0;
							break;
						}
					}

					if (pObject2->Type == OBJECT_BULLET)
					{
						TransformComponent* bulletPos = GetTransformComp(pObject2);

						TransformComponent* enemyPos = GetTransformComp(pObject);

						if (&enemyPos->position == NULL)
							continue;

						if (StaticPointToStaticRect(&bulletPos->position, &enemyPos->position, enemyPos->scale.x, enemyPos->scale.y))
						{


							EnemyComponent* enemyComp = GetEnemyComp(pObject);
							BulletComponent* bulletComp = GetBulletComp(pObject2);
							enemyComp->health -= bulletComp->damage;

							Remove_Object(pObject2);

							if (enemyComp->health <= 0)
							{
								AESysPrintf("ENEMY DELETE 2");
								money += enemyComp->value;
								Remove_Object(pObject);
							}
						}
					}
					if (pObject2->Type == OBJECT_TOWER)
					{
						EnemyComponent* enemyComp = GetEnemyComp(pObject);
						TransformComponent* enemyTrans = GetTransformComp(pObject);
						TransformComponent* towerTrans = GetTransformComp(pObject2);
						if (enemyComp == NULL)
							break;
						if (StaticRectToStaticRect(&towerTrans->position, towerTrans->scale.x, towerTrans->scale.y,
							&enemyTrans->position, enemyTrans->scale.x, enemyTrans->scale.y))
						{
							if (enemyComp->hitByWeapon2 == false)
							{
								TowerComponent* towerComp = GetTowerComp(pObject2);
								enemyComp->hitByWeapon2 = true;
								if (towerComp->isExpanded == true)
									enemyComp->health -= towerComp->damage;
							}
						}
						else
							enemyComp->hitByWeapon2 = false;
					}
				}
			}
			if (pObject->Type == OBJECT_HUD)
			{
				TransformComponent* hudTransform = GetTransformComp(pObject);
				//float barLength = (float)CurrWave / (float)TotalWaves;
				//hudTransform->scale.x = barLength * 512;
				float hudBarLength = WaveTime / WaveLength;
				hudTransform->scale.x = hudBarLength * 400;
				hudTransform->position.x = offset.x + 100 + (hudBarLength * 200);
				hudTransform->position.y = offset.y + 350;

				
			}
		}

		//reorganize the objects based on there y positions
		for (int i = 0; i < OBJECT_NUM_MAX; i++)
		{
			ObjectRenderOrder[i] = ObjectList + i;
		}

		for (int j = 0; j < 50; j++)
		{
			for (int i = 0; i < OBJECT_NUM_MAX - 1; i++)
			{
				Object_Info* p = ObjectRenderOrder[i];
				Object_Info* p2 = ObjectRenderOrder[i + 1];

				Object_Info** pObject = &ObjectRenderOrder[i];
				Object_Info** pObject2 = &ObjectRenderOrder[i + 1];
				Object_Info* tmpAddress = ObjectRenderOrder[i];

				if (p->ActiveFlag == INACTIVE || p2->ActiveFlag == INACTIVE)
					continue;

				TransformComponent* transform1 = GetTransformComp(p);
				TransformComponent* transform2 = GetTransformComp(p2);

				if (transform1 == NULL)
				{
					if (transform2 == NULL)
					{
						continue;
					}
					else
					{
						*pObject = *pObject2;
						*pObject2 = tmpAddress;
						continue;
					}
				}

				TextureComponent *pTex = GetTextureComp(*pObject);
				TextureComponent *pTex2 = GetTextureComp(*pObject2);

				if ((transform1->position.y - (transform1->scale.y / 2)) < (transform2->position.y - (transform2->scale.y / 2)) && pTex2->level == pTex->level)
				{
					*pObject = *pObject2;
					*pObject2 = tmpAddress;

					//AESysPrintf("\n////////////////////////////\nSwitching object order based on Y\n");
				}
				else
				{
					//AESysPrintf("\nNot Switching\n");
				}

				if (pTex->level > pTex2->level)
				{
					*pObject = *pObject2;
					*pObject2 = tmpAddress;
				}

			}
			//

		}

		for (int i = 0; i < OBJECT_NUM_MAX; i++)
		{
			Object_Info* pObject = ObjectRenderOrder[i];

			if (pObject->ActiveFlag == INACTIVE)
				continue;

			TransformComponent* transform1 = GetTransformComp(pObject);
			if (transform1 == NULL)
				continue;

			//AESysPrintf("the y pos of object %i is:  %f\n", i, transform1->position.y);
		}

		ParticleUpdate();



		while (updateLoopNum > 0)
		{
			PlayerPhysicsBehaivior(pPlayer);
			// ---------------------------------------------------------------------------
			// Update position based on velocity
			for (int i = 0; i < OBJECT_NUM_MAX; i++)
			{
				Object_Info* pObject = ObjectList + i;

				// skip non-active object
				if (pObject->ActiveFlag == INACTIVE)
					continue;

				// access the objects components
				PhysicsComponent* tmpPhysics = GetPhysicsComp(pObject);
				TransformComponent* tmpTransform = GetTransformComp(pObject);

				tmpTransform->position.x += tmpPhysics->velocity.x;
				tmpTransform->position.y += tmpPhysics->velocity.y;
				tmpTransform->angle += tmpPhysics->rotVelocity;
			}

			// ---------------------------------------------------------------------------
			//player weapon colisions
			for (int i = 0; i < OBJECT_NUM_MAX; i++)
			{
				Object_Info* pObject = ObjectList + i;

				// skip non-active object
				if (pObject->ActiveFlag == INACTIVE)
					continue;

				if (pObject->Type == OBJECT_ENEMY)
				{
					if (PlayerWeapon != NULL && PlayerWeapon->ActiveFlag & ACTIVE && PlayerWeapon->Type == OBJECT_PLAYER_WEAPON)
					{
						TransformComponent* WeaponTransform = GetTransformComp(PlayerWeapon);
						TransformComponent* EnemyTransform = GetTransformComp(pObject);
						EnemyComponent* enemyComp = GetEnemyComp(pObject);
						if (StaticRectToStaticRect(&WeaponTransform->position, WeaponTransform->scale.x, WeaponTransform->scale.y,
							&EnemyTransform->position, EnemyTransform->scale.x, EnemyTransform->scale.y))
						{
							
							//AESysPrintf("%i", (int)enemyComp->hitByWeapon);
							if (enemyComp->hitByWeapon == false)
							{
								//play enemy damage sound
								fmodSys->playSound(FMOD_CHANNEL_FREE, enemyDamageSound, false, 0);

								PlayerWeaponComponent* weaponComp = GetPlayerWeaponComp(PlayerWeapon);
								enemyComp->health -= weaponComp->damage;
								enemyComp->hitByWeapon = true;
								if (enemyComp->health <= 0.0f)
								{
									AESysPrintf("ENEMY DELETE 3");
									money += enemyComp->value;
									Remove_Object(pObject);
								}
							}
						}
						else
						{
							enemyComp->hitByWeapon = false;
						}
					}
				}
			}

			updateLoopNum -= 0.01f;
		}

		frameTime = (float)AEFrameRateControllerGetFrameTime();
		updateLoopNum = (float)AEFrameRateControllerGetFrameTime();
		
		//What is going on?
		/*if (money == 0)
			money = 10;*/

		goldText->SetText(std::to_string(money));
		textObject->SetPosition(-555.0f + offset.x, 370.0f + offset.y);
		goldText->SetPosition(-460.0f + offset.x, 370.0f + offset.y);
		baseHealth->SetText("X " + std::to_string(baseBase->health));

		waveText->SetPosition(offset.x + 470.0f, offset.y+370.0f);
		waveText->SetText(std::to_string(CurrWave) + "/" + std::to_string(GlobalTotalWaves));

		AEGfxSetCamPosition(offset.x, offset.y);
		if (baseBase->health <= 0 || AEInputCheckTriggered('T'))
		{
			AEGfxSetCamPosition(0.0f, 0.0f);
			gGameStateNext = GS_LOSE;
		}



		// ---------------------------------------------------------------------------
		// Calculate the transfomation matrix for all the objects
		for (int i = 0; i < OBJECT_NUM_MAX; i++)
		{
			Matrix2D		 trans, rot, scale;
			Object_Info* pObject = ObjectList + i;

			// skip non-active object
			if (pObject->ActiveFlag == INACTIVE)
				continue;


			TransformComponent* ObjectTransform;
			ObjectTransform = GetTransformComp(pObject);


			// Compute the scaling matrix
			Matrix2DScale(&scale, ObjectTransform->scale.x, ObjectTransform->scale.y);
			// Compute the rotation matrix
			Matrix2DRotRad(&rot, ObjectTransform->angle);
			// Compute the translation matrix
			Matrix2DTranslate(&trans, ObjectTransform->position.x, ObjectTransform->position.y);
			// Concatenate the 3 matrix in the correct order in the objects transform component's TransformMatrix
			Matrix2D transRot;
			Matrix2DConcat(&transRot, &trans, &rot);
			Matrix2DConcat(&ObjectTransform->TramsformMatrix, &transRot, &scale);
		}
	}

}
	
	


void GameStateLevel1Draw(void)
{
	//AESysPrintf("Level 1: Draw\n");
	drawTileMap();
	for (int i = 0; i < OBJECT_NUM_MAX; i++)
	{
		Object_Info* pObject = ObjectRenderOrder[i];

		if (pObject->ActiveFlag == INACTIVE)
			continue;

		TextureComponent* ObjectTexture;
		ObjectTexture = GetTextureComp(pObject);


		if (ObjectTexture->isVisible == FALSE)
			continue;




		MeshComponent* ObjectMesh;
		ObjectMesh = GetMeshComp(pObject);
		
		TransformComponent* ObjectTransform;
		ObjectTransform = GetTransformComp(pObject);

		

		if (ObjectMesh == NULL || ObjectTransform == NULL || ObjectTexture == NULL)
		{
			AESysPrintf("\n////////////////////////\nObject has missing componants\n cant draw.\n////////////////////////\n");
			continue;
		}
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		AEGfxSetTransform(ObjectTransform->TramsformMatrix.m);

		if(ObjectTexture->isAnimated == true)
			AEGfxTextureSet(ObjectTexture->texture, ObjectTexture->texU, ObjectTexture->texV);
		else
			AEGfxTextureSet(ObjectTexture->texture, 0.0f, 0.0f);

		AEGfxSetTransparency(1.0f);
		
		AEGfxMeshDraw(ObjectMesh->mesh, AE_GFX_MDM_TRIANGLES);
	}

	//Scroll HUD stuff -Jathan
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(scrollTex, 0.0f, 0.0f);
	AEGfxSetPosition(-550 + offset.x, 335 + offset.y);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(leftScrollMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(scrollTex, 0.0f, 0.0f);
	AEGfxSetPosition(-385.0 + offset.x, 335 + offset.y);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(rightScrollMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(scrollMidTex, 0.0f, 0.0f);
	AEGfxSetPosition(-470.0 + offset.x, 337 + offset.y);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(midScrollMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(heartTex, 0.0f, 0.0f);
	AEGfxSetPosition(baseLocation->position.x - 40, baseLocation->position.y + 90);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(heartMesh, AE_GFX_MDM_TRIANGLES);

	//player health
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(health1, 0.0f, 0.0f);
	AEGfxSetPosition(-540 + offset.x, 325 + offset.y);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(heartMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(health2, 0.0f, 0.0f);
	AEGfxSetPosition(-503 + offset.x, 325 + offset.y);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(heartMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(health3, 0.0f, 0.0f);
	AEGfxSetPosition(-466 + offset.x, 325 + offset.y);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(heartMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(health4, 0.0f, 0.0f);
	AEGfxSetPosition(-429 + offset.x, 325 + offset.y);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(heartMesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(health5, 0.0f, 0.0f);
	AEGfxSetPosition(-392 + offset.x, 325 + offset.y);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(heartMesh, AE_GFX_MDM_TRIANGLES);

	/*//Wave HUD stuff
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(playerTurretTex, 0.0f, 0.0f);
	AEGfxSetPosition(300 + offset.x, 325 + offset.y);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(heartMesh, AE_GFX_MDM_TRIANGLES);*/
	
	ParticleDraw();
	buttonDraw();
	TextManager::Update();


	//draw pause screen
	if (isPaused)
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxTextureSet(pauseScreenTex, 0.0f, 0.0f);
		AEGfxSetPosition(offset.x + 0.0, offset.y - 200.0);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(pauseScreenMesh, AE_GFX_MDM_TRIANGLES);
		buttonDraw();
	}

	
}


void GameStateLevel1Free(void)
{
	AESysPrintf("\n------------------------\nFreeing level 1\n");
	TextManager::Free();
	destroyButton(menuPauseButton);
	destroyButton(quitPauseButton);
	fmodSys->playSound(FMOD_CHANNEL_REUSE, menuMusic, false, &musicChannel);
}


void GameStateLevel1Unload(void)
{
	AESysPrintf("\n------------------------\nUnloading level 1\n");
	

	
	AEGfxTextureUnload(playerBaseTex);
	AEGfxTextureUnload(playerTurretTex);
	AEGfxTextureUnload(BulletTex);
	AEGfxTextureUnload(Jelly1);
	AEGfxTextureUnload(PlayerWeaponTex);
	AEGfxTextureUnload(scrollTex);
	AEGfxTextureUnload(scrollMidTex);
	AEGfxTextureUnload(turretPlatform);
	AEGfxTextureUnload(crab);
	AEGfxTextureUnload(heartTex);
	AEGfxTextureUnload(heartEmptyTex);
	AEGfxTextureUnload(BaseTex);
	AEGfxTextureUnload(sharkTex);
	AEGfxTextureUnload(pauseScreenTex);
	AEGfxTextureUnload(pauseMenuButtonTex);
	AEGfxTextureUnload(pauseQuitButtonTex);
	AEGfxTextureUnload(caveTex);
	AEGfxTextureUnload(PufferTowerTex);
	AEGfxTextureUnload(pufferSprite);
	AEGfxTextureUnload(towerTexture);
	AEGfxTextureUnload(PopupMenuTex);
	AEGfxTextureUnload(bullet);
	AEGfxTextureUnload(circle);
	AEGfxTextureUnload(watch);
	AEGfxTextureUnload(sword);
	AEGfxTextureUnload(meter);
	


	AEGfxMeshFree(Mesh);
	AEGfxMeshFree(squareMesh);
	AEGfxMeshFree(ButtonMesh);
	AEGfxMeshFree(leftScrollMesh);
	AEGfxMeshFree(rightScrollMesh);
	AEGfxMeshFree(midScrollMesh);
	AEGfxMeshFree(heartMesh);

	freeTilemap();
	unloadTilemap();
	FreeMapData();
	FreeEnemyMap();
}





