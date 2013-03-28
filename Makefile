################################################################################
######                         Acknowledgements                           ######
################################################################################
#                                                                              #
#   This makefile scheme is based off of the method developed by Tom Tromey.   #
#   For more information, visit: http://mad-scientist.net/make/autodep.html    #
#                                                                              #
################################################################################

################################################################################
######                          Source Folders                            ######
################################################################################
MODULES =
MODULES += lib/json/
MODULES += src/effects/
MODULES += src/graphics/
MODULES += src/gui/
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
INCLUDES += include/gui/
INCLUDES += include/json/
INCLUDES += include/raytracer/
INCLUDES += include/scene/
INCLUDES += include/shaders/
INCLUDES += include/shapes/
INCLUDES += lib/json/

GTK_INCLUDES =
GTK_INCLUDES += /usr/include/atkmm-1.6
GTK_INCLUDES += /usr/include/giomm-2.4
GTK_INCLUDES += /usr/lib/x86_64-linux-gnu/giomm-2.4/include
GTK_INCLUDES += /usr/include/pangomm-1.4
GTK_INCLUDES += /usr/lib/x86_64-linux-gnu/pangomm-1.4/include
GTK_INCLUDES += /usr/include/gtk-3.0
GTK_INCLUDES += /usr/include/cairomm-1.0
GTK_INCLUDES += /usr/lib/x86_64-linux-gnu/cairomm-1.0/include
GTK_INCLUDES += /usr/include/gdk-pixbuf-2.0
GTK_INCLUDES += /usr/include/gtk-3.0/unix-print
GTK_INCLUDES += /usr/include/atk-1.0
GTK_INCLUDES += /usr/include/glibmm-2.4
GTK_INCLUDES += /usr/lib/x86_64-linux-gnu/glibmm-2.4/include
GTK_INCLUDES += /usr/include/glib-2.0
GTK_INCLUDES += /usr/lib/x86_64-linux-gnu/glib-2.0/include
GTK_INCLUDES += /usr/include/sigc++-2.0
GTK_INCLUDES += /usr/lib/x86_64-linux-gnu/sigc++-2.0/include
GTK_INCLUDES += /usr/include/pango-1.0
GTK_INCLUDES += /usr/include/cairo
GTK_INCLUDES += /usr/include/pixman-1
GTK_INCLUDES += /usr/include/freetype2
GTK_INCLUDES += /usr/include/libpng12
GTK_INCLUDES += /usr/include/gio-unix-2.0/
GTK_INCLUDES += /usr/include/gtkmm-3.0
GTK_INCLUDES += /usr/lib/gtkmm-3.0/include
GTK_INCLUDES += /usr/include/gdkmm-3.0
GTK_INCLUDES += /usr/lib/gdkmm-3.0/include

INCLUDES += $(GTK_INCLUDES)

################################################################################
######                               Flags                                ######
################################################################################
SOURCE :=

GTK_LIBS            := -lgtkmm-3.0 -latkmm-1.6 -lgdkmm-3.0 -lgiomm-2.4 \
                       -lpangomm-1.4 -lgtk-3 -lglibmm-2.4 -lcairomm-1.0 \
                       -lgdk-3 -latk-1.0 -lgio-2.0 -lpangocairo-1.0 \
                       -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo \
                       -lsigc-2.0 -lgobject-2.0 -lglib-2.0
LIBDIRS              =
LDLIBS              := -lm $(GTK_LIBS)

CFLAGS              := $(patsubst %,-I%,$(INCLUDES)) -pthread

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
vpath $(DEP)/%.d $(DEP)

# Determine the object file names, based on whether this a debug or a release
# build
ifeq ($(MAKECMDGOALS),$(RELEASE))
OBJDIR := $(OBJ)/$(RELEASE)
OBJECT := $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o, $(notdir \
            $(filter %.cpp,$(SOURCE)))))
CXXFLAGS += $(CXX_RELEASE_FLAGS)
CCLIBFLAGS += $(LIB_RELEASE_FLAGS)
$(OBJECT): | $(BIN)/$(RELEASE)
else
OBJDIR := $(OBJ)/$(DEBUG)
OBJECT := $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o, $(notdir \
    $(filter %.cpp,$(SOURCE)))))
CXXFLAGS += $(CXX_DEBUG_FLAGS)
CCLIBFLAGS += $(LIB_DEBUG_FLAGS)
$(OBJECT): | $(BIN)/$(DEBUG)
endif

DEPENDENCIES := $(addprefix $(DEP)/, \
                    $(patsubst %.cpp,%.d,$(notdir $(filter %.cpp,$(SOURCE)))))

################################################################################
######                          Pattern Rules                             ######
################################################################################

$(OBJDIR)/%.o: %.cpp
	@printf "CPP $*.cpp\n"
	@$(CXX) $(CXXFLAGS) -MMD -MT "$(DEPFILE).d $(OBJFILE).o" \
		-MF "$(DEPFILE).d" -o $(OBJFILE).o -c $<
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(DEPFILE).d >> $(DEPFILE).d

-include $(DEPENDENCIES)

################################################################################
######                              Targets                               ######
################################################################################

.PHONY: debug release build build_debug build_release clean realclean

TARGET := radraytracer

.DEFAULT_GOAL := debug

all: debug

debug:	$(BIN)/$(DEBUG)/$(TARGET)
release: $(BIN)/$(RELEASE)/$(TARGET)

$(BIN)/$(RELEASE)/$(TARGET): $(OBJECT)
	@printf "LINK $(BIN)/$(RELEASE)/$(TARGET)\n"
	@$(CXX) -o $(BIN)/$(RELEASE)/$(TARGET) $(OBJECT) $(CCLIBFLAGS)

$(BIN)/$(DEBUG)/$(TARGET): $(OBJECT)
	@printf "LINK $(BIN)/$(DEBUG)/$(TARGET)\n"
	@$(CXX) -o $(BIN)/$(DEBUG)/$(TARGET) $(OBJECT) $(CCLIBFLAGS)

$(OBJECT): | $(OBJDIR)
$(OBJECT): | $(DEP)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(BIN)/$(RELEASE):
	$(MKDIR) $(BIN)/$(RELEASE)

$(BIN)/$(DEBUG):
	$(MKDIR) $(BIN)/$(DEBUG)

$(DEP):
	$(MKDIR) $(DEP)

clean:
	@printf "RM OBJECT FILES\n"
	@$(RM) $(OBJ)/$(RELEASE)/*.o $(OBJ)/$(DEBUG)/*.o
	@$(call RMDIR,$(OBJ)/$(DEBUG))
	@$(call RMDIR,$(OBJ)/$(RELEASE))
	@$(call RMDIR,$(OBJ))

realclean:        clean
	@printf "RM DEPENDENCY FILES\n"
	@printf "RM EXECUTABLE FILES\n"
	@$(RM) $(DEPENDENCIES)
	@$(RM) $(BIN)/$(DEBUG)/$(TARGET)
	@$(RM) $(BIN)/$(RELEASE)/$(TARGET)
	@$(call RMDIR,$(BIN)/$(DEBUG))
	@$(call RMDIR,$(BIN)/$(RELEASE))
	@$(call RMDIR,$(BIN))
	@$(call RMDIR,$(DEP))

