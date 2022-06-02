//
//  Algo.h
//
#define _USE_MATH_DEFINES
#ifndef Algo_h
#define Algo_h

#include "APF.h"
#include <vector>

using namespace std;

class Algo {

public:

    // Constructor function (special function - no return type, name = Class name)
    Algo();

    // Destructor
    ~Algo();

    float processSample(float x, int channel);

    void setFs(float Fs);

    void setFeedbackGain(float feedbackGain);

    void setDiffusionGain(float diffusionGain);

    void setDepth(float depth);

private:
    float Fs = 48000.f;

    class SimpleLPF {
    public:
        float processSample(float x, int channel) {
            float y = 0.5 * x + 0.5 * ff[channel];
            ff[channel] = x;
            return y;
        };

    private:
        float ff[2] = { 0.f };
    };

    APF apf1{ 241.f, 0.712};         APF apf2{ 83.f, 0.967f, -0.15f };
    APF apf3{ 347.f, 0.332f};        APF apf4{ 139.f, 0.733f, -0.15f };
    APF apf5{ 199.f, 0.971f};        APF apf6{ 89.f, 0.25f, -0.15f };
    APF apf7{ 251.f, 0.76f};         APF apf8{ 113.f, 0.92f, -0.15f };
    APF apf9{ 157.f, 0.845f, .15f }; APF apf10{ 223.f, 0.5821f, .15f };
    APF apf11{ 277.f, 0.61f, .15f }; APF apf12{ 379.f, 0.34f, .15f };

    FractionalDelay fractionalDelay1 { 2053.f, 0.7f };
    FractionalDelay fractionalDelay2 { 1973.f, 0.9f };             
    FractionalDelay fractionalDelay3 { 1426.f, 0.8f };
    FractionalDelay fractionalDelay4 { 1733.f, 0.75f };

    SimpleLPF lpf1;
    SimpleLPF lpf2;
    SimpleLPF lpf3;
    SimpleLPF lpf4;

    float feedbackGain = 0.5f;
    float diffusionGain = 0.5f;

    float fb1[2] = { 0.f };
    float fb2[2] = { 0.f };
    float fb3[2] = { 0.f };
    float fb4[2] = { 0.f };

    float depth = 10.0f; // percentage of intensity, control amp of LFO
};

#endif /* Algo_h */