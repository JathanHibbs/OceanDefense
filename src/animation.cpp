
// ---------------------------------------------------------------------------
// Project Name		:	ProjectLlamaCats
// File Name		:	animation.cpp
// Author			:	Jasper Mix
// Creation Date	:	2017/05/24
// ---------------------------------------------------------------------------

//includes
#include "AEEngine.h"
#include "objects.h"

extern Object_Info ObjectList[OBJECT_NUM_MAX];

//veriables
float animCounter;

void animationInit(void)
{
	
}

void loadAnimation(Object_Info* object_)
{
		
		MeshComponent* meshComp = GetMeshComp(object_);
		TextureComponent* texComp = GetTextureComp(object_);

		if (texComp == NULL)
		{
			AESysPrintf("Animation load error: object has no texture component\n");
			return;
		}
		if (meshComp == NULL)
		{
			AESysPrintf("Animation load error: object has no mesh component\n");
			return;
		}

		float frameSizeX = 1 / (float)texComp->framesX;
		float frameSizeY = 1 / (float)texComp->framesY;

		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFF0000, 0.0f, frameSizeY,
			0.5f, -0.5f, 0xFFFF0000, frameSizeX, frameSizeY,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);

		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFF0000, frameSizeX, frameSizeY,
			0.5f, 0.5f, 0xFFFF0000, frameSizeX, 0.0f,
			-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);
		meshComp->mesh = AEGfxMeshEnd();

		if (texComp->startFrame == 0 && texComp->endFrame == 0)
		{
			texComp->startFrame = 1;
			texComp->endFrame = texComp->framesX * texComp->framesY;
		}
		texComp->frameNum = texComp->framesX * texComp->framesY;
		texComp->frameCounter = texComp->startFrame - 1;
		//set the UV coordinates for the first frame

			//find the xy coordinates of the frame
		int x = 0, y = 0, count = 0;
		while (count < texComp->frameCounter)
		{
			if (x >= texComp->framesX - 1)
			{
				x = 0;
				y++;
			}
			else
			{
				x++;
			}

			count++;
		}
			// set the u and v values based on the xy coordinates and the size of the frames
		texComp->texU = frameSizeX * x;
		texComp->texV = frameSizeY * y;
}
void animationUpdate(void)
{
	for (int i = 0; i < OBJECT_NUM_MAX; i++)
	{
		Object_Info* pObject = ObjectList + i;
		if (pObject->ActiveFlag == INACTIVE)
			continue;

		TextureComponent* texComp = GetTextureComp(pObject);
		if (texComp == NULL)
			continue;

		if (texComp->isAnimated == false)
			continue;

		//
		if (texComp->frameCounter > texComp->endFrame)
			texComp->frameCounter = texComp->endFrame;

		if (texComp->frameCounter < texComp->startFrame)
			texComp->frameCounter = texComp->startFrame;

		if (texComp->animCounter >= 1.0f || texComp->animSpeed == 0.0f)
		{
			if (texComp->frameCounter >= texComp->endFrame)
				texComp->frameCounter = texComp->startFrame - 1;

			// get the size of each frame
			float frameSizeX = 1 / (float)texComp->framesX;
			float frameSizeY = 1 / (float)texComp->framesY;

			//find the xy coordinates of the frame
			int x = 0, y = 0, count = 0;
			while (count < texComp->frameCounter)
			{
				if (x >= texComp->framesX - 1)
				{
					x = 0;
					y++;
				}
				else
				{
					x++;
				}
				
				count++;
			}
			// set the u and v values based on the xy coordinates and the size of the frames
			texComp->texU = frameSizeX * x;
			texComp->texV = frameSizeY * y;

			// increment stuff
			if(texComp->animSpeed > 0.0f)
				texComp->frameCounter++;
			texComp->animCounter = 0.0f;
		}
		else
		{
			texComp->animCounter += (float)AEFrameRateControllerGetFrameTime() * texComp->animSpeed;
		}
	}
}
