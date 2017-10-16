#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class MainContentComponent   : public Component,
                               public Button::Listener // [1]
{
public:
    //==============================================================================
    MainContentComponent()
    {
        addAndMakeVisible (checkTheTimeButton);
        checkTheTimeButton.setButtonText ("Check the time...");
        checkTheTimeButton.addListener (this); // [7]
        
        addAndMakeVisible (timeLabel);
        timeLabel.setColour (Label::backgroundColourId, Colours::black);
        timeLabel.setColour (Label::textColourId, Colours::white);
        timeLabel.setJustificationType (Justification::centred);
        
        setSize (600, 110);
    }

    ~MainContentComponent()
    {
    }

    void resized() override
    {
        checkTheTimeButton.setBounds (10, 10, getWidth() - 20, 40);
        timeLabel.setBounds (10, 60, getWidth() - 20, 40);
    }

    void buttonClicked (Button* button) override  // [2]
    {
        if (button == &checkTheTimeButton)                                                      // [3]
        {
            const Time currentTime (Time::getCurrentTime());                                    // [4]
            
            const bool includeDate = true;
            const bool includeTime = true;
            const String currentTimeString (currentTime.toString (includeDate, includeTime));   // [5]
            
            timeLabel.setText (currentTimeString, dontSendNotification);                        // [6]
        }
    }

private:
    TextButton checkTheTimeButton;
    Label timeLabel;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
