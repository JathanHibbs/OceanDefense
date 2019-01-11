#pragma once

enum menuType
{
	newTower,
	upgradeTower
};

void CreatePopupMenu(Object_Info* towerPlatform, int type);
void DeletePopupMenu();
void popupMenuClick(float mouseX, float mouseY);