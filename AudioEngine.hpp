//
// Created by talleux on 1/22/24.
//

#pragma once

#include <cstring>
#include <portaudio.h>
#include <iostream>

static float max(float a, float b)
{
    return a > b ? a : b;
}

class AudioEngine {
    public:
        AudioEngine() = default;
        ~AudioEngine() = default;

        void checkError(PaError err);
        void initialize();
        void createVirtualDevice();
        void killVirtualDevice();
        void start();
        void stop();

        bool reverb = false;

    private:
        PaStreamParameters inputParameters;
        PaStreamParameters outputParameters;
        PaStream *stream;
        int device = 0;
};

static int callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
             const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    auto* in = (float*)inputBuffer;
    auto* engine = (AudioEngine*)userData;

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

    if (engine->reverb) {
        for (int i = 0; i < framesPerBuffer * 2; i++) {
            ((float *)outputBuffer)[i] = ((float *)inputBuffer)[i] * (float)0.6 + ((float *)outputBuffer)[i] * (float)0.65;
        }
    } else {
        memcpy(outputBuffer, inputBuffer, framesPerBuffer * 2 * sizeof(float));
    }

    return paContinue;
}
