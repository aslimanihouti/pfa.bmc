#include "music.hpp"
#include "ambiguous.hpp"
#include "listMidi.hpp"


using namespace music;

int main(){
  listMidi *toto = new listMidi;
  struct keyWithInfo *test = new keyWithInfo;
  braille::ambiguous::note tata;
  test->start = 32;
  tata.octave = 23;
  test->toto = tata;
  toto->addKey(test);
  toto->debug();

  delete(toto);
  return 1;
}

