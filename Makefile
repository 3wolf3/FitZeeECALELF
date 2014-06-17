
CC = g++

INCDIR = ./interface
EXEDIR = ./bin
SRCDIR = ./src
LIBDIR = ./lib

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
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(SRCDIR)/%.o,$(SRCS))

EXES1 = fitzeescale.exe fitzee.exe 

EXES2 = copyTree.exe \
        drawMee.exe \
        draw_calibTable.exe \
        calculateEtaScaleFromICs.exe \
        printic.exe \
        printetascale.exe 


all: $(EXES1) $(EXES2)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXES1): $(OBJDIR)/%.o $(OBJDIR)/config.o
	$(CC) -o $(EXEDIR)/$@ $^ $(CFLAGS) $(LIBS)

$(EXES2): $(OBJDIR)/%.o 
	$(CC) -o $(EXEDIR)/$@ $^ $(CFLAGS) $(LIBS)

clean: 
	\rm -f $(EXEDIR)/*.exe $(SRCDIR)/*.o

