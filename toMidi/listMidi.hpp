#ifndef LIST_MIDI_H
#define LIST_MIDI_H

#include "ambiguous.hpp"
#include "music.hpp"

namespace music{
  struct keyWithInfo{
    int start;
    braille::ambiguous::note toto;
    struct keyWithInfo *previous;
    struct keyWithInfo *next;
    bool startRepeat;
    bool endRepeat;
  };

class listMidi{
private:
  struct keyWithInfo *score;
  
public:
  listMidi();
  ~listMidi();
  void addKey(struct keyWithInfo *);
  void removeKey();
  void addListOfKeys(struct keyWithInfo *);
  void debug();
};
}  
#endif
