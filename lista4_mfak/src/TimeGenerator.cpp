#include "TimeGenerator.h"
#include "glm/gtc/random.hpp"`

TimeGenerator::TimeGenerator()
{
}

TimeGenerator::TimeGenerator(float minTime, float maxTime): minTime(maxTime), maxTime(maxTime)
{
}

void TimeGenerator::Generate(float dt, ParticleData* particlesData, int startId, int endId)
{
	for (int i = startId; i < endId; ++i) {
		particlesData->particles[i].get()->maxTimeAlive = glm::linearRand(minTime, maxTime);
		particlesData->particles[i].get()->timeOfLife = 0;
	}
}
