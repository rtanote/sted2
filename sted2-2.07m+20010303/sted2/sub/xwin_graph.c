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

/* ============================================================================
 * MusixTeX-derived notation glyphs (heads, flags, rests, accidentals, dot).
 *
 * Source: tools/notation-1.png, containing the musix20 font's chars
 *   9 (whole head), 8 (half head), 7 (quarter head), 0 (dot),
 *   40..43 (8th..64th upstem flags),
 *   61 (whole rest), 60 (half rest), 62..66 (qtr..64th rests),
 *   52 (sharp), 50 (flat)
 * rendered in red on a fbox grid at the same musix20 scale as the clefs.
 * Extracted by tools/extract_notation.py: red mask + flood-fill blobs;
 * resampled so 1 staff space = 8 px (matching STed2's 8-X68-unit staff
 * spacing in score view).
 *
 * Same 1bpp MSB-first row-major encoding as the clef bitmaps. Each glyph
 * has an ANCHOR y — the bitmap row that aligns with the caller-supplied
 * anchor line (pitch line for heads / dot / accidental; the staff line
 * the rest hangs from or sits on).
 * ============================================================================ */

/* Forward decl: definition sits with the clef bitmaps below. */
static void blit_clef_bm( const unsigned char *bm, int W, int H, int BPR,
                          int cx, int top, int d );

/* Note-head bitmaps get a 0.75 additional shrink on top of the global
 * TARGET_SPACING=8 scale (see tools/extract_notation.py GLYPH_SHRINK).
 * Rationale: on the DevTerm the sted2 window is scaled ~1.5x from the
 * X68 logical 768x512, but our bitmaps blit at 1:1 pixel size. At native
 * 1-space-tall heads (8 px) the tadpoles looked ~2x the (scaled) staff
 * space; 75% brings them into visual proportion. */

/* whole_head: 9x6, anchor y = 3. */
#define WHOLE_HEAD_W      9
#define WHOLE_HEAD_H      6
#define WHOLE_HEAD_BPR    2
#define WHOLE_HEAD_ANCHOR 3
static const unsigned char whole_head_bm[12] = {
    0x0E, 0x00,
    0x43, 0x80,
    0xC1, 0x80,
    0xE1, 0x80,
    0x71, 0x80,
    0x3C, 0x00,
};

/* half_head: 7x6, anchor y = 3. */
#define HALF_HEAD_W      7
#define HALF_HEAD_H      6
#define HALF_HEAD_BPR    1
#define HALF_HEAD_ANCHOR 3
static const unsigned char half_head_bm[6] = {
    0x3C, 0x60, 0x80, 0x86, 0x8C, 0x78,
};

/* qtr_head: 7x6, anchor y = 3. */
#define QTR_HEAD_W      7
#define QTR_HEAD_H      6
#define QTR_HEAD_BPR    1
#define QTR_HEAD_ANCHOR 3
static const unsigned char qtr_head_bm[6] = {
    0x3C, 0x7E, 0xFE, 0xFE, 0xFC, 0x78,
};

/* dot: 2x3, anchor y = 1. */
#define DOT_W      2
#define DOT_H      3
#define DOT_BPR    1
#define DOT_ANCHOR 1
static const unsigned char dot_bm[3] = {
    0xC0,
    0xC0,
    0xC0,
};

/* Flag bitmaps are trimmed at the first fully-empty row past the mid-point
 * (see tools/extract_notation.py TRIM_TRAILING_EMPTY) to drop the LANCZOS
 * resize artefact tail — a couple of empty rows + a stray isolated pixel —
 * which otherwise reads as a phantom augmentation dot below the flag. */

/* flag8: 8x17, anchor y = 0. */
#define FLAG8_W      8
#define FLAG8_H      17
#define FLAG8_BPR    1
#define FLAG8_ANCHOR 0
static const unsigned char flag8_bm[17] = {
    0x80, 0x80, 0xC0, 0xE0, 0xE0, 0xF0, 0xF8, 0x78, 0x1C, 0x0C,
    0x06, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
};

