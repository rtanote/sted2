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

#ifndef _RCPCONV_H_
#define _RCPCONV_H_

extern long rcpconv( unsigned char *,  /* Pointer to RCP data */
		     long,             /* Length (bytes) of RCP data */
		     unsigned char **, /* Destination of conversion */
		     unsigned char *   /* Copyright notice */
		     );

extern long rcpconv_with_notice(
		     unsigned char *,  /* Pointer to RCP data */
		     long,             /* Length (bytes) of RCP data */
		     unsigned char **, /* Destination of conversion */
		     unsigned char *,  /* Copyright notice */
		     unsigned char *,  /* Converter's command name */
		     unsigned char *,  /* Filename of original RCP file */
		     unsigned char *   /* Timestamp of original RCP file */
		     );

#endif / _RCPCONV_H_ */
