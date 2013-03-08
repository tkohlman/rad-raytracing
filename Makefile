################################################################################
######                         Acknowledgements                           ######
################################################################################
#                                                                              #
#   This makefile scheme is based off of the method developed by Tom Tromey.   #
#   For more information, visit: http://mad-scientist.net/make/autodep.html    #
#                                                                              #
################################################################################

.SILENT:

################################################################################
######                          Source Folders                            ######
################################################################################
MODULES =
MODULES += lib/json/
MODULES += src/effects/
MODULES += src/graphics/
MODULES += src/raytracer/
MODULES += src/scene/
MODULES += src/shaders/
MODULES += src/shapes/

################################################################################
######                          Header Folders                            ######
################################################################################
INCLUDES =
INCLUDES += include/effects
INCLUDES += include/graphics/
INCLUDES += include/json/
INCLUDES += include/raytracer/
INCLUDES += include/scene/
INCLUDES += include/shaders/
INCLUDES += include/shapes/
INCLUDES += lib/json/

################################################################################
######                               Flags                                ######
################################################################################
SOURCE :=

LIBDIRS              =
LDLIBS              := -lglut -lGLU -lGL -lXext -lX11 -lm

CFLAGS              := $(patsubst %,-I%,$(INCLUDES))

CXX_RELEASE_FLAGS   := $(CFLAGS) -std=c++0x
CXX_DEBUG_FLAGS     := $(CXX_RELEASE_FLAGS) -ggdb -Wall -pedantic -Wextra
CXXFLAGS             =

LIB_RELEASE_FLAGS   := $(LIBDIRS) $(LDLIBS)
LIB_DEBUG_FLAGS     := -ggdb $(LIB_RELEASE_FLAGS)
CCLIBFLAGS           =

################################################################################
######                            Directories                             ######
################################################################################
   ROOT := .
INCLUDE := $(ROOT)/include
    SRC := $(ROOT)/src
    LIB := $(ROOT)/lib
    OBJ := obj
    OBJDIR  = $(OBJ)/
    BIN := $(ROOT)/bin
    DEP := $(ROOT)/dep
  DEBUG := debug
RELEASE := release

DEPFILE = $(DEP)/$(*F)
OBJFILE = $(OBJDIR)/$(*F)

################################################################################
######                             Definitions                            ######
################################################################################

CXX := g++

CXXDEP := g++ -MM -MG $(CFLAGS)

empty :=
space := $(empty) $(empty)

RM      = rm -f
MKDIR   = mkdir -p
RMDIR   = $(MKDIR) $1; rmdir $1

################################################################################
######                              Magic                                 ######
################################################################################

# Include each module.mk file
include $(patsubst %,%module.mk,$(MODULES))

# Set the source file search path
vpath %.cpp $(MODULES)

# Determine the object file names, based on whether this a debug or a release
# build
ifeq ($(MAKECMDGOALS),)
OBJDIR := $(OBJ)/$(DEBUG)
OBJECT := $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o, $(notdir \
    $(filter %.cpp,$(SOURCE)))))
$(OBJECT): | build build_debug
CXXFLAGS += $(CXX_DEBUG_FLAGS)
CCLIBFLAGS += $(LIB_DEBUG_FLAGS)
else
OBJDIR := $(OBJ)/$(RELEASE)
OBJECT := $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o, $(notdir \
            $(filter %.cpp,$(SOURCE)))))
$(OBJECT): | build build_release
CXXFLAGS += $(CXX_RELEASE_FLAGS)
CCLIBFLAGS += $(LIB_RELEASE_FLAGS)
endif

DEPENDENCIES := $(addprefix $(DEP)/, \
                    $(patsubst %.cpp,%.d,$(notdir $(filter %.cpp,$(SOURCE)))))

################################################################################
######                          Pattern Rules                             ######
################################################################################

$(OBJDIR)/%.o: %.cpp
	printf "CPP $*.cpp\n"
	$(CXX) $(CXXFLAGS) -MMD -MT "$(DEPFILE).d $(OBJFILE).o" \
		-MF "$(DEPFILE).d" -o $(OBJFILE).o -c $<
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(DEPFILE).d >> $(DEPFILE).d

-include $(DEPENDENCIES)

################################################################################
######                              Targets                               ######
################################################################################

.PHONY: debug release build build_debug build_release clean realclean

TARGET = radraytracer

.DEFAULT_GOAL := debug

default: debug

debug:      $(OBJECT)
	printf "LINK $(BIN)/$(DEBUG)/$(TARGET)\n"
	$(CXX) -o $(BIN)/$(DEBUG)/$(TARGET) $(OBJECT) $(CCLIBFLAGS)

release: $(OBJECT)
	printf "LINK $(BIN)/$(RELEASE)/$(TARGET)\n"
	$(CXX) -o $(BIN)/$(RELEASE)/$(TARGET) $(OBJECT) $(CCLIBFLAGS)

build:
	$(MKDIR) $(OBJDIR)
	$(MKDIR) $(DEP)

build_debug:
	$(MKDIR) $(BIN)/$(DEBUG)
build_release:
	$(MKDIR) $(BIN)/$(RELEASE)

clean:
	printf "RM OBJECT FILES\n"
	$(RM) $(OBJ)/$(RELEASE)/*.o $(OBJ)/$(DEBUG)/*.o
	$(call RMDIR,$(OBJ)/$(DEBUG))
	$(call RMDIR,$(OBJ)/$(RELEASE))
	$(call RMDIR,$(OBJ))

realclean:        clean
	printf "RM DEPENDENCY FILES\n"
	printf "RM EXECUTABLE FILES\n"
	$(RM) $(DEPENDENCIES)
	$(RM) $(BIN)/$(DEBUG)/$(TARGET)
	$(RM) $(BIN)/$(RELEASE)/$(TARGET)
	$(call RMDIR,$(BIN)/$(DEBUG))
	$(call RMDIR,$(BIN)/$(RELEASE))
	$(call RMDIR,$(BIN))
	$(call RMDIR,$(DEP))

