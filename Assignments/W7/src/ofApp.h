#pragma once

#include "ofMain.h"
#include "maximilian.h"

class ofApp : public ofBaseApp{
public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void audioRequested(float * input, int bufferSize, int nChannels); /* output method */
		void audioReceived(float * input, int bufferSize, int nChannels); /* input method */

		float 	* lAudioOut; /* outputs */
		float   * rAudioOut;

		float * lAudioIn; /* inputs */
		float * rAudioIn;

		ofSoundStream soundStream;

		int		initialBufferSize; /* buffer size */
		int		sampleRate;

		maxiSample song;
		double wave, sample, outputs[2];
		maxiMix mymix;
		maxiOsc sine1;
};
