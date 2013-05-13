
//#define VERSION1

// We used serial output for debugging, but this slowed down the main loop speed so much that
// we could not move servos smoothly.  We can uncomment this line to reenable serial output.
// #define DEBUG

// Used for array indexes and readability:
#define LEFT 0
#define RIGHT 1
#define TOP 2

#define RED 0
#define GREEN 1
#define BLUE 2

enum { 
  WANDER = 0,
  MAD,
  SAD,
  CURIOUS,
  HAPPY,

  NUM_STATES
};


#define DARK 0
#define BRIGHT 2
#define MEDIUM 1
#define CLOSE 0
#define FAR 2

enum {
  MODE_AUTONOMOUS = 0,
  MODE_ORIGINAL,
  MODE_R_CONTROL,
  MODE_TEST
};

// The values that the remote control returns and which button creates that value.  May be
// different depending on the remote.
#define POWER 149
#define CH_UP 144
#define CH_DOWN 145
#define VOL_UP 146
#define VOL_DOWN 147
#define MUTE 148
#define AV_TV 165

// We count iterations of the main loop to estimate time.
// This is a rough estimate of the number of loop iterations per second. we may need to change 
// this if loops become faster or slower.
#define LOOPS_PER_SECOND 100

// The scaling factor between light sensor values and steering amount.  This value should be
// large enough so that the robot steers strongly towards a light source, but small enough 
// so that it does not wander when pointed at a light source.
#define STEER_CALIBRATION 3.0

// The duration of head bobs for each mode in loop iterations.
// These values need to be powers of 2 so that bob motion remains smooth when the loop counter
// wraps around.  
#define BOB_DUR_MAD     256
#define BOB_DUR_HAPPY   256
#define BOB_DUR_CURIOUS 512
#define BOB_DUR_SAD     1024

// The offset if the photoresistors are reading values very far from each other
// Positive numbers add to the LEFT photoresistor while negative adds to the RIGHT one
#define PHOTO_HARDWARE_OFFSET 220

#define RANGE_MAX 600
#define NEGL 150

// The current number of sounds on the SD Card
#define NUMSOUNDS 20

