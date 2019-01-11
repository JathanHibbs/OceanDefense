//By Jathan

#include "objects.h"
#include "popupMenu.h"
#include "GameState_Level1.h"
#include "GUI_Buttons.h"
#include "TowerBehavior.h"
#include "currency.h"

bool menuExists = false;
Object_Info* menu = NULL;
extern AEGfxVertexList *squareMesh;
extern AEGfxTexture* towerTexture;
Vector2D towerPos;
Object_Info* platform;
extern int money;
extern AEGfxTexture* pufferSprite;
AEGfxTexture* PopupMenuTex;
extern AEGfxTexture* sword;
extern AEGfxTexture* watch;

void CreatePopupMenu(Object_Info* towerPlatform, int type)
{
	platform = towerPlatform;
	Vector2DSet(&towerPos, GetTransformComp(towerPlatform)->position.x, GetTransformComp(towerPlatform)->position.y);
	switch (type)
	{
		case newTower:
		{
			menu = Add_Object(OBJECT_MENU);
			AddComponent(menu, COMPONENT_TRANSFORM);
			AddComponent(menu, COMPONENT_TEXTURE);
			AddComponent(menu, COMPONENT_MESH);
			AddComponent(menu, COMPONENT_PHYSICS);
			AddComponent(menu, COMPONENT_MENU);
			TransformComponent* menuPos = GetTransformComp(menu);
			TextureComponent* menuTexComp = GetTextureComp(menu);
			MeshComponent* menuMesh = GetMeshComp(menu);
			MenuComponent* menuMenu = GetMenuComp(menu);

			menuMenu->menu_type = type;
			menuPos->position.x = towerPos.x;
			menuPos->position.y = towerPos.y + 75;
			menuPos->scale.x = 200;
			menuPos->scale.y = 60;
			menuTexComp->texture = PopupMenuTex;
			menuTexComp->level = top;
			menuMesh->mesh = squareMesh;

			menuMenu->option1 = createButton(towerPos.x - 70, towerPos.y + 75, 50, 50);
			menuMenu->option1->buttonTexture = towerTexture;
			menuMenu->option1Price = new TextObject("option1", std::to_string(TOWERCOST), FELIX_TITLING_32);
			menuMenu->option1Price->SetPosition(towerPos.x - 90, towerPos.y + 75);
			menuMenu->option1Price->SetColor(0,0,0,1);

			menuMenu->option2 = createButton(towerPos.x, towerPos.y + 75, 50, 50);
			menuMenu->option2->buttonTexture = pufferSprite;
			menuMenu->option2Price = new TextObject("option2", std::to_string(TOWERCOST), FELIX_TITLING_32);
			menuMenu->option2Price->SetPosition(towerPos.x - 20, towerPos.y + 75);
			menuMenu->option2Price->SetColor(0, 0, 0, 1);

			break;
		}
		case upgradeTower:
		{
			menu = Add_Object(OBJECT_MENU);
			AddComponent(menu, COMPONENT_TRANSFORM);
			AddComponent(menu, COMPONENT_TEXTURE);
			AddComponent(menu, COMPONENT_MESH);
			AddComponent(menu, COMPONENT_PHYSICS);
			AddComponent(menu, COMPONENT_MENU);
			TransformComponent* menuPos = GetTransformComp(menu);
			TextureComponent* menuTexComp = GetTextureComp(menu);
			MeshComponent* menuMesh = GetMeshComp(menu);
			MenuComponent* menuMenu = GetMenuComp(menu);

			menuMenu->menu_type = type;
			menuPos->position.x = towerPos.x;
			menuPos->position.y = towerPos.y + 75;
			menuPos->scale.x = 200;
			menuPos->scale.y = 60;
			menuTexComp->texture = PopupMenuTex;
			menuTexComp->level = top;
			menuMesh->mesh = squareMesh;

			if (GetTurretPlatformComp(platform)->upgrade1 < 3)
			{
				menuMenu->option1 = createButton(towerPos.x - 70, towerPos.y + 75, 50, 50);
				menuMenu->option1->buttonTexture = sword;
				menuMenu->option1Price = new TextObject("option1", std::to_string(UPGRADECOST + (50 * GetTurretPlatformComp(platform)->upgrade1)), FELIX_TITLING_32);
				menuMenu->option1Price->SetPosition(towerPos.x - 90, towerPos.y + 75);
				menuMenu->option1Price->SetColor(0, 0, 0, 1);

				menuMenu->upgrade1Text = new TextObject("upgrade1", std::to_string(GetTurretPlatformComp(platform)->upgrade1), FELIX_TITLING_32);
				menuMenu->upgrade1Text->SetPosition(towerPos.x - 95, towerPos.y + 105);
				menuMenu->upgrade1Text->SetColor(0, 0, 0, 1);
				menuMenu->upgrade1Text->SetScale(0.7, 0.7);
			}

			if (GetTurretPlatformComp(platform)->upgrade2 < 3)
			{
				menuMenu->option2 = createButton(towerPos.x, towerPos.y + 75, 50, 50);
				menuMenu->option2->buttonTexture = watch;
				menuMenu->option2Price = new TextObject("option2", std::to_string(UPGRADECOST + (50 * GetTurretPlatformComp(platform)->upgrade2)), FELIX_TITLING_32);
				menuMenu->option2Price->SetPosition(towerPos.x - 20, towerPos.y + 75);
				menuMenu->option2Price->SetColor(0, 0, 0, 1);

				menuMenu->upgrade2Text = new TextObject("upgrade2", std::to_string(GetTurretPlatformComp(platform)->upgrade2), FELIX_TITLING_32);
				menuMenu->upgrade2Text->SetPosition(towerPos.x - 25, towerPos.y + 105);
				menuMenu->upgrade2Text->SetColor(0, 0, 0, 1);
				menuMenu->upgrade2Text->SetScale(0.7, 0.7);
			}

			if (GetTowerComp(GetTurretPlatformComp(platform)->tower)->type == 0)
			{
				menuMenu->option3 = createButton(towerPos.x + 70, towerPos.y + 75, 50, 50);
				menuMenu->option3->buttonTexture = pufferSprite;
				menuMenu->option3Price = new TextObject("option3", std::to_string(UPGRADECOST), FELIX_TITLING_32);
				menuMenu->option3Price->SetPosition(towerPos.x + 50, towerPos.y + 75);
				menuMenu->option3Price->SetColor(0, 0, 0, 1);
			}
			else
			{
				menuMenu->option3 = createButton(towerPos.x + 70, towerPos.y + 75, 50, 50);
				menuMenu->option3->buttonTexture = towerTexture;
				menuMenu->option3Price = new TextObject("option3", std::to_string(UPGRADECOST), FELIX_TITLING_32);
				menuMenu->option3Price->SetPosition(towerPos.x + 50, towerPos.y + 75);
				menuMenu->option3Price->SetColor(0, 0, 0, 1);
			}

			break;
		}
	}
	menuExists = true;
}

