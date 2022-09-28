#pragma once

// Delta Time for messages
namespace tmg {
	static unsigned int secondsPassed = 0;
	static unsigned int previousTime = 0;
	static unsigned int previousTimeMessage = 0;
	
	static void Increment() {
		secondsPassed++;
	}

	static void SetTimeNow() {
		previousTime = secondsPassed;
	}

	static unsigned int GetTimePassed() {
		return secondsPassed - previousTime;
	}

	static void SetTimeNowMessage() {
		previousTimeMessage = secondsPassed;
	}

	static unsigned int GetTimePassedMessage() {
		return secondsPassed - previousTimeMessage;
	}
}
