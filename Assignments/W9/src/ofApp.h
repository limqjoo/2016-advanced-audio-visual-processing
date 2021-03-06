#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{

	public:
		~ofApp();/* destructor is very useful */
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
		void audioReceived 	(float * input, int bufferSize, int nChannels); /* input method */

	
		int		initialBufferSize; /* buffer size */
		int		sampleRate;
		
		ofVideoPlayer 		myMovie;
		
        ofVideoGrabber		myGrabber;
	
		unsigned char * pixels;
	
		unsigned char * pixelout;

		unsigned char * lastPixels;
    
        unsigned char *blockpix;
		
		ofTexture myTexture,other;
    
        ofImage block;
    
        int zoom;
        int fade;
 
	
		/* stick you maximilian stuff below */
	
		double filtered,sample,outputs[2];
		maxiFilter filter1;
		ofxMaxiMix mymix;
		ofxMaxiOsc sine1;
		ofxMaxiSample beats,beat;
    	
		
};
