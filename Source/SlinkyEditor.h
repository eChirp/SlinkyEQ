#pragma once

#include "SlinkyProcessor.h"

//==============================================================================
class SlinkyEditor  : public juce::AudioProcessorEditor
{
public:
    explicit SlinkyEditor (SlinkyProcessor&);
    ~SlinkyEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SlinkyProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SlinkyEditor)
};
