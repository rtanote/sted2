dnl aclocal.m4 generated automatically by aclocal 1.4

dnl Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY, to the extent permitted by law; without
dnl even the implied warranty of MERCHANTABILITY or FITNESS FOR A
dnl PARTICULAR PURPOSE.

dnl Curses detection: Munged from Midnight Commander's configure.in
dnl
dnl What it does:
dnl =============
dnl
dnl - Determine which version of curses is installed on your system
dnl   and set the -I/-L/-l compiler entries and add a few preprocessor
dnl   symbols 
dnl - Do an AC_SUBST on the CURSES_INCLUDEDIR and CURSES_LIBS so that
dnl   @CURSES_INCLUDEDIR@ and @CURSES_LIBS@ will be available in
dnl   Makefile.in's
dnl - Modify the following configure variables (these are the only
dnl   curses.m4 variables you can access from within configure.in)
dnl   CURSES_INCLUDEDIR - contains -I's and possibly -DRENAMED_CURSES if
dnl                       an ncurses.h that's been renamed to curses.h
dnl                       is found.
dnl   CURSES_LIBS       - sets -L and -l's appropriately
dnl   CFLAGS            - if --with-sco, add -D_SVID3 
dnl   has_curses        - exports result of tests to rest of configure
dnl
dnl Usage:
dnl ======
dnl 1) Add lines indicated below to acconfig.h
dnl 2) call AC_CHECK_CURSES after AC_PROG_CC in your configure.in
dnl 3) Instead of #include <curses.h> you should use the following to
dnl    properly locate ncurses or curses header file
dnl
dnl    #if defined(USE_NCURSES) && !defined(RENAMED_NCURSES)
dnl    #include <ncurses.h>
dnl    #else
dnl    #include <curses.h>
dnl    #endif
dnl
dnl 4) Make sure to add @CURSES_INCLUDEDIR@ to your preprocessor flags
dnl 5) Make sure to add @CURSES_LIBS@ to your linker flags or LIBS
dnl
dnl Notes with automake:
dnl - call AM_CONDITIONAL(HAS_CURSES, test "$has_curses" = true) from
dnl   configure.in
dnl - your Makefile.am can look something like this
dnl   -----------------------------------------------
dnl   INCLUDES= blah blah blah $(CURSES_INCLUDEDIR) 
dnl   if HAS_CURSES
dnl   CURSES_TARGETS=name_of_curses_prog
dnl   endif
dnl   bin_PROGRAMS = other_programs $(CURSES_TARGETS)
dnl   other_programs_SOURCES = blah blah blah
dnl   name_of_curses_prog_SOURCES = blah blah blah
dnl   other_programs_LDADD = blah
dnl   name_of_curses_prog_LDADD = blah $(CURSES_LIBS)
dnl   -----------------------------------------------
dnl
dnl
dnl The following lines should be added to acconfig.h:
dnl ==================================================
dnl
dnl /*=== Curses version detection defines ===*/
dnl /* Found some version of curses that we're going to use */
dnl #undef HAS_CURSES
dnl    
dnl /* Use SunOS SysV curses? */
dnl #undef USE_SUNOS_CURSES
dnl 
dnl /* Use old BSD curses - not used right now */
dnl #undef USE_BSD_CURSES
dnl 
dnl /* Use SystemV curses? */
dnl #undef USE_SYSV_CURSES
dnl 
dnl /* Use Ncurses? */
dnl #undef USE_NCURSES
dnl 
dnl /* If you Curses does not have color define this one */
dnl #undef NO_COLOR_CURSES
dnl 
dnl /* Define if you want to turn on SCO-specific code */
dnl #undef SCO_FLAVOR
dnl 
dnl /* Set to reflect version of ncurses *
dnl  *   0 = version 1.*
dnl  *   1 = version 1.9.9g
dnl  *   2 = version 4.0/4.1 */
dnl #undef NCURSES_970530
dnl
dnl /*=== End new stuff for acconfig.h ===*/
dnl 


