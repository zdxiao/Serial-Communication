#include <stdio.h>
#include <conio.h>
#include "tserial.h"
#include "bot_control.h"
#include <fstream>
#include <iostream>

serial comm; //serial is a class type defined in these files, used for referring to the communication device
void main() {
char data; //To store the character to send
comm.startDevice("COM4", 921600);
/* “COM 2?refers to the com port in which the USB to SERIAL port is attached. It is shown by right clicking on my computer, then going to properties and then device manager
9600 is the baud-rate in bits per second */
std::ofstream file("imu.txt");
while (1)
{
	char buffer[100];
	char c = comm.get_data(buffer);
	std::cout << buffer << std::endl;
	file << buffer << std::endl;
}
file.close();
comm.stopDevice(); //The device is closed down
//getch();
} 