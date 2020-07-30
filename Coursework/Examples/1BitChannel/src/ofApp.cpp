#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
}

//--------------------------------------------------------------
void ofApp::update(){
	myGrabber.update();

	//only try and process video when we have a new frame.
	if (myGrabber.isFrameNew()) {

		pixels = myGrabber.getPixels();
		pixels.pasteInto(pixelout, 0, 0);

		for (int i = 0; i < pixelout.size(); i++) {

			//Frame Difference on the red channel			
			//			pixelout[(j*320+i)]=abs((lastPixels[(j*320+i)*3])-(pixels[(j*320+i)*3]));
			//			
			//			lastPixels[(j*320+i)*3]=pixels[(j*320+i)*3];



			//  Thresholding the red channel

			int threshold = ofMap(mouseY, 0, ofGetHeight(), 0, 255);
			ofColor c = pixels.getColor(i);
			ofColor newC = ofColor(0, 0, 0);
			if (c.r > threshold) {
				newC.r = 255;
			}
			if (c.g > threshold) {
				newC.g = 255;
			}
			if (c.b > threshold) {
				newC.b = 255;
			}

			pixelout.setColor(i, newC);
		}
	}

	myTexture.loadData(pixelout, GL_RGB);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255);

	myTexture.draw(0, 0, width, height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