AC_DEFUN(AC_CHECK_CURSES,[
	search_ncurses=true
	screen_manager=""
	has_curses=false

	CFLAGS=${CFLAGS--O}

	AC_SUBST(CURSES_LIBS)
	AC_SUBST(CURSES_INCLUDEDIR)

	AC_ARG_WITH(sco,
	  [  --with-sco              Use this to turn on SCO-specific code],[
	  if test x$withval = xyes; then
		AC_DEFINE(SCO_FLAVOR)
		CFLAGS="$CFLAGS -D_SVID3"
	  fi
	])

	AC_ARG_WITH(sunos-curses,
	  [  --with-sunos-curses     Used to force SunOS 4.x curses],[
	  if test x$withval = xyes; then
		AC_USE_SUNOS_CURSES
	  fi
	])

	AC_ARG_WITH(osf1-curses,
	  [  --with-osf1-curses      Used to force OSF/1 curses],[
	  if test x$withval = xyes; then
		AC_USE_OSF1_CURSES
	  fi
	])

	AC_ARG_WITH(vcurses,
	  [  --with-vcurses[=incdir] Used to force SysV curses],
	  if test x$withval != xyes; then
		CURSES_INCLUDEDIR="-I$withval"
	  fi
	  AC_USE_SYSV_CURSES
	)

	AC_ARG_WITH(ncurses,
	  [  --with-ncurses[=dir]    Compile with ncurses/locate base dir],
	  if test x$withval = xno ; then
		search_ncurses=false
	  elif test x$withval != xyes ; then
		CURSES_LIBS="$LIBS -L$withval/lib -lncurses"
		CURSES_INCLUDEDIR="-I$withval/include"
		search_ncurses=false
		screen_manager="ncurses"
		AC_DEFINE(USE_NCURSES)
		AC_DEFINE(HAS_CURSES)
		has_curses=true
	  fi
	)

	if $search_ncurses
	then
		AC_SEARCH_NCURSES()
	fi


])


AC_DEFUN(AC_USE_SUNOS_CURSES, [
	search_ncurses=false
	screen_manager="SunOS 4.x /usr/5include curses"
	AC_MSG_RESULT(Using SunOS 4.x /usr/5include curses)
	AC_DEFINE(USE_SUNOS_CURSES)
	AC_DEFINE(HAS_CURSES)
	has_curses=true
	AC_DEFINE(NO_COLOR_CURSES)
	AC_DEFINE(USE_SYSV_CURSES)
	CURSES_INCLUDEDIR="-I/usr/5include"
	CURSES_LIBS="/usr/5lib/libcurses.a /usr/5lib/libtermcap.a"
	AC_MSG_RESULT(Please note that some screen refreshs may fail)
])

AC_DEFUN(AC_USE_OSF1_CURSES, [
       AC_MSG_RESULT(Using OSF1 curses)
       search_ncurses=false
       screen_manager="OSF1 curses"
       AC_DEFINE(HAS_CURSES)
       has_curses=true
       AC_DEFINE(NO_COLOR_CURSES)
       AC_DEFINE(USE_SYSV_CURSES)
       CURSES_LIBS="-lcurses"
])

AC_DEFUN(AC_USE_SYSV_CURSES, [
	AC_MSG_RESULT(Using SysV curses)
	AC_DEFINE(HAS_CURSES)
	has_curses=true
	AC_DEFINE(USE_SYSV_CURSES)
	search_ncurses=false
	screen_manager="SysV/curses"
	CURSES_LIBS="-lcurses"
])

dnl AC_ARG_WITH(bsd-curses,
dnl [--with-bsd-curses         Used to compile with bsd curses, not very fancy],
dnl 	search_ncurses=false
dnl	screen_manager="Ultrix/cursesX"
dnl	if test $system = ULTRIX
dnl	then
dnl	    THIS_CURSES=cursesX
dnl        else
dnl	    THIS_CURSES=curses
dnl	fi
dnl
dnl	CURSES_LIBS="-l$THIS_CURSES -ltermcap"
dnl	AC_DEFINE(HAS_CURSES)
dnl	has_curses=true
dnl	AC_DEFINE(USE_BSD_CURSES)
dnl	AC_MSG_RESULT(Please note that some screen refreshs may fail)
dnl	AC_WARN(Use of the bsdcurses extension has some)
dnl	AC_WARN(display/input problems.)
dnl	AC_WARN(Reconsider using xcurses)
dnl)

	
dnl
dnl Parameters: directory filename cureses_LIBS curses_INCLUDEDIR nicename
dnl
AC_DEFUN(AC_NCURSES, [
    if $search_ncurses
    then
        if test -f $1/$2
	then
	    AC_MSG_RESULT(Found ncurses on $1/$2)
 	    CURSES_LIBS="$3"
	    CURSES_INCLUDEDIR="$4"
	    search_ncurses=false
	    screen_manager=$5
            AC_DEFINE(HAS_CURSES)
            has_curses=true
	    AC_DEFINE(USE_NCURSES)
	fi
    fi
])

