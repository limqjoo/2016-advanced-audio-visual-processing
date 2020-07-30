#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);

	int bufferSize = 512;
	sampleRate = 44100;
	maxiSettings::setup(sampleRate, 2, bufferSize);
	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);

	i = 0;
	amp = 100;
	phase = 0;
	elements = 12;
	for (int i = 0; i < elements; i++) {
		points.push_back(ofVec2f(200 * sin(2 * i*PI / elements), 200 * cos(2 * i*PI / elements)));
	}
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update() {
	for (int i = 0; i < elements; i++) {
		line.addVertex(points[i].x, points[i].y);
	}
	line.close();

	phase = ofGetFrameNum()*PI / 180;

	if (ofGetFrameNum()%(360/elements) == 0) {
		//amp = 
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	ofNoFill();
	ofSetColor(250);
	ofSetLineWidth(2);
	line.draw();
	
	ofDrawLine(0, 0, 400*sin(phase), 400 * cos(phase));

	ofFill();
	ofSetColor(150);
	for (int i = 0; i < elements; i++) {
		ofDrawEllipse(points[i].x, points[i].y, 10, 10);
	}
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		//sample = map(phase);
		sample = 0;

		lAudio[i] = output[i*nChannels] = sample;
		rAudio[i] = output[i*nChannels + 1] = sample;

	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (selected != -1) {
		//get off-set
		float changeX = (x - ofGetWidth() / 2) - points[selected].x; //change in x
		float changeY = (y - ofGetHeight() / 2) - points[selected].y; //change in y
		points[selected].set(points[selected].x + changeX, points[selected].y + changeY);
		//points[(selected+elements-1)%elements].set(points[(selected + elements - 1) % elements].x + changeX*0.2, points[selected-1].y + changeY*0.2);
		//points[(selected + 1) % elements].set(points[(selected + 1) % elements].x + changeX*0.2, points[selected - 1].y + changeY*0.2);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	for (int i = 1; i < elements; i++) {
		if (abs((x - ofGetWidth() / 2) - points[i].x) < 10 && abs((y - ofGetHeight() / 2) - points[i].y) < 10) {
			selected = i;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	selected = -1;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
