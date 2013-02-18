#
# Created by gmakemake (Ubuntu Dec 29 2011) on Mon Feb 27 01:20:43 2012
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.s) -o $@ $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

AS =		as
CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.s = $(AS) $(ASFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

#
# This header.mak file will set up all necessary options for compiling
# and linking C and C++ programs which use OpenGL and/or GLUT on the
# Ubuntu systems.
#
# If you want to take advantage of GDB's extra debugging features,
# change "-g" in the CFLAGS and LIBFLAGS macro definitions to "-ggdb".
#
INCLUDE =
LIBDIRS =

LDLIBS = -lglut -lGLU -lGL -lXext -lX11 -lm

CFLAGS = -g $(INCLUDE)
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)

########## End of flags from header.mak


CPP_FILES =	Color.cpp Light.cpp PhongShader.cpp Point.cpp Raytracer.cpp Rectangle.cpp Shape.cpp Sphere.cpp ToneReproducer.cpp Vector.cpp World.cpp cp7.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	Color.h Light.h PhongShader.h Point.h Raytracer.h Rectangle.h Scene.h Shape.h Sphere.h ToneReproducer.h Vector.h World.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	Color.o Light.o PhongShader.o Point.o Raytracer.o Rectangle.o Shape.o Sphere.o ToneReproducer.o Vector.o World.o 

#
# Main targets
#

all:	cp7 

cp7:	cp7.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o cp7 cp7.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

Color.o:	Color.h
Light.o:	Color.h Light.h Point.h Vector.h
PhongShader.o:	Color.h Light.h PhongShader.h Point.h Shape.h Vector.h World.h
Point.o:	Color.h Point.h Vector.h
Raytracer.o:	Color.h Light.h PhongShader.h Point.h Raytracer.h Shape.h Vector.h World.h
Rectangle.o:	Color.h Point.h Rectangle.h Shape.h Vector.h
Shape.o:	Color.h Point.h Shape.h Vector.h
Sphere.o:	Color.h Point.h Shape.h Sphere.h Vector.h
ToneReproducer.o:	Color.h ToneReproducer.h
Vector.o:	Vector.h
World.o:	Color.h World.h
cp7.o:	Color.h Light.h PhongShader.h Point.h Raytracer.h Rectangle.h Scene.h Shape.h Sphere.h ToneReproducer.h Vector.h World.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) cp7.o core

realclean:        clean
	-/bin/rm -f cp7 
