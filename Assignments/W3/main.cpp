//Using BPF equation from http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
//Example contributed by Rebecca Fiebrink

#include "maximilian.h"

float xs[3], ys[3];
float a0, a1, a2, b0, b1, b2;
float f0 = 400; //THE FREQUENCY
float Q = 1.0;

maxiOsc mySwitchableOsc, osc1, osc2, osc3, phasor1;
maxiFilter fil1, fil2;
double osc1out, osc2out, osc3out, filout, ampout, ADSRout;
int mySequence[11] = { 600, 400, 200, 250, 300, 200, 300, 400, 200, 450, 600 };

int currentCount1, currentCount2, lastCount;

maxiEnv ADSR;
maxiOsc timer;//this is the metronome


void setup() {//some inits
	ADSR.setAttack(1000);
	ADSR.setDecay(1);
	ADSR.setSustain(1);
	ADSR.setRelease(1000);
}

void play(double *output) {

	currentCount1 = (int)phasor1.phasor(1, 1, 11);
	currentCount2 = (int)timer.phasor(1);//this sets up a metronome that ticks every 2 seconds

	if (lastCount != currentCount2) {//if we have a new timer int this sample, play the sound
		ADSR.trigger = 1;

		cout << "tick\n";//the clock ticks

		lastCount = 0;//set lastCount to 0
	}

	ADSRout = ADSR.adsr(1.0, ADSR.trigger);

	//osc1out = osc1.sinewave(5) * 3;
	osc1out = osc1.square(5) * 3;
	//osc2out = osc2.sawn(mySequence[currentCount1] + osc1out);
	osc2out = osc2.sawn(fil2.lopass(mySequence[currentCount1] + osc1out, 0.005));
	osc3out = osc3.sinewave(0.5) * 50;

	filout = fil1.hires(osc2out, 200 + osc3out * 120, 20 + osc1out * 10);

	ampout = filout*0.25;

	double finalSound = ampout*ADSRout;//finally we add the ADSR as an amplitude modulator
	ADSR.trigger = 0;

	output[0] = finalSound;
	output[1] = output[0];
}