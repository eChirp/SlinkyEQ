#include <SlinkyProcessor.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <juce_dsp/juce_dsp.h>

class testFixture
{
public:
	testFixture()
	{
		parameter = processor.getParameters();
		buffer = new juce::AudioBuffer< float > ( 2, 1024 );
	}
	~testFixture() {}

	void setSamplingRate ( int rate ) { samplingRate = rate; }

	void fillBufferWithSine ( float frequency ) {}

protected:
	SlinkyProcessor processor;

	juce::Array< juce::AudioProcessorParameter* > parameter;

	juce::AudioBuffer< float >* buffer;

	juce::MidiBuffer midiBuffer;

	int samplingRate;

private:
	juce::dsp::Oscillator< float > oscillator = {
		[] ( float x ) { return std::sin ( x ); }
	};
};

TEST_CASE_METHOD ( testFixture, "Apply Gain", "[processing]" )
{
	float gainValue = GENERATE ( 1.0f, 0.5f );
	parameter.getReference ( 0 )->setValue ( gainValue );

	int bufferSize = GENERATE ( 16 );
	int diracSample = GENERATE ( 15 );

	buffer->setSample ( 0, diracSample, 1.0f );
	buffer->setSample ( 1, diracSample, -1.0f );

	processor.processBlock ( *buffer, midiBuffer );

	CHECK ( buffer->getSample ( 0, diracSample ) == gainValue );
	CHECK ( buffer->getSample ( 1, diracSample ) == -gainValue );
}

TEST_CASE_METHOD ( testFixture, "Apply Notch", "[processing]" )
{
	// parameter.getReference ( 1 )->setValue ( gainValue );
}