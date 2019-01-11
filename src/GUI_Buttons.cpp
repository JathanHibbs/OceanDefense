// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	GUI_Buttons.cpp
// Author			:	Jasper Mix
// Creation Date	:	2017/05/12
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
//includes
#include "GUI_Buttons.h"
#include "AEEngine.h"
#include "Math2D.h"

Button_Info ButtonList[BUTTON_NUM_MAX];
AEGfxVertexList* ButtonMesh;
long mouseX, mouseY;

// ---------------------------------------------------------------------------

void buttonUpdate(void)
{
	for (int i = 0; i < BUTTON_NUM_MAX; i++)
	{
		Matrix2D		 trans, rot, scale;
		Button_Info* pButton = ButtonList + i;

		// skip non-active object
		if (pButton->active == INACTIVE)
			continue;


		// Compute the scaling matrix
		if(pButton->mouseOver == ACTIVE)
			Matrix2DScale(&scale, pButton->hoverScale.x, pButton->hoverScale.y);
		else
			Matrix2DScale(&scale, pButton->Scale.x, pButton->Scale.y);

		// Compute the rotation matrix
		Matrix2DRotRad(&rot, pButton->angle);
		// Compute the translation matrix
		Matrix2DTranslate(&trans, pButton->Position.x, pButton->Position.y);
		// Concatenate the 3 matrix in the correct order in the objects transform component's TransformMatrix
		Matrix2D transRot;
		Matrix2DConcat(&transRot, &trans, &rot);
		Matrix2DConcat(&pButton->TransformMatrix, &transRot, &scale);

		buttonMouseOver(pButton);
	}
}


void buttonDraw(void)
{
	for (int i = 0; i < BUTTON_NUM_MAX; i++)
	{
		Button_Info* pButton = ButtonList + i;

		// skip non-active object
		if (pButton->active == INACTIVE)
			continue;
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		AEGfxSetTransform(pButton->TransformMatrix.m);
		AEGfxTextureSet(pButton->buttonTexture, 0.0f, 0.0f);
		AEGfxSetTransparency(1.0f);

		AEGfxMeshDraw(ButtonMesh, AE_GFX_MDM_TRIANGLES);
	}
}


bool buttonMouseOver(Button_Info* button_)
{
	//mouse stuff -Jathan

	AEInputGetCursorPosition(&mouseX, &mouseY);
	//Convert mouse's screen coordinates to world coordinates
	Vector2D mouseWorld;
	AEGfxConvertScreenCoordinatesToWorld((float) mouseX, (float) mouseY, &mouseWorld.x, &mouseWorld.y);

	//
	if (StaticPointToStaticRect(&mouseWorld, &button_->Position, button_->Scale.x, button_->Scale.y))
	{
		button_->mouseOver = ACTIVE;
		return true;
	}
		
	else
	{
		button_->mouseOver = INACTIVE;
		return false;
	}
		
}

Button_Info* createButton(float posX = 0.0f, float posY = 0.0f, float scaleX = 0.0f, float scaleY = 0.0f)
{
	for (int i = 0; i < BUTTON_NUM_MAX; i++)
	{
		Button_Info* pButton = ButtonList + i;
		if (pButton->active == INACTIVE)
		{
			pButton->active = ACTIVE;

			pButton->mouseOver = INACTIVE;
			pButton->Position.x = posX;
			pButton->Position.y = posY;
			pButton->Scale.x = scaleX;
			pButton->Scale.y = scaleY;
			pButton->hoverScale.x = scaleX * 1.1f;
			pButton->hoverScale.y = scaleY * 1.1f;
			pButton->angle = 0.0f;
			pButton->buttonTexture = NULL;

			return pButton;
			break;
		}
	}
}

void destroyButton(Button_Info* button_)
{
	button_->active = INACTIVE;
}