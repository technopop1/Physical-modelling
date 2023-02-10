#pragma once
#include "ofMain.h"
#include "Particle.h"
#include <memory.h>

class Spring
{
	public:
		//Spring(Particle &p1, Particle &p2, float r = 10.0f, float k = 0.5f) : p1(&p1), p2(&p2), k(k), r(r) {}
		Spring(Particle &p1, Particle &p2, float r = 10.0f, float ks = 0.5f, float kd = 30.0f) : p1(&p1), p2(&p2), ks(ks), kd(kd), r(r) {}
		Spring(Particle *p1, Particle *p2, float r = 10.0f, float ks = 0.5f, float kd = 30.0f) : p1(p1), p2(p2), ks(ks), kd(kd), r(r) {}

		float ks;// = 221100.0f;	// sta³a sprê¿ystoœci
		float kd;// = 30.0f;	// sta³a sprê¿ystoœci
		float r;	// maks odleg³oœæ po³o¿enia równowagi
		Particle * p1;
		Particle * p2;

		//const float pressure = 1826320.0f;
		//const float springRate = 221100.0f;
		//const float kd = 30.0f;

		void calculateForces() {
			glm::vec3 r12 = p1->position.second - p2->position.second;
			float distance = glm::length(r12);
			if (distance > 0.0f) {
				/*glm::vec3 Fs = (distance - r) * ks + (p1->velocity - p2->velocity) * ((r12) / distance) * kd;
				p1->force -= (r12 / distance) * Fs;
				p2->force += (r12 / distance) * Fs;*/
				
				// zakomentowaæ 3 powy¿sze linijki i odkomentowaæ 3 poni¿sze i dzia³a na ks=0.5f
				glm::vec3 x = glm::vec3(p2->position.second - p1->position.second);
				glm::vec3 elasticForce = -ks * x;
				applyConstraint(elasticForce);
			}
		}
		void applyConstraint(glm::vec3 elasticForce) {
			glm::vec3 x = glm::vec3(p2->position.second - p1->position.second);
			float distance = glm::length(x);
			float difference = 0;
			if (distance > 0.1f) {
				difference = (r - distance) / distance;
			}
			if (!p1->isStopped) {
				//p1->force += elasticForce * difference;
				p1->position.second += elasticForce * difference;
			}
			if (!p2->isStopped) {
				//p2->force -= elasticForce * difference;
				p2->position.second -= elasticForce * difference;
			}
			/*glm::vec3 x = glm::vec3(p2->position.second - p1->position.second);
				float distance = glm::length(x);
				float difference = glm::abs(distance - r);
				if (difference > r)
				{

					difference = difference - r;
					x = glm::normalize(x);
					x = x * difference / 2.0f;
					if (!p1->isStopped) {
						p1->position.second += -x;
					}
					if (!p2->isStopped) {
						p2->position.second -= -x;
					}
				}*/
		}

		/*void calculatePressureForce() {
			glm::vec3 x = glm::vec3(p2->position.second - p1->position.second);
			float distance = glm::length(x);
			glm::vec3 Fp = distance * pressure * (1.0f / volume)
		}*/

		glm::vec3 calcSpringCenter() {
			return (p1->position.second + p2->position.second) / 2;
		}

private:


};

