#pragma once

#include "ofMain.h"
#include <random>
#include <vector>
#include "ofxGui.h"

#define W 1920
#define H 1080
const int N = 5000;

class ofApp : public ofBaseApp {

public:

	ofxPanel gui;

	ofVec2f circlesPos[N];
	ofVec2f circlesVelocities[N];
	ofVec2f circlesAcceleration[N] = { ofVec2f(9.81f) };
	ofVec3f circlesColors[N];
	float circlesRadiuses[N];
	float circlesWeights[N];
	
	std::vector<ofVec2f> pointPos;
	ofxFloatSlider pointWeight = 150.0f;
	ofxFloatSlider G = 0.5f; // sta³a grawitacji
	ofxFloatSlider ni = 0.00000000001f; // lepkoœæ

	ofxFloatSlider dt = 1.0f;
	ofxFloatSlider Nshow = N;


	ofxFloatSlider Cd = 0.45f;
	ofxFloatSlider rho = 0.0000997f;

	mt19937 mt;


public:
	void setup();
	void update();
	void draw();

	void checkWallCollision(float& x, float& y, float& vx, float& vy, const float& r);
	void opor(const ofVec2f & pos, const ofVec2f& v, const float& r, ofVec2f& F);

	void mousePressed(int x, int y, int button) override;
	void mouseDragged(int x, int y, int button) override;
	void keyPressed(int key) override;

};
