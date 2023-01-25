#include "ParticleData.h"

void ParticleData::generate(size_t maxSize)
{
	count = maxSize;
	countAlive = 0;

	//particles.resize(maxSize);

    std::mt19937 mt(555);

    while (maxSize-- > 0) {
        //Particle *particle =  new Particle();

        glm::vec3 velocity = glm::vec3(std::uniform_real_distribution<float>(-10.0f, 10.0f)(mt), std::uniform_real_distribution<float>(-10.0f, 10.0f)(mt), std::uniform_real_distribution<float>(-10.0f, 10.0f)(mt));
        glm::vec3 acceleration = glm::vec3(std::uniform_real_distribution<float>(-3.0f, 3.0f)(mt), std::uniform_real_distribution<float>(-3.0f, 3.0f)(mt), std::uniform_real_distribution<float>(-3.0f, 3.0f)(mt));
        glm::vec3 color = glm::vec3(std::uniform_real_distribution<float>(0, 255)(mt), std::uniform_real_distribution<float>(0, 255)(mt), std::uniform_real_distribution<float>(0, 255)(mt));

        particles.push_back(std::make_unique<Particle>(velocity, acceleration, color));
    }
    /*for (unique_ptr<Particle> &particle : particles) {
        particle.get()->acceleration = ofVec3f(std::uniform_real_distribution<float>(1, 3)(mt), std::uniform_real_distribution<float>(1, 3)(mt), std::uniform_real_distribution<float>(1, 3)(mt));
        particle.get()->velocity = ofVec3f(std::uniform_real_distribution<float>(5, 10)(mt), std::uniform_real_distribution<float>(5, 10)(mt), std::uniform_real_distribution<float>(5, 10)(mt));
        particle.get()->color = ofVec3f(std::uniform_real_distribution<float>(0, 255)(mt), std::uniform_real_distribution<float>(0, 255)(mt), std::uniform_real_distribution<float>(0, 255)(mt));
    }*/
}

void ParticleData::kill(size_t id)
{
    if (countAlive > 0)
    {
        particles[id].get()->isAlive = false;
        swapData(id, countAlive - 1);
        countAlive--;
    }
}

void ParticleData::wake(size_t id)
{
    if (countAlive < count)
    {
        particles[id].get()->isAlive = true;
        swapData(id, countAlive);
        countAlive++;
    }
}

void ParticleData::swapData(size_t idA, size_t idB)
{
    std::swap(particles[idA], particles[idB]);
}