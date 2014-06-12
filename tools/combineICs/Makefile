


ROOTLIBS = -L$(ROOTSYS)/lib \
           -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d \
           -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics \
           -lMathCore -lThread -lMinuit -lMinuit2 -lpthread -lTreePlayer \
           -Wl,-rpath,$(ROOTSYS)/lib -stdlib=libc++ -lm -ldl 

ROOTCFLAGS = -m64 -I$(ROOTSYS)/include

CFLAGS = $(ROOTCFLAGS) -I.
LIBS = $(ROOTLIBS) -L. 

CC = g++ 

all: printxmltotext.exe 


printxmltotext.exe: printxmltotext.o
	$(CC) printxmltotext.o -o printxmltotext.exe $(CFLAGS) $(LIBS)

printxmltotext.o: printxmltotext.cpp 
	$(CC) -c printxmltotext.cpp -o printxmltotext.o $(CFLAGS)

clean: 
	\rm -f *.o
	\rm -f *.exe 
