#pragma once
#include "ofMain.h"
class Particle
{
public: 
	bool isAlive = false;
	float timeOfLife { 0 };
	float maxTimeAlive { 10 };
	float mass = 1;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 color;

	void update(float deltaTime);
	void draw();

	Particle(){}
	Particle(glm::vec3 velocity, glm::vec3 acceleration, glm::vec3 color) : velocity(velocity), acceleration(acceleration), color(color) {}
};

