#pragma once
#include "ofMain.h"
static const glm::vec3 G = glm::vec3(0.0f, -9.81f, 0.0f);

class Particle
{
public: 
	bool isStopped = false;
	const float mass = 1.0f;

	std::pair<glm::vec3, glm::vec3> position; // first - poprzednia pozycja, second - aktualna pozycja
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);
	glm::vec3 color = glm::vec3(255.0f, 0.0f, 50.0f);
	glm::vec3 force = glm::vec3(0.0f);

	void update(float deltaTime) {
		if (!isStopped) {
			force += mass * G;

			glm::vec3 tmpPos = position.second;
			position.second = position.second * 2 - position.first + deltaTime* deltaTime* force / mass;
			position.first = tmpPos;

			if (deltaTime == 0) deltaTime = 1.0f;
			velocity = (position.first - position.second) / deltaTime;
			force = glm::vec3(0);
		}
	}
	void draw();

	Particle(){}
	Particle(std::pair<glm::vec3, glm::vec3> position, glm::vec3 velocity = glm::vec3(0), glm::vec3 acceleration = glm::vec3(0), glm::vec3 color = glm::vec3(255.0f, 0.0f, 50.0f), bool isStopped = false) : position(position), velocity(velocity), acceleration(acceleration), color(color), isStopped(isStopped) {
		if (!isStopped) {
			this->force += this->mass * (G + glm::vec3(0.0f, 0.0f, 500.0f));
			this->position.second = this->position.first + 0.1*0.1 * this->force / this->mass;
		}
	}
};