void DeletePopupMenu()
{
	TextureComponent* menuTexComp = GetTextureComp(menu);
	MenuComponent* menuMenu = GetMenuComp(menu);
	menuTexComp->texture = NULL;

	if (menuMenu->option1 != NULL)
		destroyButton(menuMenu->option1);

	if (menuMenu->option2 != NULL)
		destroyButton(menuMenu->option2);

	if (menuMenu->option3 != NULL)
		destroyButton(menuMenu->option3);

	if (menuMenu->option1Price != NULL)
		menuMenu->option1Price->Kill();

	if (menuMenu->option2Price != NULL)
		menuMenu->option2Price->Kill();
	
	if (menuMenu->option3Price != NULL)
		menuMenu->option3Price->Kill();

	if (menuMenu->upgrade1Text != NULL)
		menuMenu->upgrade1Text->Kill();

	if (menuMenu->upgrade2Text != NULL)
		menuMenu->upgrade2Text->Kill();

	if (menuMenu->upgrade3Text != NULL)
		menuMenu->upgrade3Text->Kill();

	Remove_Object(menu);
	menuExists = false;
}

void popupMenuClick(float mouseX, float mouseY)
{
	MenuComponent* menuMenu = GetMenuComp(menu);
	
	if (menuMenu->menu_type == newTower)
	{
		if (menuMenu->option1 != NULL && menuMenu->option1->mouseOver)
		{
			if (money >= TOWERCOST)
			{
				GetTurretPlatformComp(platform)->hasTower = true;
				GetTurretPlatformComp(platform)->tower = createTowerPos(towerPos, standardTower);
				money -= TOWERCOST;
			}

			DeletePopupMenu();
			return;
		}
		if (menuMenu->option2 != NULL && menuMenu->option2->mouseOver)
		{
			if (money >= TOWERCOST)
			{
				GetTurretPlatformComp(platform)->hasTower = true;
				GetTurretPlatformComp(platform)->tower = createTowerPos(towerPos, pufferTower);
				money -= TOWERCOST;
			}

			DeletePopupMenu();
			return;
		}
	}
	else
	{
		if (menuMenu->option1 != NULL && menuMenu->option1->mouseOver)
		{
			if (money >= UPGRADECOST + (50 * GetTurretPlatformComp(platform)->upgrade1) && GetTurretPlatformComp(platform)->upgrade1 < 3)
			{
				towerUpgrade(platform, damage);
				money -= UPGRADECOST + (50 * GetTurretPlatformComp(platform)->upgrade1);
					GetTurretPlatformComp(platform)->upgrade1++;
				
			}

			DeletePopupMenu();
			return;
		}
		if (menuMenu->option2 != NULL && menuMenu->option2->mouseOver)
		{
			if (money >= UPGRADECOST + (50 * GetTurretPlatformComp(platform)->upgrade2) && GetTurretPlatformComp(platform)->upgrade2 < 4)
			{
				towerUpgrade(platform, fireRate);
				money -= UPGRADECOST + (50 * GetTurretPlatformComp(platform)->upgrade2);
				GetTurretPlatformComp(platform)->upgrade2++;
			}

			DeletePopupMenu();
			return;
		}
		if (menuMenu->option3 != NULL && menuMenu->option3->mouseOver)
		{
			if (money >= UPGRADECOST && GetTurretPlatformComp(platform)->tower != NULL)
			{
				towerUpgrade(platform, changeTower);
				money -= UPGRADECOST;
			}

			DeletePopupMenu();
			return;
		}
	}
}