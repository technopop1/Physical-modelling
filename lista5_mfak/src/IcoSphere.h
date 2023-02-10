#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "Spring.h"

class IcoSphere
{
	public:
		IcoSphere() {}
		IcoSphere(int N, float space = 10.0f) : N(N), space(space) {
			particles.resize(N);
			generateCloth(N);
			generateSprings(N);
		}
		IcoSphere operator=(const IcoSphere& sphere) {
			*this = sphere;
			return *this;
		}
		int N = 0;
		float radius = 50.0f;
		float space = 10.0f;

		// constants
		const float H_ANGLE = PI / 180 * 72;    // 72 degree = 360 / 5
		const float V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree
		float hAngle1 = -PI / 2 - H_ANGLE / 2;  // start from -126 deg at 1st row
		float hAngle2 = -PI / 2;                // start from -90 deg at 2nd row

		std::vector<Particle> particles;
		std::vector<Spring> springs;

private:
		
		void generateCloth(int N) {
			// the first top vertex at (0, 0, r)
			for (int i = 1; i <= 5; ++i)			
				particles.push_back(Particle(std::pair<glm::vec3, glm::vec3>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f))));

			particles[0].position.second = glm::vec3(0.0f, 0.0f, radius);

			int i1, i2;                             // indices
			float z, xy;                            // coords
			// compute 10 vertices at 1st and 2nd rows
			for (int i = 1; i <= 5; ++i)
			{
				i1 = i * 3;         // index for 1st row
				i2 = (i + 5) * 3;   // index for 2nd row

				z = radius * sinf(V_ANGLE);            // elevaton
				xy = radius * cosf(V_ANGLE);            // length on XY plane

				particles[i1].position.second = glm::vec3(xy * cosf(hAngle1), xy * sinf(hAngle1), z);      // x
				particles[i2].position.second = glm::vec3(xy * cosf(hAngle2), xy * sinf(hAngle2), -z);

				// next horizontal angles
				hAngle1 += H_ANGLE;
				hAngle2 += H_ANGLE;
			}

			// the last bottom vertex at (0, 0, -r)
			i1 = 11 * 3;
			particles[i1].position.second = glm::vec3(0.0f, 0.0f, -radius);
		}
		void generateSprings(int N) {
			for (int i = 0; i < 12; ++i) {
				// create springs for each vertex and its 6 adjacent vertices
				if (i % 3 != 2) {   // not the last row
					springs.push_back(Spring(&particles[i], &particles[i + 3], space));
				}
				if (i < 9) {   // not the last column
					springs.push_back(Spring(&particles[i], &particles[i + 4], space));
				}
				if (i < 8) {   // not the last row and last column
					springs.push_back(Spring(&particles[i], &particles[i + 5], space));
				}
			}
		}
public:
		void update(float deltaTime) {
			for (Spring& spring : springs) {
				spring.calculateForces();
			}
			for (int i = 0; i < particles.size(); ++i) {
				particles[i].update(deltaTime);
			}
		}

		void draw() {
			ofSpherePrimitive sphere;
			sphere.setRadius(1.5f);
			for (int i = 0; i < particles.size(); ++i) {
				ofSetColor(particles[i].color.x, particles[i].color.y, particles[i].color.z, 200);
				sphere.setPosition(particles[i].position.second.x, particles[i].position.second.y, particles[i].position.second.z);
				sphere.draw();
			}

			for (Spring& spring : springs) {
				ofSetColor(0, 0, 255, 255);
				ofDrawLine(ofVec3f(spring.p1->position.second), ofVec3f(spring.p2->position.second));
			}
		}
};

