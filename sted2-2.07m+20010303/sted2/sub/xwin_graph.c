/*
  xwin_graph.c

  xwin: drawing oriented functions

  Made by Studio Breeze. 1998

 */

#include "sted.h"
#include "xwin.h"

int isgscrchanged;
int istscrchanged;

int tpage ( int v ){
  int ret=0;

  switch ( v ) {
  case 0:
    ret=1;
    break;
  case 1:
    ret=2;
    break;
  default:
    ret=3;
    break;
  }

  return ret;
}

void XSTed_txbox( short x0, short y0, short x1, short y1, unsigned short p ) {

  int sx,sy,lx,ly;
  int c;

  c = tpage(p);

  sx = W_Width  * x0       / X68_GWidth;
  lx = W_Width  * (x1-x0)  / X68_GWidth;
  sy = (W_Height * y0      / X68_GHeight)%W_Height;
  ly = (W_Height * (y1-y0) / X68_GHeight) %W_Height;

  XSTed_SetTColor( c );
  XDrawRectangle( XSTed_d, XSTed_w, XSTed_tgc,
		  sx, sy, lx, ly );
  XDrawRectangle( XSTed_d, XSTed_tscr, XSTed_tgc,
		  sx, sy, lx, ly );
  XSTed_SetTColor( TCurrentCol );

  istscrchanged=1;
  return;
}

void XSTed_txxline( unsigned short v, short x0, short y0, short x1, unsigned short ls ) {

  int sx,sy,lx;
  int c;

  c = (ls!=0)?tpage(v):0;

  sx = W_Width  * x0  / X68_GWidth;
  lx = W_Width  * x1  / X68_GWidth;
  sy = (W_Height * y0 / X68_GHeight) % W_Height;

  if ( c!=0 ) {
    XSTed_SetTColor( c );
    XDrawLine( XSTed_d, XSTed_w, XSTed_tgc,
	       sx, sy, sx+lx, sy );
    XDrawLine( XSTed_d, XSTed_tscr, XSTed_tgc,
	       sx, sy, sx+lx, sy );
    XSTed_SetTColor( TCurrentCol );
  } else {
    XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc,
	       sx, sy, lx, 1, sx, sy );
    XDrawLine( XSTed_d, XSTed_tscr, XSTed_egc,
	       sx, sy, sx+lx, sy );
  }
  istscrchanged=1;
  return;
}

void XSTed_txyline( unsigned short v, short x0, short y0, short y1, unsigned short ls ) {

  int sx,sy,ey;
  int c;

  c = (ls!=0)?tpage(v):0;

  sx = W_Width  * x0       / X68_GWidth;
  sy = (W_Height * y0      / X68_GHeight) % W_Height;
  ey = (W_Height * (y0+y1) / X68_GHeight) % W_Height;

  if ( c!=0 ) {
    XSTed_SetTColor( c );
    XDrawLine( XSTed_d, XSTed_w, XSTed_tgc,
	       sx, sy, sx, ey-1 );
    XDrawLine( XSTed_d, XSTed_tscr, XSTed_tgc,
	       sx, sy, sx, ey-1 );
    XSTed_SetTColor( TCurrentCol );
  } else {
    XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc,
	       sx, sy, 1, ey-sy, sx, sy );
    XDrawLine( XSTed_d, XSTed_tscr, XSTed_egc,
	       sx, sy, sx, ey-1 );
  }

  istscrchanged=1;
  return;
}

void XSTed_trev( int x0, int y0, int l0, int col ) {

  int x1,y1,y2,l1;

  /*
  static const int r[4][4] = {
    {3,2,1,0},
    {1,0,3,2},
    {2,3,0,1},
    {3,2,1,0}
  };
  */

  x1 = W_Width * x0 / X68_TWidth;
  l1 = W_Width * l0 / X68_TWidth;
  y1 = W_Height* y0 / X68_THeight;
  y2 = W_Height* (y0+1) / X68_THeight;

  XSetForeground( XSTed_d, XSTed_wgc, WhitePixel(XSTed_d, XSTed_sc) );
  /*XSetForeground( XSTed_d, XSTed_wgc, (1<<XSTed_depth)-1 );*/
  XFillRectangle( XSTed_d, XSTed_vscr, XSTed_wgc,
		  0, 0, l1, y2-y1 );
  XSetForeground( XSTed_d, XSTed_wgc, 1 );
  XSetFunction( XSTed_d, XSTed_wgc, GXxor );
  XCopyArea( XSTed_d, XSTed_vscr, XSTed_w, XSTed_wgc,
	     0, 0, l1, y2-y1, x1, y1 );
  XCopyArea( XSTed_d, XSTed_vscr, XSTed_tscr, XSTed_wgc,
	     0, 0, l1, y2-y1, x1, y1 );
  XSetFunction( XSTed_d, XSTed_wgc, GXcopy );

  istscrchanged = 1;
  return;
}

