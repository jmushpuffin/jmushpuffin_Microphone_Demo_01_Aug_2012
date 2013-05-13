// MoodFunctions.ino : the original behavior code
/****************************************************************/

// Event loop entry point for the normal operating mode. 

void original_state_machine(void) {
    int new_mode = -1;
    
    // Here the robot does sampling which will be used below to determine the next 
    // mode and and servo behaviors.
    int range = Romibo.obstacleProximity();
    int light = Romibo.topBrightness();
    boolean pet = (Romibo.touchSwitches() != 0);
    int dir = 6 * (Romibo.rightFrontLightLevel() - Romibo.leftFrontLightLevel());

    // The robot continues to sample however after a set amount of time (number of loops)
    // in one mode it will decide whether or not to change modes.    
    if (loop_count > mode_delays[state]) {
      
        // Robot choses modes based on sensed proximity and light levels.
  
/*        if ( pet  == true ){
        
            new_mode = HAPPY;

        }
        
        else if( mode == WANDER && light == MEDIUM &&
                 dir > -NEGL    && dir < NEGL         ){
          
            new_mode = WANDER;
          
        }  
        
        else if ( (range == CLOSE  && light == BRIGHT) ||   // close and bright, or
                  (range == MEDIUM && light == BRIGHT) ||   // med and bright, or
                  (range == FAR    && light == BRIGHT) ) {  // far and bright

            new_mode = MAD;

        }

        else if ( (range == CLOSE && light == DARK) ||     // close and dark, or
                  (range == FAR   && light == DARK)   ) {  // far and dark

            new_mode = SAD;

        }

        else if ( (range == FAR    && light == MEDIUM) ||  // far and med, or
                  (range == CLOSE  && light == MEDIUM) ||  // close and med
                  (range == MEDIUM && light == DARK)  ) {  // med and dark

            new_mode = CURIOUS;

        }

        else if ( range == MEDIUM && light == MEDIUM ) {  // med and med

            new_mode = HAPPY;

        }



*/










            new_mode = WANDER;







        // If the robot determines that it should change mode based on what is being sensed after the 
        // mode delay has expired, then we will switch to the new mode and reset the loop counter 
        // or the amount of time spent in a current mode.
        if (new_mode >= 0 && new_mode != state) {
            state = new_mode;
            loop_count = 0;
        }
    }

    // Depending on the current mode the robot sets the LEDs to their appropriate color and 
    // calls the appropriate do_* function for the mode.
    switch (state) {
        case WANDER:
            wander_around();
            break;
            
        case MAD:
            Romibo.setAntennaColor(mad_color);
            do_mad();
            break;

        case SAD:
            Romibo.setAntennaColor(sad_color);
            do_sad();
            break;

        case CURIOUS:
            Romibo.setAntennaColor(curious_color);
            do_curious();
            break;

        case HAPPY:
            Romibo.setAntennaColor(happy_color);

            if(pet) bob(BOB_DUR_HAPPY);
            else do_happy();

            break;
            
        default:
            break;
    }

    // Here we increment the amount of time that we have been in this mode which is used above.
    {
      static unsigned last_sensor_count = 0;
      unsigned samples = Romibo.sensorSamples();
      loop_count += (samples - last_sensor_count);
      last_sensor_count = samples;
    }

    if ((loop_count % 20) == 0) Console.print(".");
}
/****************************************************************/

void wander_around(void){
  int range = Romibo.obstacleProximity();
  int direc = 0;
  
  if(range == CLOSE){
//    wander_length = 0;
    direc = 6 * (Romibo.rightFrontLightLevel() - Romibo.leftFrontLightLevel());
    // Interrupt the walk, we're about to run into something
    Romibo.stop();
    Romibo.setDriveMotor(LEFT, -direc, 255);
    Romibo.setDriveMotor(RIGHT, direc, 255);
//    Romibo.delay(700);
  }else{
    if(random(0, 2)) direc = -1;
    else direc = 1;
  }
  
  // I'm done moving, so stop and do some action and make a sound
  if(loop_count > wander_start + wander_length){
    
    // Close means already spinning
    if(range != CLOSE){
      Romibo.stop();
      
      // Rotate here
      Romibo.setDriveMotor(LEFT, -direc, 255);
      Romibo.setDriveMotor(RIGHT, direc, 255);
      
    }
    Romibo.delay(random(2, 5) * 100);
    
    // Slightly higher than 50% chance to do an action
    int action_num = random(1, NUMSOUNDS * 2); // S1 - S(2#)
    if(action_num <= NUMSOUNDS){
      Romibo.stop();
//      Romibo.delay(25);
      
      if(action_num >= 1 && action_num <= 5){
        Romibo.setAntennaColor(happy_color);
        set_servos(happy_angles1);
      }else if(action_num >= 6 && action_num <= 10){
        Romibo.setAntennaColor(sad_color);
        set_servos(sad_angles1);
      }else if(action_num >= 11 && action_num <= 15){
        Romibo.setAntennaColor(curious_color);
        set_servos(curious_angles1);        
      }else if(action_num >= 16 && action_num <= 20){
        Romibo.setAntennaColor(mad_color);
        set_servos(mad_angles1);
      }
      
      char sound_buf[12];
      String str = itoa( action_num, sound_buf, 10 );
      String str2 = "S" + str;
      str2.toCharArray(sound_buf, 12);
      Romibo.playSoundNamed(sound_buf);

//      Romibo.waitForSoundToFinish();
//      Romibo.delay(50);
      
      if(action_num >= 6 && action_num <= 10){
         set_servos(sad_angles2); 
      }
      
      Romibo.setDriveMotor(LEFT, -direc, 255);
      Romibo.setDriveMotor(RIGHT, direc, 255);
    }
    
    // Rotate again first   
    Romibo.delay(random(5, 9) * 100);
    Romibo.stop();
//    Romibo.delay(25);
    
    // Let's start moving again!
    wander_start = loop_count;
    wander_length = random(1, 6) * LOOPS_PER_SECOND;

    Romibo.setDriveMotor(LEFT, 1, 255);
    Romibo.setDriveMotor(RIGHT, 1, 255);
  }
  
}

