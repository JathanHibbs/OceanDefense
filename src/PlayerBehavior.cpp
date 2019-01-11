// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	PlayerBehavior.c
// Author			:	Jasper Mix
// Creation Date	:	2017/03/03
// ---------------------------------------------------------------------------

// includes
#include "main.h"
#include "objects.h"
#include "Particles.h"
#include "TowerBehavior.h"
#include "EnemyBehavior.h"
#include "PlayerBehavior.h"
#include "Math2D.h"
#include <cmath>

// defines
#define PLAYER_SPEED					0.8f			// the players acceleration speed
#define PLAYER_ROTATION_SPEED			0.01f			// the players rotation speed
#define PLAYER_DRAG						0.07f			// the amount to scale the players speed by to creat drag
#define PLAYER_ROTATION_DRAG			0.2f			// the amount to scale the players rotation speed by
#define WEAPON_DIST						55.0f			// the distance from the player to create the weapon
#define WEAPON_COOLDOWN_TIME			25.0f			// the amount of time to wait between attacking
#define WEAPON_ATTACK_TIME				20.0f
#define PLAYER_BOB_SPEED				0.03f
#define RESPAWN_TIME                    10.0f

//sound stuff
extern FMOD::System *fmodSys;
extern FMOD::Sound * playerAttackSound;


unsigned long attackDir = DOWN;
float WeaponCooldown;
Object_Info* PlayerWeapon;
AEGfxTexture* PlayerWeaponTex;
extern AEGfxVertexList *squareMesh;
int health = 5;
float respawnTimer = 0;
bool isDead = false;
float idleBob = 0.0f;
bool WallCollision = false;
extern Vector2D offsetVelocity;
extern Vector2D offset;
extern Vector2D cameraLead;
extern TransformComponent* baseLocation;
extern int money;

void PlayerMovement(Object_Info* player_)
{
	TransformComponent* PlayerTransform = GetTransformComp(player_);
	PhysicsComponent* PlayerPhysics = GetPhysicsComp(player_);
	TextureComponent* PlayerTex = GetTextureComp(player_);

	float TotalVelocity = sqrtf((PlayerPhysics->velocity.x * PlayerPhysics->velocity.x) + (PlayerPhysics->velocity.y * PlayerPhysics->velocity.y));
	if (!isDead)
	{
		if (AEInputCheckCurr('W') || AEInputCheckCurr(VK_UP))
		{
			PlayerPhysics->velocity.y += PLAYER_SPEED;
			cameraLead.y = 100;
			PlayerTex->frameCounter = 3;
			//attackDir = UP;
		}

		if (AEInputCheckCurr('S') || AEInputCheckCurr(VK_DOWN))
		{
			PlayerPhysics->velocity.y -= PLAYER_SPEED;
			cameraLead.y = -100;
			PlayerTex->frameCounter = 1;
			//attackDir = DOWN;
		}

		if (AEInputCheckCurr('A') || AEInputCheckCurr(VK_LEFT))
		{
			PlayerPhysics->velocity.x -= PLAYER_SPEED;
			cameraLead.x = -100;
			PlayerTex->frameCounter = 4;
			//attackDir = LEFT;
		}

		if (AEInputCheckCurr('D') || AEInputCheckCurr(VK_RIGHT))
		{
			PlayerPhysics->velocity.x += PLAYER_SPEED;
			cameraLead.x = 100;
			PlayerTex->frameCounter = 2;
			//attackDir = RIGHT;
		}

		if (!(AEInputCheckCurr('W') || AEInputCheckCurr(VK_UP)) && !(AEInputCheckCurr('S') || AEInputCheckCurr(VK_DOWN)))
			cameraLead.y = 0;

		if (!(AEInputCheckCurr('A') || AEInputCheckCurr(VK_LEFT)) && !(AEInputCheckCurr('D') || AEInputCheckCurr(VK_RIGHT)))
			cameraLead.x = 0;
		Vector2D tmpPlayerPos = PlayerTransform->position;

		if (tmpPlayerPos.x + cameraLead.x > offset.x + 50)
		{
			offsetVelocity.x += PLAYER_SPEED;
		}
		if (tmpPlayerPos.x + cameraLead.x < offset.x - 50)
		{
			offsetVelocity.x -= PLAYER_SPEED;
		}
		if (tmpPlayerPos.y + cameraLead.y > offset.y + 50)
		{
			offsetVelocity.y += PLAYER_SPEED;
		}
		if (tmpPlayerPos.y + cameraLead.y < offset.y - 50)
		{
			offsetVelocity.y -= PLAYER_SPEED;
		}
	}

	if (AEInputCheckTriggered('O'))
	{
		Vector2D temp;
		Vector2DSet(&temp, PlayerTransform->position.x, PlayerTransform->position.y);
		CreateEnemy(temp, basicEnemy);
	}


}