void XSTed_rev_area( int r_ad, int r_ln, int edit_scr ) {

  /* if your system has capable enough to draw rev_area
     uncomment the following codes.

  int x0, y0, xl, yl;

  x0 = (edit_scr==0)? 2 : 56 ;
  y0 = 6+r_ad;
  xl=36 ; yl=r_ln;

  x0 = W_Width * x0 / X68_TWidth;
  y0 = W_Height* y0 / X68_THeight;
  xl = W_Width * xl / X68_TWidth;
  yl = W_Height* yl / X68_THeight;

  XSetForeground( XSTed_d, XSTed_wgc, WhitePixel(XSTed_d, XSTed_sc) );
  XFillRectangle( XSTed_d, XSTed_vscr, XSTed_wgc,
		  0, 0, xl, yl );
  XSetForeground( XSTed_d, XSTed_wgc, 1 );
  XSetFunction( XSTed_d, XSTed_wgc, GXxor );
  XCopyArea( XSTed_d, XSTed_vscr, XSTed_w, XSTed_wgc,
	     0, 0, xl, yl, x0, y0 );
  XCopyArea( XSTed_d, XSTed_vscr, XSTed_tscr, XSTed_wgc,
	     0, 0, xl, yl, x0, y0 );
  XSetFunction( XSTed_d, XSTed_wgc, GXcopy );
  */

  return;
}

void XSTed_tfill( unsigned short p, short x0, short y0, short x1, short y1, unsigned short ls ) {

  int sx,sy,lx,ey;
  int c;

  c = (ls!=0)?tpage(p):0;

  sx = W_Width  * x0       / X68_GWidth;
  lx = W_Width  * x1       / X68_GWidth;
  sy = (W_Height * y0      / X68_GHeight) % W_Height;
  ey = (W_Height * (y0+y1) / X68_GHeight) % W_Height;

  if ( c!=0 ) {
    XSTed_SetTColor( c );
    XFillRectangle( XSTed_d, XSTed_w, XSTed_tgc,
		    sx, sy, lx, ey-sy );
    XFillRectangle( XSTed_d, XSTed_tscr, XSTed_tgc,
		    sx, sy, lx, ey-sy );
    XSTed_SetTColor( TCurrentCol );
  } else {
    XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc,
	       sx, sy, lx, ey-sy, sx, sy );
    XFillRectangle( XSTed_d, XSTed_tscr, XSTed_egc,
		    sx, sy, lx, ey-sy );
  }

  istscrchanged=1;
  return;
}

void XSTed_gbox( int x1, int y1, int x2, int y2, unsigned int col, unsigned int ls) {

  int sx,sy,ex,ey;
  int x,y;
  int d;

  sx = W_Width  * x1 / X68_GWidth;
  ex = W_Width  * x2 / X68_GWidth;
  sy = (W_Height * y1 / X68_GHeight) % W_Height;
  ey = (W_Height * y2 / X68_GHeight) % W_Height;
  d  = ( y1 >= X68_GHeight )?1:0;
  if ( sx>ex ) { x=ex;ex=sx;sx=x; }
  if ( sy>ey ) { y=ey;ey=sy;sy=y; }

  XSTed_SetGColor( col );
  if ( d==current_gwindow )
    XDrawRectangle( XSTed_d, XSTed_w, XSTed_ggc,
		    sx, sy, ex-sx+1, ey-sy+1 );
  XDrawRectangle( XSTed_d, XSTed_gscr[d], XSTed_ggc,
		  sx, sy, ex-sx+1, ey-sy+1 );

  isgscrchanged=1;
  return;
}

void XSTed_gfill( int x1, int y1, int x2, int y2, int col ) {

  int sx,sy,ex,ey;
  int x,y;
  int d;

  sx = W_Width  * x1 / X68_GWidth;
  ex = W_Width  * x2 / X68_GWidth;
  sy = (W_Height * y1 / X68_GHeight) % W_Height;
  ey = (W_Height * y2 / X68_GHeight) % W_Height;
  d  = ( y1 >= X68_GHeight )?1:0;
  if ( sx>ex ) { x=ex;ex=sx;sx=x; }
  if ( sy>ey ) { y=ey;ey=sy;sy=y; }

  XSTed_SetGColor( col );
  if ( d==current_gwindow )
    XFillRectangle( XSTed_d, XSTed_w, XSTed_ggc,
		    sx, sy, ex-sx+1, ey-sy+1 );
  XFillRectangle( XSTed_d, XSTed_gscr[d], XSTed_ggc,
		  sx, sy, ex-sx+1, ey-sy+1 );

  isgscrchanged=1;
  return;
}

