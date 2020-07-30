#pragma once

#include "ofMain.h"
#include "maximilian.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void audioOut(float * input, int bufferSize, int nChannels);

	float i, amp, phase;
	int elements;
	ofPolyline line;
	int selected = -1;

	vector <ofVec2f> points;

	ofSoundStream soundStream;

	int		sampleRate;

	vector <float> lAudio;
	vector <float> rAudio;

	maxiOsc sine1;
	double sample;
};
