#include "ParticleUpdater.h"
#include "glm/gtc/random.hpp"
#include "ofMain.h"

void EulerUpdater::update(float dt, ParticleData* particleData)
{
	const unsigned int endId = particleData->countAlive;
	for (size_t i = 0; i < endId; ++i) {
		particleData->particles[i].get()->acceleration += dt * glm::vec3(globalAcceleration);

		particleData->particles[i].get()->velocity += dt * particleData->particles[i].get()->acceleration;

		particleData->particles[i].get()->position += dt * particleData->particles[i].get()->velocity;

		particleData->particles[i].get()->timeOfLife += dt;

		
		if (particleData->particles[i].get()->timeOfLife >= particleData->particles[i].get()->maxTimeAlive) {
			particleData->kill(i);
		}
	}
}
void EulerUpdater::update2(float dt, ParticleData* particleData, ParticleGenerator *particleGenerator)
{
	const unsigned int endId = particleData->countAlive;
	for (size_t i = 0; i < endId; ++i) {

		float distance = glm::distance(particleData->particles[i].get()->position, particleGenerator->position);
		glm::vec3 direction = glm::vec3((particleGenerator->position - particleData->particles[i].get()->position) / distance);
		glm::vec3 F = G * particleData->particles[i].get()->mass * particleGenerator->mass / (distance * distance) * direction;

		particleData->particles[i].get()->acceleration = F/ particleData->particles[i].get()->mass;// globalA;

		particleData->particles[i].get()->velocity += dt * particleData->particles[i].get()->acceleration;

		particleData->particles[i].get()->position += dt * particleData->particles[i].get()->velocity;

		particleData->particles[i].get()->timeOfLife += dt;

		
		if (particleData->particles[i].get()->timeOfLife >= particleData->particles[i].get()->maxTimeAlive || abs(particleData->particles[i].get()->velocity.x) > particleGenerator->velocityMax*3 || abs(particleData->particles[i].get()->velocity.y > particleGenerator->velocityMax * 3) || abs(particleData->particles[i].get()->velocity.z > particleGenerator->velocityMax * 3)) {
			particleData->kill(i);
		}/*if (particleData->particles[i].get()->timeOfLife >= particleData->particles[i].get()->maxTimeAlive || particleData->particles[i].get()->position.y < 0 ||  abs(particleData->particles[i].get()->velocity.x) > particleGenerator->velocityMax*3 || abs(particleData->particles[i].get()->velocity.y > particleGenerator->velocityMax * 3) || abs(particleData->particles[i].get()->velocity.z > particleGenerator->velocityMax * 3)) {
			particleData->kill(i);
		}*/
	}
}
void EulerUpdater::update3(float dt, ParticleData* particleData, ParticleGenerator *particleGenerator)
{
	glm::vec4 p;
	glm::mat4 rot = glm::mat4(1);
	float angle = glm::linearRand(0.0f, 360.0f);
	rot = glm::rotate(rot, glm::radians(angle), particleGenerator->normal);
	//std::cout << particleGenerator->position << "\t";
	//glm::mat4 modelMatrix(1.0f);
	//glm::vec3 tempPosition = particleData->particles[i].get()->position + glm::vec3(glm::translate(modelMatrix, translation) * glm::vec4(1));

	glm::vec3 tempPosition = glm::vec3(glm::vec4(particleGenerator->position, 1) * rot);
	//std::cout << tempPosition << "\n";

	const unsigned int endId = particleData->countAlive;
	for (size_t i = 0; i < endId; ++i) {

		float distance = glm::distance(particleData->particles[i].get()->position, tempPosition);
		glm::vec3 direction = glm::vec3((tempPosition - particleData->particles[i].get()->position) / distance);
		glm::vec3 F = G * particleData->particles[i].get()->mass * particleGenerator->mass / (distance * distance) * direction;

		particleData->particles[i].get()->acceleration = F/ particleData->particles[i].get()->mass;// globalA;

		particleData->particles[i].get()->velocity += dt * particleData->particles[i].get()->acceleration;

		particleData->particles[i].get()->position += dt * particleData->particles[i].get()->velocity;

		particleData->particles[i].get()->timeOfLife += dt;
		//if(i%1000 == 0)
		//std::cout << tempPosition << "\n";

		if (particleData->particles[i].get()->timeOfLife >= particleData->particles[i].get()->maxTimeAlive) {
			particleData->kill(i);
		}
		if (abs(particleData->particles[i].get()->velocity.x) > particleGenerator->velocityMax * 3 || abs(particleData->particles[i].get()->velocity.y > particleGenerator->velocityMax * 3) || abs(particleData->particles[i].get()->velocity.z > particleGenerator->velocityMax * 3)) {
			particleData->kill(i);
		}
	}
}