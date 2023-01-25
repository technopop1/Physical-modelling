#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() :emitRate(100)
{
}

ParticleEmitter::ParticleEmitter(float _emitRate) :emitRate(_emitRate)
{
}

void ParticleEmitter::emit(float dt, ParticleData* particleData)
{
	const int maxNewParticles = static_cast<size_t>(dt * emitRate);
	const int startId = particleData->countAlive;
	const int endId = std::min(startId + maxNewParticles, particleData->count-1);


	for (auto &gen : generators) {
		gen->Generate(dt, particleData, startId, endId);
	}
	for (int i = startId; i < endId; ++i) {
		particleData->wake(i);
	}

}

void ParticleEmitter::addGenerator(ParticleGenerator *gen)
{
	generators.emplace_back(gen);
}
