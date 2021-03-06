#ifndef BOT_CONTROL_H
#define BOT_CONTROL_H

#include "tserial.h"

class serial{

  protected:
        // private attributes
		Tserial *com;
  public:


	serial() {
			
		 }
	
	bool startDevice(char *port,int speed)
	{
		com = new Tserial();
		if (com!=0)
		{
			if(com->connect(port, speed, spNONE))
				printf("Not Connected...\n");
			else
				printf("Connected..\n");
			return TRUE;
		}
		else
			return FALSE; 
	}

	void stopDevice()
	{
		com->disconnect();
        // ------------------
        delete com;
        com = 0;
	}

	void send_data(unsigned char data)
	{
	//	unsigned char data = 0;
	
		
		com->sendChar(data);
		printf("%c",data);
		
	}

	char get_char()
	{
		char c = com->getChar();
		//printf("%c", c);
		return c;
	}
};

#endif