AC_DEFUN(AC_SEARCH_NCURSES, [
    AC_CHECKING("location of ncurses.h file")

    AC_NCURSES(/usr/include, ncurses.h, -lncurses,, "ncurses on /usr/include")
    AC_NCURSES(/usr/include/ncurses, ncurses.h, -lncurses, -I/usr/include/ncurses, "ncurses on /usr/include/ncurses")
    AC_NCURSES(/usr/local/include, ncurses.h, -L/usr/local/lib -lncurses, -I/usr/local/include, "ncurses on /usr/local")
    AC_NCURSES(/usr/local/include/ncurses, ncurses.h, -L/usr/local/lib -L/usr/local/lib/ncurses -lncurses, -I/usr/local/include/ncurses, "ncurses on /usr/local/include/ncurses")

    AC_NCURSES(/usr/local/include/ncurses, curses.h, -L/usr/local/lib -lncurses, -I/usr/local/include/ncurses -DRENAMED_NCURSES, "renamed ncurses on /usr/local/.../ncurses")

    AC_NCURSES(/usr/include/ncurses, curses.h, -lncurses, -I/usr/include/ncurses -DRENAMED_NCURSES, "renamed ncurses on /usr/include/ncurses")

    dnl
    dnl We couldn't find ncurses, try SysV curses
    dnl
    if $search_ncurses 
    then
        AC_EGREP_HEADER(init_color, /usr/include/curses.h,
	    AC_USE_SYSV_CURSES)
	AC_EGREP_CPP(USE_NCURSES,[
#include <curses.h>
#ifdef __NCURSES_H
#undef USE_NCURSES
USE_NCURSES
#endif
],[
	CURSES_INCLUDEDIR="$CURSES_INCLUDEDIR -DRENAMED_NCURSES"
        AC_DEFINE(HAS_CURSES)
	has_curses=true
        AC_DEFINE(USE_NCURSES)
        search_ncurses=false
        screen_manager="ncurses installed as curses"
])
    fi

    dnl
    dnl Try SunOS 4.x /usr/5{lib,include} ncurses
    dnl The flags USE_SUNOS_CURSES, USE_BSD_CURSES and BUGGY_CURSES
    dnl should be replaced by a more fine grained selection routine
    dnl
    if $search_ncurses
    then
	if test -f /usr/5include/curses.h
	then
	    AC_USE_SUNOS_CURSES
        fi
    else
        # check for ncurses version, to properly ifdef mouse-fix
	AC_MSG_CHECKING(for ncurses version)
	ncurses_version=unknown
cat > conftest.$ac_ext <<EOF
[#]line __oline__ "configure"
#include "confdefs.h"
#ifdef RENAMED_NCURSES
#include <curses.h>
#else
#include <ncurses.h>
#endif
#undef VERSION
VERSION:NCURSES_VERSION
EOF
        if (eval "$ac_cpp conftest.$ac_ext") 2>&AC_FD_CC |
  egrep "VERSION:" >conftest.out 2>&1; then
changequote(,)dnl
            ncurses_version=`cat conftest.out|sed -e 's/^[^"]*"//' -e 's/".*//'`
changequote([,])dnl
	fi
	rm -rf conftest*
        AC_MSG_RESULT($ncurses_version)
	case "$ncurses_version" in
changequote(,)dnl
	4.[01])
changequote([,])dnl
            AC_DEFINE(NCURSES_970530,2)
            ;;
	1.9.9g)
            AC_DEFINE(NCURSES_970530,1)
            ;;
	1*)
            AC_DEFINE(NCURSES_970530,0)
            ;;
	esac
    fi
])






# Define a conditional.

AC_DEFUN(AM_CONDITIONAL,
[AC_SUBST($1_TRUE)
AC_SUBST($1_FALSE)
if $2; then
  $1_TRUE=
  $1_FALSE='#'
else
  $1_TRUE='#'
  $1_FALSE=
fi])

# Like AC_CONFIG_HEADER, but automatically create stamp file.