void PlayerPhysicsBehaivior(Object_Info* player_)
{
	PhysicsComponent* PlayerPhysics = GetPhysicsComp(player_);
	TransformComponent* PlayerTransform = GetTransformComp(player_);
	TextureComponent* PlayerTex = GetTextureComp(player_);

	//make the player face forward if stopped
	int playerVel = (PlayerPhysics->velocity.x + PlayerPhysics->velocity.y) / 2;
	if (playerVel < 0.04f && playerVel > -0.04)
		PlayerTex->frameCounter = 1;

	if (health == 0)
	{
		PlayerTransform->position.x = 10000;
		PlayerTransform->position.y = 10000;
		money /= 2;
		isDead = true;
	}

	if (isDead)
	{
		health = -1;
		respawnTimer += 0.01f;
		offsetVelocity.x = 0;
		offsetVelocity.y = 0;
		offset.x = 0;
		offset.y = 0;
	}

	if (respawnTimer >= RESPAWN_TIME)
	{
		isDead = false;
		respawnTimer = 0;
		PlayerTransform->position.x = baseLocation->position.x;
		PlayerTransform->position.y = baseLocation->position.x - 300;
		health = 5;
	}

	Vector2DScale(&PlayerPhysics->velocity, &PlayerPhysics->velocity, 1 - (PLAYER_DRAG));

	if (WeaponCooldown > 0.0f)
		WeaponCooldown--;

	//pInst->mpComponent_Transform->mPosition.x = AEWrap(pInst->mpComponent_Transform->mPosition.x, winMinX - SHIP_SIZE, winMaxX + SHIP_SIZE);
	//PlayerTransform->position.x = AEWrap(PlayerTransform->position.x, AEGfxGetWinMinX() - 100, AEGfxGetWinMaxX() + 100);
	//PlayerTransform->position.y = AEWrap(PlayerTransform->position.y, AEGfxGetWinMinY() - 100, AEGfxGetWinMaxY() + 100);

	//player bob
	idleBob += PLAYER_BOB_SPEED;
	PlayerTransform->position.y += cosf(idleBob) * (PLAYER_BOB_SPEED * 10);

	//weapon update
	if (PlayerWeapon != NULL && PlayerWeapon->ActiveFlag & ACTIVE && PlayerWeapon->Type == OBJECT_PLAYER_WEAPON)
	{
		PlayerWeaponComponent* WeaponComp = GetPlayerWeaponComp(PlayerWeapon);
		WeaponComp->attackDuration -= 1;

		if (WeaponComp->attackDuration <= 0.0f)
			Remove_Object(PlayerWeapon);

		TransformComponent* WeaponTransform = GetTransformComp(PlayerWeapon);
		PhysicsComponent* WeaponPhysics = GetPhysicsComp(PlayerWeapon);

		if (WeaponTransform != NULL)
		{
			WeaponPhysics->velocity.x = cosf(WeaponTransform->angle) * 3.0f + PlayerPhysics->velocity.x;
			WeaponPhysics->velocity.y = sinf(WeaponTransform->angle) * 3.0f + PlayerPhysics->velocity.y;
		}

	}

	// attack
	if (AEInputCheckTriggered(VK_LBUTTON))
	{
		if (WeaponCooldown <= 0)
		{
			WeaponCooldown = WEAPON_COOLDOWN_TIME;

			//play player attack sound
			fmodSys->playSound(FMOD_CHANNEL_FREE, playerAttackSound, false, 0);

			PlayerWeapon = Add_Object(OBJECT_PLAYER_WEAPON);

			AddComponent(PlayerWeapon, COMPONENT_TRANSFORM);
			AddComponent(PlayerWeapon, COMPONENT_PHYSICS);
			AddComponent(PlayerWeapon, COMPONENT_PLAYER_WEAPON);
			AddComponent(PlayerWeapon, COMPONENT_MESH);
			AddComponent(PlayerWeapon, COMPONENT_TEXTURE);

			ObjectSetScale(PlayerWeapon, 50.0f, 75.0f);

			TextureComponent* WeaponTex = GetTextureComp(PlayerWeapon);
			WeaponTex->texture = PlayerWeaponTex;

			TransformComponent* WeaponTransform = GetTransformComp(PlayerWeapon);
			MeshComponent* WeaponMesh = GetMeshComp(PlayerWeapon);
			WeaponMesh->mesh = squareMesh;

			PlayerWeaponComponent* WeaponComp = GetPlayerWeaponComp(PlayerWeapon);

			WeaponComp->attackDuration = WEAPON_ATTACK_TIME;

			long mousex, mousey;
			AEInputGetCursorPosition(&mousex, &mousey);
			//Convert mouse's screen coordinates to world coordinates
			Vector2D mouseWorld;
			AEGfxConvertScreenCoordinatesToWorld((float)mousex, (float)mousey, &mouseWorld.x, &mouseWorld.y);
			if (abs(PlayerTransform->position.y - mouseWorld.y) > abs(PlayerTransform->position.x - mouseWorld.x))
			{
				if (PlayerTransform->position.y < mouseWorld.y)
				{
					attackDir = UP;
				}
				else
				{
					attackDir = DOWN;
				}
			}
			else
			{
				if (PlayerTransform->position.x < mouseWorld.x)
				{
					attackDir = RIGHT;
				}
				else
				{
					attackDir = LEFT;
				}
			}

			switch (attackDir)
			{
			case UP:
				ObjectSetPosition(PlayerWeapon, PlayerTransform->position.x, PlayerTransform->position.y + WEAPON_DIST);
				WeaponTransform->angle = 0.5 * PI;
				break;
			case DOWN:
				ObjectSetPosition(PlayerWeapon, PlayerTransform->position.x, PlayerTransform->position.y - WEAPON_DIST);
				WeaponTransform->angle = -0.5 * PI;
				break;
			case LEFT:
				ObjectSetPosition(PlayerWeapon, PlayerTransform->position.x - WEAPON_DIST, PlayerTransform->position.y);
				WeaponTransform->angle = PI;
				break;
			case RIGHT:
				ObjectSetPosition(PlayerWeapon, PlayerTransform->position.x + WEAPON_DIST, PlayerTransform->position.y);
				WeaponTransform->angle = 0.0f;
				break;
			}
		}
	}

}



void PlayerWallCollision(Object_Info* player_, Object_Info* wall_)
{
	TransformComponent* playerTransform = GetTransformComp(player_);
	TransformComponent* wallTransform = GetTransformComp(wall_);
	PhysicsComponent* playerPhysics = GetPhysicsComp(player_);

	Vector2D wallCenter, playerCenter;
	wallCenter.x = wallTransform->position.x;
	wallCenter.y = wallTransform->position.y - 10.0f;

	playerCenter.x = playerTransform->position.x;
	playerCenter.y = playerTransform->position.y - 25.0f;

	if (StaticRectToStaticRect(&playerCenter, 50.0f, 5.0f, &wallCenter, wallTransform->scale.x * 0.8f, wallTransform->scale.y * 0.8f))
	{
		WallCollision = true;
		playerPhysics->velocity.x = -playerPhysics->velocity.x;
		playerPhysics->velocity.y = -playerPhysics->velocity.y;
	}
	else
	{
		WallCollision = false;
	}
}