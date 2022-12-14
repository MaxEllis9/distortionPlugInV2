#include "FilmStripKnob.h"

viator_gui::FilmStripKnob::FilmStripKnob(int knobType, const juce::String labelSuffix, double rangeMin, double rangeMax)
: _knobType(knobType)
{
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setRange(rangeMin, rangeMax, 0.1);
    
    switch (_knobType)
    {
        case 0:
        {
            filmStrip = juce::ImageCache::getFromMemory(BinaryData::Knob_04_png, BinaryData::Knob_04_pngSize);
            frameHeight = filmStrip.getHeight() / 257;
            break;
        }
            
        case 1:
        {
            filmStrip = juce::ImageCache::getFromMemory(BinaryData::Knob_03_png, BinaryData::Knob_03_pngSize);
            frameHeight = filmStrip.getHeight() / 257;
            break;
        }
            
        case 2:
        {
            filmStrip = juce::ImageCache::getFromMemory(BinaryData::Knob_01_png, BinaryData::Knob_01_pngSize);
            frameHeight = filmStrip.getHeight() / 257;
            break;
        }
    }
    
    frameWidth = filmStrip.getWidth();
//    frameWidth = frameHeight;
    
    /** Text Box Label*/
    
    
    
    addAndMakeVisible(knobLabel);
    knobLabel.setText(juce::String (getValue(), 2) + labelSuffix, juce::dontSendNotification);
    onValueChange = [this, labelSuffix]()
    {
        juce::String suffixStr = " ";
        
        float val = getValue();
        
        if(val>999.f)
        {
            val /= 1000.f;
            suffixStr << "k" << labelSuffix;
        }
        else
        {
            suffixStr << labelSuffix;
        }
        
        
        knobLabel.setText(juce::String (val) + suffixStr, juce::dontSendNotification);
    };
    
    updateLabelColor(juce::Colours::black);
}

void viator_gui::FilmStripKnob::paint(juce::Graphics &g)
{
    const float sliderPos = (float) valueToProportionOfLength(getValue());

    int value;

    value = sliderPos * (257 - 1);
    g.drawImage(filmStrip,
                getWidth() * 0.1,
                getHeight() * 0.08,
                getWidth() * 0.8,
                getHeight() * 0.8, 0, value * frameHeight, frameWidth, frameHeight);
    
    
    
    /** Dot color*/
    g.setColour (juce::Colours::black.withAlpha(0.5f));
    auto centre = getLocalBounds().getCentre();

    /** Draw dots */
    /** How many dots to draw, works well as num dial intervals + 1 for small ranges, e.g. [0 - 10]*/
    for (int i = 0; i < 11; ++i)
    {
        auto dotSize = getWidth() * 0.025;
        
        /** IF you change the number of dots, do i / (num dots - 1) */
        float mult = 1.04;
        const auto angle = juce::jmap (i / 11.0f, getRotaryParameters().startAngleRadians * mult, getRotaryParameters().endAngleRadians * mult);
        
        /** Dot distance from slider center */
        const auto point = centre.getPointOnCircumference (getWidth() * 0.31, angle);
            
        /** Dot thickness*/
        g.fillEllipse (point.getX() - 3, point.getY() - 3 * getHeight() * 0.026, dotSize, dotSize);
    }
}

void viator_gui::FilmStripKnob::resized()
{
    knobLabel.setBounds(0,
                        getHeight() * 0.8,
                        getWidth(),
                        getHeight() * 0.25f);
}

void viator_gui::FilmStripKnob::updateLabelColor(juce::Colour newColor)
{
    knobLabel.setColour(juce::Label::ColourIds::textColourId, newColor);
}

void viator_gui::FilmStripKnob::setLabelAsInt(bool isLabelInt)
{
}
