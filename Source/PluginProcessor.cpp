/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AlgoReverbAudioProcessor::AlgoReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
                #if ! JucePlugin_IsMidiEffect
                #if ! JucePlugin_IsSynth
                .withInput("Input", juce::AudioChannelSet::stereo(), true)
                #endif
                .withOutput("Output", juce::AudioChannelSet::stereo(), true)
                #endif
    ),

    parameters{ *this, nullptr, "Parameters", createParameters()}
#endif
{
}

AlgoReverbAudioProcessor::~AlgoReverbAudioProcessor()
{
}

//==============================================================================
const juce::String AlgoReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AlgoReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AlgoReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AlgoReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AlgoReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AlgoReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AlgoReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AlgoReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AlgoReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void AlgoReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AlgoReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    predelay.setFs(sampleRate);
    predelay.setDelaySamples(0.0f);
    algo.setFs(sampleRate);

    lpf.setFs(sampleRate);
    Fs = sampleRate;
}

void AlgoReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AlgoReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AlgoReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    predelay.setDepth(0.0f);
    predelay.setSpeed(0.0f);

    float predelaySec = predelayMS * 0.001;
    float predelaySamples = predelaySec * Fs;

    predelay.setDelaySamples(predelaySamples);

    algo.setFeedbackGain(timeValue);
    algo.setDiffusionGain(diffusionValue);
    algo.setDepth(modValue);
    lpf.setFrequency(lpfFreqValue);
    hpf.setFrequency(hpfFreqValue);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for (int n = 0; n < buffer.getNumSamples(); ++n) {
            float x = buffer.getWritePointer(channel)[n];
            float verb = predelay.processSample(x, channel);
            verb = algo.processSample(verb, channel);
            verb = lpf.processSample(verb, channel);
            verb = hpf.processSample(verb, channel);
            float y = (1.f - wet) * x + wet * verb;
            buffer.getWritePointer(channel)[n] = y;
        }
    }
}

//==============================================================================
bool AlgoReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AlgoReverbAudioProcessor::createEditor()
{
    return new AlgoReverbAudioProcessorEditor (*this);
}

//==============================================================================
void AlgoReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void AlgoReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlgoReverbAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout AlgoReverbAudioProcessor::createParameters() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    juce::NormalisableRange<float> timeRange(0.3f, 6.8f, 0.01f);
    juce::NormalisableRange<float> modRange(3.f, 10.f, 0.01f);
    juce::NormalisableRange<float> wetDryRange(0.0f, 1.0f, 0.01f);
    juce::NormalisableRange<float> predelayRange(0.f, 200.0f, 0.01f);
    juce::NormalisableRange<float> diffusionRange(0.2f, 0.8f, 0.01f);
    juce::NormalisableRange<float> lpfRange(1000.f, 20000.f, 1.f);
    juce::NormalisableRange<float> hpfRange(0.0f, 625.f, 1.f);


    params.push_back(std::make_unique<juce::AudioParameterFloat>("TIME", "Time", timeRange, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("MODULATION", "Mod", modRange, 3.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WETDRY", "Wet/Dry", wetDryRange, 0.50f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PREDELAY", "Predelay", predelayRange, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DIFFUSION", "Diffusion", diffusionRange, 0.20f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LOWPASS", "LPF", lpfRange, 10000.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("HIGHPASS", "HPF", hpfRange, 0.0f));

    return { params.begin(), params.end() };
}


