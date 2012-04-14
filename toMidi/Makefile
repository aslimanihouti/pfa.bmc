LIBRARIES=/usr/lib/
BOOSTDIR=../../bmc/
INCLUDE1=/usr/lib/i386-linux-gnu/glib-2.0/include/
INCLUDE2=/usr/include/glib-2.0/
INCLUDE3=/usr/include/
GCCVERSION=-std=c++0x
all:toMidi

toMidi:main.o toMidi.o noteWithInfo.o
	g++ $(GCCVERSION) -I $(BOOSTDIR) -I $(INCLUDE3) -I $(INCLUDE1) -I $(INCLUDE2) -o $@ $^ -lsmf

%.o: %.cpp
	g++ -c $(GCCVERSION) -I $(BOOSTDIR) -I $(INCLUDE3) -I $(INCLUDE1) -I $(INCLUDE2) -o $@ $< -lsmf

clean:
	rm *.o && rm toMidi