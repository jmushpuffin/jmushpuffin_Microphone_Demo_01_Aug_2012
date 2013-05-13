// Romibo.ino : top-level code for Romibo robot controller

// History:
//   2011-12-03 GJZ forked from Brian Pfiffner's MEmote sources

/**
Meet MEmote! 
MEmote is a DIY (Do it Yourself) robot aspiring to help children with Autism recognize 
and express emotion.  (The project is a preliminary exploration executed over the course of 
two weeks and will continue to be developed and researched.)

By Aubrey Shick
Final project for Making Things Interact - Fall 2010

What does MEmote do?
MEmote is an affective mobile robot that will also accepts remote control signals to effect 
it's behavior and emotional state.  Emotional state is represented by a coordinated language 
of light, movement/gesture (and eventually sound). This affective display allows the robot to
communicate its current status and intent to viewers. 

How does MEmote see light?
He calibrates to the light levels of the specific room. MEmote always starts off mad because 
the the only light he has seen so far is also the brightest light he has seen.  By shining a 
brighter light such as a light wand directly on the light sensor (photoresistor) on his head 
he will then recognize the ambient light as the medium light level.  If you then cover his 
head or shut off the light he will recognize the minimum light level.  MEmote divides sensed 
light into three possible levels: max bright, medium light  and minimum light.  He then choses
his behavior based on which of these three levels he senses.

How does MEmote follow light?
He follows the light by using two light sensors on the right and left of his body to control
the motors steer the wheels.  Each light sensor is associated with the wheel on the opposite 
side of the body.  For example, if the light sensor on the left senses the most light the 
motor on the right will go faster thereby steering the robot towards the left.  This method 
allows the robot to always drive towards the brightest light in the room which is likely to 
be the light wand/controller.

How does MEmote know when I'm close?
MEmote senses presence by using an infrared (IR) range finder.  The range finder shines IR 
light in front of the robot and is able to gauge whether something or someone is in front of
him by the amount of IR that is reflected back.  When MEmote senses a presence he will stop 
and bob, but when you get to close, and he senses brighter IR levels, he will run backwards.  

How does MEmote move?
MEmote bobs by using servos, a special kind of geared motor that will turn to a specific 
angle rather than at a certain speed.  When he senses changes in presence and light levels 
the program calls a specific angle and causes the servos between the dome and the base to 
change angles allowing him to move.  A servo in the dome also changes angles to raise and 
lower his eyelid and antenna. 


Thanks to:
Cornell Wright and Steven Brudenell 
There is no way I could have gotten MEmote working so quickly without their help!

*/

// Include the customized WaveHC sound library.  This appears to trigger adding the RomiboSound
// library to the search path for the .cpp files, so it needs to appear somewhere, even if not
// directly used by the user code.
#include <RomiboSound.h>  

// Include the robot hardware interface.
#include <RomiboRobot.h>

#include "Definitions.h"

/****************************************************************/
// Provide a few forward declarations for variables defined in Globals.ino.  It
// appears that all .ino files get compiled in the same namespace in
// alphabetical order, so Globals.ino gets loaded after Commandline.ino.
extern int energy_level, satisfaction_level;
extern void set_antenna_color_for_emotion(void);

extern const char *random_happy_sound(void);
extern const char *random_angry_sound(void);
extern const char *random_sad_sound(void);
extern const char *random_beckon_sound(void);
extern const char *random_question_sound(void);
extern const char *random_play_sound(void);
extern const char *random_greeting_sound(void);

extern int classify_emotional_state(void);
extern void set_antenna_color_for_emotion(void);
extern void set_head_pose_for_emotion(void);
extern long time_constant_for_emotion(void);
extern const char *choose_sound_for_emotion(void);
extern const char *description_for_emotion(void);
extern void set_random_emotional_state(void);
extern void adjust_satisfaction( int delta );
extern void adjust_energy( int delta );
extern void set_emotional_state( int energy, int satisfaction );

/****************************************************************/
// COLORS:
// Sets the rgb values for each mode
int mad_color[3] = {255, 0, 0};
int sad_color[3] = {0, 0, 255};
int curious_color[3] = {255, 255, 0};
int happy_color[3] = {0, 255, 0};
int off_color[3] = {0, 0, 0};

// SERVO ANGLES:
// Sets the front, back, eye servo angles for each mode. The robot alternates between each
// of 2 sets of angles in each mode.

//int mad_angles1[3] = {180 0, 45};
//int mad_angles2[3] = {135, 45, 45};
//int sad_angles1[3] = {180, 45, 67};
//int sad_angles2[3] = {180, 45, 90};
//int curious_angles1[3] = {180, 45, 45};
//int curious_angles2[3] = {180, 0, 67};
//int happy_angles1[3] = {180, 45, 45};
//int happy_angles2[3] = {135, 0, 45};

// Eye Range: 40(Open) - 140 (Closed)

int mad_angles1[3]     = {90, 90, 40};
int mad_angles2[3]     = {90, 90, 40};
int sad_angles1[3]     = {90, 90, 140};
int sad_angles2[3]     = {90, 90, 100};
int curious_angles1[3] = {90, 90, 100};
int curious_angles2[3] = {90, 90, 60};
int happy_angles1[3]   = {90, 90, 70};
int happy_angles2[3]   = {90, 90, 50};