/* flag16: 8x17, anchor y = 0. */
#define FLAG16_W      8
#define FLAG16_H      17
#define FLAG16_BPR    1
#define FLAG16_ANCHOR 0
static const unsigned char flag16_bm[17] = {
    0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0x7C, 0x9E, 0xC6, 0xE3, 0xF1,
    0xF9, 0x7D, 0x1F, 0x07, 0x03, 0x01, 0x01,
};

/* flag32: 8x23, anchor y = 0. */
#define FLAG32_W      8
#define FLAG32_H      23
#define FLAG32_BPR    1
#define FLAG32_ANCHOR 0
static const unsigned char flag32_bm[23] = {
    0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xBC, 0xCE, 0xE2, 0xF3, 0xF9,
    0xFD, 0x9D, 0xC7, 0xE3, 0xF1, 0xF9, 0xFD, 0x3F, 0x07, 0x03,
    0x01, 0x01, 0x01,
};

/* flag64: 8x29, anchor y = 0. */
#define FLAG64_W      8
#define FLAG64_H      29
#define FLAG64_BPR    1
#define FLAG64_ANCHOR 0
static const unsigned char flag64_bm[29] = {
    0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0x3C, 0x8E, 0xC6, 0xE3, 0xF1,
    0xF9, 0xBD, 0xCF, 0xE3, 0xF3, 0xF9, 0xFD, 0x9D, 0xC7, 0xE3,
    0xF1, 0xF9, 0xFD, 0x3F, 0x07, 0x03, 0x01, 0x01, 0x01,
};

/* rest_whole: 11x4, anchor y = 0 (top edge of bar sits on line 4). */
#define REST_WHOLE_W      11
#define REST_WHOLE_H      4
#define REST_WHOLE_BPR    2
#define REST_WHOLE_ANCHOR 0
static const unsigned char rest_whole_bm[8] = {
    0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0,
};

/* rest_half: 11x4, anchor y = 3 (bottom edge of bar sits on middle line). */
#define REST_HALF_W      11
#define REST_HALF_H      4
#define REST_HALF_BPR    2
#define REST_HALF_ANCHOR 3
static const unsigned char rest_half_bm[8] = {
    0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0, 0xFF, 0xE0,
};

/* rest_qtr: 7x22, anchor y = 11 (centred on middle line). */
#define REST_QTR_W      7
#define REST_QTR_H      22
#define REST_QTR_BPR    1
#define REST_QTR_ANCHOR 11
static const unsigned char rest_qtr_bm[22] = {
    0x60, 0x30, 0x18, 0x08, 0x1C, 0x1E, 0x3E, 0x3C, 0x7C, 0x78,
    0x38, 0x18, 0x0C, 0x0E, 0x7E, 0xF0, 0xE0, 0xC0, 0xC0, 0xE0,
    0x70, 0x18,
};

/* rest_8: 8x14, anchor y = 7. */
#define REST_8_W      8
#define REST_8_H      14
#define REST_8_BPR    1
#define REST_8_ANCHOR 7
static const unsigned char rest_8_bm[14] = {
    0xE0, 0xF3, 0xF6, 0x7A, 0x02, 0x02, 0x04, 0x08, 0x08, 0x08,
    0x18, 0x10, 0x10, 0x10,
};

/* rest_16: 11x22, anchor y = 11. */
#define REST_16_W      11
#define REST_16_H      22
#define REST_16_BPR    2
#define REST_16_ANCHOR 11
static const unsigned char rest_16_bm[44] = {
    0x1C, 0x00, 0x3C, 0x60, 0x1C, 0xE0, 0x0F, 0x40, 0x00, 0x40,
    0x00, 0x40, 0x00, 0xC0, 0x60, 0x80, 0x70, 0x80, 0xF1, 0x80,
    0x7F, 0x80, 0x0D, 0x00, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x06, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00,
    0x04, 0x00, 0x04, 0x00,
};

