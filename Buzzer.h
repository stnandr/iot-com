#pragma once

class Buzzer {
public:
	// Pin number
	const int PIN = 18;

	// Constructor
	Buzzer();

	// Sound functions
	void PlayStart();
	void PlayActivated();
	void PlayDeactivated();
	void PlayMessage1();
	void PlayMessage2();
	void PlayMessage3();
	void PlayMessage4();
	void PlayMessage5();
	void PlayMessage6();
	void PlayMessage7();
	void PlayMessage8();
	void PlayConfirm();
	
private:
	int playing = 0;
	// Plays tone on pin
	void Tone(int PIN, int freq);
	// Stops tone from playing 
	void NoTone();

};
