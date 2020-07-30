#include "ofApp.h"
#include "maximilian.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	// 2 output channels,
	// 0 input channels
	// 22050 samples per second
	// 512 samples per buffer
	// 4 num buffers (latency)

	int bufferSize = 512;
	sampleRate = 44100;

	maxiSettings::setup(sampleRate, 2, bufferSize);

	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);

	//soundStream.listDevices();

	//if you want to set the device id to be different than the default
	//soundStream.setDeviceID(1); 	//note some devices are input only and some are output only 
	
	gaya.load(ofToDataPath("D:/limqjoo/godetia/Year3/AAVP/gitlab/Assignments/W4/gayageum.wav"));
	taiko.load(ofToDataPath("D:/limqjoo/godetia/Year3/AAVP/gitlab/Assignments/W4/taiko1.wav"));
	vibra.load(ofToDataPath("D:/limqjoo/godetia/Year3/AAVP/gitlab/Assignments/W4/vibraphone.wav"));

	soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);

	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(225);
	ofDrawBitmapString("AUDIO OUTPUT EXAMPLE", 32, 32);
	ofDrawBitmapString("press 's' to unpause the audio\npress 'e' to pause the audio", 31, 92);

	ofNoFill();

	// draw the left channel:
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(32, 150, 0);

	ofSetColor(225);
	ofDrawBitmapString("Left Channel", 4, 18);

	ofSetLineWidth(1);
	ofRect(0, 0, 900, 200);

	ofSetColor(245, 58, 135);
	ofSetLineWidth(3);

	ofBeginShape();
	for (int i = 0; i < lAudio.size(); i++) {
		float x = ofMap(i, 0, lAudio.size(), 0, 900, true);
		ofVertex(x, 100 - lAudio[i] * 180.0f);
	}
	ofEndShape(false);

	ofPopMatrix();
	ofPopStyle();

	// draw the right channel:
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(32, 350, 0);

	ofSetColor(225);
	ofDrawBitmapString("Right Channel", 4, 18);

	ofSetLineWidth(1);
	ofRect(0, 0, 900, 200);

	ofSetColor(135, 58, 245);
	ofSetLineWidth(3);

	ofBeginShape();
	for (int i = 0; i < rAudio.size(); i++) {
		float x = ofMap(i, 0, rAudio.size(), 0, 900, true);
		ofVertex(x, 100 - rAudio[i] * 180.0f);
	}
	ofEndShape(false);

	ofPopMatrix();
	ofPopStyle();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	std::cout << key << std::endl;
	if (key == 49) {
		playGaya = !playGaya;
	}
	if (key == 50) {
		playTaiko = !playTaiko;
	}
	if (key == 51) {
		playVibra = !playVibra;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	mouseX = x;
	mouseY = y;
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

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	for (int i = 0; i < bufferSize; i++) {
		double wave = 0;
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
		sample = test1.sinewave(ofMap(mouseY, 0, ofGetHeight(), 20, 1400)) + gaya.playOnce() + taiko.playOnce() + vibra.playOnce();

		lAudio[i] = output[i*nChannels] = sample;
		rAudio[i] = output[i*nChannels + 1] = sample;

	}

}

void ofApp::audioIn(float * input, int bufferSize, int nChannels) {

	for (int i = 0; i < bufferSize; i++) {
		/* you can also grab the data out of the arrays*/

	}

}