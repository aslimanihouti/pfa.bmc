BOOST_DIRECTORY=.

CPPFLAGS=-DHAVE_CONFIG_H
CFLAGS=-g -O2 -Wextra -D_POSIX_C_SOURCE=2 -D_BSD_SOURCE -D_XOPEN_SOURCE=500 -D_XOPEN_SOURCE_EXTENDED -D_GNU_SOURCE
CXXFLAGS= -std=c++0x -I$(BOOST_DIRECTORY) -I.

TEST_OBJECTS=test.o compiler.o score.o measure.o \
	numbers.o brlsym.o music.o
prefix=/usr/local
exec_prefix=${prefix}
bindir=${exec_prefix}/bin

all: bmc

install: brltr
	/usr/bin/install -c -s brltr $(bindir)

bmc: main.o brlsym.o compiler.o score.o measure.o numbers.o music.o ttb/ttb.a fluidsynth.o toLily.o
	$(CXX) -o $@ main.o brlsym.o compiler.o score.o measure.o numbers.o music.o ttb/ttb.a fluidsynth.o toLily.o -lpthread -licuuc -lfluidsynth

test: $(TEST_OBJECTS) ttb/ttb.a
	$(CXX) -o $@ $(TEST_OBJECTS) ttb/ttb.a  -ldl -lm   -L/usr/lib -licui18n -licuuc -licudata  -ldl -lm   
	@./$@

brltr: brltr.o ttb/ttb.a
	g++ -o $@ brltr.o ttb/ttb.a   -ldl -lm   -L/usr/lib -licui18n -licuuc -licudata  -ldl -lm   

clean:
	$(MAKE) -C ttb clean
	rm -f *.o *.a text.auto.h brltr bmc tbl2hex test

full_clean: clean
	rm -rf autom4te.cache/ config.cache config.log config.status \
	configure Makefile ttb/Makefile ttb/config.h

ttb/%:
	$(MAKE) -C $(@D) $(@F)

measure.o: measure.hpp measure_def.hpp measure.cpp
score.o: score.hpp score_def.hpp
numbers.o: numbers.hpp numbers_def.hpp numbers.cpp
brlsym.o: brlsym.hpp brlsym.cpp
compiler.o: compiler.hpp disambiguate.hpp
test.o: spirit/qi/primitive/brl.hpp
toLily.o : toLily.hpp toLily.cpp