int  XSTed_gpoint( int x, int y) {

  int ret=0;

  return ret;
}

void XSTed_gline( int x1, int y1, int x2, int y2, int col, int ls ) {

  int sx,sy,ex,ey;
  int x,y;
  int d;

  sx = W_Width  * x1 / X68_GWidth;
  if ( sx < 0 ) sx=0;
  ex = W_Width  * x2 / X68_GWidth;
  if ( ex >= W_Width ) ex = W_Width-1;
  sy = (W_Height * y1 / X68_GHeight)%W_Height;
  ey = (W_Height * y2 / X68_GHeight)%W_Height;
  d  = ( y1 >= X68_GHeight )?1:0;
  if ( sx>ex ) { x=ex;ex=sx;sx=x; }
  if ( sy>ey ) { y=ey;ey=sy;sy=y; }

  XSTed_SetGColor( col );
  if ( d==current_gwindow )
    XDrawLine( XSTed_d, XSTed_w, XSTed_ggc,
	       sx, sy, ex, ey );
  XDrawLine( XSTed_d, XSTed_gscr[d], XSTed_ggc,
	     sx, sy, ex, ey );

  isgscrchanged=1;
  return;
}

/* PROTOTYPE: draw a slanted oval music note head at (x, y) in X68 graphic
 * coords. filled=0 -> hollow (whole/half family), filled=1 -> filled. The
 * head is ~7x4 pixels, slanted ~22° clockwise to mimic engraved notation. */
void XSTed_gnote_head( int x, int y, int filled, int col ) {
  int d, cx, cy;
  XPoint pts[8];
  XPoint outline[9];
  int i;
  /* gra_gakufu() computes y as the top-left of an old 16x16 glyph cell; the
   * head's visual centre sat ~13 X68 units lower. Nudging here keeps every
   * pitch landing exactly on a staff line or in the centre of a space, with
   * C4 on the ledger line between treble and bass staves. */
  const int Y_NUDGE_X68 = 13;

  cx = W_Width  * x / X68_GWidth;
  cy = (W_Height * (y + Y_NUDGE_X68) / X68_GHeight) % W_Height;
  d  = ( y >= X68_GHeight ) ? 1 : 0;

  /* Slanted ellipse octagon, ~8 wide * 5 tall, clockwise slant. */
  pts[0].x = cx + 4; pts[0].y = cy - 1;
  pts[1].x = cx + 3; pts[1].y = cy - 2;
  pts[2].x = cx + 1; pts[2].y = cy - 3;
  pts[3].x = cx - 2; pts[3].y = cy - 2;
  pts[4].x = cx - 4; pts[4].y = cy + 1;
  pts[5].x = cx - 3; pts[5].y = cy + 2;
  pts[6].x = cx - 1; pts[6].y = cy + 3;
  pts[7].x = cx + 2; pts[7].y = cy + 2;

  XSTed_SetGColor( col );
  if ( filled ) {
    if ( d == current_gwindow )
      XFillPolygon( XSTed_d, XSTed_w, XSTed_ggc, pts, 8,
                    Convex, CoordModeOrigin );
    XFillPolygon( XSTed_d, XSTed_gscr[d], XSTed_ggc, pts, 8,
                  Convex, CoordModeOrigin );
  } else {
    for ( i = 0; i < 8; i++ ) outline[i] = pts[i];
    outline[8] = pts[0];
    if ( d == current_gwindow )
      XDrawLines( XSTed_d, XSTed_w, XSTed_ggc, outline, 9, CoordModeOrigin );
    XDrawLines( XSTed_d, XSTed_gscr[d], XSTed_ggc, outline, 9, CoordModeOrigin );
  }
  isgscrchanged = 1;
}

/* PROTOTYPE: draw a stem (vertical line) and any flags for a note group.
 * The flags are little filled scrolls mimicking the ♪ tail. */
