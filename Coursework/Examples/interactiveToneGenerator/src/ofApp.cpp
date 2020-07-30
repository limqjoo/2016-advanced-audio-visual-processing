#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	sampleRate = 44100;
	bufferSize = 512;

	maxiSettings::setup(sampleRate, 2, bufferSize);

	soundStream.listDevices();
	soundStream.setOutput(this);
	soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		freq1 = 440 * pow(1.059463, floor(ofMap(ofGetMouseX(), 0, ofGetWidth(), -14, 15))); //map mouse x values to 30 semitones
		wave1 = 0.5*mySine1.sinewave(freq1); //play a simple sinewave

		if (ofGetPreviousMouseX() != ofGetMouseX() && ofGetPreviousMouseY() != ofGetMouseY()) { //mouse moved
			freq2 = ofMap(ofGetMouseX()*ofGetMouseY(), 0, ofGetWidth()*ofGetHeight(), 4, 16);
			wave2 = mySine2.sinewave(freq2); //modulate amplitude of wave
		}
		else {
			wave2 = 1;
		}
	

		if (ofGetMousePressed()) { //if mouse pressed
			freq3 = ofMap(ofGetMouseY(), 0, ofGetHeight(), 20, 500);
			wave3 = 0.5*mySine3.sinewave(mySine4.phasor(0.01, 2, freq3)); //add in a phasor
		}
		else {
			wave3 = 0;
		}

		output[i*nChannels] = wave1*wave2 + wave3;
		output[i*nChannels + 1] = output[i*nChannels];
	}
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels) {
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

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
