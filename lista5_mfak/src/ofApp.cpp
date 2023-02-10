#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	sphere.setRadius(1.8f);

	cam.setDistance(1000);

	cloth = Cloth(50, 25);
	//myIcoSphere = IcoSphere(15, 15);
}

//--------------------------------------------------------------
void ofApp::update(){
	deltaTime = ofGetLastFrameTime()*5;

	cloth.update(deltaTime);
	//myIcoSphere.update(deltaTime);
}

//--------------------------------------------------------------
void ofApp::draw(){

	cam.begin();
	ofEnableDepthTest();

	cloth.draw();
	//myIcoSphere.draw();

	//checkCollinearity();
	ofDisableDepthTest();
	cam.end();
}

void ofApp::checkCollinearity() {
	glm::vec3 lineTrace = (cam.getPosition() + cam.getLookAtDir()) * 10000;
	for (Spring &spring : cloth.springs) {
		glm::vec3 v = cam.worldToScreen(spring.p1->position.second) - cam.worldToScreen(spring.p2->position.second);
		glm::vec3 distance = glm::vec3(v.y, -v.x, 0.0f) * glm::vec3(ofGetMouseX(), ofGetMouseY(), 0.0f) / glm::length(glm::vec3(v.y, -v.x, 0.0f));
		glm::vec3 distance2 = glm::vec3(-v.z, 0.0f, v.x) * glm::vec3(ofGetMouseX(), ofGetMouseY(), 0.0f) / glm::length(glm::vec3(-v.z, 0.0f, v.x));
		//std::cout << glm::length(distance) << "\t" << glm::length(distance2) << "\n";

		/*glm::vec3 crossProd = glm::cross(lineTrace, spring.p1->position.second - spring.p2->position.second);
		if (crossProd == glm::vec3(0)) {
			std::cout << "kolizja\n";
		}*/
	}
	//glm::vec3 mouse3d = cam.screenToWorld(ofVec3f(ofGetMouseX(), ofGetMouseY(), cam.getPosition().z), ofGetCurrentViewport());
	//glm::vec3 projection = glm::vec3(glm::vec4((cam.getPosition() - mouse3d + cam.getLookAtDir(), 1.0f)) * cam.getModelViewMatrix());
	//glm::vec3 lookAtVec = glm::rotate(cam.getPosition(), glm::acos(glm::dot(cam.getLookAtDir(), (cam.getPosition() - mouse3d + cam.getLookAtDir())) / (glm::length(cam.getLookAtDir()) * glm::length(cam.getPosition() - mouse3d + cam.getLookAtDir()))), cam.getLookAtDir());
	//ofSetColor(0, 0, 255, 255);
	//ofDrawLine(ofVec3f(cam.getPosition()+glm::vec3(0.0f, -3.0f, 0.0f)), ofVec3f((cam.getPosition() + lookAtVec) * 10000));
	//ofDrawLine(ofVec3f(cam.getPosition()+glm::vec3(0.0f, -3.0f, 0.0f)), ofVec3f((cam.getPosition() - mouse3d + cam.getLookAtDir()) * 10000));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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
