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

TOPDIR := .
#
# This header.mak file will set up all necessary options for compiling
# and linking C and C++ programs which use OpenGL and/or GLUT on the
# Ubuntu systems.
#
# If you want to take advantage of GDB's extra debugging features,
# change "-g" in the CFLAGS and LIBFLAGS macro definitions to "-ggdb".
#
INCLUDE = -I $(TOPDIR) -I $(TOPDIR)/json
LIBDIRS =

LDLIBS = -lglut -lGLU -lGL -lXext -lX11 -lm

CFLAGS = -g $(INCLUDE) -Wall -pedantic -Wextra
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)

########## End of flags from header.mak


CPP_FILES :=    camera.cpp          \
                checkedshader.cpp   \
                Color.cpp           \
                cp7.cpp             \
                cylinder.cpp        \
                Light.cpp           \
                PhongShader.cpp     \
                Point.cpp           \
                proceduralshaderfactory.cpp \
                Raytracer.cpp       \
                Rectangle.cpp       \
                scene.cpp           \
                Shape.cpp           \
                ShapeFactory.cpp    \
                Sphere.cpp          \
                ToneReproducer.cpp  \
                Vector.cpp          \
                ./json/json.cpp
C_FILES =
PS_FILES =
S_FILES =
H_FILES =	    camera.h            \
                checkedshader.h     \
                Color.h             \
                cylinderh           \
                ijsonserializable.h \
                Light.h             \
                PhongShader.h       \
                Point.h             \
                proceduralshaderfactory.h \
                Raytracer.h         \
                Rectangle.h         \
                scene.h             \
                Shape.h             \
                ShapeFactory.h      \
                Sphere.h            \
                ToneReproducer.h    \
                Vector.h            \
                ./json/json.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	    camera.o          \
                checkedshader.o   \
                Color.o           \
                cylinder.o        \
                Light.o           \
                PhongShader.o     \
                Point.o           \
                proceduralshaderfactory.o \
                Raytracer.o       \
                Rectangle.o       \
                scene.o           \
                Shape.o           \
                ShapeFactory.o    \
                Sphere.o          \
                ToneReproducer.o  \
                Vector.o          \
                ./json/json.o
#
# Main targets
#

all:	cp7

cp7:	cp7.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o cp7 cp7.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

camera.o:           camera.h ijsonserializable.h
./json/json.o:		./json/json.h ./json/jsoncpp.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c ./json/jsoncpp.cpp -o ./json/json.o
cylinder.o:	        Point.h Shape.h Color.h ijsonserializable.h
checkedshader.o:    checkedshader.h proceduralshader.h
proceduralshader.o:	Color.h Point.h ijsonserializable.h
proceduralshaderfactory.o:  proceduralshaderfactory.h
scene.o:	        scene.h ./json/json.h camera.h ijsonserializable.h ShapeFactory.h proceduralshaderfactory.h
Color.o:	        Color.h ijsonserializable.h
Light.o:	        Color.h Light.h Point.h Vector.h ijsonserializable.h
PhongShader.o:	    Color.h Light.h PhongShader.h Point.h Shape.h Vector.h
Point.o:	        Color.h Point.h Vector.h ijsonserializable.h
Raytracer.o:	    Color.h Light.h PhongShader.h Point.h Raytracer.h Shape.h Vector.h
Rectangle.o:	    Color.h Point.h Rectangle.h Shape.h Vector.h ijsonserializable.h
Shape.o:	        Color.h Point.h Shape.h Vector.h checkedshader.h ijsonserializable.h
ShapeFactory.o:     ShapeFactory.h
Sphere.o:	        Color.h Point.h Shape.h Sphere.h Vector.h ijsonserializable.h
ToneReproducer.o:	Color.h ToneReproducer.h
Vector.o:	        Vector.h ijsonserializable.h
cp7.o:	            checkedshader.h Color.h Light.h PhongShader.h Point.h   \
                    Raytracer.h Rectangle.h Scene.h scene.h Shape.h         \
                    Sphere.h ToneReproducer.h Vector.h                      \
                    cylinder.h ./json/json.h camera.h proceduralshaderfactory.h

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
