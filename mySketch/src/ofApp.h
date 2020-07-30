#pragma once

#include "ofMain.h"
#include "maximilian.h"

class ofApp : public ofBaseApp{

public:
	~ofApp();
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void ofApp::gotMessage(ofMessage msg);
	void ofApp::dragEvent(ofDragInfo dragInfo);

	void audioRequested(float * input, int bufferSize, int nChannels); /* output method */
	void audioReceived(float * input, int bufferSize, int nChannels); /* input method */

	float 	* lAudioOut; /* outputs */
	float   * rAudioOut;

	float * lAudioIn; /* inputs */
	float * rAudioIn;

	int		initialBufferSize; /* buffer size */
	int		sampleRate;


	/* stick you maximilian stuff below */

	double wave, sample, outputs[2];
	maxiMix mymix;
	maxiOsc sine1;
	maxiSample beats, beat;
};
