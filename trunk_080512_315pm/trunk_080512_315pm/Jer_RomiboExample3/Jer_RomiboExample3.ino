// Jer_RomiboExample2.ino : 
// -drives in response to audioLevel
//
// Copyright (c) 2012 Jeremy Romeiko, Garth Zeglin
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
// This sketch is intended to test the minimal requirements for using the Romibo
// libraries.

#include <RomiboSound.h>  
#include <RomiboRobot.h>
//#include "ConsoleOutput.h"
//------------------------
#include <ConsoleOutput.h>

#include <RomiboPinMappings.h>
#include <RomiboConfig.h>
#include <Romibo.h>
//------------------------
int up=95,down=5;
int Shhh=45, ComeHere=55, Boo=85;
/****************************************************************/
// Declare the default parameter table object.
#include <Parameters.h>
Parameters parameters( NULL, 0 );

// Define a polled serial output stream.
ConsoleOutput Console;  

/****************************************************************/
void setup(void) 
{
  Serial.begin(57600);
  Serial1.begin(9600);

  // Initialize the Romibo system and attach it to the hardware.
  Romibo.begin();

  // Add the low-level variables to the user interface for debugging.
  parameters.addParameters( Romibo.parameters_table(), Romibo.parameters_table_size());

  Serial.println("INITIALIZED");
}

void loop( void )
{
  // Update the robot inputs and outputs.
  Romibo.poll();
  Romibo.delay(300);
  
  /*Romibo.setAntennaColor (0, 0, 255); // 
  
  Romibo.setNeutralHeadPosition ();
  Romibo.playSoundNamed ( "AWESOME" );
  Romibo.waitForSoundToFinish ();
  
  Romibo.setEyelid (up);
  Romibo.setHeadPosition (down, down);
  Romibo.setAntennaColor (0, 0, 255); // 
  //Romibo.drive (60, -60);
  Romibo.delay (4000);
  
  Romibo.setEyelid (down);
  Romibo.setHeadPosition (up, up);
  Romibo.setAntennaColor (0, 0, 255); // 
  //Romibo.drive (60, -60);
  Romibo.delay (4000);
  
  Romibo.drive (60, -60);
  Romibo.delay (2000);
  *///  Romibo.drive (0, 0);
  /////////////////////////////////////////////////////
  /*Romibo.setAntennaColor (255, 255, 255); // White
  Romibo.playSoundNamed ( "HELLO" );
  Romibo.waitForSoundToFinish ();
  
  //Romibo.poll(); // Update i/o,...
  Romibo.delay (1000);
  if(Romibo.soundLevel() < 1){       // Romibo.soundLevel()//microphone.scaled
  Romibo.setAntennaColor (255, 0, 0); // Var not reading in at all, never goes RED
  }
  
  Romibo.delay (1000);
  if(Romibo.soundLevel() > 5){
  Romibo.setAntennaColor (0, 255, 0); // 
  }
  Romibo.delay (1000);
  if(Romibo.soundLevel() > 10){
  Romibo.setAntennaColor (0, 0, 255); //
  }
  Romibo.delay (1000);
  if(Romibo.soundLevel() > 15){
  Romibo.setAntennaColor (255, 0, 0); // Flakey
  }
  Romibo.delay (1000);
  if(Romibo.soundLevel() > 20){
  Romibo.setAntennaColor (0, 255, 0); // Flakey
  }
  Romibo.delay (1000);
  if(Romibo.soundLevel() > 25){
  Romibo.setAntennaColor (0, 0, 255); // Working
  }
  *///Romibo.delay (1000);
  //////////////////////////////////////////////////////////////
  /*Romibo.delay (1000);
  if(Romibo.obstacleProximity() < 50){
  Romibo.setAntennaColor (0, 255, 0); // 
  }
  Romibo.delay (1000);
  if(Romibo.topLightLevel() > 50){
  Romibo.setAntennaColor (0, 0, 255); //
  }
  Romibo.delay (1000);
  if(Romibo.leftFrontLightLevel() > 50){
  Romibo.setAntennaColor (255, 0, 0); // Flakey
  }
  Romibo.delay (1000);
  if(Romibo.rightFrontLightLevel() > 50){
  Romibo.setAntennaColor (0, 255, 0); // Flakey
  }
  Romibo.delay (1000);
  if(Romibo.touchSwitches() != 0){
  Romibo.setAntennaColor (0, 0, 255); // Working
  }
  *///Romibo.delay (1000);
  ///////////////////////////////////////////////////////////////
  Serial.print (" ");
  Serial.print ("TopLightLevel: ");
  Serial.println( Romibo.topLightLevel() ); 
  Serial.print ("LeftLightLevel: ");
  Serial.println(Romibo.leftFrontLightLevel());
  Serial.print ("RightLightLevel: ");
  Serial.println( Romibo.rightFrontLightLevel() );
  Serial.print ("FrontRangeDistance: ");
  Serial.println( Romibo.frontRangeDistance() );
  Serial.print ("touchSwitches: ");
  Serial.println( Romibo.touchSwitches() );
  Serial.print ("soundLevel: ");
  Serial.println( Romibo.soundLevel() );
  
   /*Romibo.setEyelid (up);  //                                                NOT WORKING
   Romibo.delay(1000);
   *///Romibo.setEyelid (down);
  //////////////////////////////////////////////////////////////
  Romibo.setAntennaColor (255, 255, 255); // White
  //Romibo.playSoundNamed ( "HELLO" );
  //Romibo.waitForSoundToFinish (); 
  Romibo.drive (0, 0);
  Romibo.delay (3000);
  
  while(1){
    
  Serial.println( Romibo.soundLevel() );
  
  if(Romibo.soundLevel() > Boo){
  Serial.print ("> Boo: ");
  Serial.println( Romibo.soundLevel() );
  Romibo.setAntennaColor (255, 0, 0); // 
  Romibo.drive (-80, -80);
  Romibo.delay (2000);
  Romibo.drive (0, 0);
  Romibo.delay (1000);
  }
  else if(Romibo.soundLevel() > ComeHere){
  Serial.print ("> ComeHere: ");
  Serial.println( Romibo.soundLevel() );
  Romibo.setAntennaColor (0, 255, 0); // 
  Romibo.drive (80, 80);
  Romibo.delay (3000);
  Romibo.drive (0, 0);
  Romibo.delay (1000);
  }
  else if(Romibo.soundLevel() > Shhh){
  Serial.print ("> Shhh: ");
  Serial.println( Romibo.soundLevel() );
  Romibo.setAntennaColor (0, 0, 255); // 
  Romibo.drive (40, 40);
  Romibo.delay (1000);
  Romibo.drive (0, 0);
  Romibo.delay (1000);
  }
  else
  ;
  }
   
}
