
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

EXES1 = fitzeescale.exe fitzee.exe \
        drawMee.exe 

EXES2 = copyTree.exe \
        draw_calibTable.exe \
        calculateEtaScaleFromICs.exe \
        printic.exe \
        printetascale.exe 


all: $(EXES1) $(EXES2)

$(OBJS): %.o: %.cpp $(DEPS) 
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXES1): %.exe: $(SRCDIR)/%.o $(SRCDIR)/config.o | $(EXEDIR)
	$(CC) -o $(EXEDIR)/$@ $^ $(CFLAGS) $(LIBS)

$(EXES2): %.exe: $(SRCDIR)/%.o | $(EXEDIR)
	$(CC) -o $(EXEDIR)/$@ $^ $(CFLAGS) $(LIBS)

$(EXEDIR):
	mkdir $(EXEDIR)

clean: 
	\rm -f $(EXEDIR)/*.exe $(SRCDIR)/*.o



