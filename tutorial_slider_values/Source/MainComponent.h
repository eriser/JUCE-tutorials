#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


class MainContentComponent   : public Component,
                               public Slider::Listener
{
public:
    //==============================================================================
    MainContentComponent()
    {
        addAndMakeVisible (frequencySlider);
        frequencySlider.setRange (50, 5000.0);          // [1]
        frequencySlider.setTextValueSuffix (" Hz");     // [2]
        frequencySlider.addListener (this);             // [3]
        frequencySlider.setTextBoxStyle (Slider::TextBoxLeft, false, 160, frequencySlider.getTextBoxHeight());
        frequencySlider.setSkewFactorFromMidPoint (500);
        
        addAndMakeVisible (frequencyLabel);
        frequencyLabel.setText ("Frequency", dontSendNotification);
        frequencyLabel.attachToComponent (&frequencySlider, true); // [4]
        
        addAndMakeVisible (durationSlider);
        durationSlider.setRange (1.0 / frequencySlider.getMaximum(),
                                 1.0 / frequencySlider.getMinimum());
        durationSlider.setTextValueSuffix (" s");
        durationSlider.addListener (this);
        durationSlider.setTextBoxStyle (Slider::TextBoxLeft, false, 160, durationSlider.getTextBoxHeight());
        durationSlider.setSkewFactorFromMidPoint (0.002);
        
        addAndMakeVisible (durationLabel);
        durationLabel.setText ("Duration", dontSendNotification);
        durationLabel.attachToComponent (&durationSlider, true);
       
        frequencySlider.setValue (500.0); // [5]
        
        setSize (600, 90);
    }
    
    ~MainContentComponent()
    {
    }

    void resized() override
    {
        const int sliderLeft = 120;
        frequencySlider.setBounds (sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
        durationSlider.setBounds (sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
    }

    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &frequencySlider)
            durationSlider.setValue (1.0 / frequencySlider.getValue(), dontSendNotification);
        else if (slider == &durationSlider)
            frequencySlider.setValue (1.0 / durationSlider.getValue(), dontSendNotification);
    }

private:
    Slider frequencySlider;
    Label frequencyLabel;
    Slider durationSlider;
    Label durationLabel;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