/* rest_32: 11x30, anchor y = 15. */
#define REST_32_W      11
#define REST_32_H      30
#define REST_32_BPR    2
#define REST_32_ANCHOR 15
static const unsigned char rest_32_bm[60] = {
    0x08, 0x00, 0x1C, 0x20, 0x3C, 0x60, 0x1F, 0xA0, 0x06, 0x20,
    0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x30, 0x40, 0x78, 0xC0,
    0x79, 0xC0, 0x3E, 0xC0, 0x00, 0xC0, 0x00, 0x80, 0x00, 0x80,
    0x00, 0x80, 0xE1, 0x80, 0xE3, 0x00, 0xF7, 0x00, 0x7D, 0x00,
    0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x06, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00,
};

/* rest_64: 11x38, anchor y = 19. */
#define REST_64_W      11
#define REST_64_H      38
#define REST_64_BPR    2
#define REST_64_ANCHOR 19
static const unsigned char rest_64_bm[76] = {
    0x0C, 0x00, 0x1E, 0x20, 0x1E, 0x60, 0x0F, 0xA0, 0x00, 0x20,
    0x00, 0x20, 0x00, 0x40, 0x00, 0x40, 0x38, 0x40, 0x3C, 0x40,
    0x3F, 0xC0, 0x1F, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
    0x00, 0x40, 0x78, 0xC0, 0x79, 0x80, 0x7B, 0x80, 0x3C, 0x80,
    0x00, 0x80, 0x00, 0x80, 0x01, 0x00, 0x61, 0x00, 0xF1, 0x00,
    0xF3, 0x00, 0xFF, 0x00, 0x09, 0x00, 0x03, 0x00, 0x03, 0x00,
    0x03, 0x00, 0x03, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
};

/* Sharp / flat get the same 0.75 shrink as the note heads to keep the
 * accidentals proportional to the (smaller) heads and to the DevTerm's
 * scaled staff spacing. */

/* sharp: 6x17, anchor y = 8 (centred on pitch line). */
#define SHARP_W      6
#define SHARP_H      17
#define SHARP_BPR    1
#define SHARP_ANCHOR 8
static const unsigned char sharp_bm[17] = {
    0x08, 0x48, 0x48, 0x48, 0x5C, 0x7C, 0xF8, 0xC8, 0x48, 0x4C,
    0x7C, 0xF8, 0xE8, 0x48, 0x48, 0x48, 0x40,
};

/* flat: 5x12, anchor y = 8 (loop centre on pitch line, ascender goes up). */
#define FLAT_W      5
#define FLAT_H      12
#define FLAT_BPR    1
#define FLAT_ANCHOR 8
static const unsigned char flat_bm[12] = {
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xB8, 0x98, 0x98, 0xB8,
    0xA0, 0xC0,
};

/* Descriptor + table ------------------------------------------------------ */

typedef struct {
  int W, H, BPR, ANCHOR;
  const unsigned char *bm;
} MusixGlyph;

enum {
  GLYPH_WHOLE_HEAD = 0, GLYPH_HALF_HEAD, GLYPH_QTR_HEAD, GLYPH_DOT,
  GLYPH_FLAG8, GLYPH_FLAG16, GLYPH_FLAG32, GLYPH_FLAG64,
  GLYPH_REST_WHOLE, GLYPH_REST_HALF, GLYPH_REST_QTR,
  GLYPH_REST_8, GLYPH_REST_16, GLYPH_REST_32, GLYPH_REST_64,
  GLYPH_SHARP, GLYPH_FLAT
};

