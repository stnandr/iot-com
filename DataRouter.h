#pragma once
#include "GyroData.h"
#include "Buzzer.h"
#include <string>
#include "TimeManagement.h"

int lastCase = -1;
bool isTriggered = false;

// Returns the message id based on gyro angles
int GetCase(GyroData hand, GyroData finger) {

	// Activate/Deactivate
	if (hand.IsRollAt(0) && hand.IsPitchAt(0) && finger.GetPitch() > 125)
		return 1;

	// Dreapta
	if (hand.GetRoll() > 40) {
		// Asistenta
		if (finger.GetRoll() < -60)
			return 7;
		
		//Vreau afara
		if (finger.GetPitch() > 75)
			return 4;
	}

	// Stanga
	if (hand.GetRoll() < -30) {
		// Vreau sa ma deplasez
		if (finger.GetPitch() > 75)
			return 9;

		// Urgenta
		if (finger.IsPitchAt(0))
			return 6;
	}

	// Foame
	if (hand.GetPitch() < -35 && (finger.GetPitch() < -125 || finger.GetPitch() > 140))
		return 3;

	// Sete
	if (hand.GetPitch() < -35 && finger.GetPitch() > 75)
		return 2;

	// Baie
	if (hand.GetPitch() > 35 && finger.GetPitch() > 30)
		return 5;

	// Nu ma simt bine
	if (hand.GetPitch() > 35 && finger.GetPitch() < -15)
		return 8;

	
	return -1;
}

// Transforms the code into blynk notification id + plays sound
String Message(int code, bool* isTriggered) {
	switch (code) {
	case 2:
		(*isTriggered) = false;
		return "imi_este_sete";
		break;
			
	case 3:
		(*isTriggered) = false;
		return "imi_este_foame";
		break;
			
	case 4:
		(*isTriggered) = false;
		return "vreau_afara";
		break;
			
	case 5:
		(*isTriggered) = false;
		return "vreau_la_baie";
		break;
			
	case 6:
		(*isTriggered) = false;
		return "urgenta";
		break;
			
	case 7:
		(*isTriggered) = false;
		return "am_nevoie_de_asistenta";
		break;
			
	case 8:
		(*isTriggered) = false;
		return "nu_ma_simt_bine";
		break;
			
	case 9:
		(*isTriggered) = false;
		return "vreau_sa_ma_deplasez";
		break;
			
	default:
		break;
	}

	return "";
}

void PlayFirst(int code, Buzzer& buzzer) {
	switch (code) {
	case 2:
		buzzer.PlayMessage1();
		break;
			
	case 3:
		buzzer.PlayMessage2();
		break;
			
	case 4:
		buzzer.PlayMessage3();
		break;
			
	case 5:
		buzzer.PlayMessage4();
		break;
			
	case 6:
		buzzer.PlayMessage5();
		break;
			
	case 7:
		buzzer.PlayMessage6();
		break;
			
	case 8:
		buzzer.PlayMessage7();
		break;
			
	case 9:
		buzzer.PlayMessage8();
		break;
			
	default:
		break;
	}
}

// Routes the ids and deals with trigger logic
String DataRouter(GyroData hand, GyroData finger, Buzzer& buzzer) {
	int posCase = GetCase(hand, finger);

	tmg::Increment();
	
	Serial.print(tmg::GetTimePassed());
	Serial.print(" ");
	Serial.print(tmg::GetTimePassedMessage());
	Serial.print(" ");
	
	if (tmg::GetTimePassed() == 15 && isTriggered) {
		isTriggered = false;
		buzzer.PlayDeactivated();
		return "";
	}

	if (lastCase != posCase) {
		lastCase = posCase;
		tmg::SetTimeNowMessage();
	} else {
		if (posCase != 1 && posCase != -1 && posCase != -2 && isTriggered) {
			if (tmg::GetTimePassedMessage() == 1) {
				PlayFirst(posCase, buzzer);
				isTriggered = true;
			}
			
			if (tmg::GetTimePassedMessage() <= 2) {
				tmg::SetTimeNow();
				return "";
			}
	
			if (tmg::GetTimePassedMessage() == 3) {
				if (isTriggered) {
					buzzer.PlayConfirm();
					tmg::SetTimeNowMessage();
					tmg::SetTimeNow();
					isTriggered = false;
					return Message(posCase, &isTriggered);
				}
			}
	
			if (tmg::GetTimePassedMessage() > 3) {
				tmg::SetTimeNowMessage();
				isTriggered = false;
				return "";
			}
		} else {
			tmg::SetTimeNowMessage();
		}
	} 

	if (posCase == 1 && !isTriggered) {
		isTriggered = true;

		tmg::SetTimeNow();
		buzzer.PlayActivated();
		return "";
	}

	if (posCase == 1 && isTriggered) {
		isTriggered = false;
		buzzer.PlayDeactivated();
		return "";
	}

	if (!isTriggered && posCase != 1)
		return "";

	return "";
}
