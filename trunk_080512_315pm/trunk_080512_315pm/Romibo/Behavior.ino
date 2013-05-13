// Behavior.ino : the state machine for basic behaviors
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
// This file defines a state machine to produce basic expressive
// behavior.  This is intended to replace the prototype behavior code
// which still exists in Romibo.ino, MoodFunctions, and
// OutputFunctions.

// The robot randomly moves through different activities, interacting
// with the world, but also interrupting its activities to perform
// user-requested actions received from the remote interface.

/****************************************************************/
// The actions are modulated by the emotional state vector.
extern int energy_level, satisfaction_level;

// The random speeds are chosen over a subset of the full range to avoid friction problems.
const int min_speed = 100;
const int max_speed = 100;

// Provide global timers for measuring durations.
#include "ElapsedTimer.h"
ElapsedTimer stateTimer, phaseTimer;

/****************************************************************/
// Define the behavior states.
enum {
  STATE_NULL = 0,     // no state values can be zero
  STATE_WAKEUP, 
  // ---- states in this range can be randomly picked
  STATE_WANDER,
  STATE_DANCE,
  STATE_PAUSE,
  STATE_TALK,
  // ----
  STATE_USER,         // follow user directions
};

// Global to hold the previous state, useful as a trivial state stack.
int previous_state;

// Globals to hold other state date.  The definition of these is internal to different states.
enum { PRIMITIVE_STILL, PRIMITIVE_ROCK, PRIMITIVE_BOB, PRIMITIVE_SPIN, PRIMITIVE_TURN };
int current_primitive;

/****************************************************************/
// pick a random behavior state
int random_behavior_state(void)
{
  return random(STATE_WANDER, STATE_USER );
}

/****************************************************************/
// Transition to a new state.  The state index is temporarily set negative to
// indicate the entry condition.  The timer is reset.

void transition( int new_state )
{
  previous_state = state;
  state = -new_state;
  stateTimer.reset();
}

/****************************************************************/
void init_behavior(void)
{
  state = STATE_NULL;
  current_primitive = PRIMITIVE_STILL;
  transition( STATE_WAKEUP );
}
/****************************************************************/
// The following primitives change the current state to start a given action.
// They can be called from the user interface or as a remote command.
void set_user_state(int primitive)
{
  if (state != STATE_USER) transition(STATE_USER);
  current_primitive = primitive;
  stateTimer.reset();
}
void perform_rock(void)  { set_user_state( PRIMITIVE_ROCK ); }
void perform_bob(void)   { set_user_state( PRIMITIVE_BOB  ); }
void perform_spin(void)  { set_user_state( PRIMITIVE_SPIN ); }
void perform_turn(void)  { set_user_state( PRIMITIVE_TURN ); }

/****************************************************************/
const long user_state_timeout = 4000*1000;  // microseconds

void update_user_state(int entering_state)
{
  switch( current_primitive ) {

  case PRIMITIVE_STILL:
    if ( entering_state ) Romibo.stop();
    if ( stateTimer.elapsedMicroseconds() > user_state_timeout ) transition( previous_state );
    break;

  case PRIMITIVE_BOB:
  case PRIMITIVE_ROCK:
    {
      static long period;
      static int phase;

      if ( entering_state ) {
	period = time_constant_for_emotion() / 2;  // half-period
	phase = 0;
	phaseTimer.reset(); 
      }
      // trigger the output immediately and then every half-period
      if (phaseTimer.elapsedMicroseconds() >= 0) {
	phaseTimer.subtractMicroseconds( period );
	if (current_primitive == PRIMITIVE_ROCK) {
	  if (phase++ & 1)  Romibo.setHeadPosition(   0, 100 );
	  else              Romibo.setHeadPosition( 100,   0 );
	} else {
	  if (phase++ & 1)  Romibo.setHeadPosition( 100, 100 );
	  else              Romibo.setHeadPosition(   0,   0 );
	}
      }
      if ( stateTimer.elapsedMicroseconds() > user_state_timeout ) transition( previous_state );
    }
    break;
      
  case PRIMITIVE_SPIN:
    if ( entering_state ) Romibo.spinInPlace( 100 );
    if ( stateTimer.elapsedMicroseconds() > 2000000 ) {
      Romibo.spinInPlace( 0 );
      transition( previous_state );
    }
    break;

  case PRIMITIVE_TURN:
    if ( entering_state ) Romibo.spinInPlace( -100 );
    if ( stateTimer.elapsedMicroseconds() > 1000000 ) {
      Romibo.spinInPlace( 0 );
      transition( previous_state );
    }
    break;
  }
}

