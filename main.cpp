//
// Created by talleux on 1/19/24.
//

#include <cstring>
#include <portaudio.h>
#include <iostream>

static void checkError(PaError err)
{
    if (err != paNoError) {
        std::cerr << "Error: " << Pa_GetErrorText(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

static float max(float a, float b)
{
    return a > b ? a : b;
}

static int callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    float* in = (float*)inputBuffer;

    int dispSize = 100;
    printf("\r");

    float vol_l = 0;
    float vol_r = 0;

    for (unsigned long i = 0; i < framesPerBuffer * 2; i += 2) {
        vol_l = max(vol_l, std::abs(in[i]));
        vol_r = max(vol_r, std::abs(in[i+1]));
    }

    for (int i = 0; i < dispSize; i++) {
        float barProportion = i / (float)dispSize;
        if (barProportion <= vol_l && barProportion <= vol_r) {
            printf("█");
        } else if (barProportion <= vol_l) {
            printf("▀");
        } else if (barProportion <= vol_r) {
            printf("▄");
        } else {
            printf(" ");
        }
    }

    fflush(stdout);

    memcpy(outputBuffer, inputBuffer, framesPerBuffer * 2 * sizeof(float));

    return 0;
}

int main()
{
    PaError err = Pa_Initialize();
    checkError(err);

    int command_output = system("pacmd load-module module-null-sink sink_name=ShowTime_Virtual_Input sink_properties=device.description=ShowTime_Virtual_Input");

    if (command_output != 0) {
        std::cerr << "Error: Failed to create virtual input." << std::endl;
        exit(EXIT_FAILURE);
    }

    int numDevices = Pa_GetDeviceCount();

    std::cout << "Number of devices: " << numDevices << std::endl;

    if (numDevices < 0) {
        std::cerr << "Error: " << Pa_GetErrorText(numDevices) << std::endl;
        exit(EXIT_FAILURE);
    } else if (numDevices == 0) {
        std::cerr << "Error: No devices found." << std::endl;
        exit(EXIT_SUCCESS);
    }

    for (int i = 0; i < numDevices; ++i) {
        const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);
        std::cout << "Device " << i << ": " << deviceInfo->name << std::endl;
        std::cout << "\tMax input channels: " << deviceInfo->maxInputChannels << std::endl;
        std::cout << "\tMax output channels: " << deviceInfo->maxOutputChannels << std::endl;
        std::cout << "\tDefault sample rate: " << deviceInfo->defaultSampleRate << std::endl;
    }

    int device = Pa_GetDefaultInputDevice();

    std::cout << "Using device " << device << std::endl;

    PaStreamParameters inputParameters;
    PaStreamParameters outputParameters;

    memset(&inputParameters, 0, sizeof(inputParameters));
    memset(&outputParameters, 0, sizeof(outputParameters));

    inputParameters.device = device;
    inputParameters.channelCount = 2;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.hostApiSpecificStreamInfo = nullptr;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(device)->defaultLowInputLatency;

    outputParameters.device = device;
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.hostApiSpecificStreamInfo = nullptr;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(device)->defaultLowOutputLatency;


    PaStream *stream;
    err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, 44100, 256, paClipOff, callback, nullptr);
    checkError(err);

    err = Pa_StartStream(stream);
    checkError(err);

    std::string line;
    while (std::getline(std::cin, line) && !std::cin.eof()) {
        if (line == "exit")
            break;
    }

    err = Pa_StopStream(stream);
    checkError(err);

    err = Pa_CloseStream(stream);
    checkError(err);

    err = Pa_Terminate();
    checkError(err);

    command_output = system("pacmd unload-module module-null-sink");

    if (command_output != 0) {
        std::cerr << "Error: Failed to unload virtual input." << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
