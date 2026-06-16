/*
  SMF utility functions

  Copyright 1999 by Daisuke Nagano <breeze.nagano@nifty.ne.jp>
  Mar.14.1999


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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>

#include "smf.h"

int *smf_number_conversion( long num ) {

  /* Max number of result data sequents are limitted to 
     4 bytes. */

  static int smf_number[4];
  int i,j;
  int is_exist_upper_bytes;

  if ( num < 0 || num >= 128*128*128*128) {
    /* invalid smf number */
    return NULL;
  }

  for ( i=0 ; i<4 ; i++ ) {
    smf_number[i]=0;
  }
  i=0;
  is_exist_upper_bytes = 0;

  j = (num / (128*128*128)) % 128;
  if ( j > 0 ) {
    smf_number[i++] = j + 0x80;
    is_exist_upper_bytes = 1;
  }
  j = (num / (128*128)) % 128;
  if ( j > 0 || is_exist_upper_bytes == 1 ) {
    smf_number[i++] = j + 0x80;
    is_exist_upper_bytes = 1;
  }
  j = (num / 128) % 128;
  if ( j > 0 || is_exist_upper_bytes == 1 ) {
    smf_number[i++] = j + 0x80;
  }
  j = num % 128;
  smf_number[i] = j;

  return smf_number;
}

