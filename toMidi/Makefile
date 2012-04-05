LIBRARIES=/usr/lib/
BOOSTDIR=../bmc/
INCLUDE1=/usr/lib/i386-linux-gnu/glib-2.0/include/
INCLUDE2=/usr/include/glib-2.0/
INCLUDE3=/usr/include/

all:bmc

bmc:main.o listMidi.o
	g++ -L $(LIBRARIES) -lsmf -I $(BOOSTDIR) -I $(INCLUDE3) -I $(INCLUDE1) -I $(INCLUDE2) -o $@ $^

%.o: %.cpp
	g++ -c -L $(LIBRARIES) -lsmf -I $(BOOSTDIR) -I $(INCLUDE3) -I $(INCLUDE1) -I $(INCLUDE2) -o $@ $<

clean:
	rm *.o && rm bmc