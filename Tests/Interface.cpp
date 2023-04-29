#include <SlinkyProcessor.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

// https://github.com/McMartin/FRUT/issues/490#issuecomment-663544272
SlinkyProcessor testPlugin;

TEST_CASE ( "Plugin instance name", "[interface]" )
{
	CHECK_THAT ( testPlugin.getName().toStdString(),
		Catch::Matchers::Equals ( "Slinky EQ" ) );
}

TEST_CASE ( "Plugin channel count", "[interface]" )
{
	CHECK ( testPlugin.getNumInputChannels() == 2 );
	CHECK ( testPlugin.getNumOutputChannels() == 2 );
}

TEST_CASE ( "Midi rejection", "[interface]" )
{
	CHECK ( testPlugin.isMidiEffect() == false );
	CHECK ( testPlugin.acceptsMidi() == false );
	CHECK ( testPlugin.producesMidi() == false );
}
