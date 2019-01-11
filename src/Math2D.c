/******************************************************************************/
/*!
\file   Math2D.c
\author Jasper Mix
\edited Jake Fletcher
\par    email: jasper99.m@gmail.com
\par    DigiPen login: j.mix
\par    Course: CS230
\par    Project 2 part 1
\date   1/6/2017
\brief
This file contains several math functions
*/
/******************************************************************************/
#include "Math2D.h"
#include "stdio.h"
#define PI      3.1415926535897932384626433832795f
/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	float Dist = sqrt(((pP->x - pCenter->x) * (pP->x - pCenter->x)) + ((pP->y - pCenter->y) * (pP->y - pCenter->y)));

	if (Dist <= Radius)
		return 1;

	return 0;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	float halfWidth = Width / 2.0f;
	float halfHeight = Height / 2.0f;

	if (pPos->x < pRect->x - halfWidth)
		return 0;
	if (pPos->x > pRect->x + halfWidth)
		return 0;
	if (pPos->y < pRect->y - halfHeight)
		return 0;
	if (pPos->y > pRect->y + halfHeight)
		return 0;

	return 1;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	float Radius = Radius0 + Radius1;
	float Dist = sqrt(((pCenter0->x - pCenter1->x) * (pCenter0->x - pCenter1->x)) + ((pCenter0->y - pCenter1->y) * (pCenter0->y - pCenter1->y)));

	if (Dist <= Radius)
		return 1;

	return 0;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	int dist = Vector2DDistance(pRect0, pRect1);
	if (dist >= Width0 / 2 + Width1 / 2 || dist >= Height0 / 2 + Height1 / 2)
	{
		return 0;
	}
	return 1;
}


int RadToDeg(float angle)
{
	return angle * 180 / PI;
}

float DegToRad(int angle)
{
	return angle * (float)(PI / 180);
}
