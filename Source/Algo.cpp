//
// Algo.cpp
//

#define _USE_MATH_DEFINES
#include "Algo.h"

Algo::Algo() {
}

Algo::~Algo() {
}

float Algo::processSample(float x, int channel) {
    float y;
    // 4 Parallel AllPassLoops
    float outAPF9 = apf9.processSample(x, channel);
    float outAPF10 = apf10.processSample(outAPF9, channel);
    float outAPF11 = apf11.processSample(outAPF10, channel);        
    float outAPF12 = apf12.processSample(outAPF11, channel);

    float inAPF1 = outAPF12 + (-feedbackGain) * fb1[channel];
    float inAPF3 = outAPF12 + (-feedbackGain) * fb2[channel];      
    float inAPF5 = outAPF12 + (-feedbackGain) * fb3[channel];           
    float inAPF7 = outAPF12 + (-feedbackGain) * fb4[channel];

    // APF Loop 1
    float outAPF1 = apf1.processSample(inAPF1, channel);
    float outAPF2 = apf2.processSample(outAPF1, channel);
    float outDL1 = fractionalDelay1.processSample(outAPF2, channel);

    // APF Loop 2
    float outAPF3 = apf3.processSample(inAPF3, channel);
    float outAPF4 = apf4.processSample(outAPF3, channel);
    float outDL2 = fractionalDelay2.processSample(outAPF4, channel);          

    // APF Loop 3
    float outAPF5 = apf5.processSample(inAPF5, channel);
    float outAPF6 = apf6.processSample(outAPF5, channel);
    float outDL3 = fractionalDelay3.processSample(outAPF6, channel);

    // APF Loop 4
    float outAPF7 = apf7.processSample(inAPF7, channel);
    float outAPF8 = apf8.processSample(outAPF7, channel);
    float outDL4 = fractionalDelay4.processSample(outAPF8, channel);

    y = (0.25) * (outDL1 + outDL2 + outDL3 + outDL4);

    fb1[channel] = lpf1.processSample(outDL1, channel);
    fb2[channel] = lpf2.processSample(outDL2, channel);
    fb3[channel] = lpf3.processSample(outDL3, channel);
    fb4[channel] = lpf4.processSample(outDL4, channel);

    return y;
}

void Algo::setFs(float Fs) {
    this->Fs = Fs;
    fractionalDelay1.setFs(Fs);
    fractionalDelay2.setFs(Fs);
    fractionalDelay3.setFs(Fs);
    fractionalDelay4.setFs(Fs);
    apf1.setFs(Fs);
    apf2.setFs(Fs);
    apf3.setFs(Fs);
    apf4.setFs(Fs);
    apf5.setFs(Fs);
    apf6.setFs(Fs);
    apf7.setFs(Fs);
    apf8.setFs(Fs);
    apf9.setFs(Fs);
    apf10.setFs(Fs);
    apf11.setFs(Fs);
    apf12.setFs(Fs);
}

void Algo::setFeedbackGain(float feedbackGain) {
    this->feedbackGain = feedbackGain;
}

void Algo::setDiffusionGain(float diffusionGain) {
    this->diffusionGain = diffusionGain;

    // Diffusion control is set only for early reflections
    apf9.setFeedbackGain(diffusionGain);
    apf10.setFeedbackGain(diffusionGain);
    apf11.setFeedbackGain(diffusionGain);
    apf12.setFeedbackGain(diffusionGain);
}

void Algo::setDepth(float depth) {
    this->depth = depth;
    apf1.setDepth(depth);
    apf2.setDepth(depth);
    apf3.setDepth(depth);
    apf4.setDepth(depth);
    apf5.setDepth(depth);
    apf6.setDepth(depth);
    apf7.setDepth(depth);
    apf8.setDepth(depth);
    apf9.setDepth(depth);
    apf10.setDepth(depth);
    apf11.setDepth(depth);
    apf12.setDepth(depth);
    fractionalDelay1.setDepth(depth);
    fractionalDelay2.setDepth(depth);
    fractionalDelay3.setDepth(depth);
    fractionalDelay4.setDepth(depth);
}