 // Main libraries
#include "Wire.h"
#include <MPU6050_light.h>
#include <string>
#include "GyroData.h"
#include "DataRouter.h"
#include "Message.h"
#include "Buzzer.h"


// Network stuff
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define delayTime 1000

// Network macros
#define BLYNK_TEMPLATE_ID "TMPLqz_qz9iA"
#define BLYNK_DEVICE_NAME "StanIOT"
#define BLYNK_AUTH_TOKEN "O0XxmVuP6h240SCRRgGmlTElXMMJge-3"

// Network data
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "IoT-Stan";
char pass[] = "18d197ae7017";

// Gyroscope objects
MPU6050 mpuHand(Wire);
MPU6050 mpuFinger(Wire);
Buzzer buzzer;

int playing = 0;
unsigned int timeCounter;
unsigned long timer = 0;



void setup() {
	// MPU setup
	Serial.begin(9600);
	Wire.begin();
	mpuHand.setAddress(104);
	mpuFinger.setAddress(105);
	
	delay(delayTime);
	mpuHand.begin();
	mpuHand.calcGyroOffsets();
	
	delay(delayTime);
	mpuFinger.begin();
	mpuFinger.calcGyroOffsets();	

	// Buzzer start
	buzzer.PlayStart();

	// Blynk setup
	Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

	Blynk.notify("{DEVICE_NAME}: Conectat!");
}

void loop() {
	// Updates gyro data	
	mpuHand.update();
	mpuFinger.update();

	// Main update loop
	if ((millis() - timer) > delayTime) {	
		// Gyro data parsing
		GyroData gyroHand, gyroFinger;
		gyroHand.SetAngles(mpuHand.getAngleX(), mpuHand.getAngleY());
		gyroFinger.SetAngles(mpuFinger.getAngleX(), mpuFinger.getAngleY());

		// Message check
		String message = DataRouter(gyroHand, gyroFinger, buzzer);

		// Print updated gyro data (also for debug purposes
		Serial.print("Hand Pitch: ");
		Serial.print(gyroHand.GetPitch());
		Serial.print("\tHand Roll: ");
		Serial.print(gyroHand.GetRoll());
		Serial.print("\tFinger Pitch: ");
		Serial.print(gyroFinger.GetPitch());
		Serial.print("\tFinger Roll: ");
		Serial.print(gyroFinger.GetRoll());

		// Update + notify messasge
		if (message != "") {
			Serial.print("\t\t");
			Serial.print(message);
			Blynk.logEvent(message, "");
			Serial.print("\n");
		}

	
		// Timer update for delta time
		timer = millis();

		Serial.print("\n");		
	}

	// Runs all of the requests from the blynk buffer
	Blynk.run();
	
}