void XSTed_gnote_stem_flag( int xc, int y_top, int y_bottom, int ss, int col ) {
  int d, sx, syt, syb;
  int nflags, i;
  const int Y_NUDGE_X68 = 13;

  sx  = W_Width  * xc                       / X68_GWidth + 3;
  syt = (W_Height * (y_top    + Y_NUDGE_X68) / X68_GHeight) % W_Height;
  syb = (W_Height * (y_bottom + Y_NUDGE_X68) / X68_GHeight) % W_Height;
  d   = ( y_top >= X68_GHeight ) ? 1 : 0;

  XSTed_SetGColor( col );

  /* Stem */
  if ( d == current_gwindow )
    XDrawLine( XSTed_d, XSTed_w, XSTed_ggc, sx, syt, sx, syb );
  XDrawLine( XSTed_d, XSTed_gscr[d], XSTed_ggc, sx, syt, sx, syb );

  if      ( ss == 5  || ss == 6  ) nflags = 1;
  else if ( ss == 7  || ss == 8  ) nflags = 2;
  else if ( ss == 9  || ss == 10 ) nflags = 3;
  else if ( ss == 11 )             nflags = 4;
  else                             nflags = 0;

  for ( i = 0; i < nflags; i++ ) {
    int fy = syt + i * 5;
    /* Filled curl-shaped flag: 6 points trace stem-attach -> outer-tip ->
     * outer-back -> inner-back -> stem-attach for a comma/♪ silhouette. */
    XPoint flag[6];
    flag[0].x = sx;     flag[0].y = fy - 1;
    flag[1].x = sx + 4; flag[1].y = fy + 1;
    flag[2].x = sx + 7; flag[2].y = fy + 5;
    flag[3].x = sx + 6; flag[3].y = fy + 7;
    flag[4].x = sx + 3; flag[4].y = fy + 6;
    flag[5].x = sx + 1; flag[5].y = fy + 3;
    if ( d == current_gwindow )
      XFillPolygon( XSTed_d, XSTed_w, XSTed_ggc, flag, 6,
                    Convex, CoordModeOrigin );
    XFillPolygon( XSTed_d, XSTed_gscr[d], XSTed_ggc, flag, 6,
                  Convex, CoordModeOrigin );
  }

  isgscrchanged = 1;
}

/* PROTOTYPE: draw ledger lines for a note pitch. For pitches outside the two
 * main staves, draws every line position between the closest staff edge and
 * the note itself. So B5 (just above F5) gets the A5 ledger; B6 (5 steps
 * higher) gets A5/C6/E6/G6/B6 = 5 ledgers. C4 between staves gets one. */
static void draw_ledger_at( int cx, int cy_x68, int d ) {
  const int half_w = 10;
  int cy = (W_Height * cy_x68 / X68_GHeight) % W_Height;
  if ( d == current_gwindow )
    XDrawLine( XSTed_d, XSTed_w, XSTed_ggc, cx - half_w, cy, cx + half_w, cy );
  XDrawLine( XSTed_d, XSTed_gscr[d], XSTed_ggc, cx - half_w, cy, cx + half_w, cy );
}

void XSTed_gledger( int x, int y, int col ) {
  int cx, d, y_n, L;
  const int Y_NUDGE_X68 = 13;

  y_n = y + Y_NUDGE_X68;
  cx = W_Width * x / X68_GWidth;
  d  = ( y >= X68_GHeight ) ? 1 : 0;

  XSTed_SetGColor( col );

  if ( y_n < 680 ) {
    /* Above the treble staff. Walk down from A5 (the first ledger position
     * above F5 top line) and emit each line that sits above-or-at the note. */
    for ( L = 672; L >= y_n; L -= 8 ) {
      draw_ledger_at( cx, L, d );
    }
  } else if ( y_n == 720 ) {
    /* Middle C between the two staves. */
    draw_ledger_at( cx, 720, d );
  } else if ( y_n > 760 ) {
    /* Below the bass staff. Walk up from E2. */
    for ( L = 768; L <= y_n; L += 8 ) {
      draw_ledger_at( cx, L, d );
    }
  }

  isgscrchanged = 1;
}

/* PROTOTYPE: augmentation dot placed to the right of a note head. If the
 * note sits on a line, the dot goes up half a staff position into the space
 * above; in a space, the dot stays at the same y. */
void XSTed_gnote_dot( int x, int y, int col ) {
  int cx, cy, d, y_n;
  const int Y_NUDGE_X68 = 13;

  y_n = y + Y_NUDGE_X68;
  if ( ( y_n % 8 ) == 0 ) y_n -= 4;

  cx = W_Width * x / X68_GWidth + 8;
  cy = (W_Height * y_n / X68_GHeight) % W_Height;
  d  = ( y >= X68_GHeight ) ? 1 : 0;

  XSTed_SetGColor( col );
  if ( d == current_gwindow )
    XFillArc( XSTed_d, XSTed_w, XSTed_ggc, cx, cy - 1, 3, 3, 0, 360 * 64 );
  XFillArc( XSTed_d, XSTed_gscr[d], XSTed_ggc, cx, cy - 1, 3, 3, 0, 360 * 64 );
  isgscrchanged = 1;
}

