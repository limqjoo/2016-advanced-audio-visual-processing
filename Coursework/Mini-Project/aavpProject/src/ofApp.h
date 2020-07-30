#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "maximilian.h"
#include "maxiFFT.h"

class ofApp : public ofBaseApp {

public:
	~ofApp();/* destructor is very useful */
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
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void audioOut(float * input, int bufferSize, int nChannels); /* output method */
	void audioIn(float * input, int bufferSize, int nChannels); /* input method */

	void changeMode();

	int height, width;
	int mode = -1;
	bool recordingEnabled = true;
	bool showSoundLevel = false;
	bool showHelp = false;

	//sound stuff
	int		bufferSize; /* buffer size */
	int		sampleRate;

	ofSoundStream soundStream;
	vector <float> lAudio;
	vector <float> rAudio;
	vector <float> audio;

	double rms = 0.0;
	vector <double> past_rms;
	double silence;
	double min = 1, max = 0;
	int barSize = 5; //number of rows of pixels treated as a single bar

	maxiFFT myFFT;
	int fftSize = 1024;
	float binFreq = 44100 / fftSize;

	//image stuff
	ofVideoGrabber	myGrabber;
	ofPixels pixels;
	ofPixels pixelout;
	ofTexture myTexture;

	int darkness = 0;
};
