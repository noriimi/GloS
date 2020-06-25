// GloS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SerialPort.hpp"
#include <chrono>
#include <thread>
#include <Windows.h>
#include <vector>
#include "PortsFinder.hpp"
int main()
{
    SerialPort serial{};
    PortsFinder finder{};
  
    if (finder.find())
    {  
        auto port = SerialPort::parse(finder.getFoundPort(0));
        std::cout << "Found port : " << port << std::endl;
        if (serial.openPort(port))
        {
            serial.initPort(CBR_115200, 8, ONESTOPBIT, NOPARITY);
            serial.Send("TEST\n");
            serial.closePort();
        }
    }
    
    return 0;
}

