# Author Hengne Li @ UVa CERN 2014

CC = g++
INCDIR = ./interface
EXEDIR = ./bin
SRCDIR = ./src

ROOTLIBS = -L$(ROOTSYS)/lib \
           -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d \
           -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics \
           -lMathCore -lThread -lMinuit -lMinuit2 -lpthread -lTreePlayer \
           -Wl,-rpath,$(ROOTSYS)/lib -stdlib=libc++ -lm -ldl 

ROOTCFLAGS = -m64 -I$(ROOTSYS)/include

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

# dep: functions.hpp variables.hpp config.hpp calibRecord.hpp voigt.hpp
_OBJS1 = fitzee.o \
         fitzeescale.o 

# dep: %.hpp
_OBJS2 = config.o \
         copyTree.o 

# dep: nothing
_OBJS3 = calculateEtaScaleFromICs.o \
         printetascale.o \
         draw_calibTable.o \
         printic.o

# dep: drawMee.hpp config.hpp calibRecord.hpp etaring.hpp
_OBJS4 = drawMee.o

OBJS1 = $(patsubst %,$(SRCDIR)/%,$(_OBJS1))
OBJS2 = $(patsubst %,$(SRCDIR)/%,$(_OBJS2))
OBJS3 = $(patsubst %,$(SRCDIR)/%,$(_OBJS3))
OBJS4 = $(patsubst %,$(SRCDIR)/%,$(_OBJS4))

$(OBJS1): $(SRCDIR)/%.o: $(SRCDIR)/%.cpp \
          functions.hpp variables.hpp config.hpp calibRecord.hpp voigt.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJS2):  $(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJS3):  $(SRCDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CC) -o $@ -c $< $(CFLAGS)

$(OBJS4):  $(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.hpp config.hpp calibRecord.hpp etaring.hpp
	$(CC) -o $@ -c $< $(CFLAGS)


$(EXES1): $(EXEDIR)/%.exe: $(SRCDIR)/%.o $(SRCDIR)/config.o | $(EXEDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(EXES2): $(EXEDIR)/%.exe: $(SRCDIR)/%.o | $(EXEDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(EXEDIR):
	mkdir $(EXEDIR)

clean: 
	\rm -f $(EXEDIR)/*.exe $(SRCDIR)/*.o



