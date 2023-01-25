#pragma once

#include "ParticleGenerator.h"
#include "glm/gtc/random.hpp"

class CircleGenerator : public ParticleGenerator
{
public:
	CircleGenerator();
	CircleGenerator(float radius, float velocityMax, float velocityMin, int mode, float dispertionAgnle, float mass, glm::vec3 normal, glm::vec3 position);

	void Generate(float dt, ParticleData* particles, int startId, int endId);
	void GenerateVelocity(ParticleData* particles, int startId, int endId);
	void EnableGravity();
	void DisableGravity();

	bool circumferenceOnly = false;
	float radius = 1.0f;
	float dispertionAngle = 0;
	//float velocityMin = 1;
	//float velocityMax = 1;
	//glm::vec3 position = glm::vec3(0);
	//glm::vec3 normal = glm::vec3(0, 1, 0);

private:

	bool gravity = false;
	glm::vec3 AnyOrthogonal(glm::vec3 v);

};

