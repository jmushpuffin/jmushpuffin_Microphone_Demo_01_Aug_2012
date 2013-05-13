// Jer_Demo1_ComeHere081012.ino : 
// -Demo1:10sec Delay,[Move into Range](before infinite loop),"Come Here":Romibo forward,"Come Here":Romibo forward,[pet Romibo]:Romibo purr and cooing
// -//play with servos
// -//drives in response to audioLevel
// -//test all i/o
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
/****************************************************************/
#include <Parameters.h>          // Declare the default parameter table object.
Parameters parameters( NULL, 0 );
ConsoleOutput Console;           // Define a polled serial output stream. 

/****************************************************************/
//------------------------
int up=95,down=5;
int Shhh=45, ComeHere=55, Boo=85;
//------------------------
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


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void playAllSounds(){
  int len = 37;
  Romibo.waitForSoundToFinish ();
  for (int i = 0; i < len; i++) {
      Romibo.playSoundNamed (sounds[i]);
      Romibo.waitForSoundToFinish ();
      if (i % 3 == 2) {
        delay (2000);
}}}
//..............................
void TestMicWLED(){
  Romibo.setAntennaColor (255, 255, 255); // White
  Romibo.playSoundNamed ( "HELLO" );
  Romibo.waitForSoundToFinish ();
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
}
/////////////////////////////////////////////////////////////////////////////
 void TestSensorsWLED(){
  Romibo.delay (1000);
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
  Romibo.delay (1000); 
 }
/////////////////////////////////////////////////////////////////////////////
 void PrintSensors(){
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
 }
/////////////////////////////////////////////////////////////////////////////
  void TestOutputs(){
  Romibo.setAntennaColor (0, 0, 255); // 
  Romibo.setNeutralHeadPosition ();
  Romibo.playSoundNamed ( "AWESOME" );
  Romibo.waitForSoundToFinish ();
  
  Romibo.setEyelid (up);
  Romibo.setHeadPosition (down, down);
  Romibo.setAntennaColor (255, 0, 0); // 
  Romibo.drive (30, 30);
  Romibo.delay (4000);
  
  Romibo.setEyelid (down);
  Romibo.setHeadPosition (up, up);
  Romibo.setAntennaColor (0, 255, 0); // 
  Romibo.drive (60, -30);
  Romibo.delay (4000);
  
  Romibo.setEyelid (up);
  Romibo.setHeadPosition (down, up);
  Romibo.setAntennaColor (0, 0, 255); // 
  Romibo.drive (-30, -60);
  Romibo.delay (4000);
  
  Romibo.drive (60, -60);
  Romibo.delay (2000);
  Romibo.drive (0, 0);
}
/////////////////////////////////////////////////////////////////////////////
void RespondToSound_Drive(){
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
  }}
//......................................
void InputsOutputs(){
  Romibo.setEyelid (up);  //                                                    NOT WORKING
  Romibo.setNeutralHeadPosition ();
  Romibo.setHeadPosition (up, up);
  Romibo.drive (-80, -80);  
  Romibo.setAntennaColor (255, 255, 255); // 
  Romibo.playSoundNamed ( "HELLO" );
  Romibo.waitForSoundToFinish ();  
  
  Romibo.drive (-80, -80);                // (right motor, left motor)
  Romibo.delay (2000);
  Romibo.drive (0, 0);                    // Reset States to Neutral
  Romibo.delay (1000);                    // Include a Delay after motor/servo motions
  
  Serial.print ("> Boo: ");
  Serial.println( Romibo.soundLevel() );
  
  //if(Romibo.soundLevel() > ComeHere){     // Microphone
  //if(Romibo.obstacleProximity() < 50){
  //if(Romibo.topLightLevel() > 50){  //                                     NOT WORKING
  //if(Romibo.leftFrontLightLevel() > 50){
  //if(Romibo.rightFrontLightLevel() > 50){
  //if(Romibo.touchSwitches() != 0){  
  }
