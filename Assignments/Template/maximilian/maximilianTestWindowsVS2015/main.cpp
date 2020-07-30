#include "maximilian.h"

maxiSample taiko, gaya, flute; //it actually isnt a flute (it was)... i was too lazy to change all the names to match...

maxiOsc timer;

maxiEnv envelope;

maxiOsc mySine, myOtherSine, myLastSine, myPhasor;

int currentCount, lastCount, playHead, hit[16] = { 1,0,0,1,0,0,1,0,1,0,0,0,0,0,1,1 }; //This is the sequence for the taiko
int gaya1hit[16] = { 0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,1 };//This is the sequence for the gayageum1
int gaya2hit[16] = { 1,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0 };//This is the sequence for the gayageum2
int fluthit[16] = { 0,0,1,1,0,0,1,1 };
int fluteI = 0;

double fluteSpeeds[4] = { 1.05, 1.4, 1.8, 1.4 };

int taikotrigger = 0, gaya1trigger = 0, gaya2trigger = 0, flutetrigger = 0;
double numSamples = 4;
double taikospeed;
double gaya1speed;
double gaya2speed;
double flutespeed;

double sampleOut;

void setup() {//some inits

	taiko.load("D:/limqjoo/godetia/Year3/AAVP/gitlab/Assignments/W4/taiko1.wav");//sample from: https://www.freesound.org/people/whatsanickname4u/sounds/95624/
	gaya.load("D:/limqjoo/godetia/Year3/AAVP/gitlab/Assignments/W4/gayageum.wav");//sample from: https://www.freesound.org/people/spt3125/sounds/24551/
	flute.load("D:/limqjoo/godetia/Year3/AAVP/gitlab/Assignments/W4/vibraphone.wav");//sample from: https://www.freesound.org/people/atonia/sounds/116382/


	printf("Summary:\n%s", taiko.getSummary());
}

void play(double *output) {//this is where the magic happens. Very slow magic.

	currentCount = (int)timer.phasor(4);//this sets up a metronome that ticks 4 times a second


	if (lastCount != currentCount) {//if we have a new timer int this sample, play the sound

		taikotrigger = hit[playHead % 16];//get the value out of the array for the taiko

		gaya1trigger = gaya1hit[playHead % 16];//same for the gaya1 and...

		gaya2trigger = gaya2hit[playHead % 16];

		flutetrigger = fluthit[playHead % 8];

		//changing the pitch of samples by altering playback speed
		if (playHead % 2 == 0) {
			taikospeed = 0.5;
		}
		else {
			taikospeed = 1;
		}
		gaya1speed = (double)2 * (0.5 / ((playHead % 4) + 1) + 0.5);
		gaya2speed = (double)0.5 / (((playHead + 1) % 4) + 1) + 0.5;

		playHead++;//iterate the playhead
		lastCount = 0;//reset the metrotest
	}

	if (taikotrigger == 1) {//if the sequence has a 1 in it
		taiko.trigger();//reset the playback position of the sample to 0 (the beginning)
	}

	if (gaya1trigger == 1 && playHead >= 16 * 2) { //starts after 32 ticks
		gaya.trigger();//likewise for the gaya
	}

	if (flutetrigger == 1 && playHead >= 16 * 4) { //starts after 64 ticks
		//setting the pitch/speed here because of fluteI increment
		flutespeed = fluteSpeeds[fluteI % 4];
		fluteI++;
		flute.trigger();
	}

	sampleOut = taiko.playOnce(taikospeed) + gaya.playOnce(gaya1speed) + flute.playOnce(flutespeed);//just play the file. No looping.

	//
	if (gaya2trigger == 1 && playHead >= 16 * 3) { //starts after 48 ticks
		sampleOut += mySine.sinewave(myOtherSine.sinewave(4))*gaya.playOnce(gaya2speed);
	}

	sampleOut *= ((double)(1 / numSamples));

	output[0] = sampleOut;//left channel
	output[1] = sampleOut;//right channel

	taikotrigger = 0;//set trigger to 0 at the end of each sample to guarantee retriggering.
	gaya1trigger = 0;
	gaya2trigger = 0;
	flutetrigger = 0;
}