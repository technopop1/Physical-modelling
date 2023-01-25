#include "CircleGenerator.h"

CircleGenerator::CircleGenerator()
{
}
CircleGenerator::CircleGenerator(float radius, float velocityMax, float velocityMin, int mode, float dispertionAgnle, float mass, glm::vec3 normal, glm::vec3 position) {
	this->radius = radius;
	this->velocityMax = velocityMax;
	this->velocityMin = velocityMin;
	this->mode = mode;
	this->dispertionAngle = dispertionAgnle;
	this->mass = mass;
	this->normal = normal;
	this->position = position;
}

void CircleGenerator::Generate(float dt, ParticleData* particleData, int startId, int endId)
{
	glm::vec4 p;

	for (int i = startId; i < endId; ++i) {

		glm::mat4 rot = glm::mat4(1);
		glm::vec3 maxPos = radius * glm::normalize(AnyOrthogonal(normal)) + position;
		if (!circumferenceOnly) {
			p = glm::vec4(glm::linearRand(position, maxPos), 1);
		}
		else {
			p = glm::vec4(maxPos, 1);
		}

		float angle = glm::linearRand(0.0f, 360.0f);

		rot = glm::rotate(rot, glm::radians(angle), normal);
		
		// tu powinno byæ = position i od tego przesuniêcie o radius * rotacja
		particleData->particles[i].get()->position = glm::vec3(p * rot);
		//glm::mat4 modelMatrix(1.0f);
		//particleData->particles[i].get()->position += glm::vec3(glm::translate(modelMatrix, translation) * glm::vec4(1));

		//if (i % 1000 == 0)
			//std::cout << position << "\t" << radius << "\t" << glm::distance(position, maxPos) << "\t" << particleData->particles[i].get()->position << "\t" << glm::distance(position, particleData->particles[i].get()->position) << "\n";
	}

	GenerateVelocity(particleData, startId, endId);
}

void CircleGenerator::GenerateVelocity(ParticleData* particleData, int startId, int endId)
{

	for (int i = startId; i < endId; ++i) {

		glm::mat4 rot = glm::mat4(1);

		if (dispertionAngle != 0.0f) {
			glm::vec3 axis = glm::normalize(AnyOrthogonal(normal));
			float angle = glm::linearRand(0.0f, dispertionAngle);
			rot = glm::rotate(rot, glm::radians(angle), axis);
			rot = glm::rotate(rot, glm::radians(glm::linearRand(0.0f, 360.0f)), normal);
		}

		particleData->particles[i].get()->velocity = glm::vec4(normal, 1) * rot * glm::linearRand(velocityMin, velocityMax);

		if (gravity) {
			particleData->particles[i].get()->acceleration = glm::vec3(0.0f, -9.81f, 0.0f);
		}
		else {
			particleData->particles[i].get()->acceleration = glm::vec3(0.0f);
		}
	}
}

void CircleGenerator::EnableGravity()
{
	gravity = true;
}

void CircleGenerator::DisableGravity()
{
	gravity = false;
}


glm::vec3 CircleGenerator::AnyOrthogonal(glm::vec3 v)
{
	if (!(v.x == v.y) || !(v.y == v.z))
		// cross z permutacj¹ sk³adowych
		return glm::cross(v, glm::vec3(v.z, v.x, v.y));
	else
		// cross z wersorem osi X
		return glm::cross(v, glm::vec3(1.0f, 0.0f, 0.0f));
}