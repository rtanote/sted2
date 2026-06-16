/*
  RCP converter

  Copyright 1999 by Daisuke Nagano <breeze.nagano@nifty.ne.jp>
  May.28.1999

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <stdio.h>
#include <stdlib.h>

#include "rcp.h"
#include "rcpconv.h"

long rcpconv( unsigned char *data, long length, unsigned char **smf, 
	      unsigned char *copyright ) {

  RCP_DATA rcp;
  long smf_length;

  rcp.length       = length;
  rcp.data         = data;
  rcp.date         = NULL;  /* timestamp text (ctime) of original RCP file */
  rcp.file_name    = NULL;  /* filename of original RCP file */
#ifdef RCPCONV_COMMAND_NAME
  rcp.command_name = RCPCONV_COMMAND_NAME;
#else
  rcp.command_name = NULL;
#endif
  rcp.copyright    = copyright;

  rcp.enable_converter_notice = FLAG_FALSE;
  rcp.enable_verbose          = FLAG_FALSE;

  *smf = rcptomid( &rcp );
  if ( *smf == NULL ) smf_length = -10;
  else smf_length = rcp.smf_size;

  return smf_length;
}

long rcpconv_with_notice( unsigned char *data, long length, unsigned char **smf, 
			  unsigned char *copyright,
			  unsigned char *command_name,
			  unsigned char *file_name,
			  unsigned char *date ) {

  RCP_DATA rcp;
  long smf_length;

  rcp.length       = length;
  rcp.data         = data;
  rcp.date         = date;
  rcp.file_name    = file_name;
  rcp.command_name = command_name;
  rcp.copyright    = copyright;

  rcp.enable_converter_notice = FLAG_TRUE;
  rcp.enable_verbose          = FLAG_FALSE;

  *smf = rcptomid( &rcp );
  if ( *smf == NULL ) smf_length = -10;
  else smf_length = rcp.smf_size;

  return smf_length;
}
