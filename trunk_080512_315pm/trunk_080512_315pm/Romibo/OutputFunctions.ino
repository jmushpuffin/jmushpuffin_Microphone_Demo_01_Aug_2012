// Sets all 3 servos to given angles.  Deprecated.  This maps the previous
// uncalibrated values to the new calibrated system.
void set_servos(int *angles) 
{
  Romibo.setHeadPosition( map( angles[0], 135, 180, 100,   0 ),
			  map( angles[1],   0,  45,   0, 100 ) );
  Romibo.setEyelid( map( angles[2], 40, 140, 100, 0 ) );
}

// Sets a single servo the given angles.  Deprecated.  This maps the previous
// uncalibrated values to the new calibrated system.
void write_neck_servo( int angle0, int angle1 ) 
{
  Romibo.setHeadPosition( map( angle0, 135, 180, 100,   0 ),
			  map( angle1,   0,  45,   0, 100 ) );
}

/****************************************************************/

// dur is the number of loop iterations it takes to make a half-bob
void bob(int dur)
{
  Romibo.stop();
  // The halfbob amount is where we are in a half cycle - determines angle of change
  // a fullbob is where we are in the full cycle.
  int halfbob_amount = (loop_count % dur);
  int fullbob_amount = (loop_count % (dur * 2));
  
  // Determines how far the servo is from its starting position. 
  // we divide by 10 to avoid overflow. the value 10 really depends on LOOPS_PER_SECOND, but
  // hopefully it is small enough to be correct for most cases.
  int halfbob_angle_change = 45 * (halfbob_amount / 10) / (dur / 10);
  
  // see if we should bob up or down
  // looks at where we are in the bob to determine whether we're in the down part(first half)
  // or the up part(second half).  
  // If where we are in the cycle is less than half a cycle then we are in the first half.
  if (fullbob_amount < dur) {
    // Bobbing down - we start at the fully extended angles and go down
    write_neck_servo( (135 + halfbob_angle_change), (45  - halfbob_angle_change) );
  } else {
    // Bobbing up - we start at the rest angles and go up
    write_neck_servo( (180 - halfbob_angle_change), (0   + halfbob_angle_change) );
  }
}

// Drive toward the strongest light source as fast as we can. 
void run(void) {
    // Compares the raw values of the left and right photoresistors
    int steer = 6 * (Romibo.rightFrontLightLevel() - Romibo.leftFrontLightLevel());
    // One wheel is always going forward at full speed 
    // the wheel on the same side as the higher photoresistor value should turn slower
    // or go backwards
    int val_r = 255;
    int val_l = 255;
    // The slower wheel should go slower or reverse in proportion to the difference betweek
    // the photoresistor values.  We scale this difference so that the robot turns strongly
    // towards a light source but does not wander when pointed directly at a light source.
    if (steer > 0)
      val_l -= ((int)steer * STEER_CALIBRATION);
    else
      val_r += ((int)steer * STEER_CALIBRATION);
    // We clip val_l and val_r to be between 255 and -255.  
    val_r = (val_r < -255) ? -255 : val_r;
    val_l = (val_l < -255) ? -255 : val_l;
    // Send the proportionate drive command to the motors
    Romibo.setDriveMotor(LEFT,  (val_l > 0), (val_l > 0) ? val_l : -val_l);
    Romibo.setDriveMotor(RIGHT, (val_r > 0), (val_r > 0) ? val_r : -val_r);
}



