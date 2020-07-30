#include "ofApp.h"
#include "maximilian.h"


ofApp::~ofApp() {
	beats.clear();
}

//--------------------------------------------------------------
void ofApp::setup() {
	/* some standard setup stuff*/

	ofEnableAlphaBlending();
	ofSetupScreen();
	ofBackground(0, 0, 0);

	/* This is stuff you always need.*/

	sampleRate = 44100; /* Sampling Rate */
	initialBufferSize = 512;	/* Buffer Size. you have to fill this buffer with sound*/
	lAudioOut = new float[initialBufferSize];/* outputs */
	rAudioOut = new float[initialBufferSize];
	lAudioIn = new float[initialBufferSize];/* inputs */
	rAudioIn = new float[initialBufferSize];


	/* This is a nice safe piece of code */
	memset(lAudioOut, 0, initialBufferSize * sizeof(float));
	memset(rAudioOut, 0, initialBufferSize * sizeof(float));

	memset(lAudioIn, 0, initialBufferSize * sizeof(float));
	memset(rAudioIn, 0, initialBufferSize * sizeof(float));

	/* Now you can put anything you would normally put in maximilian's 'setup' method in here. */


	beat.load("D:/limqjoo/godetia/Year3/AAVP/Goss-Waterfall.wav");
	beat.getLength();



	ofSoundStreamSetup(2, 0, this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	/* You can use any of the data from audio received and audiorequested to draw stuff here.
	Importantly, most people just use the input and output arrays defined above.
	Clever people don't do this. This bit of code shows that by default, each signal is going to flip
	between -1 and 1. You need to account for this somehow. Get the absolute value for example.

	*/

	ofSetColor(255, 255, 255, 255);
	ofRect(600, 300, sample * 150, sample * 150); /* audio sigs go between -1 and 1. See?*/
	ofCircle(200, 300, wave * 150);

}


void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {

	for (int i = 0; i < bufferSize; i++) {

		/* Stick your maximilian 'play()' code in here ! Declare your objects in testApp.h.

		For information on how maximilian works, take a look at the example code at

		http://www.maximilian.strangeloop.co.uk

		under 'Tutorials'.

		*/

		sample = beat.play(1, 0, beat.length);
		//sample = beat.play();
		//wave = sine1.sinebuf(440);/* mouse controls sinewave pitch. we get abs value to stop it dropping
								  //delow zero and killing the soundcard*/

		mymix.stereo((sample) / 2.0, outputs, 0.5);


		lAudioOut[i] = output[i*nChannels] = outputs[0]; /* You may end up with lots of outputs. add them here */
		rAudioOut[i] = output[i*nChannels + 1] = outputs[1];
	}
}


void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {


	/* You can just grab this input and stick it in a double, then use it above to create output*/

	for (int i = 0; i < bufferSize; i++) {

		/* you can also grab the data out of the arrays*/

		lAudioIn[i] = input[i * 2];
		rAudioIn[i] = input[i * 2 + 1];
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
