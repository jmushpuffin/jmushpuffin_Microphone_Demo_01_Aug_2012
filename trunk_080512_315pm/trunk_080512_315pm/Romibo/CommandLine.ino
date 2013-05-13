// CommandLine.pde : simple command processor for interactive debugging and control
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

extern int test_mode;

void print_matching_variable( const char *name, int value )
{
  Console.print(name);
  Console.print(" = ");
  Console.println(value);
}

// Process a command string which has been parsed into tokens.  This is not a
// very efficient interpreter, but simple to code and maintain.  This is called
// from the main event loop, so it may modify global state and trigger events
// but should not stall if it is to be called during normal operation.

void execute_command( int argc, char **argv )
{
  if (argc > 0) {
    if (!strncmp(argv[0], "stat", 4)) {
      Console.print("\nTop photo = ");    Console.print( Romibo.topLightLevel() );
      Console.print("; Left photo = ");   Console.print( Romibo.leftFrontLightLevel() );
      Console.print("; Right photo = ");  Console.println( Romibo.rightFrontLightLevel() );
      Console.print("; Range = ");        Console.println( Romibo.frontRangeDistance() );
      Console.print("; Touch = ");        Console.println( Romibo.touchSwitches() ); 
      Console.print("; mode = ");         Console.println(mode);
      Console.print("; state = ");        Console.print(state);
      Console.print("; loop_count = ");   Console.print(loop_count);
    } 

    else if (!strcmp(argv[0], "get" )) {
      // Print all variables with initial string matching the given string.
      // If none is given, match everything.
      if (argc > 1)  parameters.forEachMatching( print_matching_variable, argv[1] );
      else           parameters.forEachMatching( print_matching_variable, "" );
    }

    else if (!strcmp(argv[0], "set" )) {
      if (argc < 3) Console.println("set command format: set name value");

      // Set the parameter to the given value.
      else parameters.setFirstMatching( argv[1], atoi(argv[2]));
    }
    

    /* this command is part of the host protocol */
    else if (!strcmp(argv[0], "drive" )) {
      int left = 0, right = 0;
      if (argc > 1) left = atoi(argv[1]);
      if (argc > 2) right = atoi(argv[2]);
      Romibo.drive( left, right );
    }

    /* this command is part of the host protocol */
    else if (!strcmp(argv[0], "stop")) {
      Romibo.stop();
    }

    /* this command is part of the host protocol */
    else if (!strcmp(argv[0], "say")) {
      const char *sound = "S1";
      if (argc > 1) {
	// map the abstract sound names to specific sound files
	if      (!strcmp( argv[1], "WHISTLE" )) sound = "BECKON1";
	else if (!strcmp( argv[1], "GROWL" ))   sound = "ANGRY1";
	else if (!strcmp( argv[1], "PLAY" ))    sound = "PLAYWME";
	else if (!strcmp( argv[1], "BYE" ))     sound = "GOODBYE";
	else sound = argv[1];
      }
      Romibo.playSoundNamed( sound );
      Console.print("playing sound "); Console.println( sound );
    }

    /* this command is part of the host protocol */
    else if (!strcmp(argv[0], "antenna")) {
      int color[3] = { 255, 255, 255 };
      if (argc > 1) color[0] = atoi( argv[1] );
      if (argc > 2) color[1] = atoi( argv[2] );
      if (argc > 3) color[2] = atoi( argv[3] );
      Romibo.setAntennaColor(color);
    }

    /* this command is part of the host protocol */
    else if (!strcmp(argv[0], "emote" )) {
      if (argc > 1) energy_level       = atoi(argv[1]);
      if (argc > 2) satisfaction_level = atoi(argv[2]);

      // the antenna color is overridden based on the state
      set_antenna_color_for_emotion();

      // generate some test feedback
      Console.print("set emotions to energy ");
      Console.print( energy_level );
      Console.print(", satisfaction ");
      Console.print( satisfaction_level );
      Console.print(", classified as ");
      Console.println( description_for_emotion() );
    }

    /* these commands are part of the host protocol */
    else if (!strcmp(argv[0], "rock" )) { perform_rock(); }
    else if (!strcmp(argv[0], "bob" ))  { perform_bob();  }
    else if (!strcmp(argv[0], "spin" )) { perform_spin();  }
    else if (!strcmp(argv[0], "turn" )) { perform_turn();  }

    /****************************************************************/
    /* the following commands are defined for debugging and aren't part of the official spec */
    else if (!strcmp(argv[0], "test" )) {
      Romibo.stop();
      mode = MODE_TEST;
      Console.println("Entering test mode. Set test_mode to choose a mode.");
    }

    else if (!strcmp(argv[0], "sensors" )) {
      Romibo.stop();
      mode = MODE_TEST;
      Console.println("Entering sensor test mode.");
      test_mode = 1;
    }

    else if (!strcmp(argv[0], "mic" )) {
      Romibo.stop();
      mode = MODE_TEST;
      Console.println("Entering mic test mode.");
      test_mode = 2;
    }


    else if (!strcmp(argv[0], "tilt")) {
      int front = 50;
      int back  = 50;
      if (argc > 1) front = atoi( argv[1] );
      if (argc > 2) back  = atoi( argv[2] );
      Romibo.setHeadPosition( front, back );
    }

    else if (!strcmp(argv[0], "eye")) {
      int eye = 50;
      if (argc > 1) eye = atoi( argv[1] );
      Romibo.setEyelid( eye );
    }


    else if (!strncmp(argv[0], "forward", 3)) {
      int speed = 100;
      if (argc > 1) speed = atoi(argv[1]);
      Romibo.drive( speed, speed );
    }

    else if (!strcmp(argv[0], "rev")) {
      int speed = 100;
      if (argc > 1) speed = atoi(argv[1]);
      Romibo.drive( -speed, -speed );
    }

    else if (!strcmp(argv[0], "rt")) {
      int speed = 100;
      if (argc > 1) speed = atoi(argv[1]);
      Romibo.drive( Romibo.leftSpeed(), speed );
    }

    else if (!strcmp(argv[0], "lt")) {
      int speed = 100;
      if (argc > 1) speed = atoi(argv[1]);
      Romibo.drive( speed, Romibo.rightSpeed() );
    }

    else if (!strcmp(argv[0], "rot")) {
      int speed = 100;
      if (argc > 1) speed = atoi(argv[1]);
      Romibo.drive( speed, -speed );
    }


    else {
      Console.print("Command not recognized: ");
      Console.println( argv[0] );
    }
  }
}

