#include "ofApp.h"

 //-------------------------------------------------------------
ofApp::~ofApp() {

}


//--------------------------------------------------------------
void ofApp::setup() {
	ofHideCursor();
	ofEnableAlphaBlending();
	ofSetupScreen();
	ofSetVerticalSync(true);

	width = ofGetWidth();
	height = ofGetHeight();

	//sound stuff
	sampleRate = 44100;
	bufferSize = 512;

	maxiSettings::setup(sampleRate, 2, bufferSize);

	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);
	audio.assign(bufferSize, 0.0);
	myFFT.setup(fftSize, 512, 256);

	//set-up input soundstream
	soundStream.listDevices();
	soundStream.setInput(this); //this chooses default input. you can change this if needed.
	soundStream.setup(this, 0, 2, sampleRate, bufferSize, 4);

	//image stuff
	ofBackground(255);
	myTexture.allocate(width, height, GL_RGB);

	myGrabber.listDevices();
	myGrabber.initGrabber(width, height);

	pixelout.allocate(width, height, 3);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (mode == -1) { //intro
		int i = 0;
		while (i < 50) {
			std::cout << "." << endl;
			i++;
		}
		std::cout << "welcome to the noise playground\ntry not to let the darkness consume you\npress ENTER to start" << endl;
		std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); //wait for user to press enter
		std::cout << "please keep silent while calibrating\npress ENTER to start calibration";
		std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		//calibrate silence based on RMS
		int loops = 0;
		double silence = 0;
		while (loops < 10000) {
			if (rms < min) {
				min = rms;
			}
			if (rms > max) {
				max = rms;
			}
			silence += (min + max) / 2;
			loops++;
			std::cout << '.';
		}
		silence /= loops;
		std::cout << "done calibrating" << std::endl;
		std::cout << "press ENTER to start video";
		std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		mode++;
	}

	myGrabber.update();

	//only try and process video when we have a new frame.
	if (myGrabber.isFrameNew()) {

		pixels = myGrabber.getPixels();
		pixels.pasteInto(pixelout, 0, 0);

		//darken/lighten screen
		if (rms < max + 0.001) { //darken output
			darkness++;
			darkness = std::min(darkness, 255); //don't let it get darker than 0
		}
		else { //lighten output
			darkness -= 5;
			darkness = std::max(darkness, 0); //don't let it get brighter than 0
			if (rms > silence + 0.35) { //change mode if too loud
				changeMode();
			}
		}

		if (darkness > 0) {
			for (int i = 0; i < pixelout.size(); i++) {
				ofColor c = pixels.getColor(i);
				int brightness = c.getBrightness();
				int nBrightness = std::max(brightness - darkness, 0); //in case of negative value for (brightness - darkness), choose 0
				c.setBrightness(nBrightness);
				pixelout.setColor(i, c);
			}
		}

		if (mode == 0) { //1-bit channel
			for (int i = 0; i < pixelout.size(); i++) {

				int threshold = ofMap(rms, silence, silence + 0.33, 20, 220); //change threshold according to rms.
				ofColor c = pixelout.getColor(i);
				ofColor newC = ofColor(0, 0, 0);
				//set new rgb values.
				if (c.r > threshold) {
					newC.r = 255;
				}
				if (c.g > threshold) {
					newC.g = 255;
				}
				if (c.b > threshold) {
					newC.b = 255;
				}

				pixelout.setColor(i, newC); //set new colour
			}
		}
		else if (mode == 1) { //translate pixels based on history of rms values
			if (past_rms.size() >= height / barSize) {
				for (int y = 0; y < height; y += barSize) { //every [barSize] rows of pixels
					//map average to x-distance of pixels translation
					int translateX = ceil(ofMap(past_rms[y / barSize], min, silence + 0.35, 0, width));

					for (int j = 0; j < barSize; j++) { //every row of pixels
						ofPixels row = pixelout.getLine(y + j).asPixels(); //get pixels
						for (int k = 0; k < row.size(); k++) { //every pixel
							pixelout[row.size()*(y + j) + k] = row[(k + translateX * 3) % row.size()]; //shift pixels left/right by translateX value
						}
					}

				}
			}
		}
		else if (mode == 2) { //distort video output based on fft
			if (recordingEnabled) {
				for (int y = 0; y < height; y++) { //every row of pixels
					ofPixels row = pixelout.getLine(y).asPixels(); //get pixels in row
					float translateX = 0;
					if (recordingEnabled) {
						translateX = ofMap(abs(myFFT.magnitudes[(int)ofMap(y, 0, height, 0, fftSize - 1)]), 0, 0.03, 0, width);
					}
					for (int i = 0; i < row.size(); i++) { //every pixel
						ofColor c = row.getColor(i);
						c.setHueAngle((int)(ofMap(myFFT.magnitudes[(int)ofMap(y, 0, height, 0, fftSize - 1)], 0, 0.05, 0, 360) + i) % 360); //change hue of pixel
						row.setColor(i, c);
						if (translateX >= 0) {
							pixelout[row.size()*y + i] = row[(i + (int)floor(translateX * 3)) % row.size()]; //shift pixels right by translateX value
						}
						else {
							pixelout[row.size()*y + i] = row[row.size() - abs(i + (int)floor(translateX * 3)) % row.size()]; //shift pixels left by translateX value
						}
					}
				}
			}
		}
		myTexture.loadData(pixelout, GL_RGB);
	}

	//store the last rms value
	past_rms.push_back(rms);
	if (past_rms.size() > height / barSize) {
		past_rms.erase(past_rms.begin()); //remove earliest value
	}
}


