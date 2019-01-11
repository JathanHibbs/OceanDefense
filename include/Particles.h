#include "main.h"
#include "Vector2D.h"
#include "Matrix2D.h"

#define PARTICLE_NUM_MAX		4096
// ---------------------------------------------------------------------------
// Meshes
//AEGfxVertexList* ParticleSquareMesh;
//AEGfxVertexList* ParticleCircleMesh;

// ---------------------------------------------------------------------------
// particle structs
enum PARTICLE_TYPE
{
	PARTICLE_SMOKE1,
	PARTICLE_FIRE1,
	PARTICLE_BULLET_TRAIL
};


typedef struct ParticlePhysics ParticlePhysics;
struct ParticlePhysics
{
	Vector2D Velocity;
	float rotVelocity;
};

typedef struct ParticleTransform ParticleTransform;
struct ParticleTransform
{
	Vector2D Position;
	Vector2D Scale;
	Matrix2D TransformMatrix;
	float angle;
};

typedef struct ParticleColor ParticleColor;
struct ParticleColor
{
	float r;
	float g;
	float b;
	float a;
};

typedef struct ParticleMesh ParticleMesh;
struct ParticleMesh
{
	AEGfxVertexList* Mesh;
	ParticleColor Color;
};



typedef struct Particle_Info Particle_Info;
struct Particle_Info
{
	unsigned long Type;
	unsigned long ActiveFlag;

	ParticlePhysics Physics;
	ParticleTransform Transform;
	ParticleMesh Mesh;
};
// ---------------------------------------------------------------------------
// creat the list of particles

//Particle_Info ParticleList[PARTICLE_NUM_MAX];

// ---------------------------------------------------------------------------
// function prototypes
void SetParticleColor(Particle_Info* particle_, float r_, float g_, float b_, float a_);

Particle_Info* CreateParticle(unsigned long type_);

void ParticleEmit(unsigned long type, float x, float y, float width, float height, float particlesPerSec);

void ParticleLoad();
void ParticleInit();
void ParticleUpdate();
void ParticleDraw();
void ParticleFree();