/****************************************************************/
int parse_arg_line(char *string, char **argv, int argmax)
{
  int argc = 0;
  char *cp = string;
  while (*cp && argc < argmax) {
    while (*cp && isspace(*cp)) cp++;     /* scan past white space */
    if (*cp) argv[argc++] = cp;           /* save pointer to text */  
    else break;
    while (*cp && !isspace(*cp)) cp++;    /* scan past text */
    if (*cp) *cp++ = 0;
  }
  return argc;
}

/****************************************************************/
// Define a simple global buffer for accumulating a command string.
const int max_command_length = 80;
const int max_command_terms  =  5;
static char command_buffer[max_command_length+1];
static int next_command_char = 0;

// Polling function to be called from the main event loop.
void poll_command_input(void)
{
  while (Serial.available()) {
    int next_char = Serial.read();

    // once a line terminator is received, process the available command string
    if (next_char == '\r') {
      command_buffer[next_command_char] = 0; // terminate the string

      // parse the string into pieces and execute them
      char *argv[max_command_terms];
      int argc = parse_arg_line( command_buffer, argv, max_command_terms);
      execute_command(argc, argv);

      // then reset the command buffer
      next_command_char = 0;
    }

    // else store the characters until a full line is received, ignoring overrun
    if (next_command_char < max_command_length) {
      command_buffer[next_command_char++] = next_char;
    }
  }
}
/****************************************************************/
#if ROMIBO_WIFLY_INSTALLED
// This should be refactored with the previous function.
// Polling function to be called from the main event loop.
void poll_network_input(void)
{
  static char command_buffer[max_command_length+1];
  static int next_command_char = 0;
  static int connected = 0;

  while (Serial1.available()) {
    int next_char = Serial1.read();

    // once a line terminator is received, process the available command string
    if (next_char == '\r') {
      command_buffer[next_command_char] = 0; // terminate the string

      Console.print("received network command: ");
      Console.println( command_buffer );

      // parse the string into pieces and execute them
      char *argv[max_command_terms];
      int argc = parse_arg_line( command_buffer, argv, max_command_terms);

      // a little logic to ignore handshaking output from the WiFly until the stream is established
      if (!connected) {
	if (argc > 0 && !strcmp( argv[0], "begin")) connected = 1;

      } else {
	if (argc > 0 && !strcmp( argv[0], "end")) connected = 0;
	else execute_command(argc, argv);
      }

      // then reset the command buffer
      next_command_char = 0;
    }

    // else store the characters until a full line is received, ignoring overrun
    if (next_command_char < max_command_length) {
      command_buffer[next_command_char++] = next_char;
    }
  }
}

#endif
/****************************************************************/
