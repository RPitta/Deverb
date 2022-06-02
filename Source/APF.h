//
//  APF.h
//

#define _USE_MATH_DEFINES
#ifndef APF_h
#define APF_h 

#include "FractionalDelay.h"
using namespace std;

class APF {

public:

    APF();

    APF(float delay, float speed);

    APF(float delay, float speed, float feedbackGain);

    ~APF();

    float processSample(float x, int channel);

    void setFs(float Fs);

    void setDelay(float delay) { fractionalDelay.setDelaySamples(delay); };

    void setSpeed(float speed) { fractionalDelay.setSpeed(speed); };
    
    void setFeedbackGain(float timeValue);

    void setDepth(float depth);


private:
    float Fs = 48000.f;

    FractionalDelay fractionalDelay{ 240.f, 0.7f };

    //float feedbackGain = 0.5f;
    // TODO: Try larger values for feedbackGain that don't produce feedback
    // TODO: Try different feedbackGains for each APF

    float feedbackGain = 0.15f;

    float fb1[2] = { 0.f };

    float depth = 10.0f; // percentage of intensity, control amp of LFO
};

#endif /* APF_h */