bin_PROGRAMS = \
	balde-template-gen

noinst_HEADERS = \
	template-parser.h

balde_template_gen_SOURCES = \
	balde-template-gen.c \
	template-parser.c

AM_CFLAGS = \
	$(all_includes) \
	$(GLIB_CFLAGS) \
	-I$(top_srcdir)/include

AM_LDFLAGS = \
	$(GLIB_LIBS)
