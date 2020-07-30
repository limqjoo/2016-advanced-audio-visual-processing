#include "ofApp.h"
#define PI 3.14159265
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetBackgroundAuto(false);

	int bufferSize = 512;
	sampleRate = 44100;

	maxiSettings::setup(sampleRate, 2, bufferSize);

	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);

	//replace path names:
	gaya.load(ofToDataPath("...gayageum.wav"));
	taiko.load(ofToDataPath("...taiko1.wav"));
	vibra.load(ofToDataPath("...vibraphone.wav"));

	soundStream.setOutput(this);
	soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);

	myFFT.setup(fftSize, fftSize, 256);
	lines.assign(fftSize, ofPolyline());
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(0, 10);
	ofFill();
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight()); //fade effect

	//draw 'flower' based on amplitude of fft bins
	ofNoFill();
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2 + (int)(x += lAudio[0] * 10) % ofGetWidth(), ofGetHeight() / 2 + (int)(y += lAudio[1] * 10) % ofGetHeight());
	ofRotate(lAudio[2]);

	ofSetLineWidth(1);
	for (int i = 0; i < fftSize; i++) { //every bin
		ofSetColor(ofMap(i, 0, fftSize - 1, 0, 255), ofMap(i, 0, fftSize - 1, 30, 200), ofMap(i, 0, fftSize-1, 100, 250));
		lines[i].clear();
		for (int a = 0; a < 360; a += 2) { //180 vertices for circle
			float r = 50 * myFFT.magnitudes[i] * sin(ofMap(binFreq*i,0, binFreq*fftSize, 0, 2*PI)+(a*PI/18));
			float x = r*sin(a * PI/180);
			float y = r*cos(a * PI/180);
			lines[i].addVertex(ofVec2f(x, y));
		}
		lines[i].close();
		lines[i].draw();
	}

	ofPopMatrix();
	ofPopStyle();

	ofSetColor(225);
	ofDrawBitmapString("Press '1', '2', or '3' to trigger sounds.", 20, 25);
}

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		if (playGaya) {
			gaya.trigger();
			playGaya = false;
		}
		if (playTaiko) {
			taiko.trigger();
			playTaiko = false;
		}
		if (playVibra) {
			vibra.trigger();
			playVibra = false;
		}

		sample = gaya.playOnce() + taiko.playOnce() + vibra.playOnce();

		if (myFFT.process(sample)) {
			myFFT.magsToDB();
		}

		lAudio[i] = output[i*nChannels] = sample;
		rAudio[i] = output[i*nChannels + 1] = sample;
	}
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels) {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//std::cout << key << std::endl;
	if (key == '1') {
		playGaya = !playGaya;
	}
	if (key == '2') {
		playTaiko = !playTaiko;
	}
	if (key == '3') {
		playVibra = !playVibra;
	}
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