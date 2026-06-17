## Process this file with automake to produce Makefile.in

SUBDIRS = sted2 etc doc contrib

EXTRA_DIST = README.jp \
	intl/libgettext.h \
	intl/po2tbl.sed.in

YYMMDD=`date +%Y%m%d`

.PHONY: .version

.version:
	-rm $(srcdir)/sted2/version.h
	echo "#define VERSION_ID	\"$(YYMMDD)\"" > $(srcdir)/sted2/version.h
	autoconf

