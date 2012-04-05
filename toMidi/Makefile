LIBRARIES=/usr/lib/
BOOSTDIR=../bmc/
INCLUDE1=/usr/lib/i386-linux-gnu/glib-2.0/include/
INCLUDE2=/usr/include/glib-2.0/
INCLUDE3=/usr/include/

all:bmc

bmc:main.o listMidi.o
	g++ -I $(BOOSTDIR) -I $(INCLUDE3) -I $(INCLUDE1) -I $(INCLUDE2) -o $@ $^ -lsmf

%.o: %.cpp
	g++ -c -I $(BOOSTDIR) -I $(INCLUDE3) -I $(INCLUDE1) -I $(INCLUDE2) -o $@ $< -lsmf

clean:
	rm *.o && rm bmc