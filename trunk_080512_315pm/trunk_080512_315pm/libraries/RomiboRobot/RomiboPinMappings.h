// RomiboPinMappings.h : definitions for the Romibo hardware interface
// Copyright (c) 2011 Aubrey Shick, Brian Pfiffner, Garth Zeglin
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
#ifndef __ROMIBOPINMAPPINGS_H_INCLUDED__
#define __ROMIBOPINMAPPINGS_H_INCLUDED__

#include "RomiboConfig.h"  // Use the top-level source-code configuration settings.

// Define the pins to which various bits of hardware are attached.  In all cases
// the pin number is the value passed to the corresponding Arduino library
// functions.  E.g., analog input A1 is simply 1 and is valid for analogRead(),
// digital input D1 (a different physical input) is also simply 1 and is valid
// for digitalRead().

// Note that the SD Card interface is not specified here, that is buried in the
// RomiboSound library (a modified WaveHC library).

#if ROMIBO_ELECTRONICS_MAJOR_REV == 0
// Version 1 is the the version of Memote without the Arduino shield.  This
// section will eventually be eliminated. This isn't actually in a compilable
// state.
const int tilt_servo_pin[3] = { 12, 13, 8 };
const int rgb_led[3]        = { 11, 10, 9 };
const int dac_sckPin        = 44;
const int dac_sdiPin        = 46;
const int dac_ldacPin       = 48;
const int irPin             = 28;
const int touch_sensor[4]   = { 29, 31, 33, 35 };
#endif

//===============================================================================
// Rev1 and Rev2 are very similar.
#if (ROMIBO_ELECTRONICS_MAJOR_REV==1) || (ROMIBO_ELECTRONICS_MAJOR_REV==2)

// -------------------------- Output Pins ----------------------------------------
// Motors.  Left and right indexes are used so = {left, right}.  Each direction
// input controls the current flow in a half bridge, e.g. a high input on 1A
// will drive the 1Y output from the motor supply.  The corresponding enable
// input turns on a pair of half-bridges when high, or allows them to float when
// low, and is used as a PWM input.  This is not a servo PWM signal, but a
// variable duty cycle square wave.

enum { ROMIBO_LEFT_MOTOR = 0, ROMIBO_RIGHT_MOTOR = 1 };
const int mot_fwd_pin[2] = {2, 7};  // direction pins:  SN754410 inputs 1A, 4A
const int mot_rev_pin[2] = {3, 4};  // direction pins:  SN754410 inputs 2A, 3A
const int mot_spd_pin[2] = {5, 6};  // PWM pins:        SN754410 inputs 1-2EN, 3-4EN

// Servos = front, back, eye.  These are digital outputs which generate the
// servo-command format PWM signal.
enum { ROMIBO_FRONT_SERVO, ROMIBO_BACK_SERVO, ROMIBO_EYE_SERVO };
const int tilt_servo_pin[3] = {12, 8, 14};

// RGB Leds: red, green, blue.  These are digital outputs.
const int rgb_led[3] = {11, 9, 10}; // PWM pins

// Sound D/A converter.  These are digital outputs.
const int dac_csPin   = 42;  // Chip Select
const int dac_sckPin  = 43;  // Serial Clock
const int dac_sdiPin  = 44;  // Serial Data In
const int dac_ldacPin = 45;  // LDAC

// -------------------------- Input Pins ----------------------------------------

// Analog range finder on analog input A1.
const int range_finder = 1;

// Photo sensor.  These are CdS cells on analog inputs.
// On the Arduino Shield Rev2: JP9==right, JP10==left, JP11=top.
enum { ROMIBO_PHOTO_RIGHT, ROMIBO_PHOTO_LEFT, ROMIBO_PHOTO_TOP };
const int photo_sensor[3] = {3, 2, 4}; // left, right, top

// Remote Control.  This is a digital input.
#if !ROMIBO_AUDIO_PWM_ENABLED
const int irPin = 13;  // usage conflicts with OC1C for audio
#endif

// Audio PWM output.
#if ROMIBO_AUDIO_PWM_ENABLED
const int audio_PWM_pin = 13; // OC1C timer compare output
#endif

// Touch switches, defined in the wiring order. These are digital inputs from microswitches.
enum { ROMIBO_TOUCH_LEFT, ROMIBO_TOUCH_BOTTOM, ROMIBO_TOUCH_RIGHT, ROMIBO_TOUCH_TOP,ROMIBO_NUM_TOUCH_SWITCHES };
const int touch_sensor[4] = {28, 29, 30, 31};

