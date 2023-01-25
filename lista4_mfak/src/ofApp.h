#pragma once

#include "ofMain.h"
#include "ParticleSystem.h"
#include "ParticleUpdater.h"
#include "ParticleEmitter.h"
#include "ParticleData.h"
#include "ParticleGenerator.h"
#include "CircleGenerator.h"
#include "TimeGenerator.h"
#include "ColorGenerator.h"
#include "SphereVelGen.h"


class ofApp : public ofBaseApp{

	public:

		//ParticleSystem particleSystem;
		ofCamera camera;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofSpherePrimitive sphere;
		ofEasyCam cam;
		ofLight light1;
		ofLight light2;
		ofPlanePrimitive ground;
		float deltaTime = 0.0f;

		ParticleEmitter emiter;
		//ParticleEmitter holeEmiter;

		CircleGenerator circleGen;
		ColorGenerator colorGen;
		TimeGenerator timeGen;

		std::vector<CircleGenerator> holesCircleGen;
		std::vector<ParticleData> holesParticles;
		std::vector<ParticleEmitter> holesEmiter;
		CircleGenerator holeCircleGen;
		ColorGenerator holeColorGen;
		TimeGenerator holeTimeGen;

		ParticleData particles;
		//ParticleData holeParticles;

		std::vector<glm::vec3> emitPositions;

		EulerUpdater updater;

		ofxPanel gui;
		ofxFloatSlider mass;
		ofxFloatSlider G;
		ofxFloatSlider dispertionAngle;
		;
};
