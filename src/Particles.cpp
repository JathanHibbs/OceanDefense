#include "main.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Particles.h"
#include "objects.h"
#include "2DGameEngineIncludes.h"

AEGfxVertexList* ParticleSquareMesh;
AEGfxVertexList* ParticleCircleMesh;
Particle_Info ParticleList[PARTICLE_NUM_MAX];

void SetParticleColor(Particle_Info* particle_, float r_, float g_, float b_, float a_)
{
	particle_->Mesh.Color.r = r_;
	particle_->Mesh.Color.g = g_;
	particle_->Mesh.Color.b = b_;
	particle_->Mesh.Color.a = a_;
}

// ---------------------------------------------------------------------------
void ParticleEmit(unsigned long type, float x, float y, float width, float height, float particlesPerSec)
{

	for (int i = 0; i < particlesPerSec; i++)
	{
		Particle_Info* pParticle = CreateParticle(type);
		pParticle->Transform.Position.x = x + (AERandFloat() * width - (width / 2));
		pParticle->Transform.Position.y = y + (AERandFloat() * height - (height / 2));

	}
}

// ---------------------------------------------------------------------------
Particle_Info* CreateParticle(unsigned long type_)
{
	Particle_Info* NewParticle;
	

	switch (type_)
	{
		case PARTICLE_SMOKE1:
		{
			for (int i = 0; i < PARTICLE_NUM_MAX; i++)
			{
				NewParticle = ParticleList + i;
				if (NewParticle->ActiveFlag == INACTIVE)
				{
					// initialize all the veriables
					NewParticle->Transform.angle = 0.0f;
					NewParticle->Physics.rotVelocity = 0.0f;

					Vector2DZero(&NewParticle->Transform.Position);
					Vector2DSet(&NewParticle->Transform.Scale, 13, 13);

					Vector2DZero(&NewParticle->Physics.Velocity);

					// Set up veriables depending on the particle type
					NewParticle->Mesh.Mesh = ParticleCircleMesh;
					SetParticleColor(NewParticle, 0.4f, 0.4f, 0.5f, 0.2f);

					NewParticle->ActiveFlag = ACTIVE;
					NewParticle->Type = PARTICLE_SMOKE1;

					break;
				}
			}
			break;
		}
		

		// ---------------------------------------------------------------------------
		case PARTICLE_FIRE1:
		{
			for (int i = 0; i < PARTICLE_NUM_MAX; i++)
			{
				NewParticle = ParticleList + i;
				if (NewParticle->ActiveFlag == INACTIVE)
				{
					// initialize all the veriables
					NewParticle->Transform.angle = 0.0f;
					NewParticle->Physics.rotVelocity = 0.0f;

					Vector2DZero(&NewParticle->Transform.Position);
					Vector2DSet(&NewParticle->Transform.Scale, 10, 10);

					Vector2DZero(&NewParticle->Physics.Velocity);

					// Set up veriables depending on the particle type
					NewParticle->Mesh.Mesh = ParticleSquareMesh;
					SetParticleColor(NewParticle, 1.0f, 0.1f + (AERandFloat() * 0.6f), 0.1f, 0.4f);

					NewParticle->ActiveFlag = ACTIVE;
					NewParticle->Type = PARTICLE_FIRE1;

					break;
				}
			}
			break;
		}
		// ---------------------------------------------------------------------------
		case PARTICLE_BULLET_TRAIL:
		{
			for (int i = 0; i < PARTICLE_NUM_MAX; i++)
			{
				NewParticle = ParticleList + i;
				if (NewParticle->ActiveFlag == INACTIVE)
				{
					// initialize all the veriables
					NewParticle->Transform.angle = 0.0f;
					NewParticle->Physics.rotVelocity = 0.0f;

					Vector2DZero(&NewParticle->Transform.Position);
					Vector2DSet(&NewParticle->Transform.Scale, 5, 5);

					Vector2DZero(&NewParticle->Physics.Velocity);

					// Set up veriables depending on the particle type
					NewParticle->Mesh.Mesh = ParticleCircleMesh;
					SetParticleColor(NewParticle, 0.0f, 0.0f, 0.0f, AERandFloat());

					NewParticle->ActiveFlag = ACTIVE;
					NewParticle->Type = PARTICLE_BULLET_TRAIL;

					break;
				}
			}
			break;
		}
	}
	return NewParticle;
}

