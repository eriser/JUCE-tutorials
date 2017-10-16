#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class MainContentComponent   : public AudioAppComponent
{
public:
    MainContentComponent()
    {
        leftLevelSlider.setRange (0.0, 0.25);
        leftLevelSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
        leftLevelLabel.setText ("Left", dontSendNotification);
        
        addAndMakeVisible (leftLevelSlider);
        addAndMakeVisible (leftLevelLabel);
        
        rightLevelSlider.setRange (0.0, 0.25);
        rightLevelSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
        rightLevelLabel.setText ("Right", dontSendNotification);
        
        addAndMakeVisible (rightLevelSlider);
        addAndMakeVisible (rightLevelLabel);
        
        setSize (600, 100);
        setAudioChannels (0, 2);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    void prepareToPlay (int /*samplesPerBlockExpected*/, double /*sampleRate*/) override
    {
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        const float leftLevel = (float) leftLevelSlider.getValue();
        const float rightLevel = (float) rightLevelSlider.getValue();
        
        float* const leftBuffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            const float noise = random.nextFloat() * 2.0f - 1.0f;
            leftBuffer[sample] = noise * leftLevel;
        }
        
        float* const rightBuffer = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            const float noise = random.nextFloat() * 2.0f - 1.0f;
            rightBuffer[sample] = noise * rightLevel;
        }
    }
    
    void releaseResources() override
    {
    }

    void resized() override
    {
        leftLevelLabel.setBounds (10, 10, 90, 20);
        leftLevelSlider.setBounds (100, 10, getWidth() - 110, 20);
        
        rightLevelLabel.setBounds (10, 30, 90, 20);
        rightLevelSlider.setBounds (100, 30, getWidth() - 110, 20);
    }
    

private:
    Random random;
    Slider leftLevelSlider;
    Label leftLevelLabel;
    Slider rightLevelSlider;
    Label rightLevelLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
