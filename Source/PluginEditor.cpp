/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AlgoReverbAudioProcessorEditor::AlgoReverbAudioProcessorEditor (AlgoReverbAudioProcessor& p) : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    // This is what's allocating mem on the heap for our dial attachment

    juce::LookAndFeel::setDefaultLookAndFeel (&myCustomLNF);
    setSize (600, 300);

    // Reverb time dial
    reverbTimeDial.addListener(this);
    addAndMakeVisible(reverbTimeDial);
    timeAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "TIME", reverbTimeDial );

    reverbTimeLabel.setText("Time", juce::dontSendNotification);
    reverbTimeLabel.attachToComponent(&reverbTimeDial, false);
    reverbTimeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(reverbTimeLabel);

    // Modulation Dial
    modulationDial.addListener(this);
    addAndMakeVisible(modulationDial);
    modAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "MODULATION", modulationDial);

    modulationLabel.setText("Mod", juce::dontSendNotification);
    modulationLabel.attachToComponent(&modulationDial, false);
    modulationLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(modulationLabel);

    // Wet/dry dial
    wetDryDial.addListener(this);
    addAndMakeVisible(wetDryDial);
    wetDryAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "WETDRY", wetDryDial);

    wetDryLabel.setText("Wet/Dry", juce::dontSendNotification);
    wetDryLabel.attachToComponent(&wetDryDial, false);
    wetDryLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(wetDryLabel);

    // Predelay dial
    predelayDial.addListener(this);
    addAndMakeVisible(predelayDial);
    predelayAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "PREDELAY", predelayDial);

    predelayLabel.setText("Predelay", juce::dontSendNotification);
    predelayLabel.attachToComponent(&predelayDial, false);
    predelayLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(predelayLabel);

    // Diffusion dial
    diffusionDial.addListener(this);
    addAndMakeVisible(diffusionDial);
    diffusionAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "DIFFUSION", diffusionDial);

    diffusionLabel.setText("Diffusion", juce::dontSendNotification);
    diffusionLabel.attachToComponent(&diffusionDial, false);
    diffusionLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(diffusionLabel);

    // LPF Dial
    lpfDial.addListener(this);
    addAndMakeVisible(lpfDial);
    lpfAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "LOWPASS", lpfDial);

    lpfLabel.setText("LPF", juce::dontSendNotification);
    lpfLabel.attachToComponent(&lpfDial, false);
    lpfLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lpfLabel);

    // HPF Dial
    hpfDial.addListener(this);
    addAndMakeVisible(hpfDial);
    hpfAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "HIGHPASS", hpfDial);

    hpfLabel.setText("HPF", juce::dontSendNotification);
    hpfLabel.attachToComponent(&hpfDial, false);
    hpfLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(hpfLabel);
}

AlgoReverbAudioProcessorEditor::~AlgoReverbAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel (nullptr); 
}

//==============================================================================
void AlgoReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    background = juce::ImageCache::getFromMemory(BinaryData::deverbBg_png, BinaryData::deverbBg_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
}

void AlgoReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    reverbTimeDial.setBounds(50, 30, 100, 100);
    modulationDial.setBounds(150, 30, 100, 100);
    wetDryDial.setBounds(250, 30, 100, 100);
    predelayDial.setBounds(50, 175, 100, 100);
    diffusionDial.setBounds(150, 175, 100, 100);
    lpfDial.setBounds(350, 175, 100, 100);
    hpfDial.setBounds(250, 175, 100, 100);

}

void AlgoReverbAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    if (slider == &reverbTimeDial) {
        float revTimeSec = reverbTimeDial.getValue();
        float revTimeNorm = (revTimeSec - 0.3f) / 6.5f;
        float revTimeGain = revTimeNorm * 0.55f + 0.4f;
        processor.timeValue = revTimeGain;
    }

    if (slider == &predelayDial) {
        processor.predelayMS = predelayDial.getValue();
    }

    if (slider == &wetDryDial) {
        processor.wet = wetDryDial.getValue();
    }

    if (slider == &modulationDial) {
        processor.modValue = modulationDial.getValue();
    }
    
    if (slider == &diffusionDial) {
        processor.diffusionValue = diffusionDial.getValue();
    }

    if (slider == &lpfDial) {
        processor.lpfFreqValue = lpfDial.getValue();
    }

    if (slider == &hpfDial) {
        processor.hpfFreqValue = hpfDial.getValue();
    }
}
