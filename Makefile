# Author Hengne Li @ UVa CERN 2014

CC = g++
INCDIR = ./interface
EXEDIR = ./bin
SRCDIR = ./src

	ROOTLIBS = -L$(ROOTSYS)/lib -lMinuit2\
           -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad \
           -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore \
           -lThread -pthread -lm -ldl -rdynamic


ROOTCFLAGS = -pthread -std=c++11 -Wno-deprecated-declarations -m64 -I$(ROOTSYS)/include

CFLAGS = $(ROOTCFLAGS) -I$(INCDIR)
LIBS = $(ROOTLIBS)

DEPS = $(wildcard $(INCDIR)/*.hpp)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(SRCDIR)/%.o,$(SRCS))

vpath %.hpp $(INCDIR)
vpath %.cpp $(SRCDIR)
vpath %.o   $(SRCDIR)
vpath %.exe $(EXEDIR)

# this group of exes use config.o
_EXES1 = fitzeescale.exe fitzee.exe \
        drawMee.exe

# this group of exes do not use config.o
_EXES2 = copyTree.exe \
        draw_calibTable.exe \
        calculateEtaScaleFromICs.exe \
        printic.exe \
        printetascale.exe

EXES1 = $(patsubst %.exe,$(EXEDIR)/%.exe,$(_EXES1))
EXES2 = $(patsubst %.exe,$(EXEDIR)/%.exe,$(_EXES2))

all: $(EXES1) $(EXES2)


# dep: nothing
_OBJS3 = calculateEtaScaleFromICs.o \
         printetascale.o \
         draw_calibTable.o \
         printic.o

OBJS3 = $(patsubst %,$(SRCDIR)/%,$(_OBJS3))

$(SRCDIR)/fitzee.o $(SRCDIR)/fitzeescale.o: $(SRCDIR)/%.o: $(SRCDIR)/%.cpp \
          functions.hpp variables.hpp config.hpp calibRecord.hpp voigt.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(SRCDIR)/config.o: $(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(SRCDIR)/copyTree.o: $(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.hpp calibTreeDef.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJS3):  $(SRCDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CC) -o $@ -c $< $(CFLAGS)

$(SRCDIR)/drawMee.o: $(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.hpp config.hpp calibRecord.hpp etaring.hpp calibTreeDef.hpp
	$(CC) -o $@ -c $< $(CFLAGS)


$(EXES1): $(EXEDIR)/%.exe: $(SRCDIR)/%.o $(SRCDIR)/config.o | $(EXEDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(EXES2): $(EXEDIR)/%.exe: $(SRCDIR)/%.o | $(EXEDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(EXEDIR):
	mkdir $(EXEDIR)

clean: 
	\rm -f $(EXEDIR)/*.exe $(SRCDIR)/*.o



