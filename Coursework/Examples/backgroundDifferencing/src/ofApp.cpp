#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofEnableAlphaBlending();
	ofSetupScreen();
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);

	width = ofGetWidth();
	height = ofGetHeight();

	myTexture.allocate(width, height, GL_RGB);

	myGrabber.listDevices();

	myGrabber.initGrabber(width, height);

	pixelout.allocate(width, height, 3);

	//lastPixels.allocate(width, height, 3);

	myfont.loadFont("font1.ttf", 14);
}

//--------------------------------------------------------------
void ofApp::update() {
	myGrabber.update();

	if (myGrabber.isFrameNew()) {
		pixels = myGrabber.getPixels();
		pixels.pasteInto(pixelout, 0, 0);

		//process video only when there is a reference image
		if (refPicTaken) {
			int threshold = ofMap(mouseY, 0, ofGetHeight(), 0, 255);
			for (int i = 0; i < pixelout.size(); i++) {
				//compare pixel values
				if (abs(pixels.getColor(i).r - refImg.getColor(i).r) < threshold &&
					abs(pixels.getColor(i).g - refImg.getColor(i).g) < threshold &&
					abs(pixels.getColor(i).b - refImg.getColor(i).b) < threshold) {
					pixelout.setColor(i, ofColor(255)); //set output as white if colour is similar
				}
				else {
					pixelout.setColor(i, ofColor(0)); // set output as black if colour is not similar
				}
			}
		}
	}

	myTexture.loadData(pixelout, GL_RGB);
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(255);

	myTexture.draw(0, 0, width, height);

	ofSetColor(5, 255, 255);
	myfont.drawString("Press spacebar to start.\nPress again to retake reference image.", 10, height-30);
	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		refImg = myGrabber.getPixels();
		refPicTaken = true;
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