// ---------------------------------------------------------------------------
void ParticleLoad()
{
	// creat the basic square mesh
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	ParticleSquareMesh = AEGfxMeshEnd();


	//Creating the circle mesh
	float parts = 12;
	float circleAngleStep = PI / parts;
	for (int i = 0; i < parts; ++i)
	{
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f,
			cosf(i * 2 * circleAngleStep) *0.5f, sinf(i * 2 * circleAngleStep) *0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
			cosf((i + 1) * 2 * circleAngleStep) *0.5f, sinf((i + 1) * 2 * circleAngleStep) *0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	}

	ParticleCircleMesh = AEGfxMeshEnd();
}
// ---------------------------------------------------------------------------
void ParticleInit()
{
	// set all the active flags to INACTIVE
	for (int i = 0; i < PARTICLE_NUM_MAX; i++)
	{
		Particle_Info* pParticle = ParticleList + i;
		pParticle->ActiveFlag = INACTIVE;


		// initialize all the veriables
		pParticle->Transform.angle = 0.0f;
		pParticle->Physics.rotVelocity = 0.0f;

		Vector2DZero(&pParticle->Transform.Position);
		Vector2DZero(&pParticle->Transform.Scale);

		Vector2DZero(&pParticle->Physics.Velocity);

	}
}
// ---------------------------------------------------------------------------
void ParticleUpdate()
{
	for (int i = 0; i < PARTICLE_NUM_MAX; i++)
	{
		Particle_Info* pParticle = ParticleList + i;
		if (pParticle->ActiveFlag == INACTIVE)
			continue;

		// ---------------------------------------------------------------------------
		// update position based on velocity
		pParticle->Transform.Position.x += pParticle->Physics.Velocity.x;
		pParticle->Transform.Position.y += pParticle->Physics.Velocity.y;
							
		pParticle->Transform.angle += pParticle->Physics.rotVelocity;


		// ---------------------------------------------------------------------------
		// Particle Behaivior
		switch (pParticle->Type)
		{
			case PARTICLE_SMOKE1:
			{
				pParticle->Physics.Velocity.y = 0.5f + AERandFloat();
				pParticle->Physics.Velocity.x = 1.0f + AERandFloat();
				pParticle->Physics.rotVelocity = AERandFloat() - 0.5f;

				if (AERandFloat() < 0.03)
					pParticle->ActiveFlag = INACTIVE;

				break;
			}

			case PARTICLE_FIRE1:
			{
				pParticle->Physics.Velocity.y = (AERandFloat() * 4.0f) - 2.0f;
				pParticle->Physics.Velocity.x = (AERandFloat() * 4.0f) - 2.0f;
				pParticle->Physics.rotVelocity = AERandFloat() - 0.5f;

				if (AERandFloat() < 0.15)
					pParticle->ActiveFlag = INACTIVE;

				break;
			}

			case PARTICLE_BULLET_TRAIL:
			{
				pParticle->Physics.Velocity.y = (AERandFloat() * 2.0f) - 1.0f;
				pParticle->Physics.Velocity.x = (AERandFloat() * 2.0f) - 1.0f;
				pParticle->Physics.rotVelocity = AERandFloat() - 0.5f;

				if (AERandFloat() < 0.15)
					pParticle->ActiveFlag = INACTIVE;

				break;
			}
		}

		// ---------------------------------------------------------------------------
		// calculate the transformation matrix
		Matrix2D		 trans, rot, scale;

		// Compute the scaling matrix
		Matrix2DScale(&scale, pParticle->Transform.Scale.x, pParticle->Transform.Scale.y);
		// Compute the rotation matrix
		Matrix2DRotRad(&rot, pParticle->Transform.angle);
		// Compute the translation matrix
		Matrix2DTranslate(&trans, pParticle->Transform.Position.x, pParticle->Transform.Position.y);
		// Concatenate the 3 matrix in the correct order, in the particles TransformMatrix
		Matrix2D transRot;
		Matrix2DConcat(&transRot, &trans, &rot);
		Matrix2DConcat(&pParticle->Transform.TransformMatrix, &transRot, &scale);
	}
}
// ---------------------------------------------------------------------------
void ParticleDraw()
{
	for (int i = 0; i < PARTICLE_NUM_MAX; i++)
	{
		Particle_Info* pParticle = ParticleList + i;
		if (pParticle->ActiveFlag == INACTIVE)
			continue;

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetTransform(pParticle->Transform.TransformMatrix.m);
		AEGfxSetTintColor(pParticle->Mesh.Color.r, pParticle->Mesh.Color.g, pParticle->Mesh.Color.b, pParticle->Mesh.Color.a);
		AEGfxMeshDraw(pParticle->Mesh.Mesh, AE_GFX_MDM_TRIANGLES);
		AEGfxSetTintColor(1, 1, 1, 1);
	}
}