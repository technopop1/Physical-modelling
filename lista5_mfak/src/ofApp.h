#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "Spring.h"
#include "Cloth.h"
#include "IcoSphere.h"
#include "SystemData.h"

class IcoSphere;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		float deltaTime = 0.0f;

		ofEasyCam cam;
		ofSpherePrimitive sphere;

		std::vector<Particle> particles;
		std::vector<Spring> springs;
		Cloth cloth;
		IcoSphere myIcoSphere;
		//SystemData systemData;

		void checkCollinearity();

	public:


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
		
};
