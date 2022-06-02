/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FractionalDelay.h"
#include "APF.h"
#include "Algo.h"
#include "LPF.h"
#include "HPF.h"

//==============================================================================
/**
*/
class AlgoReverbAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    AlgoReverbAudioProcessor();
    ~AlgoReverbAudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    // Holds the list of our parameters
    juce::AudioProcessorValueTreeState parameters;

    float predelayMS = 0.0f;
    float wet = 0.5f;
    float timeValue = 0.5f;
    float modValue = 3.f;
    float diffusionValue = 0.2f;
    float lpfFreqValue = 10000.f;
    float hpfFreqValue = 0.f;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout AlgoReverbAudioProcessor::createParameters();
    FractionalDelay predelay;
    Algo algo;
    LPF lpf;
    HPF hpf;

    float Fs = 44100.f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AlgoReverbAudioProcessor)
};