/* PROTOTYPE: rest symbol at (x, y). y is the X68 coord of the staff line we
 * hang from / sit on (no Y_NUDGE — caller already passes a line position). */
void XSTed_grest( int x, int y, int ss, int col ) {
  int d, cx, cy;

  cx = W_Width  * x / X68_GWidth;
  cy = (W_Height * y / X68_GHeight) % W_Height;
  d  = ( y >= X68_GHeight ) ? 1 : 0;

  XSTed_SetGColor( col );

  if ( ss <= 1 ) {
    /* whole rest — fat slab hanging below the line */
    if ( d == current_gwindow )
      XFillRectangle( XSTed_d, XSTed_w, XSTed_ggc, cx - 5, cy, 11, 4 );
    XFillRectangle( XSTed_d, XSTed_gscr[d], XSTed_ggc, cx - 5, cy, 11, 4 );
  } else if ( ss <= 3 ) {
    /* half rest — fat slab sitting on the line */
    if ( d == current_gwindow )
      XFillRectangle( XSTed_d, XSTed_w, XSTed_ggc, cx - 5, cy - 4, 11, 4 );
    XFillRectangle( XSTed_d, XSTed_gscr[d], XSTed_ggc, cx - 5, cy - 4, 11, 4 );
  } else if ( ss <= 5 ) {
    /* quarter rest — zigzag */
    if ( d == current_gwindow ) {
      XDrawLine( XSTed_d, XSTed_w, XSTed_ggc, cx - 3, cy - 7, cx + 3, cy - 2 );
      XDrawLine( XSTed_d, XSTed_w, XSTed_ggc, cx + 3, cy - 2, cx - 3, cy + 2 );
      XDrawLine( XSTed_d, XSTed_w, XSTed_ggc, cx - 3, cy + 2, cx + 3, cy + 7 );
    }
    XDrawLine( XSTed_d, XSTed_gscr[d], XSTed_ggc, cx - 3, cy - 7, cx + 3, cy - 2 );
    XDrawLine( XSTed_d, XSTed_gscr[d], XSTed_ggc, cx + 3, cy - 2, cx - 3, cy + 2 );
    XDrawLine( XSTed_d, XSTed_gscr[d], XSTed_ggc, cx - 3, cy + 2, cx + 3, cy + 7 );
  } else {
    /* eighth / sixteenth / 32nd / 64th rest — slanted stem + 1..4 dots */
    int n_curls, i;
    if      ( ss <= 7 )  n_curls = 1;
    else if ( ss <= 9 )  n_curls = 2;
    else if ( ss <= 10 ) n_curls = 3;
    else                 n_curls = 4;

    if ( d == current_gwindow )
      XDrawLine( XSTed_d, XSTed_w, XSTed_ggc, cx + 3, cy - 7, cx - 3, cy + 7 );
    XDrawLine( XSTed_d, XSTed_gscr[d], XSTed_ggc, cx + 3, cy - 7, cx - 3, cy + 7 );
    for ( i = 0; i < n_curls; i++ ) {
      int dy = -6 + i * 5;
      if ( d == current_gwindow )
        XFillArc( XSTed_d, XSTed_w, XSTed_ggc, cx - 3, cy + dy - 2, 4, 4, 0, 360 * 64 );
      XFillArc( XSTed_d, XSTed_gscr[d], XSTed_ggc, cx - 3, cy + dy - 2, 4, 4, 0, 360 * 64 );
    }
  }

  isgscrchanged = 1;
}

/* PROTOTYPE: 0..2 augmentation dots to the right of a rest. */
void XSTed_grest_dots( int x, int y, int dots, int col ) {
  int cx, cy, d, i;

  if ( dots <= 0 ) return;

  cx = W_Width * x / X68_GWidth;
  cy = (W_Height * y / X68_GHeight) % W_Height;
  d  = ( y >= X68_GHeight ) ? 1 : 0;

  XSTed_SetGColor( col );
  for ( i = 0; i < dots; i++ ) {
    int dx = cx + 8 + i * 5;
    if ( d == current_gwindow )
      XFillArc( XSTed_d, XSTed_w, XSTed_ggc, dx, cy - 2, 3, 3, 0, 360 * 64 );
    XFillArc( XSTed_d, XSTed_gscr[d], XSTed_ggc, dx, cy - 2, 3, 3, 0, 360 * 64 );
  }
  isgscrchanged = 1;
}

