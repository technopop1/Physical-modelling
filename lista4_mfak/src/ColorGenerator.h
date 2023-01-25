#pragma once
#include "ParticleGenerator.h"

class ColorGenerator : public ParticleGenerator
{
public:
	ColorGenerator();
	ColorGenerator(glm::vec3 startColor, glm::vec3 endColor);


	void Generate(float dt, ParticleData* particles, int startId, int endId);

	glm::vec3 startColor = glm::vec3(0);
	glm::vec3 endColor = glm::vec3(0);

};