static const MusixGlyph musix_glyphs[] = {
  { WHOLE_HEAD_W, WHOLE_HEAD_H, WHOLE_HEAD_BPR, WHOLE_HEAD_ANCHOR, whole_head_bm },
  { HALF_HEAD_W,  HALF_HEAD_H,  HALF_HEAD_BPR,  HALF_HEAD_ANCHOR,  half_head_bm  },
  { QTR_HEAD_W,   QTR_HEAD_H,   QTR_HEAD_BPR,   QTR_HEAD_ANCHOR,   qtr_head_bm   },
  { DOT_W,        DOT_H,        DOT_BPR,        DOT_ANCHOR,        dot_bm        },
  { FLAG8_W,      FLAG8_H,      FLAG8_BPR,      FLAG8_ANCHOR,      flag8_bm      },
  { FLAG16_W,     FLAG16_H,     FLAG16_BPR,     FLAG16_ANCHOR,     flag16_bm     },
  { FLAG32_W,     FLAG32_H,     FLAG32_BPR,     FLAG32_ANCHOR,     flag32_bm     },
  { FLAG64_W,     FLAG64_H,     FLAG64_BPR,     FLAG64_ANCHOR,     flag64_bm     },
  { REST_WHOLE_W, REST_WHOLE_H, REST_WHOLE_BPR, REST_WHOLE_ANCHOR, rest_whole_bm },
  { REST_HALF_W,  REST_HALF_H,  REST_HALF_BPR,  REST_HALF_ANCHOR,  rest_half_bm  },
  { REST_QTR_W,   REST_QTR_H,   REST_QTR_BPR,   REST_QTR_ANCHOR,   rest_qtr_bm   },
  { REST_8_W,     REST_8_H,     REST_8_BPR,     REST_8_ANCHOR,     rest_8_bm     },
  { REST_16_W,    REST_16_H,    REST_16_BPR,    REST_16_ANCHOR,    rest_16_bm    },
  { REST_32_W,    REST_32_H,    REST_32_BPR,    REST_32_ANCHOR,    rest_32_bm    },
  { REST_64_W,    REST_64_H,    REST_64_BPR,    REST_64_ANCHOR,    rest_64_bm    },
  { SHARP_W,      SHARP_H,      SHARP_BPR,      SHARP_ANCHOR,      sharp_bm      },
  { FLAT_W,       FLAT_H,       FLAT_BPR,       FLAT_ANCHOR,       flat_bm       }
};

/* Blit `gid`. The glyph's ANCHOR row lands at X68 y_anchor. The glyph left
 * edge lands at physical pixel (x*W_Width/X68_GWidth + px_shift). Pass a
 * negative px_shift to horizontally centre (-W/2) or right-align (-W). */
static void blit_glyph_px( int gid, int x_x68, int px_shift,
                           int y_anchor_x68, int col ) {
  const MusixGlyph *g = &musix_glyphs[gid];
  int cx = W_Width  * x_x68        / X68_GWidth + px_shift;
  int cy = (W_Height * y_anchor_x68 / X68_GHeight) % W_Height;
  int d  = ( y_anchor_x68 >= X68_GHeight ) ? 1 : 0;
  int top = cy - g->ANCHOR;
  XSTed_SetGColor( col );
  blit_clef_bm( g->bm, g->W, g->H, g->BPR, cx, top, d );
  isgscrchanged = 1;
}

/* Head types passed to XSTed_gnote_head (see score.c SS_TO_HEAD). */
#define HEAD_WHOLE 0
#define HEAD_HALF  1
#define HEAD_QTR   2

/* Music note head. y is the OLD 16x16 CGROM cell top; head centre lands
 * 13 X68 units lower so pitches line up on staff lines / space centres. */
void XSTed_gnote_head( int x, int y, int head_type, int col ) {
  const int Y_NUDGE_X68 = 13;
  int gid = ( head_type == HEAD_WHOLE ) ? GLYPH_WHOLE_HEAD :
            ( head_type == HEAD_HALF  ) ? GLYPH_HALF_HEAD  :
                                          GLYPH_QTR_HEAD;
  const MusixGlyph *g = &musix_glyphs[ gid ];
  blit_glyph_px( gid, x, -( g->W / 2 ), y + Y_NUDGE_X68, col );
}

/* Stem + upstem flag for a note group. Whole / dotted-whole (ss<=1) get
 * no stem. ss=2..4: stem only. ss=5..11: stem + 1..4 flags. */
