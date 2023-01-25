#pragma once
#include "ParticleGenerator.h"
#include "ParticleData.h"

class TimeGenerator : public ParticleGenerator
{
public:
	TimeGenerator();
	TimeGenerator(float minTime, float maxTime);

	virtual void Generate(float dt, ParticleData* particles, int startId, int endId);

	float maxTime = 1.0f;
	float minTime = 1.0f;

};

