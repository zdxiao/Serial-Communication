#pragma once
#ifndef	CAPTURE_IMU_H
#define CAPTURE_IMU_H

#include "tserial.h"
#include "bot_control.h"
#include <sstream>
#include <string>
#include <vector>

class CaptureIMU: public serial
{
public:
	CaptureIMU() {};
	~CaptureIMU() {};
	bool get_imudata(double *mag, double *acce, double *gyro);

private:
	void parse_rawdata(double *mag, double *acce, double *gyro);
	void loop_query(std::string &str);
	static const double imu_sensitive[3];
};

#endif