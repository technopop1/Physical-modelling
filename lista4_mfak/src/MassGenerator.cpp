#include "MassGenerator.h"
#include "glm/gtc//random.hpp"

MassGenerator::MassGenerator()
{
}

MassGenerator::MassGenerator(float min, float max): minMass(min), maxMass(max)
{
}

void MassGenerator::Generate(float dt, ParticleData* particles, int startId, int endId)
{
	for (int i = startId; i < endId; ++i) {
		particles->particles[i].get()->mass = glm::linearRand(minMass, maxMass);
	}
}
