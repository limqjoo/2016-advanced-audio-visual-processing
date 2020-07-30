#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	i = 0;
	amp = 100;
	phase = 0;
	elements = 12;
	for (int i = 0; i < elements; i++) {
		points.push_back(ofVec2f(200*sin(2*i*PI/elements), 200 * cos(2*i*PI / elements)));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < elements; i++) {
		line.addVertex(points[i].x, points[i].y);
	}
	line.close();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(0);
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

	ofNoFill();
	ofSetColor(250);
	ofSetLineWidth(2);
	line.draw();
	

	ofFill();
	ofSetColor(150);
	for (int i = 0; i < elements; i++) {
		ofDrawEllipse(points[i].x, points[i].y, 10, 10);
	}
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
	if (selected != -1) {
		points[selected].set(x- ofGetWidth() / 2, y- ofGetHeight() / 2);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (int i = 1; i < elements; i++) {
		if (abs((x-ofGetWidth()/2) - points[i].x) < 10 && abs((y - ofGetHeight() / 2) - points[i].y) < 10) {
			selected = i;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	selected = -1;
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
