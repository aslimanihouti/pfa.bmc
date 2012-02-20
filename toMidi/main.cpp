#include "music.hpp"
#include "ambiguous.hpp"
#include "listMidi.hpp"


using namespace music;

int main(){
  listMidi *toto = new listMidi;
  struct keyWithInfo *test = new keyWithInfo;
  braille::ambiguous::note tata;
  toto->song.push_back(test);
  delete(toto);
  return 1;
}

