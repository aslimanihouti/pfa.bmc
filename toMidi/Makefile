BOOST_DIRECTORY=.

CPPFLAGS=-DHAVE_CONFIG_H
CFLAGS=-g -O2 -Wextra -D_POSIX_C_SOURCE=2 -D_BSD_SOURCE -D_XOPEN_SOURCE=500 -D_XOPEN_SOURCE_EXTENDED -D_GNU_SOURCE
CXXFLAGS= -std=c++0x -I$(BOOST_DIRECTORY) -I.

all: bmc

bmc: main.o music.o listMidi.o
	$(CXX) -o $@ main.o music.o listMidi.o -lpthread -licuuc

clean:
	rm bmc
	rm *.o
	rm *~
