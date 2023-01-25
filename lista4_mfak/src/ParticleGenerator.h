#pragma once
#include "ParticleData.h"

#ifndef M_PI
#define M_PI 		3.1415926535897932384626433832795f
#define M_2_PI 		6.28318530717958647692528676655901f		// PI*2
#endif

class ParticleGenerator
{
public:
	ParticleGenerator();

	virtual void Generate(float dt, ParticleData* particles, int startId, int endId);

	int mode = 1;
	float mass = 1.0f;
	float velocityMin = 1.0f;
	float velocityMax = 1.0f;
	glm::vec3 position = glm::vec3(0);
	glm::vec3 translation = glm::vec3(0);
	glm::vec3 normal = glm::vec3(0, 1, 0);
};
