#define NOMINMAX

#define CBR_1000000 1000000
#define CBR_2000000 2000000
#define CBR_500000 500000

#define __HEADERSIZE 4
#include "thrFunc.h"


int record(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames, double streamTime, unsigned int status, void* userData)
{
    memcpy(userData, inputBuffer, NUMOFSAMPLES * sizeof(sample_t));
    threadHelper::staticFlags::s_read_ = true;
	//callback executed after every sample
    if (status)
        std::cout << "Stream overflow detected\n";
    return 0;
}
int main()
{
	RtAudio sound{};
    unsigned rs = 0;
    sample_t data[NUMOFSAMPLES];
    auto sum = NUMOFSAMPLES;
    auto res = 0;
    while (sum > (NUMOFSAMPLES / 2))
    {
        sum = 0;
        res++;
        for (float i = 1.0f; i <= NUMOFLEDS; i++)
        {
            sum += std::ceil(i / res);
        }
    }
    rs = res;
    if (sound.getDeviceCount() < 1)
    {
        std::cout << "\nNo audio devices found!\n";
        exit(0);
    }
    RtAudio::StreamParameters parameters;
    parameters.deviceId = 2;
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = NUMOFSAMPLES;
    for (int i = 0; i < sound.getDeviceCount(); i++)
    {
        std::cout << sound.getDeviceInfo(i).name<<'\n';
    }
    std::cout << "using  " << sound.getDeviceInfo(2).name;
    
    try {
        sound.openStream(NULL, &parameters, RTAUDIO_SINT16, sampleRate, &bufferFrames, &record,data);
        sound.startStream();
    }
    catch (RtAudioError& e)
    {
        e.printMessage();
        exit(0);
    }
    char input;
    std::function<void(sample_t[],unsigned)> func = thrFunc;
    threadHelper worker(func, data,rs);
    std::cout << "\nRecording ... press <enter> to quit. \n";
    std::cin.get(input);
    worker.interruptThread();
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
    return 0;
}
