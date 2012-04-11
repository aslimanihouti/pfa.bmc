#ifndef NOTE_WITH_INFO_H
#define NOTE_WITH_INFO_H

#include "ambiguous.hpp"
#include "music.hpp"

namespace music{
  class noteWithInfo{
  public:
    braille::ambiguous::note note;
    double start_date;
    double end_date;
    bool begin_repeat;
    bool end_repeat;
    int nb_repetitions;
  };
}

#endif
