#include "GyroData.h"
#define toleranceDegree 15

GyroData::GyroData() {
	pitch = 0;
	roll = 0;
}

double GyroData::GetPitch() {
	return pitch;
}

double GyroData::GetRoll() {
	return roll;
}

void GyroData::SetAngles(double pitch, double roll) {
	this->pitch = pitch;
	this->roll = roll;
}
 
bool GyroData::IsPitchAt(double expected) {
	double minim = expected - toleranceDegree;
	double maxim = expected + toleranceDegree;

	if (minim < -180)
		minim += 360;

	if (maxim > 180)
		maxim -= 360;
	
	if (minim > maxim)
		if (pitch < maxim || pitch > minim)
			return true;

	if (pitch < maxim && pitch > minim)
		return true;

	return false;
}

bool GyroData::IsRollAt(double expected) {
	double minim = expected - toleranceDegree;
	double maxim = expected + toleranceDegree;

	if (minim < -180)
		minim += 360;

	if (maxim > 180)
		maxim -= 360;
	
	if (minim > maxim)
		if (roll < maxim || roll > minim)
			return true;

	if (roll < maxim && roll > minim)
		return true;

	return false;
}
