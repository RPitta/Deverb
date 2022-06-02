#include "StyleSheet.h"

namespace juce
{
	void CustomLNF::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) 
	{
        auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
        auto fill = slider.findColour(Slider::rotarySliderFillColourId);

        auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

        auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin(8.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        // Dial background path
        Path backgroundArc;
        backgroundArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour(outline);
        g.strokePath(backgroundArc, PathStrokeType(lineW * 0.4f, PathStrokeType::curved, PathStrokeType::rounded));

        if (slider.isEnabled())
        {
            // Dial fill path
            Path valueArc;
            valueArc.addCentredArc(bounds.getCentreX(),
                bounds.getCentreY(),
                arcRadius,
                arcRadius,
                0.0f,
                rotaryStartAngle,
                toAngle,
                true);

            g.setColour(fill);
            g.strokePath(valueArc, PathStrokeType(lineW * 0.4f, PathStrokeType::curved, PathStrokeType::rounded));
        }

        // Thumb 
        auto thumbWidth = lineW * 2.0f;
        Point<float> thumbPoint(bounds.getCentreX() + (arcRadius - 3.0f) * std::cos(toAngle - MathConstants<float>::halfPi),
                                bounds.getCentreY() + (arcRadius - 3.0f) * std::sin(toAngle - MathConstants<float>::halfPi));

        g.setColour(slider.findColour(Slider::thumbColourId));
        g.drawLine(backgroundArc.getBounds().getCentreX(), backgroundArc.getBounds().getCentreY(), thumbPoint.getX(), thumbPoint.getY(), lineW * 0.4f);
	}
	
}