
CC = g++

INCDIR = ./interface
EXEDIR = ./bin
OBJDIR = ./src
SRCDIR = ./src

ROOTLIBS = -L$(ROOTSYS)/lib \
           -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d \
           -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics \
           -lMathCore -lThread -lMinuit -lMinuit2 -lpthread -lTreePlayer \
           -Wl,-rpath,$(ROOTSYS)/lib -stdlib=libc++ -lm -ldl 

ROOTCFLAGS = -m64 -I$(ROOTSYS)/include

CFLAGS = $(ROOTCFLAGS) -I$(INCDIR)
LIBS = $(ROOTLIBS) -L$(LIBDIR)

DEPS = $(wildcard $(INCDIR)/*.hpp)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


all: fitzeescale.exe \
        fitzee.exe \
        copyTree.exe \
        drawMee.exe \
        draw_calibTable.exe \
        calculateEtaScaleFromICs.exe \
        printic.exe \
        printetascale.exe 

printetascale.exe: $(OBJDIR)/printetascale.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

printic.exe: printic.o
	$(CC) printic.o -o printic.exe $(CFLAGS) $(LIBS)

calculateEtaScaleFromICs.exe: calculateEtaScaleFromICs.o
	$(CC) calculateEtaScaleFromICs.o -o calculateEtaScaleFromICs.exe $(CFLAGS) $(LIBS)

draw_calibTable.exe: draw_calibTable.o 
	$(CC) draw_calibTable.o -o draw_calibTable.exe $(CFLAGS) $(LIBS)

fitzeescale.exe: fitzeescale.o config.o
	$(CC) fitzeescale.o config.o -o fitzeescale.exe $(CFLAGS) $(LIBS)

fitzee.exe: fitzee.o config.o
	$(CC) fitzee.o config.o -o fitzee.exe $(CFLAGS) $(LIBS)

copyTree.exe: copyTree.o
	$(CC) copyTree.o -o copyTree.exe $(CFLAGS) $(LIBS)

drawMee.exe: drawMee.o
	$(CC) drawMee.o -o drawMee.exe $(CFLAGS) $(LIBS)

.PHONY: clean

clean: 
	\rm -f $(EXEDIR)/*.exe *~ core $(INCDIR)/*~ $(LIBDIR)/*.o

