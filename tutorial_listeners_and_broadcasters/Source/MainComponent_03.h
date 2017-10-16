#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class MainContentComponent   : public Component,
                               public Button::Listener
{
public:
    //==============================================================================
    MainContentComponent()
        : latestTime (Time::getCurrentTime())
    {
        addAndMakeVisible (checkTheTimeButton);
        checkTheTimeButton.setButtonText ("Check the time...");
        checkTheTimeButton.addListener (this);
        
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

    void buttonClicked (Button* button) override
    {
        if (button == &checkTheTimeButton)
        {
            const Time currentTime (Time::getCurrentTime());
            const RelativeTime timeDifference (currentTime - latestTime);
            const String timeDifferenceString (String (timeDifference.inMilliseconds()) + " milliseconds");
            
            timeLabel.setText (timeDifferenceString, dontSendNotification);
            latestTime = currentTime;
        }
    }

private:
    TextButton checkTheTimeButton;
    Label timeLabel;
    Time latestTime;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
