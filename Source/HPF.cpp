#define _USE_MATH_DEFINES
#include "HPF.h"
#include <iostream>

HPF::HPF() {
}

HPF::~HPF() {
}

float HPF::processSample(float x, int channel) {
    float y;

    y = (b0 / a0) * x + (b1 / a0) * x1[channel] + (b2 /a0) * x2[channel] + (-a1 / a0) * y1[channel] + (-a2 / a0) * y2[channel];

    x2[channel] = x1[channel];
    x1[channel] = x;
    y2[channel] = y1[channel];
    y1[channel] = y;

    return y;
}

void HPF::setFs(float Fs) {
    this->Fs = Fs;
}

void HPF::setFrequency(float newFreq) {
    // Constantly updating coefficients can be expensive so only do so if needed
    if (newFreq != freq || newFreq != 0.0f) {
        updateCoefficients();
        freq = newFreq;
    }   
}

void HPF::updateCoefficients() {
    float w0 = (2.f * M_PI) * freq / Fs;
    float alpha = sin(w0) * (2.f * Q);
    float cw0 = cos(w0);

    a0 = 1.f + alpha;
    b0 = (1.f + cw0) / 2.f;
    b1 = -(1.f + cos(w0));
    b2 = (1.f + cw0) / 2.f;
    a1 = -2.f * cw0;
    a2 = 1.f - alpha;
}
