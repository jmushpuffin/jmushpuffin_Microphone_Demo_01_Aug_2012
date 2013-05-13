// Globals.pde : a convenient place to declare global variables.
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

// Global variables controlling the test mode.
int test_mode = 0;
int test_period = 1000;

// Global variables defining the emotional state.
int energy_level       = 0;
int satisfaction_level = 0;

/****************************************************************/

#include "Parameters.h"

struct parameter_descriptor_t global_parameter_descriptor_table[] = {
  { "mode",     &mode   },
  { "state",    &state  },

  { "test_mode",    &test_mode },
  { "test_period",  &test_period },

  { "energy",        &energy_level },
  { "satisfaction",  &satisfaction_level },

};

// Declare the default parameter table object.
#include "Parameters.h"
Parameters parameters( global_parameter_descriptor_table, sizeof(global_parameter_descriptor_table) );

/****************************************************************/
