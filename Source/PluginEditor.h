/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "StyleSheet.h"

//==============================================================================
/**
*/
class AlgoReverbAudioProcessorEditor : public juce::AudioProcessorEditor,
                                       public juce::Slider::Listener 
{
public:
    AlgoReverbAudioProcessorEditor(AlgoReverbAudioProcessor&);
    ~AlgoReverbAudioProcessorEditor();

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AlgoReverbAudioProcessor& processor;

    juce::Image background;

    juce::CustomDial reverbTimeDial;
    juce::CustomDial modulationDial;
    juce::CustomDial wetDryDial;
    juce::CustomDial predelayDial;
    juce::CustomDial diffusionDial;
    juce::CustomDial lpfDial;
    juce::CustomDial hpfDial;

    juce::Label wetDryLabel;
    juce::Label modulationLabel;
    juce::Label reverbTimeLabel;

    juce::Label predelayLabel;
    juce::Label diffusionLabel;
    juce::Label lpfLabel;
    juce::Label hpfLabel;

    juce::CustomLNF myCustomLNF;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> timeAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> modAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> wetDryAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> predelayAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> diffusionAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lpfAttach;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> hpfAttach;


public:


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AlgoReverbAudioProcessorEditor)
};