/****************************************************************/
void update_wander_state(int entering_state)
{
  static long random_duration = 0;
  static int phase = 0;
  static int iteration_count = 0;
  
  // start out by driving forward
  if (entering_state) {
    iteration_count = 0;
    phase = 0;
    random_duration = random( 2000, 4000 );
    Romibo.driveForward( random(min_speed, max_speed) );
  }

  // handle asynchronous transitions

  // if we get close to something, switch to backing up
  if (phase != 2) {
    int range = Romibo.obstacleProximity();
    if ( range == ROMIBO_CLOSE ) {
      iteration_count++;
      if (!Romibo.isSoundPlaying()) Romibo.playSoundNamed( random_question_sound() );
      Romibo.driveBackward( 100 );
      random_duration = random( 1000, 2000 );
      stateTimer.reset();
      phase = 2;
      
      // magnify the energy emotion
      adjust_energy( (energy_level < 0) ? -30 : 30 );
      set_head_pose_for_emotion();
      set_antenna_color_for_emotion();
    }
  }

  // if we get petted, switch modes
  if (Romibo.touchSwitches()) transition( STATE_TALK );

  // handle synchronous transitions when the timer expires
  // else normally alternate between phases of driving forward and spinning
  if (stateTimer.elapsedMilliseconds() > random_duration)  {
    stateTimer.reset();
    iteration_count++;
    switch(phase) {
    case 0: // driving
      random_duration = random( 1000, 3000 );
      Romibo.spinInPlace( random( min_speed, max_speed ) );
      phase++;
      break;

    case 1: // turning
      random_duration = random( 2000, 4000 );
      Romibo.driveForward( random(min_speed, max_speed) );
      phase = 0;
      break;

    case 2: // backing up
      transition(STATE_TALK); // temporary
      random_duration = random( 1000, 3000 );
      Romibo.spinInPlace( random( min_speed, max_speed ) );
      phase = 0;
      break;
    }
  }

  // if this goes on long enough, do something different
  // if (iteration_count > 5) {   // FIXME
  if (iteration_count > 1) {
    transition( random_behavior_state() );
    set_random_emotional_state();
  }
}

/****************************************************************/
void update_dance_state(int entering_state)
{
  static long period;
  static int duration;
  static int style;
  static int phase;

#define NUM_DANCE_STYLES 4

  if (entering_state) { 
    period = time_constant_for_emotion() / 4;
    duration = random( 10, 20 );
    style = random( NUM_DANCE_STYLES );
    phaseTimer.reset();
    phase = 0;
  }

  // if we get close to something, switch back to wandering
  if ( Romibo.obstacleProximity() == ROMIBO_CLOSE ) transition( STATE_WANDER );
  
  // make moves at rhythmic intervals
  if (phaseTimer.elapsedMicroseconds() >= 0) {
    phaseTimer.subtractMicroseconds( period );
    
    switch(style) {

    case 0:  // move forward and back
      if (++phase & 1) {
	Romibo.driveForward( 100 );
	Romibo.tiltHeadForward();
	Romibo.setAntennaColor( 255, 255, 0 );
	if (!Romibo.isSoundPlaying()) Romibo.playSoundNamed( random_beckon_sound() );
      } else {
	Romibo.driveBackward( 100 );
	Romibo.tiltHeadBack();
	Romibo.setAntennaColor( 0, 255, 255 );
	if (random(5) == 0) style = random( NUM_DANCE_STYLES );
      }
      break;

    case 10:  // turn back and forth
      if (++phase & 1) {
	Romibo.spinInPlace( 100 );
	Romibo.tiltHeadForward();
	Romibo.setAntennaColor( 255, 255, 0 );
	if (!Romibo.isSoundPlaying()) Romibo.playSoundNamed( random_beckon_sound() );
      } else {
	Romibo.spinInPlace( -100 );
	Romibo.tiltHeadBack();
	Romibo.setAntennaColor( 0, 255, 255 );
	if (random(5) == 0) style = random( NUM_DANCE_STYLES );
      }
      break;

    case 1:
    case 2:  // just move head
      if (++phase & 1) {
	Romibo.stop();
	Romibo.tiltHeadForward();
	Romibo.setAntennaColor( 255, 255, 0 );
	if (!Romibo.isSoundPlaying()) Romibo.playSoundNamed( random_beckon_sound() );
      } else {
	Romibo.stop();
	Romibo.tiltHeadBack();
	Romibo.setAntennaColor( 0, 255, 255 );
	if (random(5) == 0) style = random( NUM_DANCE_STYLES );
      }
      break;

    case 3: // just move eyes
      if (++phase & 1) {
	Romibo.stop();
	Romibo.setNeutralHeadPosition();
	Romibo.setEyelid( 100 );
	Romibo.setAntennaColor( 255, 255, 0 );
	if (!Romibo.isSoundPlaying()) Romibo.playSoundNamed( random_beckon_sound() );
      } else {
	Romibo.stop();
	Romibo.setNeutralHeadPosition();
	Romibo.setEyelid( 0 );
	Romibo.setAntennaColor( 0, 255, 255 );
	if (random(5) == 0) style = random( NUM_DANCE_STYLES );
      }
      break;
    }
  }
  // transition out on timeout
  if (stateTimer.elapsedSeconds() > duration) {
    // worked off some energy
    energy_level = 0;
    adjust_satisfaction( 30 );
    transition( random_behavior_state() );
  }
}

