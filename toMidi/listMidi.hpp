#ifndef LIST_MIDI_H
#define LIST_MIDI_H

#include "ambiguous.hpp"
#include "music.hpp"
#include <smf.h>

#define NOTE_ON 0x90
#define NOTE_OFF 0x80

namespace music{
  struct keyWithInfo{
    float start_date;
    float end_date;
    braille::ambiguous::note toto;
    bool startRepeat;
    bool endRepeat;
  };

class listMidi{
public:
  std::list <struct keyWithInfo *> song[2];
  //  std::list <struct keyWithInfo *> song_up;
  //  std::list <struct keywithInfo *> song_down;
  
public:
  void unfold_repetitions();
  void create_midi_file();
};
}  
#endif
