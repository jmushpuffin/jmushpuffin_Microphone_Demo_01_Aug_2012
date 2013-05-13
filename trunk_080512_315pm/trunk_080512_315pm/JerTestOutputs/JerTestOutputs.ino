 // Based on romibotest.ino : A simple user program that calls romibo library functions, intended to
//   be used to get familiar with the RomiboRobot library.
// Copyright (c) 2012 John Frens
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
/****************************************************************/
// This sketch is intended to test the minimal requirements for using the Romibo
// libraries.

#include <RomiboSound.h>  
#include <RomiboRobot.h>
#include <ConsoleOutput.h>
#include <RomiboPinMappings.h>
#include <RomiboConfig.h>
//#include <Romibo.h>
//#include <Romibo.h>
//#include <Romibo.h>
/****************************************************************/
// Declare the default parameter table object.
#include <Parameters.h>
Parameters parameters( NULL, 0 );

// Define a polled serial output stream.
ConsoleOutput Console;  

int up = 95;
int down = 5;
/****************************************************************/
static const char *sounds[] = {
  "HAPPY1",
  "HAPPY2",
  "HAPPY3",
  "ANGRY1",
  "ANGRY2",
  "ANGRY3",
  "SAD1",
  "SAD2",
  "SAD3",
  "SAD4",
  "SAD5",
  "SAD6",
  "BECKON1",
  "BECKON2",
  "BECKON3",
  "BECKON4",
  "BECKON5",
  "BECKON6",
  "AWESOME",
  "GOODBYE",
  "HELLO",
  "LETSPLA1",
  "LETSPLA2",
  "PLAYWME",
  "QUEST1",
  "QUEST2",
  "POWERON",
  "DIGIT0",
  "DIGIT1",
  "DIGIT2",
  "DIGIT3",
  "DIGIT4",
  "DIGIT5",
  "DIGIT6",
  "DIGIT7",
  "DIGIT8",
  "DIGIT9",
  
};

/*void playallsounds()
{
  int len = 37;
  Romibo.waitForSoundToFinish ();
  for (int i = 0; i < len; i++) {
      Romibo.playSoundNamed (sounds[i]);
      Romibo.waitForSoundToFinish ();
      if (i % 3 == 2) {
        delay (2000);
      }
  }
*///}


void setup(void) 
{
  Serial.begin(57600);
  Serial1.begin(9600);
  // Initialize the Romibo system and attach it to the hardware.
  Romibo.begin();
  // Add the low-level variables to the user interface for debugging.
  parameters.addParameters( Romibo.parameters_table(), Romibo.parameters_table_size());
  //Romibo.delay (1000); // sleeps while processing i/o for 3 seconds
} 

