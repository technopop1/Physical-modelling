#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetCircleResolution(128);
	ofSetFrameRate(60);

	gui.setup();
	gui.add(Nshow.setup("N", Nshow, 0, Nshow));
	gui.add(pointWeight.setup("blackPointsWeights", pointWeight, 10, 2500));
	gui.add(G.setup("G", G, 0.001f, 2.0f));
	gui.add(dt.setup("dt", dt, 0.001f, 10.0f));
	gui.add(ni.setup("ni", ni, 0.0000001f, 0.05f));
	gui.add(Cd.setup("Cd", Cd, 0.001f, 0.5f));
	gui.add(rho.setup("rho", rho, 0.001f, 0.5f));

	mt.seed(1366);
	for (int i = 0; i < N; ++i) {

		circlesRadiuses[i] = std::uniform_real_distribution<float>(3.0f, 6.0f)(mt);
		circlesPos[i] = ofVec2f(std::uniform_int_distribution<int>(circlesRadiuses[i] *2, W - circlesRadiuses[i] *2)(mt), std::uniform_int_distribution<int>(circlesRadiuses[i] *2, H - circlesRadiuses[i] *2)(mt));
		circlesColors[i] = ofVec3f(std::uniform_int_distribution<int>(0, 255)(mt), std::uniform_int_distribution<int>(0, 255)(mt), std::uniform_int_distribution<int>(0, 255)(mt));
		circlesWeights[i] = std::uniform_real_distribution<float>(90.0f, 100.0f)(mt);

		circlesVelocities[i] = ofVec2f(std::uniform_real_distribution<float>(-1.0f, 1.0f)(mt), std::uniform_real_distribution<float>(-1.0f, 1.0f)(mt));
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	
	if (pointPos.size() > 0) {
		for (int i = 0; i < N; ++i) {

			ofVec2f F = ofVec2f(.0f, .0f);
			for (int j = 0; j < pointPos.size(); ++j) {
				float distance = (circlesPos[i].distance(pointPos[j]));
				ofVec2f direction = ofVec2f((pointPos[j] - circlesPos[i]) / distance);
				F += G * circlesWeights[i] * pointWeight / (distance * distance)* direction;
			}
			opor(circlesPos[i], circlesVelocities[i], circlesRadiuses[i], F);

			circlesAcceleration[i] = F / circlesWeights[i];
			
			circlesVelocities[i].x += circlesAcceleration[i].x * dt;
			circlesVelocities[i].y += circlesAcceleration[i].y * dt;
			

			circlesPos[i].x += circlesVelocities[i].x * dt;
			circlesPos[i].y += circlesVelocities[i].y * dt;
			


			checkWallCollision(circlesPos[i].x, circlesPos[i].y, circlesVelocities[i].x, circlesVelocities[i].y, circlesRadiuses[i]);
		}
	}
	else {
		for (int i = 0; i < N; ++i) {
			circlesPos[i].x += circlesVelocities[i].x * dt;
			circlesPos[i].y += circlesVelocities[i].y * dt;
			circlesVelocities[i].y += circlesAcceleration[i].y * dt;

			checkWallCollision(circlesPos[i].x, circlesPos[i].y, circlesVelocities[i].x, circlesVelocities[i].y, circlesRadiuses[i]);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < Nshow; ++i) {
		ofSetColor(circlesColors[i].x, circlesColors[i].y, circlesColors[i].z);
		ofDrawCircle(circlesPos[i].x, circlesPos[i].y, circlesRadiuses[i]);
	}
	for (int i = 0; i < pointPos.size(); ++i) {
		ofSetColor(ofColor::black);
		ofDrawCircle(pointPos[i].x, pointPos[i].y, 20);
	}
	gui.draw();
}	
void ofApp::opor(const ofVec2f&pos, const ofVec2f &v, const float &r, ofVec2f &F) {
	// zastosowanie Formu³y na wielkoœæ oporu aero(hydro)dynamicznego
		//F -= -6 * PI * v * ni * r;
	if (pos.x > W / 2 - 200 && pos.x < W / 2 + 200) {
		float Sd = PI * r * r;
		float pd = rho * v.length() * v.length() / 2;
		float D = Cd * Sd * pd;
		//F += D;
		if (F.x > 0) F.x -= D;
		else F.x += D;
		if (F.y > 0) F.y -= D;
		else F.y += D;
	}
}

void ofApp::checkWallCollision(float& x, float& y, float& vx, float& vy, const float &r) {
	float newSpeed = -0.5f; // wystracenie prêdkoœci przy uderzeniu w œcianê
	if (x + r > W) {
		x = W - r;
		vx *= newSpeed;
	}
	if (x - r < 0 ) {
		x = r;
		vx *= newSpeed;
	}
	if (y + r > H) {
		y = H - r;
		vy *= newSpeed;
	}
	if (y - r < 0) {
		y = r;
		vy *= newSpeed;
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	if (button == OF_MOUSE_BUTTON_LEFT) {
		pointPos.push_back(ofVec2f(x, y));
	}
	if (button == OF_MOUSE_BUTTON_RIGHT) {
		pointPos.push_back(ofVec2f(x, y));
	}
}

void ofApp::keyPressed(int key) {
	if (key == OF_KEY_BACKSPACE) {
		pointPos.clear();
	}

}

void ofApp::mouseDragged(int x, int y, int button) {

}