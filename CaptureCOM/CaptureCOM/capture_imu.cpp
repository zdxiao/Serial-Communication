#include "capture_imu.h"

static const double PI = 3.14159265359;

const double CaptureIMU::imu_sensitive[3] = { 16.0/* LSB/UT mag*/ , 8192.0 /* LSB/G acce*/, 65.6 /* LSB/degree/s gyro*/ };

void CaptureIMU::get_imudata(double *mag, double *acce, double *gyro)
{
	std::string line;
	loop_query(line);
	std::istringstream line_stream(line);
	std::string dump;
	line_stream >> mag[0] >> dump >> mag[1] >> dump >> mag[2] 
		>> acce[0] >> dump >> acce[1] >> dump >> acce[2] 
		>> gyro[0] >> dump >> gyro[1] >> dump >> gyro[2];
	parse_rawdata(mag, acce, gyro);
}

void CaptureIMU::loop_query(std::string &str)
{
	bool start_flag = false;
	std::ostringstream line;
	while (1)
	{
		char c = comm.get_char();
		if (c == '#')
		{
			start_flag = true;
			continue;
		}
		if (start_flag)
		{
			if (c == '*')
			{
				break;
			}
			else
			{
				line << c;
			}
		}
	}
	str = line.str();
}

void CaptureIMU::parse_rawdata(double *mag, double* acce, double *gyro)
{
	for (int i = 0; i < 3; ++i)
	{
		mag[i] = mag[i] / imu_sensitive[0];
		acce[i] = acce[i] / imu_sensitive[1] * 9.81;
		gyro[i] = gyro[i] / imu_sensitive[2] / PI * 180.0;
	}
}