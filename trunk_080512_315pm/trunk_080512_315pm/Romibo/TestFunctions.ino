/* These are the functions that were used for testing MEmote. They test many of MEmote's
 * various capabilities. None of these functions are currently in use but feel free to
 * mess around with them and create your own!
 */

// Spirals outward
void circle(void) {
    int left_spd = ((loop_count - behav_start) >> 0) - 255;
    if (left_spd > 255) {
        left_spd = 255;
    }

    Romibo.setDriveMotor(LEFT, left_spd, (left_spd < 0) ? -left_spd : left_spd);
    Romibo.setDriveMotor(RIGHT, 1, 255);
}

// Turns left and right
void dance(void) {

    // Turn left for half the time, then turn right (these timings are too short now)
    if (loop_count % 8 < 4) {
        Romibo.setDriveMotor(LEFT, -1, 255);
        Romibo.setDriveMotor(RIGHT, 1, 255);
    }

    else {
        Romibo.setDriveMotor(LEFT, 1, 255);
        Romibo.setDriveMotor(RIGHT, -1, 255);
    }
}

// Hides in the dark
void hide(void){
   int steer = 6 * (Romibo.rightFrontLightLevel() - Romibo.leftFrontLightLevel());

   if(Romibo.obstacleProximity() != CLOSE){
     int val_r = 255;
     int val_l = 255;
     if(steer > 0)
       val_l -= ((int)steer * STEER_CALIBRATION);
     else
       val_r += ((int)steer * STEER_CALIBRATION);
     val_r = (val_r < -255) ? -255 : val_r;
     val_l = (val_l < -255) ? -255 : val_l;
     Romibo.setDriveMotor(LEFT,  (val_l > 0), (val_l > 0) ? val_l : -val_l);
     Romibo.setDriveMotor(RIGHT, (val_r > 0), (val_r > 0) ? val_r : -val_r);
  }else{
     Romibo.setDriveMotor(LEFT,  (steer > 0), 255);
     Romibo.setDriveMotor(RIGHT, (steer < 0), 255);
     Romibo.delay(1000);
  }
}

// Quick and easy test for the range finder
void led_range(void){
    if(Romibo.obstacleProximity() == CLOSE)
        Romibo.setAntennaColor(mad_color);
    else if(Romibo.obstacleProximity() == MEDIUM)
        Romibo.setAntennaColor(happy_color);
    else if(Romibo.obstacleProximity() == FAR)
        Romibo.setAntennaColor(sad_color);
    else Romibo.setAntennaColor(curious_color);
}

// Check mood color and servo alignments
void moodTest(void){
  Romibo.setAntennaColor(mad_color);
  set_servos(mad_angles1);
  Romibo.delay(1000);
  set_servos(mad_angles2);
  Romibo.delay(1000);
  Romibo.setAntennaColor(sad_color);
  set_servos(sad_angles1);
  Romibo.delay(1000);
  set_servos(sad_angles2);
  Romibo.delay(1000);
  Romibo.setAntennaColor(curious_color);
  set_servos(curious_angles1);
  Romibo.delay(1000);
  set_servos(curious_angles2);
  Romibo.delay(1000);
  Romibo.setAntennaColor(happy_color);
  set_servos(happy_angles1);
  Romibo.delay(1000);
  set_servos(happy_angles2);
  Romibo.delay(1000);
}

// Test function for sounds.  No particular order
void playDifferentSounds(void)
{
  Romibo.playSoundNamed("S1");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed("S4");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed("S7");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed("S3");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed("S9");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed("S15");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed("S2");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed("S1");
  Romibo.waitForSoundToFinish();
  Romibo.playSoundNamed("S1");
}
