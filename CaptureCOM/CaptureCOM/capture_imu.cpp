#include "capture_imu.h"

static const double PI = 3.14159265359;

const double CaptureIMU::imu_sensitive[3] = { 16.0/* LSB/UT mag*/ , 8192.0 /* LSB/G acce*/, 65.6 /* LSB/degree/s gyro*/ };

bool CaptureIMU::get_imudata(double *mag, double *acce, double *gyro)
{
	std::string line;
	loop_query(line);
	std::vector<double> tmp_vec;
	std::istringstream line_stream(line);
	double num;
	while (line_stream >> num)
	{
		tmp_vec.push_back(num);
		if (line_stream.peek() == ',')
		{
			line_stream.ignore();
		}
	}
	if (tmp_vec.size() != 9)
	{
		return false;
	}
	for (int i = 0; i < 3; ++i)
	{
		mag[i] = tmp_vec[i];
		acce[i] = tmp_vec[i + 3];
		gyro[i] = tmp_vec[i + 6];
	}

	parse_rawdata(mag, acce, gyro);
	return true;
}

void CaptureIMU::loop_query(std::string &str)
{
	bool start_flag = false;
	std::ostringstream line;
	while (1)
	{
		char c = get_char();
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
		gyro[i] = gyro[i] / imu_sensitive[2] / 180.0 * PI;
	}
}