//--------------------------------------------------------------
void ofApp::draw() {

	myTexture.draw(0, 0, width, height); //display image output

	//UI
	ofPushStyle();
	if (showSoundLevel) { //show something like a cheatkey
		ofSetColor(0, 125);
		ofDrawRectangle(0, 0, 120, 20);
		ofSetColor(255);
		if (rms < max + 0.001) {
			ofDrawBitmapString("silent", 20, 14);
		}
		else if (rms > silence + 0.30) {
			ofDrawBitmapString("getting too loud", 10, 14);
		}
		else {
			ofDrawBitmapString("alright now", 15, 14);
		}
	}
	
	if (showHelp) { //show some hints/what this is about
		ofSetColor(0, 125);
		ofDrawRectangle(width / 2 - 200, 100, 420, 100);
		ofSetColor(255);
		ofDrawBitmapString("There are three modes of play.\nSometimes it gets darker when it is\nsilent, but then brighter when there is sound.\nMake louder sounds to change modes.\nIf not, press the spacebar.\nHave fun making noise. Or not.", width / 2 - 190, 120);
	}
	ofSetColor(0, 125);
	ofDrawRectangle(0, height - 35, width, 35);
	ofSetColor(255);
	ofDrawBitmapString("Press to toggle:\n'h'-show/hide some help | 'o'-show/hide sound level | 'p'-on/off recording", 10, height - 20);
	
	if (recordingEnabled) { //show if buffer is being updated at the moment
		ofDrawBitmapString("Recording mic...", width - 135, height - 20);
	}
	else {
		ofDrawBitmapString("Not recording.", width - 135, height - 20);
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
	
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels) {
	if (recordingEnabled) {
		int numCounted = 0;

		for (int i = 0; i < bufferSize; i++) {
			float leftSample = input[i * nChannels] * 0.5;
			float rightSample = input[i * nChannels + 1] * 0.5;

			lAudio[i] = leftSample;
			rAudio[i] = rightSample;
			audio[i] = (leftSample + rightSample) / 2;

			rms += leftSample * leftSample;
			rms += rightSample * rightSample;

			numCounted += 2;

			if (myFFT.process(audio[i])) {
				myFFT.magsToDB();
			}
		}
		rms /= numCounted;
		rms = sqrt(rms);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'p') { //enable recording mode
		recordingEnabled = !recordingEnabled;
	}
	else if (key == ' ') { //manually change modes
		changeMode();
	}
	else if (key == 'o') { //show/hide real-time rms
		showSoundLevel = !showSoundLevel;
	}
	else if (key == 'h') {
		showHelp = !showHelp;
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
void ofApp::windowResized(int w, int h) {

}



//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::changeMode() {
	mode++;
	mode %= 3;
}