#pragma once
#include "ofMain.h"
#include "ParticleData.h"
#include "ParticleEmitter.h"
#include "ParticleUpdater.h"

class ParticleSystem
{
protected:
	ParticleData particles;
	ParticleData aliveParticles;

	size_t count;

	std::vector<std::shared_ptr<ParticleEmitter>> emitters;
	std::vector<std::shared_ptr<ParticleUpdater>> updaters;

public:
	ParticleSystem() {}
	explicit ParticleSystem(size_t maxCount);
	virtual ~ParticleSystem() { }

	ParticleSystem(const ParticleSystem&) = delete;
	ParticleSystem& operator=(const ParticleSystem&) = delete;

	virtual void update(double dt);
	virtual void reset();

	virtual size_t numAllParticles() const { return particles.count; }
	virtual size_t numAliveParticles() const { return particles.countAlive; }

	void addEmitter(std::shared_ptr<ParticleEmitter> em) { emitters.push_back(em); }
	void addUpdater(std::shared_ptr<ParticleUpdater> up) { updaters.push_back(up); }

	ParticleData* finalData() { return &particles; }
};