/****************************************************************/
// Take a short break.
void update_pause_state(int entering_state)
{
  static long duration;

  if ( entering_state ) {
    Romibo.stop();                    // stop driving and express emotional state
    set_head_pose_for_emotion();      //  on the head
    set_antenna_color_for_emotion();  //  and on the LEDs
    duration = random(4, 12 );        // number of seconds to pause
    Romibo.playSoundNamed( choose_sound_for_emotion() );
    Romibo.setEyelid( 0 );            // close the eyes for a timeout
  }

  // if we get petted, wake up and talk
  if (Romibo.touchSwitches()) {
    adjust_energy( 30 );
    transition( STATE_TALK );
  }

  // if something gets close, start wandering
  if ( Romibo.obstacleProximity() == ROMIBO_CLOSE ) {
    adjust_satisfaction( -30 );
    adjust_energy( (energy_level < 0) ? -30 : 30 );
    transition( STATE_WANDER );
  }

  if (stateTimer.elapsedSeconds() > duration) {
    // come out of a break in a neutral state
    set_emotional_state( 0, 0 );
    transition( random_behavior_state() );
  }
}

/****************************************************************/
void update_talk_state(int entering_state)
{
  static int iterations;
  static long period;
  static int is_playing;

  if ( entering_state ) {
    Romibo.stop();                    // stop driving and express emotional state
    set_head_pose_for_emotion();      //  on the head
    set_antenna_color_for_emotion();  //  and on the LEDs
    iterations = random( 2, 6 );      // choose number of things to say

    period = time_constant_for_emotion() / 2;  // choose a silence delay

    // say something right away
    Romibo.playSoundNamed( choose_sound_for_emotion() );
    set_head_pose_for_emotion();
    is_playing = 1;
  }

  // if we get petted, keep talking
  if (Romibo.touchSwitches()) iterations = random( 2, 4);

  // if something gets close, switch back to wandering
  if ( Romibo.obstacleProximity() == ROMIBO_CLOSE ) transition( STATE_WANDER );
  
  // wait for the sound to stop
  if (!Romibo.isSoundPlaying()) {

    // if the sound just stopped, begin the silence timer
    if (is_playing) {
      is_playing = 0;
      phaseTimer.reset(); // clear a delay timer to use for silences

    } else {

      // check if the silence has finished
      if (phaseTimer.elapsedMicroseconds() > period) {

	// check if enough cycles have elapsed
	if (--iterations <= 0) transition( random_behavior_state() );
	else {

	  // say something new
	  Romibo.playSoundNamed( choose_sound_for_emotion() );
	  is_playing = 1;
	  adjust_satisfaction( 30 );
	  set_head_pose_for_emotion();
	  set_antenna_color_for_emotion();
	}
      }
    }
  }
}

/****************************************************************/
void state_debug_output( const char *statename , const char *sound )
{
  // if (sound) Romibo.playSoundNamed( sound );
  Console.print("entering state ");
  Console.println( statename );
}
/****************************************************************/
// Update the behavior state machine.
void behavior_update(void)
{
  int entering_state = 0;

  // detect an uninitialized state
  if (state == 0) transition( STATE_WANDER );

  // detect the onset of a new state
  if (state < 0) {
    state = -state;
    entering_state = 1;
  }

  switch(state) {
  case STATE_WAKEUP:
    if (entering_state) {
      state_debug_output( "WAKEUP", NULL );
      Romibo.stop();
      Romibo.playSoundNamed( "POWERON" ); 
      set_emotional_state( 0, 0);
      set_head_pose_for_emotion();
      set_antenna_color_for_emotion();
    }
    if (stateTimer.elapsedSeconds() > 2) {
      adjust_energy( 30 );
      transition( random_behavior_state() );
    }
    break;

  case STATE_WANDER:
    if (entering_state) state_debug_output( "WANDER", "DIGIT1" );
    update_wander_state(entering_state);
    break;

  case STATE_DANCE:
    if (entering_state) state_debug_output( "DANCE", "DIGIT2" );
    update_dance_state(entering_state);
    break;

  case STATE_PAUSE:
    if (entering_state) state_debug_output( "PAUSE", "DIGIT3" );
    update_pause_state(entering_state);
    break;

  case STATE_TALK:
    if (entering_state) state_debug_output( "TALK", "DIGIT4" );
    update_talk_state(entering_state);
    break;

  case STATE_USER:
    if (entering_state) state_debug_output( "USER", "DIGIT9" );
    update_user_state(entering_state);
    break;
  }
}

/****************************************************************/
