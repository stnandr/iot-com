#pragma once

class GyroData {
private:
	double pitch, roll;

public:
	GyroData();

	// Returns gyro data
	double GetPitch();
	double GetRoll();

	// Sets the data into the Gyro object from MPU api
	void SetAngles(double pitch, double roll);

	// Returns true when the pich or roll are in the specified position with tolerance
	bool IsPitchAt(double expected);
	bool IsRollAt(double expected);
};
