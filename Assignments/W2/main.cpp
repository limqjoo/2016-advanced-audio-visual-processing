
#include "maximilian.h"

maxiOsc mySine1, mySine2, mySine3, mySine4, mySine5;
maxiClock myClock; // This will allow us to generate a clock signal and do things at specific times
double freq1, freq2; // This is a variable that we will use to hold and set the current frequency of the oscillator

void setup() {

	myClock.setTicksPerBeat(1);//This sets the number of ticks per beat
	myClock.setTempo(120);// This sets the tempo in Beats Per Minute
	freq1 = 20; // Here we initialise the variable
	freq2 = 440; // Here we initialise the variable
}

void play(double *output) {

	myClock.ticker(); // This makes the clock object count at the current samplerate


					  //Code for W2_02
	if (myClock.tick) {

		freq1 += 10;
		freq2 -= 10;
		if (freq1 > 1000) {
			freq1 = 20;
		}
		if (freq2 < 0) {
			freq2 = 440;
		}

	}

	output[0] = 0.5 * mySine1.sinewave(mySine2.sinewave(mySine3.sinewave(0.1) * 30) * freq1) + 0.5 * mySine5.phasor(0.01, 2, freq2) * mySine4.sinewave(mySine5.phasor(0.01, 2, freq2) / 2);
	output[1] = output[0];

}

