#define NOMINMAX
#define __TIMEMEASURING 0
#include <iostream>
#include "SerialPort.hpp"
#if __TIMEMEASURING
#include <chrono>
#include <thread>
#endif // 
#include <algorithm>

#include "PortsFinder.hpp"
int main()
{
    
    PortsFinder finder{};
    uint8_t data[5] = { 20,60,200,60,10 };
    
        
    if (finder.find())
    {  
        auto port = SerialPort::parse(finder.getFoundPort(0));
        std::cout << "Found port : " << port << std::endl;
        SerialPort serial(port,CBR_9600,8,ONESTOPBIT,NOPARITY,TRUE);
        if (serial.isOpen())
        {
            while (1)
            {
                    data[0] = std::min(71,rand()%72);
                    data[1] = std::min(255, (int)++data[1]);
                    serial.Send(data, 5);
            }
        }
    }
    
    return 0;
}

