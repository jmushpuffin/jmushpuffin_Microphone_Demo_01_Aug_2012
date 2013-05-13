Microphone Demo 01, aug 2012 ( Jer_Demo1_ComeHere081012.ino ) :)
Jeremy R Romeiko

This trunk contains all the files associated with the initial demonstration of microphone
Amplitude response. This includes complex use of eye lid servos, head servos, drive wheels, 
output sounds and antennae LEDs in expressing emotion throughout a ~30sec interaction. 
Outputs are defined within the main program (.ino).


http://youtu.be/CMLHtuIWWmI 

Notes on Mic use which I wrote for John:
----------------------------------------
John,
 Aubrey asked me to get you the microphone code. Here are some snippets from my demo.

#include <RomiboSound.h>  
#include <RomiboRobot.h>
#include <ConsoleOutput.h>
#include <RomiboPinMappings.h>
#include <RomiboConfig.h>
#include <Romibo.h>
#include <Parameters.h>          // Declare the default parameter table object.
Parameters parameters( NULL, 0 );
ConsoleOutput Console;           // Define a polled serial output stream. 
//...
  Serial.begin(57600);
  Serial1.begin(9600);
  Romibo.begin();
  parameters.addParameters( Romibo.parameters_table(), Romibo.parameters_table_size());
  Serial.println("INITIALIZED");
  Romibo.poll();
  Romibo.delay(500);
//...
int n=0;
 for(n=0;n<40;n++){                         // Upon Romibo Setup, Before First Microphone use, Allow Mic Algo to Buffer and Stabalize, 10 seconds
   Romibo.setAntennaColor (255, 0, 0);        // Red  
   Romibo.delay (125);   
   Romibo.setAntennaColor (0, 0, 0);          // Off 
   Romibo.delay (125);  
   PrintSensors();
  }
//...
int Shhh=45, ComeHere=55, Boo=85;

 while(Romibo.soundLevel() < ComeHere)      // Microphone
  PrintSensors();


Luck!

--------
oh yeah,
 after the "while <", I include a delay, ~500ms, to allow the person to finish speaking, after detection, before a response.
 Works most reliably when stretching out a phrase, "Come Heeeeere".
 Also, amplitude depends on voice, range, orientation, attitude, experience,... We're gonna need to do some more work on the filtering before the mic is very useful.
So, I only used the single "ComeHere" threshold in my first demo.

BTW, I mentioned some things after our experience with filming last time.To reiterate...
-Could we increase the time before the romibo returns to smart wonder, after the ipad use. maybe 3 minutes. The bot keeps running away just as the kids is about to respond...
-ipad link reliability
-a response of some sort to any type of input at just about any time during operation.
-richer responses:  

Also, I was playing with head servo angles. Here's what i got. 
int up=95,down=5;

void TestHead(){
  Romibo.setNeutralHeadPosition ();         //level pop-high                      
  Romibo.setHeadPosition (down, down);      //level pop-low                 
  Romibo.setHeadPosition (up, up);          //up very-low pop-high                       
  Romibo.setHeadPosition (down, up);        //down low                     
  Romibo.setHeadPosition (up, down);        //up high                       
  Romibo.setHeadPosition (50, down);        //up low                       
  Romibo.setHeadPosition (50, up);          //level                      
  Romibo.setHeadPosition (down, 50);        //down high                      
  Romibo.setHeadPosition (up, 50);          //up high

//Bob up-down-up-down while level
  Romibo.setNeutralHeadPosition ();         //level pop-high   
  Romibo.delay (150);   
  Romibo.setHeadPosition (down, down);      //level pop-low      
  Romibo.delay (150); 
  Romibo.setNeutralHeadPosition ();         //level pop-high   
  Romibo.delay (150);   
  Romibo.setHeadPosition (down, down);      //level pop-low      
  Romibo.delay (150); 
...
}


chears,
j






















