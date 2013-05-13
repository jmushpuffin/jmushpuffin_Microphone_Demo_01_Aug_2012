// SoundLibrary.ino : provide an abstract interface for choosing sound files
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

static const char *angry_sounds[] = {
  "ANGRY1",
  "ANGRY2",
  "ANGRY3",
};

static const char *happy_sounds[] = {
  "HAPPY1",
  "HAPPY2",
  "HAPPY3",
};
static const char *sad_sounds[] = {
  "SAD1",
  "SAD2",
  "SAD3",
  "SAD4",
  "SAD5",
  "SAD6",
};
static const char *beckon_sounds[] = {
  "BECKON1",
  "BECKON2",
  "BECKON3",
  "BECKON4",
  "BECKON5",
  "BECKON6",
};

static const char *question_sounds[] = {
  "QUEST1",
  "QUEST2",
};

static const char *play_sounds[] = {
  "LETSPLA1",
  "LETSPLA2",
  "PLAYWME",
};

static const char *greeting_sounds[] = {
  "AWESOME",
  "GOODBYE",
  "HELLO",
};

#define NUM_HAPPY_SOUNDS    (sizeof(happy_sounds) / sizeof(char *))
#define NUM_ANGRY_SOUNDS    (sizeof(angry_sounds) / sizeof(char *))
#define NUM_SAD_SOUNDS      (sizeof(sad_sounds) / sizeof(char *))
#define NUM_BECKON_SOUNDS   (sizeof(beckon_sounds) / sizeof(char *))
#define NUM_QUESTION_SOUNDS (sizeof(question_sounds) / sizeof(char *))
#define NUM_PLAY_SOUNDS (sizeof(play_sounds) / sizeof(char *))
#define NUM_GREETING_SOUNDS    (sizeof(greeting_sounds) / sizeof(char *))

/*****************************************************************/
static const char *digit_sounds[10] = {
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

// other utility sounds:
//  "POWERON"

/****************************************************************/
const char *digit_sound( int digit ) {
  return digit_sounds[ constrain( digit, 0, 9 ) ];
}

/****************************************************************/
const char *random_play_sound(void)     { return play_sounds    [ random( NUM_PLAY_SOUNDS ) ]; }
const char *random_happy_sound(void) 	{ return happy_sounds   [ random( NUM_HAPPY_SOUNDS ) ]; }
const char *random_angry_sound(void) 	{ return angry_sounds   [ random( NUM_ANGRY_SOUNDS ) ]; }
const char *random_beckon_sound(void)   { return beckon_sounds  [ random( NUM_BECKON_SOUNDS ) ]; }
const char *random_sad_sound(void)      { return sad_sounds     [ random( NUM_SAD_SOUNDS ) ]; }

const char *random_question_sound(void) { return question_sounds[ random( NUM_QUESTION_SOUNDS ) ]; }
const char *random_greeting_sound(void) { return greeting_sounds[ random( NUM_GREETING_SOUNDS ) ]; }

/****************************************************************/
