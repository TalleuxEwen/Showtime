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

        void setVolume(int volume_to_set) {
            this->volume = volume_to_set;
        }

        int getVolume() const {
            return this->volume;
        }

        bool reverb = false;
        float reverberation = 1.0;
        float reverb_decay = 0.5;
        int reverb_delay = 1024;
        float gain = 1.0;
        float pan = 0.0;

        float *inputBuffer;
        float *outputBuffer;
        float *reverbBuffer;

    private:
        PaStreamParameters inputParameters;
        PaStreamParameters outputParameters;
        PaStream *stream;
        int device = 0;
        int volume = 0;
};

static int callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
             const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    auto* in = (float*)inputBuffer;
    auto* engine = (AudioEngine*)userData;

    int dispSize = 100;
    //printf("\r");

    float vol_l = 0;
    float vol_r = 0;

    for (unsigned long i = 0; i < framesPerBuffer * 2; i += 2) {
        vol_l = max(vol_l, std::abs(in[i]));
        vol_r = max(vol_r, std::abs(in[i+1]));
    }



    engine->inputBuffer = (float*)inputBuffer;
    //std::cout << engine->getVolume() << std::endl;
    //std::cout << (float)engine->getVolume() / 100.f << std::endl;

    for (int i = 0; i < framesPerBuffer * 2; i++) {
        ((float *)inputBuffer)[i] = ((float *)inputBuffer)[i] * (float)((float)engine->getVolume() / 100.f);
    }

    /*for (int i = 0; i < dispSize; i++) {
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

    fflush(stdout);*/

    if (engine->reverb) {

        for (int i = 0; i < framesPerBuffer * 2; i++) {
            if (engine->reverb_delay == framesPerBuffer) {
                ((float *)outputBuffer)[i] = ((float *)inputBuffer)[i] * engine->reverberation + ((float *)outputBuffer)[i] * engine->reverb_decay;
            } else if (engine->reverb_delay < framesPerBuffer) {
                if (i < engine->reverb_delay) {
                    ((float *)outputBuffer)[i] = ((float *)inputBuffer)[i] * engine->reverberation + ((float *)outputBuffer)[i + framesPerBuffer - engine->reverb_delay] * engine->reverb_decay;
                } else {
                    ((float *)outputBuffer)[i] = ((float *)inputBuffer)[i] * engine->reverberation + ((float *)outputBuffer)[i - engine->reverb_delay] * engine->reverb_decay;
                }
            } else {
                /*int index = i - engine->reverb_delay + framesPerBuffer;
                ((float *)outputBuffer)[i] = ((float *)inputBuffer)[i] * engine->reverberation + ((float *)engine->reverbBuffer)[index] * engine->reverb_decay;
            */
            }
            /*((float *)outputBuffer)[i] = ((float *)inputBuffer)[i] * engine->reverberation + ((float *)outputBuffer)[i] * engine->reverb_decay;*/
        }
    } else {
        memcpy(outputBuffer, inputBuffer, framesPerBuffer * 2 * sizeof(float));
    }

    for (int i = 0; i < framesPerBuffer * 2; i++) {
        ((float *)outputBuffer)[i] = ((float *)outputBuffer)[i] * engine->gain;
    }

    for (int i = 0; i < framesPerBuffer * 2; i += 2) {
        if (engine->pan > 0) {
            ((float *)outputBuffer)[i] = ((float *)outputBuffer)[i] * (1.f - engine->pan);
        } else if (engine->pan < 0) {
            ((float *)outputBuffer)[i + 1] = ((float *)outputBuffer)[i + 1] * (1.f + engine->pan);
        }
    }

    engine->outputBuffer = (float*)outputBuffer;

    //memcpy(&engine->reverbBuffer, inputBuffer, framesPerBuffer * 2 * sizeof(float));

    return paContinue;
}
