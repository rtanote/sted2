## Process this file with automake to produce Makefile.in

SUBDIRS = sub rcpconv itor

localedir = $(datadir)/locale

bin_PROGRAMS = sted2

LDADD = sub/libx68funcs.a rcpconv/librcpconv.a \
	itor/libitor.a \
	@x_ldflags@ @x_libs@ @INTLLIBS@ @CURSES_LIBS@ -lm

INCLUDES = -I../intl -I.. -I$(srcdir) -I$(top_srcdir)/sted2/sub -I$(top_srcdir)/sted2/rcpconv -DSTED_LOCALE_DIR=\"$(localedir)\" @DEFS@

sted2_DEPENDENCIES = sub/libx68funcs.a rcpconv/librcpconv.a \
	itor/libitor.a

sted2_SOURCES =		\
	assign.c	\
	cm6con.c	\
	defload.c	\
	disp.c		\
	edit.c		\
	edits.c		\
	exclu.c		\
	file.c		\
	graphic.c	\
	key_sub.c	\
	mkeyb.c		\
	record.c	\
	redit.c		\
	score.c		\
	select.c	\
	sted.c		\
	track.c		\
	trkset.c	\
	visual.c

noinst_HEADERS = \
	machin.h	\
	rcddef.h	\
	sted.h		\
	version.h
