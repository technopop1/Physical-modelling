#pragma once
#include "ParticleData.h"
#include "ParticleGenerator.h"
#include "ofxGui.h"

class ParticleUpdater
{
public:
	ParticleUpdater() { }
	virtual ~ParticleUpdater() { }

	virtual void update(float dt, ParticleData* p) = 0;
	virtual void update2(float dt, ParticleData* p, ParticleGenerator *particleEmitter) = 0;
	virtual void update3(float dt, ParticleData* particleData, ParticleGenerator *particleGenerator) = 0;
};


class EulerUpdater : public ParticleUpdater
{
public:
	glm::vec4 globalAcceleration;
	float G = 15.0f;

public:
	EulerUpdater() : globalAcceleration(0.0) { }

	virtual void update(float dt, ParticleData* p) override;
	virtual void update2(float dt, ParticleData* p, ParticleGenerator *particleGenerator) override;
	virtual void update3(float dt, ParticleData* particleData, ParticleGenerator *particleGenerator) override;
};