// Minimum amount of time to stay in each mode
// It is possible to change the amount of time in each mode by changing the delays below.
// The first mode is wander mode, we don't want to stay in it if we find something else to do
// The other modes are mad, sad, curious, happy.
// Currently, we stay in each mood for the same amount of time (about five seconds).
int mode_delays[5] = {
  LOOPS_PER_SECOND,
  5 * LOOPS_PER_SECOND,
  5 * LOOPS_PER_SECOND, 
  5 * LOOPS_PER_SECOND, 
  5 * LOOPS_PER_SECOND
};

// The current number of loop iterations used to estimate time.  We start at 10000 so that
// we always reset to a new mode w/o delay
// It is an unsigned long so that the batteries are guaranteed to run out before this rolls over
unsigned long loop_count = 10000;

// Loop number that he starts to wander forward, to compare with the current loop number for
// timing purposes
unsigned long wander_start = 0;
// Time in seconds to do the current activity
unsigned long wander_length = 0;

// Both of these are used to spin in a circle but we don't do that anymore.
int last_range = -1;
int behav_start = 0;

// Define the general operating mode of the robot.
int mode = MODE_AUTONOMOUS;

// Define the transient state of the robot.  Starts out in WANDER mode, exploring the world.
int state = WANDER;

#include "ConsoleOutput.h"
ConsoleOutput Console;  // Define a polled serial output stream.

// Forward declaration for default parameter table.
#include "Parameters.h"
extern Parameters parameters;

#include "RomiboRobot.h"

/****************************************************************/
// One-time initialization function called by the Arduino runtime.
void setup(void) {

  // Set up serial port to receive and commands and transmit status.  The
  // standard Arduino serial driver has interrupt-driven input but polled
  // output, so this sequence won't finish until all but the last character are
  // transmitted.
  Serial.begin(57600);
  const char version_string[] = "Romibo version " __DATE__ " " __TIME__;
  Serial.println( version_string );

  // If the WiFi network module is installed, configure another serial port.
#if ROMIBO_WIFLY_INSTALLED
  Serial1.begin(9600);
#endif

  // Initialize the Romibo system and attach it to the hardware.
  Romibo.begin();

  // Add the low-level variables to the user interface for debugging.
  parameters.addParameters( Romibo.parameters_table(), Romibo.parameters_table_size());

  // Initialize the behavior state machine.
  init_behavior();

  // Choose an alternative operating mode if particular combinations of touch
  // switches are depressed at power-on.
  if (Romibo.topSwitch() && Romibo.bottomSwitch() ) {
    Romibo.playSoundNamed( digit_sound(1) );
    mode = MODE_ORIGINAL;

  } else if (Romibo.leftSwitch() && Romibo.rightSwitch() ) {
    Romibo.playSoundNamed( digit_sound(2) );
    mode = MODE_TEST;
  }

  Serial.println("INITIALIZED");
}

/****************************************************************/
// This the entry point for the main event loop, which is called repeatedly by
// the Arduino runtime system.  To make sure that real time events are
// continually processed, every function called should either use the safe
// blocking methods in RomiboRobot which poll I/O or return without stalling.

void loop( void )
{
  // Update the robot inputs and outputs.
  Romibo.poll();

  // The main loop function that decides the state and performs actions based on state
  switch(mode){
  case MODE_AUTONOMOUS:
    // In this state Romibo is moving on its own.
    behavior_update();
    break;

  case MODE_ORIGINAL:
    // In this state Romibo is moving on its own.
    original_state_machine();
    break;
      
  case MODE_R_CONTROL:
    // In this state MEmote is controlled by an external remote control.
    remote_control_mode();
    break;

  default:
  case MODE_TEST:  // test mode added for debugging hardware
    test_mode_update();
    break;
  }
}

/****************************************************************/
// In this state MEmote is controlled by an external remote control.  This mode
// is currently problematic because the IR receiver code blocks waiting for an
// input, so the rest of the I/O goes untended.
void remote_control_mode(void)
{
  int key = getIRKey();
  if(key != 0){
    switch(key) 
      {
      case CH_UP:
	Romibo.driveForward( 100 );
	break;
            
      case CH_DOWN:
	Romibo.driveBackward( 100 );
	break;
          
      case VOL_UP:
	Romibo.spinInPlace( -100 );
	break;
          
      case VOL_DOWN:
	Romibo.spinInPlace(  100 );
	break;
          
      case MUTE:
	Romibo.stop();
	break;
            
      case AV_TV:
	if( Romibo.soundEnabled() ){
	  Romibo.setAntennaColor(happy_color);
	  Romibo.playSoundNamed("S1");
	}
	break;
            
      case POWER:  
	// Switch out of IR remote control mode into a normal operating
	// mode.  The robot can be configured in setup() to start in remote
	// control mode, or set via the command line interface.
	if(mode == MODE_AUTONOMOUS)     { mode = MODE_R_CONTROL;   } 
	else if(mode == MODE_R_CONTROL) { mode = MODE_AUTONOMOUS;  }
	Romibo.stop();
	break;
            
      default:
	break;
      }
  }
}
/****************************************************************/
