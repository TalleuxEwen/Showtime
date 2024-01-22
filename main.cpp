//
// Created by talleux on 1/19/24.
//

#include <cstring>
#include <portaudio.h>
#include <iostream>
#include "Equalizer.hpp"
#include "AudioEngine.hpp"
#include "ClientCore.hpp"

int main()
{
    std::shared_ptr<AudioEngine> engine = std::make_shared<AudioEngine>();
    engine->initialize();
    ClientCore core(engine);
    Equalizer eq;
    eq.initializeCoefficients();

    /*int numDevices = Pa_GetDeviceCount();

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

    int device = Pa_GetDefaultInputDevice();*/

    engine->start();


    core.run();
    /*std::string line;
    while (std::getline(std::cin, line) && !std::cin.eof()) {
        if (line == "exit")
            break;
        else if (line == "eq") {
            eq.setActive(!eq.isActive());
        } else if (line == "reverb") {
            engine.reverb = !engine.reverb;
        }
    }*/

    engine->stop();

    return EXIT_SUCCESS;
}
