#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "Spring.h"
#include "SystemData.h"

class Cloth
{
	public:
		Cloth() {}
		Cloth(int N, float space = 10.0f) : N(N), space(space) {
			particles.resize(N);
			generateIcoSphere(N);
			generateSprings(N);
		}
		int N = 0;
		float space = 10.0f;
		std::vector<std::vector<Particle>> particles;
		std::vector<Spring> springs; // num = (col_num-1) * row_num  + (row_num-1) * col_num

private:
		
		void generateIcoSphere(int N) {
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					if (i == 0) {
						particles[i].push_back(Particle(
							std::pair<glm::vec3, glm::vec3>(glm::vec3(j * space, i * (-space), 0.0f), glm::vec3(j * space, i * (-space), 0.0f)),
							glm::vec3(0.0f, 0.0f, 0.0f),
							glm::vec3(0.0f, 0.0, 0.0f),
							glm::vec3(50.0f, 255.0f, 0.0f),
							true));
					}
					else {
						particles[i].push_back(Particle(
							std::pair<glm::vec3, glm::vec3>(glm::vec3(j * space, i * (-space), 0.0f), glm::vec3(j * space, i * (-space), 0.0f)),
							glm::vec3(0.0f, 0.0f, 0.0f),
							glm::vec3(0.0f, 0.0, 0.0f),
							glm::vec3(255.0f, 0.0f, 50.0f),
							false));
					}
				}
			}
		}
		void generateSprings(int N) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					//int index = i * N + j;
					if (i < N - 1) {
						springs.push_back(Spring(particles[i][j], particles[i + 1][j], space));
					}
					if (j < N - 1) {
						springs.push_back(Spring(particles[i][j], particles[i][j + 1], space));
					}
				}
			}
		}
public:
		void update(float deltaTime) {
			for (Spring& spring : springs) {
				spring.calculateForces();
			}
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					particles[i][j].update(deltaTime);
				}
			}
		}

		void draw() {
			ofSpherePrimitive sphere;
			sphere.setRadius(1.5f);
			static int angle = 25;
			static int multiplicator = -1;
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					if (i < N/2)
						ofSetColor(255, 255, 255, 255);
					else
						ofSetColor(255, 0, 0, 255);
						//ofSetColor(particles[i][j].color.x, particles[i][j].color.y, particles[i][j].color.z, 200);
					sphere.setPosition(particles[i][j].position.second.x, particles[i][j].position.second.y, particles[i][j].position.second.z);
					sphere.draw();

					if (i < N - 1 && j < N - 1) {
						// PACMAN
						float pacManSize = N * 3 / 10 * space;
						if (glm::distance(particles[i][j].position.second, particles[N / 2][N / 2].position.second) < pacManSize &&
							(ofVec2f(ofVec2f(N / 2, N / 2) - ofVec2f(N / 2, N / 2 + 1)).angle(ofVec2f(ofVec2f(N / 2, N / 2) - ofVec2f(i, j))) > angle ||
								ofVec2f(ofVec2f(N / 2, N / 2) - ofVec2f(N / 2, N / 2 + 1)).angle(ofVec2f(ofVec2f(N / 2, N / 2) - ofVec2f(i, j))) < -angle))
						{
							ofSetColor(255, 255, 0, 255);
						}
						if ( (j == N / 2 + 2 && i == N / 2 - 5) ||
							(j == N / 2 + 1 && i == N / 2 - 6) ||
							(j == N / 2 + 2 && i == N / 2 - 6) ||
							(j == N / 2 + 3 && i == N / 2 - 6) ||
							(j == N / 2 + 2 && i == N / 2 - 7)){
							ofSetColor(0, 0, 0, 255);
						}
						ofDrawTriangle(particles[i][j].position.second, particles[i + 1][j].position.second, particles[i + 1][j + 1].position.second);
						ofDrawTriangle(particles[i][j].position.second, particles[i][j+1].position.second, particles[i + 1][j + 1].position.second);
					}
				}
			}
			if (angle > 0 && angle <= 25) {
				angle += multiplicator * 1;
			}
			else {
				multiplicator *= -1;
				angle = 1;
			}
			for (Spring& spring : springs) {
				ofSetColor(0, 0, 255, 255);
				ofDrawLine(ofVec3f(spring.p1->position.second), ofVec3f(spring.p2->position.second));
			}
		}
};

