#define NOMINMAX
#define NUMOFLEDS 60
#define CBR_1000000 1000000
#define CBR_2000000 2000000
#define CBR_500000 500000
#define __HEADERSIZE 4
#include <iostream>
#include "SerialPort.hpp"
#include "PortsFinder.hpp"
int main()
{
  /*
    PortsFinder finder{};
    uint8_t data[__HEADERSIZE+3*NUMOFLEDS];
    data[0] = 0xDE;
    data[1] = 0xAD;
    data[2] = 0xBE;
    data[3] = 0xEF;
        
    if (finder.find())
    {  
        auto port = SerialPort::parse(finder.getFoundPort(0));
        std::cout << "Found port : " << port << std::endl;
        SerialPort serial(port, CBR_1000000,8,ONESTOPBIT,NOPARITY,FALSE);
        if (serial.isOpen())
        {
            while (1)
            {
                serial.UpdateLED(data, __HEADERSIZE + 3 * NUMOFLEDS);
            }
        }
    }
    
    return 0;*/
}