void loop( void )
{
  //////////////////////////////////////////////////////
  //Outputs::
  //Working:     LED, drive, speaker
  //Not Working: All Servos
  // Chat with John, No related Issue entry found on Site
  //////////////////////////////////////////////////////
  //Romibo.setDriveMotor(LEFT,  (steer > 0), 255);
   
  /*Romibo.setNeutralHeadPosition ();
  Romibo.playSoundNamed ( "AWESOME" );
  Romibo.waitForSoundToFinish ();
  
  Romibo.setEyelid (up);
  Romibo.setHeadPosition (down, down);
  Romibo.setAntennaColor (0, 0, 255); // 
  Romibo.drive (60, -60);
  Romibo.delay (2000);
    
  Romibo.setEyelid (down);
  Romibo.setHeadPosition (up, down);
  Romibo.setAntennaColor (255, 0, 0); // 
  Romibo.drive (0, 0);
  Romibo.delay (2000);
    
  Romibo.setEyelid (50);
  Romibo.setHeadPosition (up, up);
  Romibo.setAntennaColor (255, 255, 255); // 
  Romibo.drive (0, 0);
  *///Romibo.delay (2000);
  
  ///////////////////////////////////////////////////////
  //Inputs::    
  //Working:    Switch,
  //Not Working: 
  //Unknown:    
  ///////////////////////////////////////////////////////
  /*
  /////// RomiboRobot.cpp:
  unsigned RomiboRobot::sensorSamples(void)   { return cycle_count; }

int RomiboRobot::frontRangeDistance(void)   { poll(); return range.scaled; }
int RomiboRobot::topLightLevel(void)        { poll(); return photo_top.scaled; }
int RomiboRobot::leftFrontLightLevel(void)  { poll(); return photo_left.scaled; }
int RomiboRobot::rightFrontLightLevel(void) { poll(); return photo_right.scaled; }
int RomiboRobot::soundLevel(void)           { poll(); return microphone.scaled; }

int RomiboRobot::obstacleProximity(void)    { poll();  return discretized_sensor_value( &range ); }
int RomiboRobot::topBrightness(void)        { poll();  return discretized_sensor_value( &photo_top ); }
int RomiboRobot::leftBrightness(void)       { poll();  return discretized_sensor_value( &photo_left ); }
int RomiboRobot::rightBrightness(void)      { poll();  return discretized_sensor_value( &photo_right ); }

int RomiboRobot::frontLightHeading(void) { return 0; }

// FIXME: the switch inputs should be properly debounced from the polling cycle.
// But be careful, this might be called before polling begins.

// Return true if the given switch is pressed.
int RomiboRobot::touchSwitch(int switchnum) 
  ///////
  
  int light = Romibo.topBrightness();
  int dir = 6 * (Romibo.rightFrontLightLevel() - Romibo.leftFrontLightLevel());
  boolean pet = (Romibo.touchSwitches() != 0);
  int range = Romibo.obstacleProximity(); //CLOSE,MEDIUM,FAR
  
  //Func In libraries/RomiboRobot/RomiboRobot.ccp
  microphone.raw = analogRead( microphone_pin ) << 5; 
  microphone.max
  microphone.min
  microphone.average
  microphone.smoothed
  microphone.scaled
  normalized
  
  //analog inputs: photo_left,photo_right,photo_top ?,range,microphone 
  (Romibo.touchSwitches() != 0)
  (startLightAngle < 0)
  (Romibo.obstacleProximity () < 1)  
  //in L/RR/RRcpp "int RomiboRobot::rightFrontLightLevel(void) { poll(); return photo_right.scaled; }"
  (Romibo.rightFrontLightLevel() 
  (Romibo.leftFrontLightLevel()
  (Romibo.topLightLevel()
  */
  Romibo.setAntennaColor (255, 255, 255); // White
  Romibo.playSoundNamed ( "HAPPY1" );
  Romibo.waitForSoundToFinish ();
  Romibo.delay (1000);
  
  //Romibo.poll(); // Update i/o,...
  
  if(Romibo.soundLevel() < 10){       // Romibo.soundLevel()//microphone.scaled
  Romibo.setAntennaColor (255, 0, 0); // Var not reading in at all, never goes RED
  Romibo.delay (1000);
  }
  if(Romibo.obstacleProximity() < 127){
  Romibo.setAntennaColor (0, 255, 0); // 
  Romibo.delay (1000);
  }
  if(Romibo.topLightLevel() > 127){
  Romibo.setAntennaColor (0, 0, 255); //
  Romibo.delay (1000); 
  }
  if(Romibo.leftFrontLightLevel() > 127){
  Romibo.setAntennaColor (255, 0, 0); // Flakey
  Romibo.delay (1000); 
  }
  if(Romibo.rightFrontLightLevel() > 127){
  Romibo.setAntennaColor (0, 255, 0); // Flakey
  Romibo.delay (1000);
  }
  if(Romibo.touchSwitches() != 0){
  Romibo.setAntennaColor (0, 0, 255); // Working
  Romibo.delay (1000);
  }
  
  /////////////////////////////////////////////
  //TimeFuncs::
  ////////////////////////////////////////////
  //if ((loop_count % 20) == 0) Console.print(".");
  
  
  
  
  
  // Update the robot inputs and outputs.
  //Romibo.poll();
  
  //Serial.print ("TopLightLevel: ");
  //Serial.println( Romibo.topLightLevel() ); 
  /*Serial.print ("LeftLightLevel: ");
  Serial.println(Romibo.leftFrontLightLevel());
  Serial.print ("RightLightLevel: ");
  Serial.println( Romibo.rightFrontLightLevel() );
  Serial.print ("FrontRangeDistance: ");
  Serial.println( Romibo.frontRangeDistance() );
  Serial.print ("touchSwitches: ");
  *///Serial.println( Romibo.touchSwitches() );
  
  ////playallsounds();  

  Romibo.delay (300);
  
}
