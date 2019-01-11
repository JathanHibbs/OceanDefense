/******************************************************************************/
/*!
\file   Vector2D.c
\author Jasper Mix
\par    email: jasper99.m@gmail.com
\par    DigiPen login: j.mix
\par    Course: CS230
\par    Project 2 part 1
\date   1/6/2017
\brief
This file contains several vector math functions
*/
/******************************************************************************/
#include "Vector2D.h"

#define EPSILON 0.0001
#define PI      3.1415926535897932384626433832795f

// ---------------------------------------------------------------------------

void Vector2DZero(Vector2D *pResult)
{
	pResult->x = 0;
	pResult->y = 0;
}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D *pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
{
	pResult->x = -pVec0->x;
	pResult->y = -pVec0->y;
}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = (pVec0->x + pVec1->x);
	pResult->y = (pVec0->y + pVec1->y);
}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = (pVec0->x - pVec1->x);
	pResult->y = (pVec0->y - pVec1->y);
}

// ---------------------------------------------------------------------------

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
{
	float mag;
	mag = sqrt((pVec0->x * pVec0->x)+(pVec0->y * pVec0->y));
	pResult->x = (1 / mag) * pVec0->x;
	pResult->y = (1 / mag) * pVec0->y;
}


float Vector2DMag(Vector2D *pVec0)
{
	return sqrt((pVec0->x * pVec0->x) + (pVec0->y * pVec0->y));
}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
{
	pResult->x = pVec0->x * c;
	pResult->y = pVec0->y * c;
}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = (pVec0->x * c) + pVec1->x;
	pResult->y = (pVec0->y * c) + pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = (pVec0->x * c) - pVec1->x;
	pResult->y = (pVec0->y * c) - pVec1->y;
}

// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D *pVec0)
{
	return sqrt((pVec0->x * pVec0->x) + (pVec0->y * pVec0->y));
}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D *pVec0)
{
	return (pVec0->x * pVec0->x) + (pVec0->y * pVec0->y);
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	//sqrt((x2 – x1)2 + (y2 - y1)2)
	return sqrt(((pVec0->x - pVec1->x) * (pVec0->x - pVec1->x)) + ((pVec1->y - pVec0->y) * (pVec1->y - pVec0->y)));
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return ((pVec0->x - pVec1->x) * (pVec0->x - pVec1->x)) + ((pVec1->y - pVec0->y) * (pVec1->y - pVec0->y));
}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
{
	return (pVec0->x * pVec1->x) + (pVec0->y * pVec1->y);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{
	float RadAngle = angle * (PI / 180);
	pResult->x = cos(RadAngle);
	pResult->y = sin(RadAngle);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	pResult->x = cos(angle);
	pResult->y = sin(angle);
}

// ---------------------------------------------------------------------------
