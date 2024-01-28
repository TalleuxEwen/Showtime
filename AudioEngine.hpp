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
        float reverb_decay = 0;
        int reverb_delay = 0;
        int prev_reverb_delay = 0;
        float gain = 1.0;
        float pan = 0.0;

        float *inputBuffer;
        float *outputBuffer;
        float **reverbBuffer = nullptr;
        float *reverbOutputBuffer = nullptr;

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
        if (engine->reverbOutputBuffer == nullptr) {
            for (int i = 0; i < framesPerBuffer * 2; i++) {
                ((float *)outputBuffer)[i] = ((float *)inputBuffer)[i] * engine->reverberation + ((float *)outputBuffer)[i] * engine->reverb_decay;
            }
        } else {
            for (int i = 0; i < framesPerBuffer * 2; i++) {
                ((float *)outputBuffer)[i] = ((float *)inputBuffer)[i] * engine->reverberation + ((float *)engine->reverbOutputBuffer)[i] * engine->reverb_decay;
            }
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

    /*if (engine->reverbBuffer1 != nullptr) {
        if (engine->reverbBuffer2 == nullptr) {
            engine->reverbBuffer2 = new float[framesPerBuffer * 2]();
        }
        memcpy(engine->reverbBuffer2, engine->reverbBuffer1, framesPerBuffer * 2 * sizeof(float));
    }

    if (engine->reverbBuffer2 != nullptr) {
        if (engine->reverbBuffer3 == nullptr) {
            engine->reverbBuffer3 = new float[framesPerBuffer * 2]();
        }
        memcpy(engine->reverbBuffer3, engine->reverbBuffer2, framesPerBuffer * 2 * sizeof(float));
    }

    if (engine->reverbBuffer3 != nullptr) {
        if (engine->reverbOutputBuffer == nullptr) {
            engine->reverbOutputBuffer = new float[framesPerBuffer * 2]();
        }
        memcpy(engine->reverbOutputBuffer, engine->reverbBuffer3, framesPerBuffer * 2 * sizeof(float));
    }

    if (engine->reverbBuffer1 == nullptr) {
        engine->reverbBuffer1 = new float[framesPerBuffer * 2]();
    }

    memcpy(engine->reverbBuffer1, inputBuffer, framesPerBuffer * 2 * sizeof(float));*/

    if (engine->prev_reverb_delay != engine->reverb_delay) {
        for (int i = 0; i < engine->prev_reverb_delay; i++) {
            if (engine->reverbBuffer[i] != nullptr)
                delete[] engine->reverbBuffer[i];
        }
        if (engine->reverbBuffer != nullptr)
            delete[] engine->reverbBuffer;
        engine->reverbBuffer = nullptr;
        if (engine->reverbOutputBuffer != nullptr)
            delete[] engine->reverbOutputBuffer;
        engine->reverbOutputBuffer = nullptr;
        engine->prev_reverb_delay = engine->reverb_delay;
    }

    if (engine->reverbBuffer == nullptr) {
        engine->reverbBuffer = new float*[engine->reverb_delay];
        for (int i = 0; i < engine->reverb_delay; i++) {
            engine->reverbBuffer[i] = new float[framesPerBuffer * 2]();
        }
    }

    if (engine->reverbOutputBuffer == nullptr) {
        engine->reverbOutputBuffer = new float[framesPerBuffer * 2]();
    }

    for (int i = 0; i < engine->reverb_delay; i++) {
        if (i == 0) {
            memcpy(engine->reverbOutputBuffer, engine->reverbBuffer[i], framesPerBuffer * 2 * sizeof(float));
        } else {
            for (int j = 0; j < framesPerBuffer * 2; j++) {
                engine->reverbOutputBuffer[j] += engine->reverbBuffer[i][j] * engine->reverb_decay;
            }
        }
    }

    for (int i = engine->reverb_delay - 1; i > 0; i--) {
        memcpy(engine->reverbBuffer[i], engine->reverbBuffer[i - 1], framesPerBuffer * 2 * sizeof(float));
    }

    if (engine->reverb_delay > 0)
        memcpy(engine->reverbBuffer[0], inputBuffer, framesPerBuffer * 2 * sizeof(float));

    //memcpy(&engine->reverbBuffer, inputBuffer, framesPerBuffer * 2 * sizeof(float));

    return paContinue;
}
