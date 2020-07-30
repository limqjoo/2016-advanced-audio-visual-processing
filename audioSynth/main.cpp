
#include "maximilian.h"

maxiOsc mySine1;
maxiClock myClock; // This will allow us to generate a clock signal and do things at specific times
double freq1, freq2; // This is a variable that we will use to hold and set the current frequency of the oscillator
int melody[] = { -9, -6, -2, -1, -1, -2, -6, -7, -1, 1, -2, -2 }; //a melody to be played.
int note = 0;

double frequency(int step) { //step - semitones away from note A4
	double freq = 440 * pow(1.059463, step); //generates a frequency for a note
	return freq;
}

void setup() {
	myClock.setTicksPerBeat(1);//This sets the number of ticks per beat
	myClock.setTempo(120);// This sets the tempo in Beats Per Minute
}

void play(double *output) {

	myClock.ticker(); // This makes the clock object count at the current samplerate

	if (myClock.tick) {
		freq1 = frequency(melody[note]);
		note++;
		note%=melody.length;
	}

	output[0] = mySine1.sinewave(freq1);
	output[1] = output[0];

}