AC_DEFUN(AM_CONFIG_HEADER,
[AC_PREREQ([2.12])
AC_CONFIG_HEADER([$1])
dnl When config.status generates a header, we must update the stamp-h file.
dnl This file resides in the same directory as the config header
dnl that is generated.  We must strip everything past the first ":",
dnl and everything past the last "/".
AC_OUTPUT_COMMANDS(changequote(<<,>>)dnl
ifelse(patsubst(<<$1>>, <<[^ ]>>, <<>>), <<>>,
<<test -z "<<$>>CONFIG_HEADERS" || echo timestamp > patsubst(<<$1>>, <<^\([^:]*/\)?.*>>, <<\1>>)stamp-h<<>>dnl>>,
<<am_indx=1
for am_file in <<$1>>; do
  case " <<$>>CONFIG_HEADERS " in
  *" <<$>>am_file "*<<)>>
    echo timestamp > `echo <<$>>am_file | sed -e 's%:.*%%' -e 's%[^/]*$%%'`stamp-h$am_indx
    ;;
  esac
  am_indx=`expr "<<$>>am_indx" + 1`
done<<>>dnl>>)
changequote([,]))])

# Do all the work for Automake.  This macro actually does too much --
# some checks are only needed if your package does certain things.
# But this isn't really a big deal.

# serial 1

dnl Usage:
dnl AM_INIT_AUTOMAKE(package,version, [no-define])

AC_DEFUN(AM_INIT_AUTOMAKE,
[AC_REQUIRE([AC_PROG_INSTALL])
PACKAGE=[$1]
AC_SUBST(PACKAGE)
VERSION=[$2]
AC_SUBST(VERSION)
dnl test to see if srcdir already configured
if test "`cd $srcdir && pwd`" != "`pwd`" && test -f $srcdir/config.status; then
  AC_MSG_ERROR([source directory already configured; run "make distclean" there first])
fi
ifelse([$3],,
AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version number of package]))
AC_REQUIRE([AM_SANITY_CHECK])
AC_REQUIRE([AC_ARG_PROGRAM])
dnl FIXME This is truly gross.
missing_dir=`cd $ac_aux_dir && pwd`
AM_MISSING_PROG(ACLOCAL, aclocal, $missing_dir)
AM_MISSING_PROG(AUTOCONF, autoconf, $missing_dir)
AM_MISSING_PROG(AUTOMAKE, automake, $missing_dir)
AM_MISSING_PROG(AUTOHEADER, autoheader, $missing_dir)
AM_MISSING_PROG(MAKEINFO, makeinfo, $missing_dir)
AC_REQUIRE([AC_PROG_MAKE_SET])])

#
# Check to make sure that the build environment is sane.
#

AC_DEFUN(AM_SANITY_CHECK,
[AC_MSG_CHECKING([whether build environment is sane])
# Just in case
sleep 1
echo timestamp > conftestfile
# Do `set' in a subshell so we don't clobber the current shell's
# arguments.  Must try -L first in case configure is actually a
# symlink; some systems play weird games with the mod time of symlinks
# (eg FreeBSD returns the mod time of the symlink's containing
# directory).
if (
   set X `ls -Lt $srcdir/configure conftestfile 2> /dev/null`
   if test "[$]*" = "X"; then
      # -L didn't work.
      set X `ls -t $srcdir/configure conftestfile`
   fi
   if test "[$]*" != "X $srcdir/configure conftestfile" \
      && test "[$]*" != "X conftestfile $srcdir/configure"; then

      # If neither matched, then we have a broken ls.  This can happen
      # if, for instance, CONFIG_SHELL is bash and it inherits a
      # broken ls alias from the environment.  This has actually
      # happened.  Such a system could not be considered "sane".
      AC_MSG_ERROR([ls -t appears to fail.  Make sure there is not a broken
alias in your environment])
   fi

   test "[$]2" = conftestfile
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly created file is older than distributed files!
Check your system clock])
fi
rm -f conftest*
AC_MSG_RESULT(yes)])

dnl AM_MISSING_PROG(NAME, PROGRAM, DIRECTORY)
dnl The program must properly implement --version.
AC_DEFUN(AM_MISSING_PROG,
[AC_MSG_CHECKING(for working $2)
# Run test in a subshell; some versions of sh will print an error if
# an executable is not found, even if stderr is redirected.
# Redirect stdin to placate older versions of autoconf.  Sigh.
if ($2 --version) < /dev/null > /dev/null 2>&1; then
   $1=$2
   AC_MSG_RESULT(found)
else
   $1="$3/missing $2"
   AC_MSG_RESULT(missing)
fi
AC_SUBST($1)])

