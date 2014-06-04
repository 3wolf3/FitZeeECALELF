


ROOTLIBS = -L$(ROOTSYS)/lib \
           -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d \
           -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics \
           -lMathCore -lThread -lMinuit -lMinuit2 -lpthread -lTreePlayer \
           -Wl,-rpath,$(ROOTSYS)/lib -stdlib=libc++ -lm -ldl 

ROOTCFLAGS = -m64 -I$(ROOTSYS)/include
#ROOTCFLAGS = -pthread -m64 -I$(ROOTSYS)/include

CFLAGS = $(ROOTCFLAGS) -I.
LIBS = $(ROOTLIBS) -L. 

CC = g++ 

all: fitzeescale.exe fitzee.exe copyTree.exe drawMee.exe draw_calibTable.exe calculateEtaScaleFromICs.exe printic.exe printetascale.exe 


printetascale.exe: printetascale.o
	$(CC) printetascale.o -o printetascale.exe $(CFLAGS) $(LIBS)

pprintetascale.o: printetascale.cpp
	$(CC) -c printetascale.cpp -o printetascale.o $(CFLAGS)

printic.exe: printic.o
	$(CC) printic.o -o printic.exe $(CFLAGS) $(LIBS)

printic.o: printic.cpp
	$(CC) -c printic.cpp -o printic.o $(CFLAGS)

calculateEtaScaleFromICs.exe: calculateEtaScaleFromICs.o
	$(CC) calculateEtaScaleFromICs.o -o calculateEtaScaleFromICs.exe $(CFLAGS) $(LIBS)

calculateEtaScaleFromICs.o: calculateEtaScaleFromICs.cpp
	$(CC) -c calculateEtaScaleFromICs.cpp -o calculateEtaScaleFromICs.o $(CFLAGS)

draw_calibTable.exe: draw_calibTable.o 
	$(CC) draw_calibTable.o -o draw_calibTable.exe $(CFLAGS) $(LIBS)

draw_calibTable.o: draw_calibTable.cpp
	$(CC) -c draw_calibTable.cpp -o draw_calibTable.o $(CFLAGS)

fitzeescale.exe: fitzeescale.o config.o
	$(CC) fitzeescale.o config.o -o fitzeescale.exe $(CFLAGS) $(LIBS)

fitzee.exe: fitzee.o config.o
	$(CC) fitzee.o config.o -o fitzee.exe $(CFLAGS) $(LIBS)

copyTree.exe: copyTree.o
	$(CC) copyTree.o -o copyTree.exe $(CFLAGS) $(LIBS)

drawMee.exe: drawMee.o
	$(CC) drawMee.o -o drawMee.exe $(CFLAGS) $(LIBS)

fitzeescale.o: fitzeescale.cpp
	$(CC) -c fitzeescale.cpp -o fitzeescale.o  $(CFLAGS)

fitzee.o: fitzee.cpp
	$(CC) -c fitzee.cpp -o fitzee.o  $(CFLAGS)

copyTree.o: copyTree.cpp
	$(CC) -c copyTree.cpp -o copyTree.o  $(CFLAGS)

drawMee.o: drawMee.cpp
	$(CC) -c drawMee.cpp -o drawMee.o  $(CFLAGS)

config.o: config.cpp
	$(CC) -c config.cpp -o config.o 



clean: 
	\rm -f *.o
	\rm -f *.exe 
