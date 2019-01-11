// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	GUI_Buttons.h
// Author			:	Jasper Mix
// Creation Date	:	2017/05/12
// ---------------------------------------------------------------------------
#pragma once
// ---------------------------------------------------------------------------
//includes
#include "Vector2D.h"
#include "Matrix2D.h"
#include "AEEngine.h"

// ---------------------------------------------------------------------------
//defines
#define BUTTON_NUM_MAX		32
#define ACTIVE				1
#define INACTIVE			0


typedef struct Button_Info Button_Info;
struct Button_Info
{
	unsigned active, mouseOver;
	float angle;
	Vector2D Position, Scale, hoverScale;
	Matrix2D TransformMatrix;
	AEGfxTexture* buttonTexture;
};

void buttonUpdate(void);

void buttonDraw(void);

bool buttonMouseOver(Button_Info* button_);

Button_Info* createButton(float posX, float posY, float scaleX, float scaleY);

void destroyButton(Button_Info* button_);
