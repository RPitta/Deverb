//
//  HPF.hpp
//

#define _USE_MATH_DEFINES
#ifndef HPF_h
#define HPF_h 
#include <math.h>

using namespace std;

class HPF {

public:

    // Constructor function (special function - no return type, name = Class name)
    HPF();

    // Destructor
    ~HPF();

    float processSample(float x, int channel);

    void setFs(float Fs);
    
    void setFrequency(float newFreq);

    void setDepth(float depth);

    void updateCoefficients();


private:
    float Fs = 48000.f;

    float freq = 20.f;
    const float Q = 0.7071f; // Q value that allows for a flat pass band

    float x1[2] = { 0.f };
    float x2[2] = { 0.f };
    float y1[2] = { 0.f };
    float y2[2] = { 0.f };

    float b0 = 1.f; float b1 = 0.f; float b2 = 0.f;
    float a0 = 1.f; float a1 = 0.f; float a2 = 0.f;
};

#endif /* HPF_h */