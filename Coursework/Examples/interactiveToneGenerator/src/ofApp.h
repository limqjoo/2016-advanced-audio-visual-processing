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

		void audioOut(float * input, int bufferSize, int nChannels); /* output method */
		void audioIn(float * input, int bufferSize, int nChannels); /* input method */

		int		bufferSize; /* buffer size */
		int		sampleRate;

		ofSoundStream soundStream;

		double wave1, wave2, wave3;
		maxiOsc mySine1, mySine2, mySine3, mySine4;
		double freq1, freq2, freq3; // This is a variable that we will use to hold and set the current frequency of the oscillator
		
};