/* Treble and bass clef bitmaps.
 *
 * Sourced from a MusixTeX-rendered staff (open-source — the LaTeX MusixTeX
 * package and the Computer Modern–derived musixmf fonts are GPL-compatible),
 * extracted by tools/extract_clefs.py: red pixels in crefs.png isolated, the
 * source's own staff lines auto-detected, and resampled so 1 staff space ==
 * 8 px (matching STed2's 8-X68-unit staff spacing in score view).
 *
 * Encoding is row-major 1bpp, MSB-first; _ANCHOR is the bitmap row that
 * aligns with the clef's reference staff line (G4 for treble, F3 for bass).
 */
#define treble_clef_W      20
#define treble_clef_H      57
#define treble_clef_BPR    3
#define treble_clef_ANCHOR 37
static const unsigned char treble_clef_bm[ treble_clef_H * treble_clef_BPR ] = {
    0x00, 0x18, 0x00,
    0x00, 0x38, 0x00,
    0x00, 0x7C, 0x00,
    0x00, 0x7C, 0x00,
    0x00, 0xF6, 0x00,
    0x00, 0xE2, 0x00,
    0x00, 0xC2, 0x00,
    0x01, 0x82, 0x00,
    0x01, 0x83, 0x00,
    0x01, 0x82, 0x00,
    0x01, 0x86, 0x00,
    0x01, 0x86, 0x00,
    0x01, 0x8E, 0x00,
    0x01, 0x9C, 0x00,
    0x01, 0x9C, 0x00,
    0x01, 0xB8, 0x00,
    0x01, 0xF8, 0x00,
    0x00, 0xF0, 0x00,
    0x01, 0xF0, 0x00,
    0x03, 0xE0, 0x00,
    0x03, 0xE0, 0x00,
    0x07, 0xC0, 0x00,
    0x0F, 0xC0, 0x00,
    0x0F, 0xC0, 0x00,
    0x1F, 0x40, 0x00,
    0x3E, 0x40, 0x00,
    0x3E, 0x40, 0x00,
    0x7C, 0x40, 0x00,
    0x78, 0x7E, 0x00,
    0xF8, 0xFF, 0x80,
    0xF1, 0xFF, 0xC0,
    0xF3, 0xFF, 0xE0,
    0xE3, 0xA1, 0xE0,
    0xE3, 0x30, 0xF0,
    0xC6, 0x30, 0xF0,
    0xC6, 0x30, 0x70,
    0xC6, 0x10, 0x70,
    0x42, 0x10, 0x70,
    0x62, 0x10, 0x70,
    0x20, 0x10, 0xE0,
    0x30, 0x18, 0xE0,
    0x18, 0x19, 0xC0,
    0x0C, 0x0F, 0x80,
    0x03, 0xFF, 0x00,
    0x00, 0x78, 0x00,
    0x00, 0x08, 0x00,
    0x00, 0x08, 0x00,
    0x00, 0x08, 0x00,
    0x0C, 0x08, 0x00,
    0x3E, 0x0C, 0x00,
    0x3F, 0x0C, 0x00,
    0x3F, 0x0C, 0x00,
    0x3F, 0x08, 0x00,
    0x3E, 0x08, 0x00,
    0x1C, 0x18, 0x00,
    0x1C, 0x70, 0x00,
    0x0F, 0xE0, 0x00,
};

#define bass_clef_W      22
#define bass_clef_H      26
#define bass_clef_BPR    3
#define bass_clef_ANCHOR 8
static const unsigned char bass_clef_bm[ bass_clef_H * bass_clef_BPR ] = {
    0x03, 0xE0, 0x00,
    0x0F, 0xF8, 0x00,
    0x18, 0x1E, 0x00,
    0x30, 0x0E, 0x08,
    0x60, 0x0F, 0x1C,
    0x60, 0x07, 0xBC,
    0x78, 0x07, 0x9C,
    0x7C, 0x07, 0x80,
    0x7C, 0x07, 0xC0,
    0x7C, 0x07, 0x88,
    0x38, 0x07, 0xDC,
    0x00, 0x07, 0xBC,
    0x00, 0x07, 0x9C,
    0x00, 0x07, 0x80,
    0x00, 0x0F, 0x80,
    0x00, 0x0F, 0x00,
    0x00, 0x0F, 0x00,
    0x00, 0x1E, 0x00,
    0x00, 0x1E, 0x00,
    0x00, 0x3C, 0x00,
    0x00, 0x78, 0x00,
    0x00, 0xF0, 0x00,
    0x01, 0xE0, 0x00,
    0x03, 0x80, 0x00,
    0x0E, 0x00, 0x00,
    0x78, 0x00, 0x00,
};