void XSTed_gnote_stem_flag( int xc, int y_top, int y_bottom, int ss, int col ) {
  const int Y_NUDGE_X68 = 13;
  int d, sx, syt, syb;

  if ( ss <= 1 ) return;

  sx  = W_Width  * xc                        / X68_GWidth + 3;
  syt = (W_Height * ( y_top    + Y_NUDGE_X68 ) / X68_GHeight) % W_Height;
  syb = (W_Height * ( y_bottom + Y_NUDGE_X68 ) / X68_GHeight) % W_Height;
  d   = ( y_top >= X68_GHeight ) ? 1 : 0;

  XSTed_SetGColor( col );
  if ( d == current_gwindow )
    XDrawLine( XSTed_d, XSTed_w, XSTed_ggc, sx, syt, sx, syb );
  XDrawLine( XSTed_d, XSTed_gscr[d], XSTed_ggc, sx, syt, sx, syb );

  {
    int nflags, gid;
    if      ( ss == 5  || ss == 6  ) nflags = 1;
    else if ( ss == 7  || ss == 8  ) nflags = 2;
    else if ( ss == 9  || ss == 10 ) nflags = 3;
    else if ( ss == 11 )             nflags = 4;
    else                             nflags = 0;

    if ( nflags > 0 ) {
      const MusixGlyph *g;
      int top;
      gid = GLYPH_FLAG8 + ( nflags - 1 );
      g   = &musix_glyphs[ gid ];
      top = syt - g->ANCHOR;
      blit_clef_bm( g->bm, g->W, g->H, g->BPR, sx, top, d );
    }
  }
  isgscrchanged = 1;
}

/* PROTOTYPE: draw ledger lines for a note pitch. For pitches outside the two
 * main staves, draws every line position between the closest staff edge and
 * the note itself. So B5 (just above F5) gets the A5 ledger; B6 (5 steps
 * higher) gets A5/C6/E6/G6/B6 = 5 ledgers. C4 between staves gets one. */
static void draw_ledger_at( int cx, int cy_x68, int d ) {
  /* half_w was 10 (total 21 px) when the vector heads were ~8 px wide;
   * shrunk to match the 7-px whole-note head (see WHOLE_HEAD_W above) —
   * total 11 px keeps a ~2-px margin beyond the head on each side. */
  const int half_w = 5;
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

/* Augmentation dot next to a note head. If the note sits on a line
 * (y_n % 8 == 0), lift the dot into the space above (STed2 convention).
 * Dot is drawn 8 px to the right of the caller x. */
void XSTed_gnote_dot( int x, int y, int col ) {
  const int Y_NUDGE_X68 = 13;
  int y_n = y + Y_NUDGE_X68;
  if ( ( y_n % 8 ) == 0 ) y_n -= 4;
  blit_glyph_px( GLYPH_DOT, x, +8, y_n, col );
}

/* Rest symbol. y is the X68 coord of the anchor staff line (no Y_NUDGE):
 *   whole / dotted-whole: line 4 (D5 / F3), bar hangs below.
 *   half  / dotted-half:  middle line (B4 / D3), bar sits on top.
 *   qtr and shorter: middle line, glyph centred vertically.
 * Bitmap is centred horizontally on the caller x. */
void XSTed_grest( int x, int y, int ss, int col ) {
  int gid;
  const MusixGlyph *g;
  if      ( ss <= 1 ) gid = GLYPH_REST_WHOLE;
  else if ( ss <= 3 ) gid = GLYPH_REST_HALF;
  else if ( ss <= 5 ) gid = GLYPH_REST_QTR;
  else if ( ss <= 7 ) gid = GLYPH_REST_8;
  else if ( ss <= 9 ) gid = GLYPH_REST_16;
  else if ( ss <= 10 ) gid = GLYPH_REST_32;
  else                 gid = GLYPH_REST_64;
  g = &musix_glyphs[ gid ];
  blit_glyph_px( gid, x, -( g->W / 2 ), y, col );
}

/* 0..2 augmentation dots to the right of a rest. y is the rest's anchor
 * staff line; dots sit slightly above that line to stay visible. */
void XSTed_grest_dots( int x, int y, int dots, int col ) {
  int i;
  if ( dots <= 0 ) return;
  for ( i = 0; i < dots; i++ ) {
    blit_glyph_px( GLYPH_DOT, x, 8 + i * 5, y - 1, col );
  }
}

/* Accidental (sharp or flat) drawn with LEFT edge at caller x, ANCHOR row
 * at caller y. accid > 0 = sharp, accid < 0 = flat. */
void XSTed_gaccidental( int x, int y, int accid, int col ) {
  int gid = ( accid > 0 ) ? GLYPH_SHARP : GLYPH_FLAT;
  blit_glyph_px( gid, x, 0, y, col );
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