# Macro to add for using GNU gettext.
# Ulrich Drepper <drepper@cygnus.com>, 1995.
#
# This file can be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU Public License
# but which still want to provide support for the GNU gettext functionality.
# Please note that the actual code is *not* freely available.

# serial 5

AC_DEFUN(AM_WITH_NLS,
  [AC_MSG_CHECKING([whether NLS is requested])
    dnl Default is enabled NLS
    AC_ARG_ENABLE(nls,
      [  --disable-nls           do not use Native Language Support],
      USE_NLS=$enableval, USE_NLS=yes)
    AC_MSG_RESULT($USE_NLS)
    AC_SUBST(USE_NLS)

    USE_INCLUDED_LIBINTL=no

    dnl If we use NLS figure out what method
    if test "$USE_NLS" = "yes"; then
      AC_DEFINE(ENABLE_NLS)
      AC_MSG_CHECKING([whether included gettext is requested])
      AC_ARG_WITH(included-gettext,
        [  --with-included-gettext use the GNU gettext library included here],
        nls_cv_force_use_gnu_gettext=$withval,
        nls_cv_force_use_gnu_gettext=no)
      AC_MSG_RESULT($nls_cv_force_use_gnu_gettext)

      nls_cv_use_gnu_gettext="$nls_cv_force_use_gnu_gettext"
      if test "$nls_cv_force_use_gnu_gettext" != "yes"; then
        dnl User does not insist on using GNU NLS library.  Figure out what
        dnl to use.  If gettext or catgets are available (in this order) we
        dnl use this.  Else we have to fall back to GNU NLS library.
	dnl catgets is only used if permitted by option --with-catgets.
	nls_cv_header_intl=
	nls_cv_header_libgt=
	CATOBJEXT=NONE

	AC_CHECK_HEADER(libintl.h,
	  [AC_CACHE_CHECK([for gettext in libc], gt_cv_func_gettext_libc,
	    [AC_TRY_LINK([#include <libintl.h>], [return (int) gettext ("")],
	       gt_cv_func_gettext_libc=yes, gt_cv_func_gettext_libc=no)])

	   if test "$gt_cv_func_gettext_libc" != "yes"; then
	     AC_CHECK_LIB(intl, bindtextdomain,
	       [AC_CACHE_CHECK([for gettext in libintl],
		 gt_cv_func_gettext_libintl,
		 [AC_CHECK_LIB(intl, gettext,
		  gt_cv_func_gettext_libintl=yes,
		  gt_cv_func_gettext_libintl=no)],
		 gt_cv_func_gettext_libintl=no)])
	   fi

	   if test "$gt_cv_func_gettext_libc" = "yes" \
	      || test "$gt_cv_func_gettext_libintl" = "yes"; then
	      AC_DEFINE(HAVE_GETTEXT)
	      AM_PATH_PROG_WITH_TEST(MSGFMT, msgfmt,
		[test -z "`$ac_dir/$ac_word -h 2>&1 | grep 'dv '`"], no)dnl
	      if test "$MSGFMT" != "no"; then
		AC_CHECK_FUNCS(dcgettext)
		AC_PATH_PROG(GMSGFMT, gmsgfmt, $MSGFMT)
		AM_PATH_PROG_WITH_TEST(XGETTEXT, xgettext,
		  [test -z "`$ac_dir/$ac_word -h 2>&1 | grep '(HELP)'`"], :)
		AC_TRY_LINK(, [extern int _nl_msg_cat_cntr;
			       return _nl_msg_cat_cntr],
		  [CATOBJEXT=.gmo
		   DATADIRNAME=share],
		  [CATOBJEXT=.mo
		   DATADIRNAME=lib])
		INSTOBJEXT=.mo
	      fi
	    fi
	])

        if test "$CATOBJEXT" = "NONE"; then
	  AC_MSG_CHECKING([whether catgets can be used])
	  AC_ARG_WITH(catgets,
	    [  --with-catgets          use catgets functions if available],
	    nls_cv_use_catgets=$withval, nls_cv_use_catgets=no)
	  AC_MSG_RESULT($nls_cv_use_catgets)

	  if test "$nls_cv_use_catgets" = "yes"; then
	    dnl No gettext in C library.  Try catgets next.
	    AC_CHECK_LIB(i, main)
	    AC_CHECK_FUNC(catgets,
	      [AC_DEFINE(HAVE_CATGETS)
	       INTLOBJS="\$(CATOBJS)"
	       AC_PATH_PROG(GENCAT, gencat, no)dnl
	       if test "$GENCAT" != "no"; then
		 AC_PATH_PROG(GMSGFMT, gmsgfmt, no)
		 if test "$GMSGFMT" = "no"; then
		   AM_PATH_PROG_WITH_TEST(GMSGFMT, msgfmt,
		    [test -z "`$ac_dir/$ac_word -h 2>&1 | grep 'dv '`"], no)
		 fi
		 AM_PATH_PROG_WITH_TEST(XGETTEXT, xgettext,
		   [test -z "`$ac_dir/$ac_word -h 2>&1 | grep '(HELP)'`"], :)
		 USE_INCLUDED_LIBINTL=yes
		 CATOBJEXT=.cat
		 INSTOBJEXT=.cat
		 DATADIRNAME=lib
		 INTLDEPS='$(top_builddir)/intl/libintl.a'
		 INTLLIBS=$INTLDEPS
		 LIBS=`echo $LIBS | sed -e 's/-lintl//'`
		 nls_cv_header_intl=intl/libintl.h
		 nls_cv_header_libgt=intl/libgettext.h
	       fi])
	  fi
        fi

        if test "$CATOBJEXT" = "NONE"; then
	  dnl Neither gettext nor catgets in included in the C library.
	  dnl Fall back on GNU gettext library.
	  nls_cv_use_gnu_gettext=yes
        fi
      fi

      if test "$nls_cv_use_gnu_gettext" = "yes"; then
        dnl Mark actions used to generate GNU NLS library.
        INTLOBJS="\$(GETTOBJS)"
        AM_PATH_PROG_WITH_TEST(MSGFMT, msgfmt,
	  [test -z "`$ac_dir/$ac_word -h 2>&1 | grep 'dv '`"], msgfmt)
        AC_PATH_PROG(GMSGFMT, gmsgfmt, $MSGFMT)
        AM_PATH_PROG_WITH_TEST(XGETTEXT, xgettext,
	  [test -z "`$ac_dir/$ac_word -h 2>&1 | grep '(HELP)'`"], :)
        AC_SUBST(MSGFMT)
	USE_INCLUDED_LIBINTL=yes
        CATOBJEXT=.gmo
        INSTOBJEXT=.mo
        DATADIRNAME=share
	INTLDEPS='$(top_builddir)/intl/libintl.a'
	INTLLIBS=$INTLDEPS
	LIBS=`echo $LIBS | sed -e 's/-lintl//'`
        nls_cv_header_intl=intl/libintl.h
        nls_cv_header_libgt=intl/libgettext.h
      fi

      dnl Test whether we really found GNU xgettext.
      if test "$XGETTEXT" != ":"; then
	dnl If it is no GNU xgettext we define it as : so that the
	dnl Makefiles still can work.
	if $XGETTEXT --omit-header /dev/null 2> /dev/null; then
	  : ;
	else
	  AC_MSG_RESULT(
	    [found xgettext program is not GNU xgettext; ignore it])
	  XGETTEXT=":"
	fi
      fi

      # We need to process the po/ directory.
      POSUB=po
    else
      DATADIRNAME=share
      nls_cv_header_intl=intl/libintl.h
      nls_cv_header_libgt=intl/libgettext.h
    fi
    AC_LINK_FILES($nls_cv_header_libgt, $nls_cv_header_intl)
    AC_OUTPUT_COMMANDS(
     [case "$CONFIG_FILES" in *po/Makefile.in*)
        sed -e "/POTFILES =/r po/POTFILES" po/Makefile.in > po/Makefile
      esac])


    # If this is used in GNU gettext we have to set USE_NLS to `yes'
    # because some of the sources are only built for this goal.
    if test "$PACKAGE" = gettext; then
      USE_NLS=yes
      USE_INCLUDED_LIBINTL=yes
    fi

    dnl These rules are solely for the distribution goal.  While doing this
    dnl we only have to keep exactly one list of the available catalogs
    dnl in configure.in.
    for lang in $ALL_LINGUAS; do
      GMOFILES="$GMOFILES $lang.gmo"
      POFILES="$POFILES $lang.po"
    done

    dnl Make all variables we use known to autoconf.
    AC_SUBST(USE_INCLUDED_LIBINTL)
    AC_SUBST(CATALOGS)
    AC_SUBST(CATOBJEXT)
    AC_SUBST(DATADIRNAME)
    AC_SUBST(GMOFILES)
    AC_SUBST(INSTOBJEXT)
    AC_SUBST(INTLDEPS)
    AC_SUBST(INTLLIBS)
    AC_SUBST(INTLOBJS)
    AC_SUBST(POFILES)
    AC_SUBST(POSUB)
  ])

