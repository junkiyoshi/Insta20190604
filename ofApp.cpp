#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int n = 300;
	vector<glm::vec3> locations(n);
	for (int i = 0; i < n; i++) {

		auto R = 300;
		auto r = ofRandom(30, 80);
		auto u = ofRandom(360) + ofGetFrameNum() * ofRandom(0.5, 1.0) * (ofRandom(1) < 0.5 ? 1 : -1);
		auto v = ofRandom(360) + ofGetFrameNum() * ofRandom(0.5, 1.0) * (ofRandom(1) < 0.5 ? 1 : -1);

		locations[i] = this->make_point(R, r, u, v);
	}

	ofFill();
	ofSetColor(255);
	for (auto& location : locations) {

		ofDrawSphere(location, 3);
		for (auto& other : locations) {

			if (location == other) { continue; }

			auto distance = glm::distance(location, other);
			if (distance < 40) {

				ofDrawLine(location, other);
			}
		}
	}

	ofNoFill();
	ofSetColor(255, 64);
	auto R = 300;
	auto r = 100;
	for (auto v = 0; v < 360; v += 10) {

		for (auto u = 0; u < 360; u += 20) {

			ofBeginShape();
			ofVertex(this->make_point(R, r, u - 10, v - 5));
			ofVertex(this->make_point(R, r, u + 10, v - 5));
			ofVertex(this->make_point(R, r, u + 10, v + 5));
			ofVertex(this->make_point(R, r, u - 10, v + 5));
			ofEndShape(true);
		}
	}


	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}