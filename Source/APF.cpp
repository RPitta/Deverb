//
//  APF.cpp
//

#define _USE_MATH_DEFINES
#include "APF.h"

APF::APF() {
}

APF::APF(float delay, float speed) {
    fractionalDelay.setDelaySamples(delay);
    fractionalDelay.setSpeed(speed);
}

APF::APF(float delay, float speed, float feedbackGain) {
    fractionalDelay.setDelaySamples(delay);
    fractionalDelay.setSpeed(speed);
    this->feedbackGain = feedbackGain;
}

APF::~APF() {
}

float APF::processSample(float x, int channel) {
    float y;

    float inDL1 = x + (-feedbackGain) * fb1[channel];

    float outDL1 = fractionalDelay.processSample(inDL1, channel);

    y = outDL1 + feedbackGain * inDL1;

    fb1[channel] = outDL1;

    return y;
}

void APF::setFs(float Fs) {
    this->Fs = Fs;
    fractionalDelay.setFs(Fs);
}

void APF::setFeedbackGain(float feedbackGain) {
    this->feedbackGain = feedbackGain;
}

void APF::setDepth(float depth) {
    this->depth = depth;
    fractionalDelay.setDepth(depth);
}