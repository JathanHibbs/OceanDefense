// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	PlayerBehavior.h
// Author			:	Jasper Mix
// Creation Date	:	2017/03/03
// ---------------------------------------------------------------------------

#include "main.h"
//#include "objects.h"
enum ATTACK_DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

void PlayerMovement(Object_Info* player_);
void PlayerPhysicsBehaivior(Object_Info* player_);