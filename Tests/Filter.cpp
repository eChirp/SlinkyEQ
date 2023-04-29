#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <equalizer/equalizer.h>

TEST_CASE ( "Chebyshev1 BandStop", "[filter]" )
{
	Dsp::SimpleFilter< Dsp::ChebyshevI::BandStop< 6 >, 2 > f;
	f.setup ( 3, // order
		48000, // sample rate
		4000, // center frequency
		880, // band width
		1 ); // ripple dB

	CHECK ( f.getPoleZeros().size() == 3 );
}