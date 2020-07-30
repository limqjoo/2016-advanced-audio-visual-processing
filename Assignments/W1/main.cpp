//This examples shows another fundamental building block of digital audio - adding two sine waves together. When you add waves together they create a new wave whose amplitude at any time is computed by adding the current amplitudes of each wave together. So, if one wave has an amplitude of 1, and the other has an amplitude of 1, the new wave will be equal to 2 at that point in time. Whereas, later, if one wave has an amplitude of -1, and the other has an amplitude of 1, the new wave - the one you hear - will equal 0. This can create some interesting effects, including 'beating', when the waves interact to create a single wave that fades up and down based on the frequencies of the two interacting waves. The frequency of the 'beating' i.e. the fading in and out, is equal to the difference in frequency between the two waves.

#include "maximilian.h"

maxiOsc sin1, sin2, sin3, sin4; //4 oscillators with names.

void setup() {
}

void play(double *output) {
	//output[0] is the left output. output[1] is the right output
	output[0] = sin1.sinewave(0.5)*sin2.sinewave((220 * sin1.sinewave(0.5)) + 100); //using amplitude modulation for a FM synthesis
	output[1] = 0.5 * sin3.phasor(0.01, 0, 440) * sin4.sinewave(sin3.phasor(0.01, 0, 440)) ; //using phasor for amplitude modulation
}

