//
// Created by talleux on 1/19/24.
//

#pragma once

#include <cmath>

#define bufferSize 1024
#define centerFrequency (float)2000.0
#define Q (float)5.0
#define gain (float)0.005

class Equalizer {
public:
    Equalizer() : inputBuffer(new float[bufferSize]()), outputBuffer(new float[bufferSize]()) {
        initializeCoefficients();
    }

    ~Equalizer() {
        delete[] inputBuffer;
        delete[] outputBuffer;
    }

    void processBuffer(float* buffer) {
        // Initialize the first two elements
        inputBuffer[0] = buffer[0];
        inputBuffer[1] = buffer[1];
        outputBuffer[0] = b0 / a0 * inputBuffer[0];
        outputBuffer[1] = b0 / a0 * inputBuffer[1] + b1 / a0 * inputBuffer[0];

        for (int i = 2; i < bufferSize; ++i) {
            inputBuffer[i] = buffer[i];

            // Apply the parametric bandpass filter
            outputBuffer[i] = b0 / a0 * inputBuffer[i] + b1 / a0 * inputBuffer[i - 1]
                              + b2 / a0 * inputBuffer[i - 2] - a1 / a0 * outputBuffer[i - 1] - a2 / a0 * outputBuffer[i - 2];
        }

        // Copy the result into the original buffer
        for (int i = 0; i < bufferSize; ++i) {
            buffer[i] = (float)outputBuffer[i];
            std::cerr << buffer[i] << std::endl;
            if (buffer[i] <= -1.0 || buffer[i] >= 1.0) {
                std::cerr << "Buffer overflow: " << buffer[i] << std::endl;
            }
        }
    }

    void initializeCoefficients() {
        float w0 = (float)2.0 * (float)M_PI * centerFrequency / sampleRate;
        float alpha = sinf(w0) / (float)(2.0 * Q);

        b0 = (float)1.0 + alpha * gain;
        b1 = (float)-2.0 * cosf(w0);
        b2 = (float)1.0 - alpha * gain;

        a0 = (float)1.0 + alpha / gain;
        a1 = (float)-2.0 * cosf(w0);
        a2 = (float)1.0 - alpha / gain;
    }

    void setActive(bool active) {
        this->active = active;
        std::cerr << "Active: " << active << std::endl;
    }

    bool isActive() {
        return active;
    }

private:
    float b0, b1, b2, a0, a1, a2;
    const float sampleRate = 44100.0;
    float* inputBuffer;
    float* outputBuffer;
    bool active = false;

};
