if HAVE_GTK

blurscopeltlibs = libblurscope.la
blurscopeldflags = -export-dynamic -avoid-version @GTK_LIBS@
blurscopesources = blurscope.c

lib_LTLIBRARIES = $(blurscopeltlibs)

else

blurscopeltlibs =
blurscopeldflags =
blurscopesources =

endif

libdir = $(ADDON_DIR)/scopes

AM_CFLAGS = -D_REENTRANT -I$(top_builddir) -I$(top_srcdir)/alsaplayer \
			@ARCH_CFLAGS@ @GTK_CFLAGS@ @DFLAGS@

libblurscope_la_LDFLAGS = $(blurscopeldflags)
LIBS =

libblurscope_la_SOURCES= $(blurscopesources)
