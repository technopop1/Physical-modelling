#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ParticleData.h"
#include "ParticleGenerator.h"

class ParticleEmitter
{
public:

	std::vector<std::unique_ptr<ParticleGenerator>> generators;
	float emitRate{ 100.0f };

	void emit(float dt, ParticleData* particleSystem);

	ParticleEmitter();
	ParticleEmitter(float _emitRate);
	//virtual ~ParticleEmitter() { }

	// calls all the generators and at the end it activates (wakes) particle
	//virtual void emit(float dt, ParticleData* p);

	void addGenerator(ParticleGenerator *gen);
};

