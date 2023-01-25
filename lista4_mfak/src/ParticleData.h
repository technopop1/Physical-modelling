#pragma once

#include "ofMain.h"
#include <vector>
#include <random>

#include "Particle.h"

class ParticleData
{
public:
	int count = 0;
	int countAlive = 0;
	float maxVel = 300;
	//glm::vec3 groupColor = glm::vec3(0);
	
	std::vector<std::unique_ptr<Particle>> particles;

	ParticleData() { }
	ParticleData(size_t maxCount) { generate(maxCount); }

	void generate(size_t maxSize);
	void kill(size_t id);
	void wake(size_t id);
	void swapData(size_t a, size_t b);
};