AC_DEFUN(AM_GNU_GETTEXT,
  [AC_REQUIRE([AC_PROG_MAKE_SET])dnl
   AC_REQUIRE([AC_PROG_CC])dnl
   AC_REQUIRE([AC_PROG_RANLIB])dnl
   AC_REQUIRE([AC_ISC_POSIX])dnl
   AC_REQUIRE([AC_HEADER_STDC])dnl
   AC_REQUIRE([AC_C_CONST])dnl
   AC_REQUIRE([AC_C_INLINE])dnl
   AC_REQUIRE([AC_TYPE_OFF_T])dnl
   AC_REQUIRE([AC_TYPE_SIZE_T])dnl
   AC_REQUIRE([AC_FUNC_ALLOCA])dnl
   AC_REQUIRE([AC_FUNC_MMAP])dnl

   AC_CHECK_HEADERS([argz.h limits.h locale.h nl_types.h malloc.h string.h \
unistd.h sys/param.h])
   AC_CHECK_FUNCS([getcwd munmap putenv setenv setlocale strchr strcasecmp \
strdup __argz_count __argz_stringify __argz_next])

   if test "${ac_cv_func_stpcpy+set}" != "set"; then
     AC_CHECK_FUNCS(stpcpy)
   fi
   if test "${ac_cv_func_stpcpy}" = "yes"; then
     AC_DEFINE(HAVE_STPCPY)
   fi

   AM_LC_MESSAGES
   AM_WITH_NLS

   if test "x$CATOBJEXT" != "x"; then
     if test "x$ALL_LINGUAS" = "x"; then
       LINGUAS=
     else
       AC_MSG_CHECKING(for catalogs to be installed)
       NEW_LINGUAS=
       for lang in ${LINGUAS=$ALL_LINGUAS}; do
         case "$ALL_LINGUAS" in
          *$lang*) NEW_LINGUAS="$NEW_LINGUAS $lang" ;;
         esac
       done
       LINGUAS=$NEW_LINGUAS
       AC_MSG_RESULT($LINGUAS)
     fi

     dnl Construct list of names of catalog files to be constructed.
     if test -n "$LINGUAS"; then
       for lang in $LINGUAS; do CATALOGS="$CATALOGS $lang$CATOBJEXT"; done
     fi
   fi

   dnl The reference to <locale.h> in the installed <libintl.h> file
   dnl must be resolved because we cannot expect the users of this
   dnl to define HAVE_LOCALE_H.
   if test $ac_cv_header_locale_h = yes; then
     INCLUDE_LOCALE_H="#include <locale.h>"
   else
     INCLUDE_LOCALE_H="\
/* The system does not provide the header <locale.h>.  Take care yourself.  */"
   fi
   AC_SUBST(INCLUDE_LOCALE_H)

   dnl Determine which catalog format we have (if any is needed)
   dnl For now we know about two different formats:
   dnl   Linux libc-5 and the normal X/Open format
   test -d intl || mkdir intl
   if test "$CATOBJEXT" = ".cat"; then
     AC_CHECK_HEADER(linux/version.h, msgformat=linux, msgformat=xopen)

     dnl Transform the SED scripts while copying because some dumb SEDs
     dnl cannot handle comments.
     sed -e '/^#/d' $srcdir/intl/$msgformat-msg.sed > intl/po2msg.sed
   fi
   dnl po2tbl.sed is always needed.
   sed -e '/^#.*[^\\]$/d' -e '/^#$/d' \
     $srcdir/intl/po2tbl.sed.in > intl/po2tbl.sed

   dnl In the intl/Makefile.in we have a special dependency which makes
   dnl only sense for gettext.  We comment this out for non-gettext
   dnl packages.
   if test "$PACKAGE" = "gettext"; then
     GT_NO="#NO#"
     GT_YES=
   else
     GT_NO=
     GT_YES="#YES#"
   fi
   AC_SUBST(GT_NO)
   AC_SUBST(GT_YES)

   dnl If the AC_CONFIG_AUX_DIR macro for autoconf is used we possibly
   dnl find the mkinstalldirs script in another subdir but ($top_srcdir).
   dnl Try to locate is.
   MKINSTALLDIRS=
   if test -n "$ac_aux_dir"; then
     MKINSTALLDIRS="$ac_aux_dir/mkinstalldirs"
   fi
   if test -z "$MKINSTALLDIRS"; then
     MKINSTALLDIRS="\$(top_srcdir)/mkinstalldirs"
   fi
   AC_SUBST(MKINSTALLDIRS)

   dnl *** For now the libtool support in intl/Makefile is not for real.
   l=
   AC_SUBST(l)

   dnl Generate list of files to be processed by xgettext which will
   dnl be included in po/Makefile.
   test -d po || mkdir po
   if test "x$srcdir" != "x."; then
     if test "x`echo $srcdir | sed 's@/.*@@'`" = "x"; then
       posrcprefix="$srcdir/"
     else
       posrcprefix="../$srcdir/"
     fi
   else
     posrcprefix="../"
   fi
   rm -f po/POTFILES
   sed -e "/^#/d" -e "/^\$/d" -e "s,.*,	$posrcprefix& \\\\," -e "\$s/\(.*\) \\\\/\1/" \
	< $srcdir/po/POTFILES.in > po/POTFILES
  ])