// Corresponding masks for the combined switch value:
#define ROMIBO_TOUCH_TOP_BIT    (1 << ROMIBO_TOUCH_TOP)
#define ROMIBO_TOUCH_LEFT_BIT   (1 << ROMIBO_TOUCH_LEFT)
#define ROMIBO_TOUCH_RIGHT_BIT  (1 << ROMIBO_TOUCH_RIGHT)
#define ROMIBO_TOUCH_BOTTOM_BIT (1 << ROMIBO_TOUCH_BOTTOM)

// Unassigned analog input pin for use by the random number generator.
const int unassigned_pin = 15;

#if ROMIBO_ELECTRONICS_MAJOR_REV >= 2
// Microphone input, added in Shield Rev 2.  As designed, this was connected to
// digital input 32, but was rewired to an analog input.  There is no envelope
// detector, the audio rate signal is presented at the pin.  We are not sampling
// very fast, so the data is highly aliased, and the best hope is to try to
// detect overall energy from peaks.

const int microphone_pin = 5;
#define ROMIBO_MICROPHONE_DEFINED 1
#endif

#endif // Rev1 or Rev2

// ==============================================================================
// ==============================================================================
#if (ROMIBO_ELECTRONICS_MAJOR_REV==3)

// -------------------------- Output Pins ----------------------------------------
// Motors.  Left and right indexes are used so = {left, right}.  Each driver
// input controls the state of one driver output.  So forward = {1,0}, reverse
// is {0,1}, coast is {0,0}, brake is {1,1}.  Fast-decay PWM switches between a
// drive state and coast, so one pin or the other requires PWM, depending on
// direction. (This is not a servo PWM signal, but a variable duty cycle square
// wave.)

enum { ROMIBO_LEFT_MOTOR = 0, ROMIBO_RIGHT_MOTOR = 1 };
const int mot_drv1_pin[2] = { 2, 7 };   // DRV8833 inputs IN1
const int mot_drv2_pin[2] = { 3, 8 };   // DRV8833 inputs IN2

// Servos = front, back, eye.  These are digital outputs which generate the
// servo-command format PWM signal.
enum { ROMIBO_FRONT_SERVO, ROMIBO_BACK_SERVO, ROMIBO_EYE_SERVO };
const int tilt_servo_pin[3] = { 40, 39, 38 };

// RGB Leds: red, green, blue.  These are digital PWM outputs.
const int rgb_led[3] = { 4, 9, 10 }; // PWM pins

// Sound D/A converter.  These are digital outputs.
const int dac_csPin   = 42;  // Chip Select
const int dac_sckPin  = 43;  // Serial Clock
const int dac_sdiPin  = 44;  // Serial Data In
const int dac_ldacPin = 45;  // LDAC

// Audio PWM output.
const int audio_PWM_pin = 13; // OC1C timer compare output

// -------------------------- Input Pins ----------------------------------------

// Analog range finder on analog input A1.
const int range_finder = 1;

// Photo sensor.  These are CdS cells on analog inputs.
// On the Arduino Shield Rev2: JP9==right, JP10==left, JP11=top.
enum { ROMIBO_PHOTO_RIGHT, ROMIBO_PHOTO_LEFT, ROMIBO_PHOTO_TOP };
const int photo_sensor[3] = {3, 2, 4}; // left, right, top

// Remote Control.  This is a digital input. Pin48 is also ICP5 to allow hardware edge capture.
const int irPin = 48;

// Touch switches, defined in the wiring order. These are digital inputs from microswitches.
enum { ROMIBO_TOUCH_LEFT, ROMIBO_TOUCH_BOTTOM, ROMIBO_TOUCH_RIGHT, ROMIBO_TOUCH_TOP,ROMIBO_NUM_TOUCH_SWITCHES };
const int touch_sensor[4] = {28, 29, 30, 31};

// Corresponding masks for the combined switch value:
#define ROMIBO_TOUCH_TOP_BIT    (1 << ROMIBO_TOUCH_TOP)
#define ROMIBO_TOUCH_LEFT_BIT   (1 << ROMIBO_TOUCH_LEFT)
#define ROMIBO_TOUCH_RIGHT_BIT  (1 << ROMIBO_TOUCH_RIGHT)
#define ROMIBO_TOUCH_BOTTOM_BIT (1 << ROMIBO_TOUCH_BOTTOM)

// Unassigned analog input pin for use by the random number generator.
const int unassigned_pin = 15;

// Microphone input, added in Shield Rev 2.  The audio rate signal is presented
// at the pin.  We are not sampling very fast, so the signal data is highly aliased.

const int microphone_pin = 5;
#define ROMIBO_MICROPHONE_DEFINED 1

#endif // Rev3
// ==============================================================================

#endif __ROMIBOPINMAPPINGS_H_INCLUDED__
