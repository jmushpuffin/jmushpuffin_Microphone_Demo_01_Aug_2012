// REMOTE CONTROL TIME THRESHOLD VALUES
// This is how long (in Microseconds) a bit needs to be seen by the sensor to determine that it
// is an actual value and not noise.

#include "RomiboPinMappings.h"

const int start_bit = 2200; // Start Bit
const int bin_1 = 1000;     // Binary 1
const int bin_0 = 400;      // Binary 0

int getIRKey(void) 
{
  int data[12];
  int i;

  while(pulseIn(irPin, LOW) < start_bit); //Wait for a start bit
  
  for(i = 0 ; i < 11 ; i++)
    data[i] = pulseIn(irPin, LOW); //Start measuring bits, I only want low pulses
  
  for(i = 0 ; i < 11 ; i++) //Parse them
  {	    
    if(data[i] > bin_1) //is it a 1?
      data[i] = 1;
    else if(data[i] > bin_0) //is it a 0?
      data[i] = 0;
    else
      return -1; //Flag the data as invalid. Return -1 on invalid data
  }

  int result = 0;
  for(i = 0 ; i < 11 ; i++) //Convert data bits to integer
    if(data[i] == 1) result |= (1<<i);

  return result; //Return key number
} 
