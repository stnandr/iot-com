#include "Buzzer.h"
#include "Notes.h"
#include "Arduino.h"

Buzzer::Buzzer() {
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, LOW);
	NoTone();
}

void Buzzer::Tone(int pin, int freq) {
	digitalWrite(PIN, HIGH);
	ledcSetup(0, 2000, 8);
	ledcAttachPin(pin, 0);
	ledcWriteTone(0, freq);
	playing = pin;
}

void Buzzer::NoTone() {
	Tone(playing, 0);
	digitalWrite(PIN, LOW);
}


void Buzzer::PlayStart() {
	Tone(PIN, note::D3);
	delay(200);
	NoTone();
	Tone(PIN, note::D6);
	delay(200);
	NoTone();
}

void Buzzer::PlayActivated() {
	Tone(PIN, note::C4);
	delay(200);
	NoTone();
	Tone(PIN, note::C6);
	delay(200);
	NoTone();
}

void Buzzer::PlayDeactivated() {
	Tone(PIN, note::Bb4);
	delay(200);
	NoTone();
	Tone(PIN, note::F3);
	delay(200);
	NoTone();
}

void Buzzer::PlayMessage1() {
	Tone(PIN, note::C4);
	delay(200);
	Tone(PIN, note::Gb4);
	delay(200);
	Tone(PIN, note::G4);
	delay(200);
	Tone(PIN, note::F3);
	delay(200);
	NoTone();
}

void Buzzer::PlayMessage2() {
	Tone(PIN, note::Db6);
	delay(200);
	Tone(PIN, note::Bb5);
	delay(200);
	Tone(PIN, note::Ab4);
	delay(200);
	Tone(PIN, note::Ab4);
	delay(200);
	NoTone();
}

void Buzzer::PlayMessage3() {
	Tone(PIN, note::F4);
	delay(200);
	Tone(PIN, note::F4);
	delay(200);
	Tone(PIN, note::Eb4);
	delay(200);
	Tone(PIN, note::Ab3);
	delay(200);
	NoTone();
}
void Buzzer::PlayMessage4() {
	Tone(PIN, note::Eb4);
	delay(200);
	Tone(PIN, note::F4);
	delay(200);
	Tone(PIN, note::F4);
	delay(200);
	Tone(PIN, note::Ab4);
	delay(200);
	NoTone();
}
void Buzzer::PlayMessage5() {
	Tone(PIN, note::E5);
	delay(100);
	Tone(PIN, note::A5);
	delay(100);
	Tone(PIN, note::E5);
	delay(100);
	Tone(PIN, note::Bb5);
	delay(100);
	Tone(PIN, note::Db5);
	delay(100);
	NoTone();
}
void Buzzer::PlayMessage6() {
	Tone(PIN, note::Bb3);
	delay(200);
	Tone(PIN, note::Eb4);
	delay(200);
	Tone(PIN, note::Db4);
	delay(200);
	Tone(PIN, note::Eb4);
	delay(200);
	NoTone();
}
void Buzzer::PlayMessage7() {
	Tone(PIN, note::Bb4);
	delay(200);
	Tone(PIN, note::B4);
	delay(200);
	Tone(PIN, note::F4);
	delay(200);
	Tone(PIN, note::E4);
	delay(200);
	NoTone();
}
void Buzzer::PlayMessage8() {
	Tone(PIN, note::D6);
	delay(200);
	Tone(PIN, note::F5);
	delay(200);
	Tone(PIN, note::Eb5);
	delay(200);
	Tone(PIN, note::Db5);
	delay(200);
	NoTone();
}

void Buzzer::PlayConfirm() {
	Tone(PIN, note::E5);
	delay(200);
	NoTone();
}
