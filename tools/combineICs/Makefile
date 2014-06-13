


ROOTLIBS = -L$(ROOTSYS)/lib \
           -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d \
           -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics \
           -lMathCore -lThread -lMinuit -lMinuit2 -lpthread -lTreePlayer \
           -Wl,-rpath,$(ROOTSYS)/lib -stdlib=libc++ -lm -ldl 

ROOTCFLAGS = -m64 -I$(ROOTSYS)/include

CFLAGS = $(ROOTCFLAGS) -I.
LIBS = $(ROOTLIBS) -L. 

CC = g++ 

all: printxmltotext.exe multiplyICfiles.exe calEtaScaleFromICfile.exe

calEtaScaleFromICfile.exe: calEtaScaleFromICfile.o
	$(CC) calEtaScaleFromICfile.o -o calEtaScaleFromICfile.exe $(CFLAGS) $(LIBS)

calEtaScaleFromICfile.o: calEtaScaleFromICfile.cpp
	$(CC) -c calEtaScaleFromICfile.cpp -o calEtaScaleFromICfile.o $(CFLAGS) 

multiplyICfiles.exe: multiplyICfiles.o
	$(CC) multiplyICfiles.o -o multiplyICfiles.exe $(CFLAGS) $(LIBS)

multiplyICfiles.o: multiplyICfiles.cpp
	$(CC) -c multiplyICfiles.cpp -o multiplyICfiles.o $(CFLAGS)

printxmltotext.exe: printxmltotext.o
	$(CC) printxmltotext.o -o printxmltotext.exe $(CFLAGS) $(LIBS)

printxmltotext.o: printxmltotext.cpp 
	$(CC) -c printxmltotext.cpp -o printxmltotext.o $(CFLAGS)

clean: 
	\rm -f *.o
	\rm -f *.exe 
