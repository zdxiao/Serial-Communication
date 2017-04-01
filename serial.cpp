#include <stdio.h>
#include <conio.h>
#include "tserial.h"
#include "bot_control.h"
#include <fstream>
#include <iostream>
#include "capture_imu.h"
#include <sstream>

CaptureIMU comm; //serial is a class type defined in these files, used for referring to the communication device
void main() {
char data; //To store the character to send
comm.startDevice("COM4", 921600);
/* “COM 2?refers to the com port in which the USB to SERIAL port is attached. It is shown by right clicking on my computer, then going to properties and then device manager
9600 is the baud-rate in bits per second */
std::ofstream file("imu.txt");
while (1)
{
	char buffer[100];
	double acce[3] = { 0 }, gyro[3] = { 0 }, mag[3] = { 0 };
	comm.get_imudata(mag, acce, gyro);
	std::ostringstream ostream;
	ostream << mag[0] << "," << mag[1] << "," << mag[2] << ","
		<< acce[0] << "," << acce[1] << "," << acce[2] << ","
		<< gyro[0] << "," << gyro[1] << "," << gyro[2] << " " 
		<< std::endl;
	std::cout << ostream.str();
	file << ostream.str();
}
file.close();
comm.stopDevice(); //The device is closed down
//getch();
} 