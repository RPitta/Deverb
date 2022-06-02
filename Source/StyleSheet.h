#include <JuceHeader.h>

namespace juce
{
	class CustomLNF : public juce::LookAndFeel_V4
	{
	public:
		void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider&);
	};

	class CustomDial : public Slider
	{
	public:
		CustomDial() {
			auto rotaryParams = getRotaryParameters();
			rotaryParams.startAngleRadians = juce::MathConstants<float>::pi * 1.5f;
			rotaryParams.endAngleRadians = juce::MathConstants<float>::pi * 3.0f;
			setRotaryParameters(rotaryParams);
			setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
			setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::orange);
			setColour(juce::Slider::ColourIds::thumbColourId, findColour(juce::Slider::rotarySliderOutlineColourId));
			setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 30);
		}

	};
}
