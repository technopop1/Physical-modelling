#pragma once

#include "ParticleGenerator.h"
#include "glm/gtc/random.hpp"

class SphereVelGen : public ParticleGenerator
{
public:
	float m_minVel;
	float m_maxVel;
public:
	SphereVelGen() : m_minVel(0.0), m_maxVel(0.0) { }

	void Generate(double dt, ParticleData* p, size_t startId, size_t endId);
	//virtual void generate(double dt, ParticleData* p, size_t startId, size_t endId) override;
};