// In every loop one of the functions below is called to govern the servos and the motors
// based on the current mode and what is sensed by the range finder. 
void do_mad(void) {
    int range = Romibo.obstacleProximity();

    // If the range is != 1(medium) then we set the servos statically.
    if (range != 1) {
      
      // Every 1.5 seconds alternate between mad_angles1 and mad_angles2. 
      // Every 3 seconds loop_count % (3 * LOOPS_PER_SECOND) loops between 
      // 0 and 3 * LOOPS_PER_SECOND - 1.  In the first half of the range we set mad_angles1
      // in the second half we set to mad_angles2.
      if (loop_count % (3 * LOOPS_PER_SECOND) < (3 * LOOPS_PER_SECOND / 2)) {
        set_servos(mad_angles1);
      }
      else {
        set_servos(mad_angles2);
      }
    }
    // Records when we start being in the current range.  This is used for turning in a circle but
    // the robot is not currently using that function.
    if (range != last_range) {
        behav_start = loop_count;
        last_range = range;
    }

    // Here it is looking at the value sampled by the range finder and is deciding what to do.
    switch (range) {
        case 0: // CLOSE
            Romibo.driveBackward( 100 );
            break;

        case 1: // MEDIUM
            bob(BOB_DUR_MAD);
            break;

        case 2: // FAR
            run();
            break;

        default:
            break;
    }
}


//Do_sad, Do_mad, Do_curious and do_happy all go through the same basic functions but with
//different servo angles and bob durations.

void do_sad(void) {

    int range = Romibo.obstacleProximity();

    if (range != 1) {
      if (loop_count % (3 * LOOPS_PER_SECOND) < (3 * LOOPS_PER_SECOND / 2)) {
        set_servos(sad_angles1);
      }
      else {
        set_servos(sad_angles2);
      }
    }

    if (range != last_range) {
        behav_start = loop_count;
        last_range = range;
    }

    switch (range) {
        case 0: // CLOSE
          Romibo.driveBackward( 100 );
          break;
        case 1: // MEDIUM
            bob(BOB_DUR_SAD);
            break;

        case 2: // FAR
            run();
            break;
      
        default:
            break;
    }
}

void do_curious(void) {
    int range = Romibo.obstacleProximity();
    if (range != 1) {
      if (loop_count % (3 * LOOPS_PER_SECOND) < (3 * LOOPS_PER_SECOND / 2)) {
        set_servos(curious_angles1);
      }
      else {
        set_servos(curious_angles2);
      }
    }

    if (range != last_range) {
        behav_start = loop_count;
        last_range = range;
    }

    switch (range) {
        case 0: // CLOSE
          Romibo.driveBackward( 100 );
          break;

        case 1: // MEDIUM
            bob(BOB_DUR_CURIOUS);
            break;

        case 2: // FAR
            run();
            break;

        default:
            break;
    }
}

void do_happy(void) {
    int range = Romibo.obstacleProximity();
    if (range != 1) {
      if (loop_count % (3 * LOOPS_PER_SECOND) < (3 * LOOPS_PER_SECOND / 2)) {
        set_servos(happy_angles1);
      }
      else {
        set_servos(happy_angles2);
      }
    }

    if (range != last_range) {
        behav_start = loop_count;
        last_range = range;
    }

    switch (range) {
        case 0: // CLOSE
            Romibo.driveBackward( 100 );
            break;

        case 1: // MEDIUM
            bob(BOB_DUR_HAPPY);
            break;

        case 2: // FAR
            run();
            break;

        default:
            break;
    }
}

