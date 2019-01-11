// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	MenuFunctions.cpp
// Author			:	Jasper Mix
// Creation Date	:	2017/04/10
// ---------------------------------------------------------------------------
#include "objects.h"

Object_Info* createButton(float x, float y, float width, float height)
{
	Object_Info* Button = Add_Object(COMPONENT_BUTTON);

	AddComponent(Button, COMPONENT_TRANSFORM);
	AddComponent(Button, COMPONENT_MESH);
	AddComponent(Button, COMPONENT_TEXTURE);

	ObjectSetPosition(Button, x, y);
	ObjectSetScale(Button, width, height);
}