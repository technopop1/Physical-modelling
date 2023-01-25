#include "ofApp.h"

#include "ParticleSystem.h"
#include "ParticleUpdater.h"
#include "ParticleEmitter.h"
#include "ParticleData.h"
#include "ParticleGenerator.h"
#include <random>
#include "ofxGui.h"


//ofxAssimpModelLoader model;

//--------------------------------------------------------------
void ofApp::setup(){

	sphere.setRadius(1.8f);
	//sphere.setPosition(ofGetWidth() * .2, ofGetHeight() * .2, 0);

	cam.setDistance(100);

	light1.setPosition(20, 400, 20);
	light1.setDiffuseColor(ofColor(200, 220, 250, 200));
	light1.enable();

	light2.setPosition(600, 100, 20);
	light2.setDiffuseColor(ofColor(200, 220, 250, 100));
	light2.enable();

	ground.setWidth(5000);
	ground.setHeight(5000);
	ground.rotate(-90, 1, 0, 0);
	ground.setPosition(0,-1000,0);

	updater = EulerUpdater();
	
	emiter = ParticleEmitter(2000);
	particles = ParticleData(30000);

	circleGen = CircleGenerator();
	colorGen = ColorGenerator(glm::vec3(255), glm::vec3(200));
	timeGen = TimeGenerator(1, 20);

	circleGen.radius = 10000;
	circleGen.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	circleGen.position = glm::vec3(0, 1000, 0);
	circleGen.velocityMax = 200;
	circleGen.velocityMin = 100;
	circleGen.dispertionAngle = 1;

	emiter.addGenerator(&circleGen);
	emiter.addGenerator(&colorGen);
	emiter.addGenerator(&timeGen);


	holeTimeGen = TimeGenerator(0.5, 2.0f);

	std::vector<glm::vec3> positions {
		glm::vec3(0.0f, 200.0f, 100.0f),
		glm::vec3(500.0f, 200.0f, 500.0f),
		glm::vec3(500.0f, 200.0f, -550.0f),/*
		glm::vec3(-500.0f, 200.0f, 500.0f),
		glm::vec3(-500.0f, 200.0f, -500.0f)*/
	};
	std::vector<glm::vec3> translation = positions;/*{
		glm::vec3(0.0f, 200.0f, 100.0f),
		glm::vec3(500.0f, 200.0f, 500.0f),
		glm::vec3(500.0f, 200.0f, -1500.0f),
		glm::vec3(-500.0f, 200.0f, 500.0f),
		glm::vec3(-500.0f, 200.0f, -500.0f)
	};*/
	std::vector<glm::vec3> normals;
	for (glm::vec3 position : translation) {
		normals.push_back(
			glm::vec3(
				position.x != 0 ? -100.0f / position.x : 0.0f,
				position.y != 0 ? -100.0f / position.y : 0.0f,
				position.z != 0 ? -100.0f / position.z : 0.0f
			));
			//1.0f / position
	}
	for (int i = 0; i < translation.size(); ++i) {
		holesCircleGen.push_back(CircleGenerator(200.0f, 200.0f, -200.0f, 3, 180, 1000'000.0f, normals[i], positions[i]));// positions[i]));
	}
	for (int i = 0; i < translation.size(); ++i) {
		holesCircleGen[i].translation = translation[i];
	}

	for (CircleGenerator& holeCircleGen : holesCircleGen) {
		holesParticles.push_back(ParticleData(25000));
		holesParticles.back().maxVel = holeCircleGen.radius * 15;
		holeCircleGen.circumferenceOnly = true;
		//holesParticles.back().groupColor = glm::vec3(glm::linearRand(0, 255));
	}

	for (int i = 0; i < translation.size(); ++i) {
		holesEmiter.push_back(ParticleEmitter(10000));
	}
	for (int i = 0; i < translation.size(); ++i) {
		holesEmiter[i].addGenerator(&holesCircleGen[i]);
		//holesEmiter[i].addGenerator(&holeColorGen);
		holesEmiter[i].addGenerator(&holeTimeGen);
	}

	std::mt19937 mt(1522);

	gui.setup();
	gui.add(G.setup("G", 10, 0.5, 100));
	gui.add(mass.setup("mass", 1000000.0f, 15000, 1500000));
	gui.add(dispertionAngle.setup("angle", 180.0f, 0.0f, 180.0f));

}

//--------------------------------------------------------------
void ofApp::update(){
	deltaTime = ofGetLastFrameTime();
	emiter.emit(deltaTime, &particles);
	updater.update(deltaTime, &particles);

	for (int i = 0; i < holesCircleGen.size(); ++i) {

		holesEmiter[i].emit(deltaTime, &holesParticles[i]);

		if (holesCircleGen[i].mode == 2) {
			updater.update2(deltaTime, &holesParticles[i], &holesCircleGen[i]);
		}
		else if (holesCircleGen[i].mode == 3) {
			updater.update3(deltaTime, &holesParticles[i], &holesCircleGen[i]);
		}
		else {
			updater.update(deltaTime, &holesParticles[i]);
		}
		updater.G = G;
		holesCircleGen[i].mass = mass;
		holesCircleGen[i].dispertionAngle = dispertionAngle;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	ofEnableDepthTest();

	for (int i = 0; i < particles.countAlive; ++i) {

		ofSetColor(particles.particles[i].get()->color.x, particles.particles[i].get()->color.y, particles.particles[i].get()->color.z, 255);
		sphere.setPosition(particles.particles[i].get()->position);
		sphere.draw();

	}
	for (int j = 0 ; j < holesParticles.size(); ++j){
		for (int i = 0; i < holesParticles[j].countAlive; ++i) {
			ofSetColor(i*i*i, i*i, i, 255);
			//ofSetColor(holesParticles[j].particles[i].get()->color.x, holesParticles[j].particles[i].get()->color.y, holesParticles[j].particles[i].get()->color.z, 255);
			//ofSetColor(holesParticles[i].groupColor.x, holesParticles[i].groupColor.y, holesParticles[i].groupColor.z, 255.0f);
			sphere.setPosition(holesParticles[j].particles[i].get()->position);
			sphere.draw();
		}
	}

	ofSetColor(200, 200, 200, 155);
	ground.draw();

	ofDisableDepthTest();

	cam.end();

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == int('w')) {
		glm::vec3 dir = cam.getLookAtDir();
		cam.move(dir * deltaTime * 1000);
	}
	if (key == int('s')) {
		glm::vec3 dir = cam.getLookAtDir();
		cam.move(-dir * deltaTime * 1000);
	}
	if (key == int('a')) {
		glm::vec3 dir = cam.getSideDir();
		cam.move(-dir * deltaTime * 1000);
	}
	if (key == int('d')) {
		glm::vec3 dir = cam.getSideDir();
		cam.move(dir * deltaTime * 1000);
	}
	if (key == int('e')) {
		glm::vec3 dir = cam.getUpDir();
		cam.move(dir * deltaTime * 1000);
	}
	if (key == int('q')) {
		glm::vec3 dir = -cam.getUpDir();
		cam.move(dir * deltaTime * 1000);
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
