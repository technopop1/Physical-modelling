#pragma once
#include "ParticleGenerator.h"
#include "ParticleData.h"


class MassGenerator : public ParticleGenerator
{
public:
	MassGenerator();
	MassGenerator(float min, float max);

	void Generate(float dt, ParticleData* particles, int startId, int endId);

	float minMass;
	float maxMass;
};

