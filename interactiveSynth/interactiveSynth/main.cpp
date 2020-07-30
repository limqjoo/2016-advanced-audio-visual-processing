// interactiveSynth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "maximilian.h"

using namespace std;

//sound stuff
maxiOsc mySine1, mySine2, mySine3, mySine4, mySine5;
maxiClock myClock; // This will allow us to generate a clock signal and do things at specific times
double freq, freq1, freq2; // This is a variable that we will use to hold and set the current frequency of the oscillator
vector <int> sequence;

//ui stuff
//string lastSequence = "";
bool playMelody = false;
int note = 0;
bool running = true;

// function declaration
bool processInput(string input);
void createMelody(string melody);

void setup() {
	myClock.setTicksPerBeat(1);//This sets the number of ticks per beat
	myClock.setTempo(80);// This sets the tempo in Beats Per Minute
	//freq1 = 20; // Here we initialise the variable
	//freq2 = 440; // Here we initialise the variable
}

void play(double *output) {

	myClock.ticker(); // This makes the clock object count at the current samplerate

	if (myClock.tick) {
		output[0] = mySine1.sinewave(440);
		output[1] = output[0];
		if (playMelody) {
			if (sequence[note] == -1) {
				freq = 0;
			}
			else {
				freq = 440 * pow(1.059463, sequence[note]);
			}
			note++;
			if (note >= sequence.size()) {
				note = 0;
				playMelody = false;
				//lastSequence = melody;
			}
			output[0] = mySine1.sinewave(freq);
			output[1] = output[0];
		}
		else {
			output[0] = mySine1.sinewave(0);
			output[1] = output[0];
		}
	}



}

/*int main() {
	while (running == false) {
		string input = "";
		bool validInput1 = false;
		bool validInput2 = false;

		if (!validInput1) {
			cout << "Try typing this and press enter:\n";
			cout << "CCGGAAG\n";
			getline(cin, input);
			cout << "You entered: " << input << endl;
			if (!processInput(input)) {
				cout << "That was an invalid input. Enter only letters from A to G." << endl;
			}
			else {
				validInput1 = true;
			}
		}
		cout << "That played the first line of Twinkle Twinkle Little Star." << endl;
		while (!validInput2) {
			cout << "Try changing the speed faster by typing 'bpm100' or 'bpm120':\n";
			getline(cin, input);
			cout << "You entered: " << input << endl;
			if (!processInput(input)) {
				cout << "That was an invalid input. Try entering 'bpm' followed by a number between 50 to 200 without any spaces." << endl;
			}
			else {
				validInput2 = true;
			}
		}

		cout << "All done with the tutorial. If you need help, type 'help'." << endl << endl;
	}

	return 0;
}*/

bool processInput(string input) {
	std::size_t found = input.find("bpm");
	if (found != std::string::npos) { //check if it is "bpm[number]"
		if (found == 0) {
			string tempo = input.substr(3);
			if (tempo[0] != 0) { //number cannot start with '0'
				for (char c : tempo) { //if string after "bpm" is number
					if (!isdigit(c)) {
						return false; //not a digit
					}
					int x = stoi(tempo);
					if (x < 200 && x > 50) { //if 'x' is within valid tempo range
						int bpm = x; //set new bpm
						return true;
					}
				}
			}
		}
	}
	else { //not starting with "bpm"
		for (char c : input) {
			if (((int)c > 64 && (int)c < 72) || c == ',') { //if within int 65 to 71 (ASCII for A to G) or a ','
				createMelody(input);
				return true;
			}
		}
	}
	return false;
}

void createMelody(string melody) {
	sequence.clear();
	for (int i = 0; i < melody.size(); i++) {
		if (melody[i] == ',') { //indicates a rest
			sequence.push_back(-1);
		}
		else {
			if ((int)melody[i] < 67) { // 65 or 66 -> note A or B
				sequence.push_back(((int)melody[i] - 65) * 2); // step 0 or 2
			}
			else if ((int)melody[i] > 69) { // 70 or 71 -> note F or G
				sequence.push_back((((int)melody[i] - 65) - 7) * 2); // step -4 or -2
			}
			else { //67, 68, or 69 -> note C, D, or E
				sequence.push_back((((int)melody[i] - 65) - 7) * 2 + 1); // step -9, -7, or -5
			}
		}
	}
	playMelody = true;
}

