//
// Created by talleux on 1/22/24.
//

#include "AudioEngine.hpp"

void AudioEngine::checkError(PaError err) {
    if (err != paNoError) {
        std::cerr << "Error: " << Pa_GetErrorText(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

void AudioEngine::initialize() {
    createVirtualDevice();
    checkError(Pa_Initialize());

    int numDevices = Pa_GetDeviceCount();

    std::cout << "Number of devices: " << numDevices << std::endl;

    if (numDevices < 0) {
        std::cerr << "Error: " << Pa_GetErrorText(numDevices) << std::endl;
        exit(EXIT_FAILURE);
    } else if (numDevices == 0) {
        std::cerr << "Error: No devices found." << std::endl;
        exit(EXIT_SUCCESS);
    }

    memset(&inputParameters, 0, sizeof(inputParameters));
    memset(&outputParameters, 0, sizeof(outputParameters));

    reverbBuffer = static_cast<float *>(malloc(sizeof(float) * 1024 * 2));

    memset(&reverbBuffer, 0, sizeof(reverbBuffer));


    device = Pa_GetDefaultInputDevice();

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

    checkError(Pa_OpenStream(&stream, &inputParameters, &outputParameters, 44100, 1024, paClipOff, callback, this));
}

void AudioEngine::createVirtualDevice() {
    int command_output = system("pacmd load-module module-null-sink sink_name=ShowTime_Virtual_Input sink_properties=device.description=ShowTime_Virtual_Input");

    if (command_output != 0) {
        std::cerr << "Error: Failed to create virtual input." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void AudioEngine::killVirtualDevice() {
    int command_output = system("pacmd unload-module module-null-sink");

    if (command_output != 0) {
        std::cerr << "Error: Failed to kill virtual input." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void AudioEngine::start() {
    checkError(Pa_StartStream(stream));
}

void AudioEngine::stop() {
    checkError(Pa_StopStream(stream));
    checkError(Pa_CloseStream(stream));
    checkError(Pa_Terminate());
    killVirtualDevice();
}
