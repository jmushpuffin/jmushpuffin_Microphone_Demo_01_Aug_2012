// Emotions.ino : define operations on the basic emotional state space
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
//
// Classify the emotion state into discrete categories.
//
//                   (satisfied)
//                  +satisfaction
//  (angry) -energy    (neutral)         +energy  (excited)
//                  -satisfaction 
//                   (discontent)

enum emotion_class { EMOTION_NEUTRAL, EMOTION_EXCITED, EMOTION_SATISFIED, EMOTION_ANGRY, EMOTION_DISCONTENT };

int classify_emotional_state(void)
{
  int e  = energy_level;
  int s  = satisfaction_level;
  int ae = abs(energy_level);
  int as = abs(satisfaction_level);

  if (ae < 20 && as < 20)    return EMOTION_NEUTRAL;    // origin of the emotion space
  else if (e > 0 && as <  e) return EMOTION_EXCITED;    // right quadrant
  else if (e < 0 && as < -e) return EMOTION_ANGRY;      // left quadrant
  else if (s > 0)            return EMOTION_SATISFIED;  // upper quadrant
  else                       return EMOTION_DISCONTENT; // lower quadrant 
}
/****************************************************************/
// Set the antenna color to match the basic emotional state.  This is
// consistent with the graphics in the iPad interface:
//                  yellow
//               +satisfaction
//  red -energy     cyan        +energy  green
//               -satisfaction 
//                   blue

void set_antenna_color_for_emotion(void)
{
  switch( classify_emotional_state() ){
  case EMOTION_NEUTRAL:    Romibo.setAntennaColor(   0, 255, 255 ); break;  // origin of the emotion space
  case EMOTION_EXCITED:    Romibo.setAntennaColor(   0, 255,   0 ); break;  // right quadrant
  case EMOTION_SATISFIED:  Romibo.setAntennaColor( 255, 255,   0 ); break;  // upper quadrant
  case EMOTION_ANGRY:      Romibo.setAntennaColor( 255,   0,   0 ); break;  // left quadrant
  case EMOTION_DISCONTENT: Romibo.setAntennaColor(   0,   0, 255 ); break;  // lower quadrant 
  }
}
/****************************************************************/
// The head movement is based on the emotional state:
//
//                                (head tilted up)
//                                 +satisfaction
//
// (eyes wide open)   -energy     neutral (eyes half closed)    +energy  (eyes wide open)
//
//                                -satisfaction 
//                              (head tilted forward)

void set_head_pose_for_emotion(void)
{
  // the neutral pose is 50,50
  // the full tilt forward is 0, 100
  int s = constrain( satisfaction_level, -100, 100 );

  // map the satisfaction level from [-100, 100]  [discontent, satisfied]
  //   to [0, 100] for front
  //   to [100, 0] for back
  // e.g. -100 discontent == (0, 100) which has the front pulled down and the back elevated

  int front = (s + 100) / 2;
  int back  = 100 - front;
  Romibo.setHeadPosition( front, back );

  // set the eyelids according to energy
  Romibo.setEyelid( 50 + abs(energy_level) / 2);
}

/****************************************************************/
// Choose an characteristic time period in microseconds based on the emotional
// state.  This can be used to time the rocking and bobbing motions, silences,
// dance moves, etc.  As the absolute value of the energy level increases, the
// period decreases for faster motions.  This can be fine-tuned, but the code
// uses multiples of this value assuming that the shortest period is about a
// second.
long time_constant_for_emotion(void)
{
  int e = constrain( abs(energy_level), 0, 100);

  // between 3 seconds and 1 second, for low energy to high energy
  return 3000000 - e*20000;

  // this is effectively the following:
  // return max_period - e * ((max_period-min_period) / 100)
}

/****************************************************************/
const char *choose_sound_for_emotion(void)
{
  switch( classify_emotional_state() ){
  case EMOTION_NEUTRAL:    return random_play_sound();   break;  // origin of the emotion space
  case EMOTION_EXCITED:    return random_happy_sound();  break;  // right quadrant
  case EMOTION_ANGRY:      return random_angry_sound();  break;  // left quadrant
  case EMOTION_SATISFIED:  return random_beckon_sound(); break;  // upper quadrant
  case EMOTION_DISCONTENT: return random_sad_sound();    break;  // lower quadrant 
  }
}

/****************************************************************/
const char *description_for_emotion(void)
{
  switch( classify_emotional_state() ){
  case EMOTION_NEUTRAL:    return "neutral";      break;  // origin of the emotion space
  case EMOTION_EXCITED:    return "excited";      break;  // right quadrant
  case EMOTION_ANGRY:      return "angry";        break;  // left quadrant
  case EMOTION_SATISFIED:  return "satisfied";    break;  // upper quadrant
  case EMOTION_DISCONTENT: return "discontented"; break;  // lower quadrant 
  }
}

/****************************************************************/
void set_random_emotional_state(void)
{
  energy_level       = random( -100, 100 );
  satisfaction_level = random( -100, 100 );
}
/****************************************************************/
void adjust_satisfaction( int delta )
{
  satisfaction_level = constrain( satisfaction_level + delta, -100, 100 );
}
void adjust_energy( int delta )
{
  energy_level = constrain( energy_level + delta, -100, 100 );
}
void set_emotional_state( int e, int s )
{
  energy_level       = constrain( e, -100, 100 );
  satisfaction_level = constrain( s, -100, 100 );
}
/****************************************************************/
