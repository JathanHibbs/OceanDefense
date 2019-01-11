// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	TowerBehavior.h
// Author			:	Jathan Hibbs
// Creation Date	:	2017/03/03
// ---------------------------------------------------------------------------

#pragma once


typedef struct Object_Info Object_Info;

enum towerType
{
	standardTower,
	pufferTower
};

enum upgradeType
{
	damage,
	fireRate,
	changeTower
};

void updateTower(Object_Info* tower);

Object_Info* createTowerPos(Vector2D pos, int type);

void updateTarget(Object_Info* tower);

void towerFire(Object_Info* tower);

void towerUpgrade(Object_Info* tower, int type);