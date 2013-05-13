// TestMode.pde : behavior functions for the test mode
// Copyright (c) 2011 Garth Zeglin

// ##BEGIN_LICENSE##
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this file; if not, write to the Free Software Foundation,
// Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
// ##END_LICENSE##
/****************************************************************/
// Valid values for test_mode.
enum { TEST_IDLE, TEST_SENSORS, TEST_MICROPHONE, TEST_LED_BLINK, TEST_EYE_OSCILLATE, TEST_NECK_OSCILLATE };

// A timer for measuring intervals during tests.
static ElapsedTimer testTimer;

// Polling function called from the main event loop when in test mode.  This
// should avoid any operation which might stall, but update state and
// return within a short interval.
void test_mode_update(void)
{
  switch( test_mode ) {

  default:
  case TEST_IDLE:
    testTimer.reset();
    break;

  case TEST_SENSORS:
    {
      Console.println("Entering sensor test.  Set test_mode to exit.");
      static int count = 0;
      while( test_mode == TEST_SENSORS ) {
	int sound = Romibo.soundLevel();
	int top   = Romibo.topLightLevel();
	int left  = Romibo.leftFrontLightLevel();
	int right = Romibo.rightFrontLightLevel();
	int range = Romibo.frontRangeDistance(); 
	int touch = Romibo.touchSwitches();

	Console.print("snd:  ");	Console.print( sound );
	Console.print( " top: " );	Console.print( top );
	Console.print( " left: " );	Console.print( left );
	Console.print( " right: " );	Console.print( right );
	Console.print( " range: " );	Console.print( range );
	Console.print( " touch: " );	Console.print( touch );
	Console.println();
	Romibo.delay(100);
      }
      Console.println("Exiting sensor test mode.");
    }
    break;


  case TEST_MICROPHONE:
    {
      Console.println("Entering microphone test.");
      static int count = 0;
      while( test_mode == TEST_MICROPHONE ) {
	int sound = Romibo.soundLevel();
	Console.print("level: ");	Console.print( sound );
	Console.print( " raw: " );	Console.print( parameters.value("microphone.raw" ) );
	Console.print( " smoothed: " );	Console.print( parameters.value("microphone.smoothed") );
	Console.print( " average: " );	Console.print( parameters.value("microphone.average") );
	Console.println();
	Romibo.delay(100);
      }
      Console.println("Exiting microphone mode.");
    }
    break;

  case TEST_LED_BLINK:
    {
      Console.println("Entering LED blink mode.");
      static int count = 0;
      while( test_mode == TEST_LED_BLINK) {
	Romibo.setAntennaColor( count & 1, count & 2, count & 4);
	count++;
	Romibo.delay(1000);
      }
      Console.println("Exiting LED blink mode.");
    }
    break;

  case TEST_EYE_OSCILLATE:  
    {
      static int eye_open_position = 0;
      if (testTimer.elapsedMilliseconds() > test_period) {
	testTimer.reset();
	if (eye_open_position <= 0)  eye_open_position = 100;
	else                         eye_open_position = 0;
	Romibo.setEyelid( eye_open_position );
      }
    }	
    break;
      
  case TEST_NECK_OSCILLATE:
    {
      static int position = 0;
      if (testTimer.elapsedMilliseconds() > test_period) {
	testTimer.reset();
	if (position <= 0)             position = 100;
	else               	       position = 0;
	Romibo.setHeadPosition( position, position );
      }
    }	
    break;

  }
}
