/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */



#include "ofApp.h"


//-------------------------------------------------------------
ofApp::~ofApp() {
    
//    delete pixelout;
//    delete lastPixels;
//    delete blockpix;
	

}


//--------------------------------------------------------------
void ofApp::setup(){
	/* some standard setup stuff*/
	ofHideCursor();
	ofEnableAlphaBlending();
	ofSetupScreen();
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    
	
	/* This is stuff you always need.*/
	
	sampleRate 			= 44100; /* Sampling Rate */
	initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
	
	fade=200;
    zoom=10;

	/* Now you can put anything you would normally put in maximilian's 'setup' method in here. */
    
//    beat.load(ofToDataPath("beat2.wav"));
//    myMovie.loadMovie("wotEva");
	
	myTexture.allocate(320,240,GL_RGB);
	
    myGrabber.listDevices();
            
	myGrabber.initGrabber(320,240);

	pixelout = new unsigned char [320*240];
	lastPixels = new unsigned char [320*240*3];
    
//    blockpix = new unsigned char [ofGetWidth(),ofGetHeight()];
	
	ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){

    
	
//	myMovie.setFrame(300*(fabs(sample)));
	//this updates the movie...
//	myMovie.updateMovie();
	
	myGrabber.update();

	//only try and process video when we have a new frame.
	if (myGrabber.isFrameNew()) {

		
		pixels = myGrabber.getPixels();

	
	for (int i = 0; i < 320*240*3; i+=3){
        
//      pixelout[i]=pixels[i]* fabs(sample) * 10;//change brightness based on audio
//		pixelout[i+2]=pixels[(320*240*3)-(i+1)];//flip the blue  
//		pixelout[i+1]=pixels[(320*240*3)-(i+2)];//flip the green 
//		pixelout[i+0]=pixels[(320*240*3)-(i+3)];//flip the red 
//
		}

	for (int i = 0; i < 320; i++){
		for (int j = 0; j < 240; j++) {

			
//Frame Difference on the red channel			
//			pixelout[(j*320+i)]=abs((lastPixels[(j*320+i)*3])-(pixels[(j*320+i)*3]));
//			
//			lastPixels[(j*320+i)*3]=pixels[(j*320+i)*3];
			
//  Thresholding the red channel
			if (pixels[(j*320+i)*3]>mouseX/4){
				pixelout[(j*320+i)]=255;//red
			} else {
				pixelout[(j*320+i)]=0;
			}

//Straight copy of all the pixels
//			pixelout[(j*320+i)*3+1]=pixels[(j*320+i)*3+0];//red
//			pixelout[(j*320+i)*3+1]=pixels[(j*320+i)*3+1];//green
//			pixelout[(j*320+i)*3+2]=pixels[(j*320+i)*3+2];//blue
//		}
//	}
        }
    }
//      myTexture.loadData(pixelout,320,240,GL_RGB);
		
		myTexture.loadData(pixelout,320,240,GL_LUMINANCE);

//        blockpix = block.getPixels();
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	/* You can use any of the data from audio received and audiorequested to draw stuff here.
	 Importantly, most people just use the input and output arrays defined above.
	 Clever people don't do this. This bit of code shows that by default, each signal is going to flip
	 between -1 and 1. You need to account for this somehow. Get the absolute value for example.
	 */
	
    ofSetColor(255, 255, 255,255);
    
//    block.setAnchorPercent(0.5, 0.5);
        
//    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    
//    ofRotate(10, 0, 0, 1);
    
//    block.draw(zoom,zoom,ofGetWidth()-(zoom*2),ofGetHeight()-(zoom*2));
    
//	ofSetColor(255, 255, 255,fade);

	myTexture.draw(0, 0,ofGetWidth(),ofGetHeight());
        
//    block.grabScreen(0, 0, ofGetWidth(),ofGetHeight());

    
}

//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
	
	
	for (int i = 0; i < bufferSize; i++){
		
		/* Stick your maximilian 'play()' code in here ! Declare your objects in ofApp.h.
		 
		 For information on how maximilian works, take a look at the example code at
		 
		 http://www.maximilian.strangeloop.co.uk
		 
		 under 'Tutorials'.
		 
		 */
			
//		sample=beat.play(0.5, 0, beat.length);
//		sample=beats.bufferPlay(*blockpix,40,0,ofGetWidth()*ofGetHeight()*0.5);
//        sample=(sample-0.5)*2;
//		filtered=filter1.lopass(sample,0.25);
		
//		mymix.stereo(filtered, outputs, 0.5);
//      mymix.stereo(sample, outputs, 0.5);

		
		output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
		output[i*nChannels + 1] = outputs[1];
	}
	
}

//--------------------------------------------------------------
void ofApp::audioReceived 	(float * input, int bufferSize, int nChannels){	
	
	
	/* You can just grab this input and stick it in a double, then use it above to create output*/
	
	for (int i = 0; i < bufferSize; i++){
		
		/* you can also grab the data out of the arrays*/
		
		
	}
	
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == 's') {
        
        myGrabber.videoSettings();
    }
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
//	fade=x-(ofGetWidth()/2);
//    zoom=y-(ofGetHeight()/2);
	
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
void ofApp::windowResized(int w, int h){
	
}



//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}