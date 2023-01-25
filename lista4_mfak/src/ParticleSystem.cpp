#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(size_t maxCount)
{
	count = maxCount;
	particles.generate(maxCount);
	aliveParticles.generate(maxCount);

	for (size_t i = 0; i < maxCount; ++i)
		particles.particles[i].get()->isAlive = false;
}

void ParticleSystem::update(double dt)
{
	for (auto& em : emitters)
	{
		em->emit(dt, &particles);
	}

	for (size_t i = 0; i < count; ++i)
	{
		particles.particles[i].get()->acceleration = glm::vec4(0.0f);
	}

	for (auto& up : updaters)
	{
		up->update(dt, &particles);
	}

	//ParticleData::copyOnlyAlive(&particles, &aliveParticles);
}


void ParticleSystem::reset()
{
	particles.countAlive = 0;
}