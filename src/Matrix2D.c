/******************************************************************************/
/*!
\file   Matrix2D.c
\author Jasper Mix
\par    email: jasper99.m@gmail.com
\par    DigiPen login: j.mix
\par    Course: CS230
\par    Project 2 part 1
\date   1/6/2017
\brief
This file contains several matrix math functions
*/
/******************************************************************************/
#include "Matrix2D.h"
#include <string.h>
#define PI      3.1415926535897932384626433832795f

/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
	pResult->m[0][0] = 1;
	pResult->m[0][1] = 0;
	pResult->m[0][2] = 0;
	pResult->m[1][0] = 0;
	pResult->m[1][1] = 1;
	pResult->m[1][2] = 0;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	Matrix2D tmpResult;

	tmpResult.m[0][0] = pMtx->m[0][0];
	tmpResult.m[0][1] = pMtx->m[1][0];
	tmpResult.m[0][2] = pMtx->m[2][0];
	tmpResult.m[1][0] = pMtx->m[0][1];
	tmpResult.m[1][1] = pMtx->m[1][1];
	tmpResult.m[1][2] = pMtx->m[2][1];
	tmpResult.m[2][0] = pMtx->m[0][2];
	tmpResult.m[2][1] = pMtx->m[1][2];
	tmpResult.m[2][2] = pMtx->m[2][2];

	memcpy(pResult, &tmpResult, sizeof(Matrix2D));
}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	Matrix2D tmpResult;
	tmpResult.m[0][0] = ((pMtx0->m[0][0])*(pMtx1->m[0][0])) + ((pMtx0->m[0][1])*(pMtx1->m[1][0])) + ((pMtx0->m[0][2])*(pMtx1->m[2][0]));
	tmpResult.m[0][1] = ((pMtx0->m[0][0])*(pMtx1->m[0][1])) + ((pMtx0->m[0][1])*(pMtx1->m[1][1])) + ((pMtx0->m[0][2])*(pMtx1->m[2][1]));
	tmpResult.m[0][2] = ((pMtx0->m[0][0])*(pMtx1->m[0][2])) + ((pMtx0->m[0][1])*(pMtx1->m[1][2])) + ((pMtx0->m[0][2])*(pMtx1->m[2][2]));

	tmpResult.m[1][0] = ((pMtx0->m[1][0])*(pMtx1->m[0][0])) + ((pMtx0->m[1][1])*(pMtx1->m[1][0])) + ((pMtx0->m[1][2])*(pMtx1->m[2][0]));
	tmpResult.m[1][1] = ((pMtx0->m[1][0])*(pMtx1->m[0][1])) + ((pMtx0->m[1][1])*(pMtx1->m[1][1])) + ((pMtx0->m[1][2])*(pMtx1->m[2][1]));
	tmpResult.m[1][2] = ((pMtx0->m[1][0])*(pMtx1->m[0][2])) + ((pMtx0->m[1][1])*(pMtx1->m[1][2])) + ((pMtx0->m[1][2])*(pMtx1->m[2][2]));

	tmpResult.m[2][0] = ((pMtx0->m[2][0])*(pMtx1->m[0][0])) + ((pMtx0->m[2][1])*(pMtx1->m[2][0])) + ((pMtx0->m[2][2])*(pMtx1->m[2][0]));
	tmpResult.m[2][1] = ((pMtx0->m[2][0])*(pMtx1->m[0][1])) + ((pMtx0->m[2][1])*(pMtx1->m[2][1])) + ((pMtx0->m[2][2])*(pMtx1->m[2][1]));
	tmpResult.m[2][2] = ((pMtx0->m[2][0])*(pMtx1->m[0][2])) + ((pMtx0->m[2][1])*(pMtx1->m[2][2])) + ((pMtx0->m[2][2])*(pMtx1->m[2][2]));

	memcpy(pResult, &tmpResult, sizeof(Matrix2D));
}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	pResult->m[0][0] = 1;
	pResult->m[0][1] = 0;
	pResult->m[0][2] = x;
	pResult->m[1][0] = 0;
	pResult->m[1][1] = 1;
	pResult->m[1][2] = y;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	pResult->m[0][0] = x;
	pResult->m[0][1] = 0;
	pResult->m[0][2] = 0;
	pResult->m[1][0] = 0;
	pResult->m[1][1] = y;
	pResult->m[1][2] = 0;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	float angleRad = Angle * (PI / 180);
	pResult->m[0][0] = cos(angleRad);
	pResult->m[0][1] = -sin(angleRad);
	pResult->m[0][2] = 0;
	pResult->m[1][0] = sin(angleRad);
	pResult->m[1][1] = cos(angleRad);
	pResult->m[1][2] = 0;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	pResult->m[0][0] = cos(Angle);
	pResult->m[0][1] = -sin(Angle);
	pResult->m[0][2] = 0;
	pResult->m[1][0] = sin(Angle);
	pResult->m[1][1] = cos(Angle);
	pResult->m[1][2] = 0;
	pResult->m[2][0] = 0;
	pResult->m[2][1] = 0;
	pResult->m[2][2] = 1;
}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	Vector2D tmpResult;

	tmpResult.x = pMtx->m[0][0] * pVec->x + pMtx->m[0][1] * pVec->y;
	tmpResult.y = pMtx->m[1][0] * pVec->x + pMtx->m[1][1] * pVec->y;

	tmpResult.x += pMtx->m[0][2];
	tmpResult.y += pMtx->m[1][2];

	memcpy(pResult, &tmpResult, sizeof(Vector2D));
}

// ---------------------------------------------------------------------------