/* Blit a 1bpp packed bitmap to (cx, top) in physical pixel coords on both the
 * window and the off-screen pixmap. Set bits are drawn as individual points
 * in the current GC's foreground colour. Caller positions the bitmap; the
 * anchor row offset has already been subtracted from top. */
static void blit_clef_bm( const unsigned char *bm, int W, int H, int BPR,
                          int cx, int top, int d ) {
  static XPoint pts[ 2048 ];
  int n = 0;
  int row, byte_idx, bit;

  for ( row = 0; row < H; row++ ) {
    for ( byte_idx = 0; byte_idx < BPR; byte_idx++ ) {
      unsigned char v = bm[ row * BPR + byte_idx ];
      if ( v == 0 ) continue;
      for ( bit = 0; bit < 8; bit++ ) {
        int col_px = byte_idx * 8 + bit;
        if ( col_px >= W ) break;
        if ( v & ( 1 << ( 7 - bit ) ) ) {
          if ( n >= (int)( sizeof(pts) / sizeof(pts[0]) ) ) break;
          pts[n].x = cx + col_px;
          pts[n].y = top + row;
          n++;
        }
      }
    }
  }
  if ( n == 0 ) return;
  if ( d == current_gwindow )
    XDrawPoints( XSTed_d, XSTed_w, XSTed_ggc, pts, n, CoordModeOrigin );
  XDrawPoints( XSTed_d, XSTed_gscr[d], XSTed_ggc, pts, n, CoordModeOrigin );
}

/* Treble clef at (x, y_anchor). x is the X68 logical x of the
 * bitmap's left edge; y_anchor is the X68 y of the G4 line (= y=704 in the
 * score view's treble staff). */
void XSTed_gtreble_clef( int x, int y_anchor, int col ) {
  int cx, cy, top, d;

  cx  = W_Width  * x        / X68_GWidth;
  cy  = (W_Height * y_anchor / X68_GHeight) % W_Height;
  d   = ( y_anchor >= X68_GHeight ) ? 1 : 0;
  top = cy - treble_clef_ANCHOR;

  XSTed_SetGColor( col );
  blit_clef_bm( treble_clef_bm, treble_clef_W, treble_clef_H,
                treble_clef_BPR, cx, top, d );
  isgscrchanged = 1;
}

/* Bass clef at (x, y_anchor). y_anchor is the F3 line (= y=736 in
 * the score view's bass staff). */
void XSTed_gbass_clef( int x, int y_anchor, int col ) {
  int cx, cy, top, d;

  cx  = W_Width  * x        / X68_GWidth;
  cy  = (W_Height * y_anchor / X68_GHeight) % W_Height;
  d   = ( y_anchor >= X68_GHeight ) ? 1 : 0;
  top = cy - bass_clef_ANCHOR;

  XSTed_SetGColor( col );
  blit_clef_bm( bass_clef_bm, bass_clef_W, bass_clef_H,
                bass_clef_BPR, cx, top, d );
  isgscrchanged = 1;
}

void XSTed_trascpy( int dst, int src, int line, int mode ) {

  int sx, lx;
  int sy,dy,ly;

  ly = W_Height * (line/4-1) / X68_THeight;

  if ((src==63*4)||(src==30*4)) {
    sx=0;
    lx=W_Width;
  } else {
    if ( edit_scr==0 ) {
      sx=W_Width * 2 /X68_TWidth;
      lx=W_Width * 36/X68_TWidth;
    } else {
      sx=W_Width * 58/X68_TWidth;
      lx=W_Width * 36/X68_TWidth;
    }
  }

  if ( mode >= 0x8000 ) {
    sy = W_Height * ((src+1)/4) / X68_THeight;
    dy = W_Height * ((dst+1)/4) / X68_THeight;

    XCopyArea( XSTed_d, XSTed_w, XSTed_w, XSTed_wgc,
	       sx, sy-ly, lx, ly, sx, dy-ly );
    XCopyArea( XSTed_d, XSTed_tscr, XSTed_tscr, XSTed_wgc,
	       sx, sy-ly, lx, ly, sx, dy-ly );
  } else {

    if ( src == 63*4 ) {
      sy=W_Height * dst/4 /X68_THeight;
      dy=sy+XSTed_fs_max_height;
      
      XClearArea( XSTed_d, XSTed_w,
		  sx, sy, lx, dy-sy, False );
      XFillRectangle( XSTed_d, XSTed_tscr, XSTed_egc,
		      sx, sy, lx, dy-sy );
    } else {

      sy = W_Height * (src/4) / X68_THeight;
      dy = W_Height * (dst/4) / X68_THeight;

      XCopyArea( XSTed_d, XSTed_w, XSTed_w, XSTed_wgc,
		 sx, sy, lx, ly, sx, dy );
      XCopyArea( XSTed_d, XSTed_tscr, XSTed_tscr, XSTed_wgc,
		 sx, sy, lx, ly, sx, dy );
    }
  }

  istscrchanged=1;
  return;
}

