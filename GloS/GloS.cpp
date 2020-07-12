#define NOMINMAX
#define NUMOFLEDS 60
#define CBR_1000000 1000000
#define CBR_2000000 2000000
#define CBR_500000 500000
#define __HEADERSIZE 4
#include <iostream>
#include "SerialPort.hpp"
#include "PortsFinder.hpp"
#include "threadHelper.hpp"
#include "RtAudio/RtAudio.h"
int record(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus, void* userData)
{
	//callback executed after every sample
    return 0;
}
int main()
{
	RtAudio sound{};
    if (sound.getDeviceCount() < 1)
    {
        std::cout << "\nNo audio devices found!\n";
        exit(0);
    }
    RtAudio::StreamParameters parameters;
    parameters.deviceId = 3;
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 1024;
    try {
        sound.openStream(NULL, &parameters, RTAUDIO_FLOAT32, sampleRate, &bufferFrames, &record);
        sound.startStream();
    }
    catch (RtAudioError& e)
    {
        e.printMessage();
        exit(0);
    }
    char input;
    std::cout << "\nRecording ... press <enter> to quit. \n";
    std::cin.get(input);
    try
    {
        sound.stopStream();

    }
    catch (RtAudioError& e)
    {
        e.printMessage();
    }
    if (sound.isStreamOpen())
        sound.closeStream();
}