//............................
void TestHead(){
  Romibo.setNeutralHeadPosition ();         //level pop-high
  Romibo.delay (2000);                       
  Romibo.setHeadPosition (down, down);      //level pop-low
  Romibo.delay (2000);                        
  Romibo.setHeadPosition (up, up);          //up very-low pop-high
  Romibo.delay (2000);                         
  Romibo.setHeadPosition (down, up);        //down low
  Romibo.delay (2000);                         
  Romibo.setHeadPosition (up, down);        //up high
  Romibo.delay (2000);                        
  Romibo.setHeadPosition (50, down);        //up low
  Romibo.delay (2000);                         
  Romibo.setHeadPosition (50, up);          //level
  Romibo.delay (2000);                        
  Romibo.setHeadPosition (down, 50);        //down high
  Romibo.delay (2000);                         
  Romibo.setHeadPosition (up, 50);          //up high
  Romibo.delay (2000);   
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//==========================================================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(void) 
{
  Serial.begin(57600);
  Serial1.begin(9600);

  // Initialize the Romibo system and attach it to the hardware.
  Romibo.begin();

  // Add the low-level variables to the user interface for debugging.
  parameters.addParameters( Romibo.parameters_table(), Romibo.parameters_table_size());

  Serial.println("INITIALIZED");
  // Update the robot i/o
  Romibo.poll();
  Romibo.delay(500);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void loop( void )
{
 //playAllSounds();
 
 Romibo.drive (0, 0);                       // Ready State
 Romibo.setEyelid (up);
 Romibo.setNeutralHeadPosition ();
 int n=0;
 for(n=0;n<40;n++){                         // Before First Microphone use, Allow Mic Algo to Buffer and Stabalize
   Romibo.setAntennaColor (255, 0, 0);        // Red  
   Romibo.delay (125);   
   Romibo.setAntennaColor (0, 0, 0);          // Red  
   Romibo.delay (125);  
   PrintSensors();
  }
 Romibo.setAntennaColor (255, 255, 255);    // White
 Romibo.setEyelid (10);
 Romibo.delay (200);
 Romibo.setEyelid (50);
 Romibo.delay (100);
 Romibo.setEyelid (up);
 Romibo.delay (300);
 
 while(Romibo.frontRangeDistance() > 390)      // Range Sensor
  PrintSensors();
 
 while(1){
  Romibo.drive (0, 0);                       // Ready State
  Romibo.setEyelid (80); 
  Romibo.setHeadPosition (up, down);         //up high
  Romibo.setAntennaColor (255, 255, 255);    // White
  Romibo.delay (300);                        // Before Microphone use, Include a Delay after motor/servo motions

 while(Romibo.soundLevel() < ComeHere)      // Microphone
  PrintSensors();
  //;
  Romibo.setEyelid (10);
  Romibo.delay (200);
  Romibo.setEyelid (50);
  Romibo.delay (100);
  Romibo.setEyelid (up);
  Romibo.delay (200);                       // Give me time to finish speaking 
  Romibo.drive (60, 60);
  Romibo.setAntennaColor (0, 255, 0);       // Green  
  //Romibo.playSoundNamed ( ":(" );
  //Romibo.delay (200);                     // cut it short, so it won't trigger the next Mic input
  //Romibo.playSoundNamed ( "TheSilenceShallFall" );
  Romibo.delay (200);  
  Romibo.setHeadPosition (down, up);        //down low
  Romibo.setEyelid (10);
  Romibo.delay (400);
  Romibo.setEyelid (40);
  Romibo.delay (400);
  Romibo.drive (0, 0);                      // Stop
  Romibo.setAntennaColor (255, 255, 255);   // White
  Romibo.delay (200);                       // Before Microphone use, Include a Delay after motor/servo motions

 while(Romibo.soundLevel() < ComeHere)      // Microphone
  PrintSensors();
  //;
  Romibo.delay (200);                       // Give me time to finish speaking 
  Romibo.drive (90, 90);
  Romibo.setAntennaColor (0, 255, 0);       // Green  
  Romibo.setEyelid (up);
  Romibo.playSoundNamed ( "Happy2" );
  Romibo.setHeadPosition (up, down);        //up high
  Romibo.setEyelid (up);
  Romibo.delay (400);
  Romibo.delay (400);
  Romibo.drive (0, 0);                      // Stop
  Romibo.setAntennaColor (255, 255, 255);   // White
  Romibo.setEyelid (70);
  Romibo.delay (200);                       // Before Microphone use, Include a Delay after motor/servo motions

 while(Romibo.touchSwitches() == 0)
  PrintSensors();
  //;
  //Romibo.delay (100);
  Romibo.setAntennaColor (0, 0, 255);       // Blue 
  Romibo.setEyelid (up);
  Romibo.drive (90, 60);  
  Romibo.playSoundNamed ( "Happy1" );
  Romibo.delay (400);
  Romibo.drive (0, 0);
  Romibo.delay (100);
  
  Romibo.setHeadPosition (down, down);
  Romibo.setEyelid (70);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.delay (200);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setNeutralHeadPosition ();         //level pop-high
  Romibo.setAntennaColor (255, 255, 255);   // White 
  Romibo.setEyelid (10);
  Romibo.delay (150);
  Romibo.setEyelid (up);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setHeadPosition (down, down);      //level pop-low
  Romibo.setAntennaColor (0, 0, 255);       // Blue 
  Romibo.setEyelid (30);
  Romibo.delay (150);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setNeutralHeadPosition ();         //level pop-high
  Romibo.setAntennaColor (255, 255, 255);   // White 
  Romibo.setEyelid (10);
  Romibo.delay (150);
  Romibo.setEyelid (80);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setHeadPosition (down, down);      //level pop-low
  Romibo.setAntennaColor (0, 0, 255);       // Blue 
  //Romibo.setEyelid (50);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setNeutralHeadPosition ();         //level pop-high
  Romibo.setAntennaColor (255, 255, 255);   // White 
  Romibo.delay (150);
  Romibo.setEyelid (up);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setHeadPosition (down, down);      //level pop-low
  Romibo.setAntennaColor (0, 0, 255);       // Blue 
  /*Romibo.delay (150);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setNeutralHeadPosition ();         //level pop-high
  Romibo.setAntennaColor (255, 255, 255);   // White 
  Romibo.delay (150);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setHeadPosition (down, down);      //level pop-low
  Romibo.setAntennaColor (0, 0, 255);       // Blue 
  Romibo.delay (150);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setNeutralHeadPosition ();         //level pop-high
  Romibo.setAntennaColor (255, 255, 255);   // White 
  Romibo.delay (150);
  *///Romibo.playSoundNamed ( "Digit0" );
  
  //Romibo.playSoundNamed ( "Happy1" );
  Romibo.setHeadPosition (down, down);      //level pop-low
  Romibo.setAntennaColor (0, 0, 255);       // Blue 
  Romibo.delay (150);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setNeutralHeadPosition ();         //level pop-high
  Romibo.setAntennaColor (255, 255, 255);   // White 
  Romibo.delay (150);
  Romibo.setEyelid (80);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setHeadPosition (down, down);      //level pop-low
  Romibo.setAntennaColor (0, 0, 255);       // Blue 
  Romibo.delay (150);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setNeutralHeadPosition ();         //level pop-high
  Romibo.setAntennaColor (255, 255, 255);   // White 
  Romibo.delay (150);
  Romibo.setEyelid (up);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setHeadPosition (down, down);      //level pop-low
  Romibo.setAntennaColor (0, 0, 255);       // Blue 
  Romibo.delay (150);
  Romibo.playSoundNamed ( "Digit0" );
  Romibo.setNeutralHeadPosition ();         //level pop-high
  Romibo.setAntennaColor (255, 255, 255);   // White 
  Romibo.delay (150);
  Romibo.playSoundNamed ( "Digit0" );
  
  Romibo.setEyelid (up);
  Romibo.setHeadPosition (up, down);        //up high
  Romibo.delay (500);
  Romibo.setHeadPosition (down, up);        //down low
  Romibo.delay (500);      
  Romibo.setHeadPosition (up, up);          //up very-low pop-high 
  Romibo.delay (500);  
  Romibo.setHeadPosition (up, down);        //up high
  Romibo.delay (300); 
  Romibo.setEyelid (10);
  Romibo.delay (200);
  Romibo.setEyelid (50);
  Romibo.delay (100);
  Romibo.setEyelid (up);
 
}

}























