#include "ColorGenerator.h"
#include "glm/gtc/random.hpp"

ColorGenerator::ColorGenerator()
{
}

ColorGenerator::ColorGenerator(glm::vec3 startColor, glm::vec3 endColor) : startColor(startColor), endColor(endColor)
{
}

void ColorGenerator::Generate(float dt, ParticleData* particleData, int startId, int endId)
{
	for (int i = startId; i < endId; ++i) {
		particleData->particles[i].get()->color = glm::linearRand(startColor, endColor);
	}
}