# Search path for a program which passes the given test.
# Ulrich Drepper <drepper@cygnus.com>, 1996.
#
# This file can be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU Public License
# but which still want to provide support for the GNU gettext functionality.
# Please note that the actual code is *not* freely available.

# serial 1

dnl AM_PATH_PROG_WITH_TEST(VARIABLE, PROG-TO-CHECK-FOR,
dnl   TEST-PERFORMED-ON-FOUND_PROGRAM [, VALUE-IF-NOT-FOUND [, PATH]])
AC_DEFUN(AM_PATH_PROG_WITH_TEST,
[# Extract the first word of "$2", so it can be a program name with args.
set dummy $2; ac_word=[$]2
AC_MSG_CHECKING([for $ac_word])
AC_CACHE_VAL(ac_cv_path_$1,
[case "[$]$1" in
  /*)
  ac_cv_path_$1="[$]$1" # Let the user override the test with a path.
  ;;
  *)
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:"
  for ac_dir in ifelse([$5], , $PATH, [$5]); do
    test -z "$ac_dir" && ac_dir=.
    if test -f $ac_dir/$ac_word; then
      if [$3]; then
	ac_cv_path_$1="$ac_dir/$ac_word"
	break
      fi
    fi
  done
  IFS="$ac_save_ifs"
dnl If no 4th arg is given, leave the cache variable unset,
dnl so AC_PATH_PROGS will keep looking.
ifelse([$4], , , [  test -z "[$]ac_cv_path_$1" && ac_cv_path_$1="$4"
])dnl
  ;;
esac])dnl
$1="$ac_cv_path_$1"
if test -n "[$]$1"; then
  AC_MSG_RESULT([$]$1)
else
  AC_MSG_RESULT(no)
fi
AC_SUBST($1)dnl
])

# Check whether LC_MESSAGES is available in <locale.h>.
# Ulrich Drepper <drepper@cygnus.com>, 1995.
#
# This file can be copied and used freely without restrictions.  It can
# be used in projects which are not available under the GNU Public License
# but which still want to provide support for the GNU gettext functionality.
# Please note that the actual code is *not* freely available.

# serial 1

AC_DEFUN(AM_LC_MESSAGES,
  [if test $ac_cv_header_locale_h = yes; then
    AC_CACHE_CHECK([for LC_MESSAGES], am_cv_val_LC_MESSAGES,
      [AC_TRY_LINK([#include <locale.h>], [return LC_MESSAGES],
       am_cv_val_LC_MESSAGES=yes, am_cv_val_LC_MESSAGES=no)])
    if test $am_cv_val_LC_MESSAGES = yes; then
      AC_DEFINE(HAVE_LC_MESSAGES)
    fi
  fi])