void XSTed_t_scrw( int x1, int y1, int xs, int ys, int x2, int y2 ) {

  x1 = W_Width * x1 / X68_TWidth;
  x2 = W_Width * x2 / X68_TWidth;
  xs = W_Width * xs / X68_TWidth;
  y1 = W_Height* y1 / X68_GHeight;
  y2 = W_Height* y2 / X68_GHeight;
  ys = W_Height* ys / X68_GHeight;

  XCopyArea( XSTed_d, XSTed_w, XSTed_w, XSTed_wgc,
	     x1, y1, xs, ys, x2, y2 );
  XCopyArea( XSTed_d, XSTed_tscr, XSTed_tscr, XSTed_wgc,
	     x1, y1, xs, ys, x2, y2 );

  istscrchanged=1;
  return;
}

void XSTed_tg_copy( int edit_scr ) {

  int x1, y1, x2, y2;
  int xt, xl, yt, yl;

  xl=36 ; yl=24;
  if ( edit_scr==0 ) {
    xt= 2 ; yt= 6;
  } else {
    xt=58 ; yt= 6;
  }
  x1 = W_Width * xt      / X68_TWidth;
  x2 = W_Width * xl      / X68_TWidth;
  y1 = W_Height * yt     / X68_THeight;
  y2 = W_Height * (yt+yl)/ X68_THeight;

  XCopyArea( XSTed_d, XSTed_tscr, XSTed_gscr[1], XSTed_wgc,
	     x1, y1, x2, y2-y1, x1, y1 );

  isgscrchanged=1;
  return;
}

void XSTed_tg_copy2( int edit_scr ) {

  int x1, y1, x2, y2;
  int xt, xl, yt, yl;

  xl=56 ; yl=24;
  if ( edit_scr==0 ) {
    xt= 0 ; yt= 6;
  } else {
    xt=38 ; yt= 6;
  }
  x1 = W_Width * xt      / X68_TWidth;
  x2 = W_Width * xl      / X68_TWidth;
  y1 = W_Height * yt     / X68_THeight;
  y2 = W_Height * (yt+yl)/ X68_THeight;

  XCopyArea( XSTed_d, XSTed_tscr, XSTed_gscr[1], XSTed_wgc,
	     x1, y1, x2, y2-y1, x1, y1 );

  isgscrchanged=1;
  return;
}

void XSTed_ghome( int home_flag ){

  current_gwindow=home_flag;

  XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc,
	     0, 0, W_Width, W_Height, 0, 0 );

  isgscrchanged=1;
  return;
}

void XSTed_gclr( void ) {

  XFillRectangle( XSTed_d, XSTed_gscr[current_gwindow], XSTed_egc,
		  0, 0, W_Width, W_Height );
  XClearArea( XSTed_d, XSTed_w, 0, 0, W_Width, W_Height, False );

  isgscrchanged=1;
  return;
}

void XSTed_cls_al( void ) {

  XCopyArea( XSTed_d, XSTed_gscr[current_gwindow], XSTed_w, XSTed_wgc, 
	     0, 0, W_Width, W_Height, 0, 0 );
  XFillRectangle( XSTed_d, XSTed_tscr, XSTed_egc,
		  0, 0, W_Width, W_Height );

  istscrchanged=1;
  return;
}

void XSTed_overlap( void ) {

  static char *namlist[2];
  int l,r;
  XTextProperty ct;

  if ( strcmp( last_file_name, rcp_file ) != 0 ) {
    strncpy( last_file_name, rcp_file, 512 );
    l =strlen( XSTed_Window_Title );
    l+=strlen( (char *)eucconv(mtitle) );
    l+=strlen( rcp_file );
    l+=10;
    namlist[0] = (char *)malloc(sizeof(char)*l);

    if ( rcp_file[0] != 0 )
      r=snprintf( namlist[0], l, "%s : [ %s ] %s",
	       XSTed_Window_Title, rcp_file, eucconv(mtitle) );
    else
      r=snprintf( namlist[0], l, "%s", XSTed_Window_Title );
    if ( r > 0 ) {
      XmbTextListToTextProperty( XSTed_d, namlist, 1, XCompoundTextStyle, &ct );
    
      XSetWMName ( XSTed_d, XSTed_w, &ct );
    }
    free(namlist[0]);
  }

  XSync(XSTed_d, False);

  istscrchanged=0;
  isgscrchanged=0;
  return;
}
