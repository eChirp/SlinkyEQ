#include "SlinkyProcessor.h"
#include "SlinkyEditor.h"

//==============================================================================
SlinkyProcessor::SlinkyProcessor()
	: AudioProcessor (
		BusesProperties()
			.withInput ( "Input",
				juce::AudioChannelSet::stereo() )
			.withOutput ( "Output",
				juce::AudioChannelSet::stereo() ) )
{
	addParameter ( gain = new juce::AudioParameterFloat (
					   juce::ParameterID ( "gain", 1 ),
					   "Gain",
					   0.0f,
					   1.0f,
					   1.0f ) );
}

SlinkyProcessor::~SlinkyProcessor() {}

//==============================================================================
const juce::String SlinkyProcessor::getName() const
{
	return JucePlugin_Name;
}

bool SlinkyProcessor::acceptsMidi() const { return false; }

bool SlinkyProcessor::producesMidi() const { return false; }

bool SlinkyProcessor::isMidiEffect() const { return false; }

double SlinkyProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int SlinkyProcessor::getNumPrograms()
{
	return 1; // NB: some hosts don't cope very well if you tell them there are 0
		// programs, so this should be at least 1, even if you're not
		// really implementing programs.
}

int SlinkyProcessor::getCurrentProgram() { return 0; }

void SlinkyProcessor::setCurrentProgram ( int index )
{
	juce::ignoreUnused ( index );
}

const juce::String SlinkyProcessor::getProgramName ( int index )
{
	juce::ignoreUnused ( index );
	return {};
}

void SlinkyProcessor::changeProgramName ( int index,
	const juce::String& newName )
{
	juce::ignoreUnused ( index, newName );
}

//==============================================================================
void SlinkyProcessor::prepareToPlay ( double sampleRate,
	int samplesPerBlock )
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	juce::ignoreUnused ( sampleRate, samplesPerBlock );
}

void SlinkyProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

bool SlinkyProcessor::isBusesLayoutSupported (
	const BusesLayout& layouts ) const
{
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if ( layouts.getMainOutputChannelSet()
			 != juce::AudioChannelSet::mono()
		 && layouts.getMainOutputChannelSet()
				!= juce::AudioChannelSet::stereo() )
		return false;

	// This checks if the input layout matches the output layout
	if ( layouts.getMainOutputChannelSet()
		 != layouts.getMainInputChannelSet() )
		return false;

	return true;
}

void SlinkyProcessor::processBlock (
	juce::AudioBuffer< float >& buffer,
	juce::MidiBuffer& midiMessages )
{
	juce::ignoreUnused ( midiMessages );

	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for ( auto i = totalNumInputChannels;
		  i < totalNumOutputChannels;
		  ++i )
		buffer.clear ( i, 0, buffer.getNumSamples() );

	buffer.applyGain ( (float) *gain );

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	// Make sure to reset the state if your inner loop is processing
	// the samples and the outer loop is handling the channels.
	// Alternatively, you can process the samples with the channels
	// interleaved by keeping the same state.
	for ( int channel = 0; channel < totalNumInputChannels;
		  ++channel )
	{
		auto* channelData = buffer.getWritePointer ( channel );
		juce::ignoreUnused ( channelData );
		// ..do something to the data...
	}
}

//==============================================================================
bool SlinkyProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* SlinkyProcessor::createEditor()
{
	return new SlinkyEditor ( *this );
}

//==============================================================================
void SlinkyProcessor::getStateInformation (
	juce::MemoryBlock& destData )
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
	juce::ignoreUnused ( destData );
}

void SlinkyProcessor::setStateInformation ( const void* data,
	int sizeInBytes )
{
	// You should use this method to restore your parameters from this memory
	// block, whose contents will have been created by the getStateInformation()
	// call.
	juce::ignoreUnused ( data, sizeInBytes );
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new SlinkyProcessor();
}
