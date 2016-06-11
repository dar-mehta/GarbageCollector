#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include <iostream>

// application reads from the specified serial port and reports the collected data
int main()
{
	printf("Welcome to the serial test app!\n\n");

	//Serial* SP = new Serial("\\\\.\\COM10");    // adjust as needed
	Serial* SP = new Serial("COM5");    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
											//printf("%s\n",incomingData);
	int dataLength = 255;
	int readResult = 0;

	while (SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData, dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;


		//printf("%s", incomingData);

		//Sleep(1000);

		//printf("%s", incomingData);

		std::cout << "Enter data" << std::endl;
		char cinval1;
		char cinval2;
		std::cin >> cinval1 >> cinval2;

		SP->WriteData(&cinval1, cinval1);
		SP->WriteData(&cinval2, cinval2);

		Sleep(500);
	}
	return 0;
}