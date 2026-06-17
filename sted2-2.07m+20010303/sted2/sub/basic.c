/* basic.c

   some of X-BASIC compatible functions

   Made by Studio Breeze. 1998

*/

#include "sted.h"


/* graphic functions */

void fill( int x1, int y1, int x2, int y2, unsigned int col ) {

  if ( isconsole ) {
    curses_gfill( x1, y1, x2, y2, col );

  } else if ( isxwin ) {
    XSTed_gfill( x1, y1, x2, y2, col );
  }
  return;
}

void box( int x1, int y1, int x2, int y2, unsigned int col, unsigned int ls ) {

  if ( isxwin ) {
    XSTed_gbox( x1, y1, x2, y2, col, ls );
  }
  return;
}

int point( int x, int y ) {

  int ret=0;
  if ( isxwin ) {
    ret = XSTed_gpoint( x, y );
  }
  return ret;
}

void line( int x1, int y1, int x2, int y2, int col, int ls ) {

  if ( isxwin ) {
    XSTed_gline( x1, y1, x2, y2, col ,ls );
  }
  return;
}

/* PROTOTYPE: vector-drawn music note head + stem/flag + ledger + rest + dot */
extern void XSTed_gnote_head( int x, int y, int filled, int col );
extern void XSTed_gnote_stem_flag( int xc, int y_top, int y_bottom, int ss, int col );
extern void XSTed_gledger( int x, int y, int col );
extern void XSTed_grest( int x, int y, int ss, int col );
extern void XSTed_gnote_dot( int x, int y, int col );
extern void XSTed_grest_dots( int x, int y, int dots, int col );

void note_head_print( int x, int y, int filled, int col ) {
  if ( isxwin ) {
    XSTed_gnote_head( x, y, filled, col );
  }
  return;
}

void note_stem_flag_print( int xc, int y_top, int y_bottom, int ss, int col ) {
  if ( isxwin ) {
    XSTed_gnote_stem_flag( xc, y_top, y_bottom, ss, col );
  }
  return;
}

void ledger_line_print( int x, int y, int col ) {
  if ( isxwin ) {
    XSTed_gledger( x, y, col );
  }
  return;
}

void note_rest_print( int x, int y, int ss, int col ) {
  if ( isxwin ) {
    XSTed_grest( x, y, ss, col );
  }
  return;
}

void note_dot_print( int x, int y, int dots, int col ) {
  /* Draws `dots` augmentation dots stacked horizontally to the right of a
   * note head. Caller computes dots from the raw step value (see score.c). */
  int i;
  if ( ! isxwin ) return;
  for ( i = 0; i < dots; i++ ) {
    XSTed_gnote_dot( x + i * 5, y, col );
  }
}

void rest_dot_print( int x, int y, int dots, int col ) {
  if ( isxwin ) XSTed_grest_dots( x, y, dots, col );
}

void symbol( int x, int y, char *st, char h,
	     char v, char mo, int p, char an ) {

  if ( isconsole ) {
    curses_gcolor( p );
    curses_gputs( x, y, st );

  } else if ( isxwin ) {
    XSTed_gcolor( p );
    XSTed_gputs( x, y, st );
  }
  return;
}


/* other functions */

/* returns string describing current day(?) */
char *dtasc( unsigned int j ) {

  static char dtasc_name[10];
  int y,a,b;

  a=(j>>9)&0x7f;
  b=a%10;
  a=a%100-b;
  y=a+b;
  
  snprintf(dtasc_name, 10, "%02d-%02d-%02d", y, ((j>>5)&0x0f)+1, j&0x1f );

  return dtasc_name;
}

/* returns string describing current time(?) */
char *tmasc( unsigned int j ) {

  static char tmasc_name[10];

  snprintf(tmasc_name, 10, "%02d:%02d:%02d", (j>>11)&0x1f, (j>>5)&0x3f, (j&0x1f)*2 );
  return tmasc_name;
}

/* returns mouse positions */
int mspos( int *x, int *y ) {

  int ret=0;

  if ( isxwin ) {
    XSTed_ms_pos( x, y );
  }

  return ret;
}

/* returns someting B-) */
void b_striS ( char * buf, int bufSize, int num ) {
  int r;

  r=snprintf( buf, bufSize, "%d", num );
  if ( r < 0 ) {
    buf[0]='\0';
  }
  return;
}

/* set current Kanji mode */
void KNJCTRL( int i, int j ) {

  /* not implemented */
  return;
}
