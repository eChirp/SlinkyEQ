#include <SlinkyProcessor.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE ( "Plugin instance name", "[interface]" )
{
	SlinkyProcessor testPlugin;

	CHECK_THAT ( testPlugin.getName().toStdString(),
		Catch::Matchers::Equals ( "Slinky EQ" ) );
}

TEST_CASE ( "Plugin channel count", "[interface]" )
{
	SlinkyProcessor testPlugin;

	CHECK ( testPlugin.getNumInputChannels() == 2 );
	CHECK ( testPlugin.getNumOutputChannels() == 2 );
}

TEST_CASE ( "Midi rejection", "[interface]" )
{
	SlinkyProcessor testPlugin;

	CHECK ( testPlugin.isMidiEffect() == false );
	CHECK ( testPlugin.acceptsMidi() == false );
	CHECK ( testPlugin.producesMidi() == false );
}

TEST_CASE ( "Plugin Parameters", "[interface]" )
{
	SlinkyProcessor testPlugin;

	CHECK ( testPlugin.getParameterName ( 0 ) == "Gain" );
	CHECK ( testPlugin.getParameterName ( 1 )
			== "HighPassFrequency" );
}
