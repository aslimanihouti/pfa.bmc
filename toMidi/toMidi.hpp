#ifndef TO_MIDI_H
#define TO_MIDI_H

#include "ambiguous.hpp"
#include "music.hpp"

#include <list>
#include <vector>

#define NOTE_ON 0x90
#define NOTE_OFF 0x80

namespace music{namespace toMidiPFA{


    class noteWithInfo{
    public:
      braille::ambiguous::note *note;
      double start_date;
      double end_date;
      bool begin_repeat;
      bool end_repeat;
      int nb_repetitions;

    };

    
    class toMidi : public boost::static_visitor<void> {
      // typedef bool result_type;

    private:
      std::list<noteWithInfo *> song[2];
    public:
      void generate_midi_file();

    private:
      void unfold_repetitions();
      void debugSongList();

      struct braille::ambiguous::note* copyNote(braille::ambiguous::note const&);

    public:
      result_type operator() (braille::ambiguous::measure const&);
      result_type operator() (braille::ambiguous::barline const&);
      result_type operator() (braille::ambiguous::simile const&) const;
      result_type operator() (braille::ambiguous::value_distinction const&) const;
      result_type operator() (braille::ambiguous::hand_sign const&) const;
      result_type operator() (braille::ambiguous::rest const&);
      result_type operator() (braille::ambiguous::note const&);
      result_type operator() (braille::ambiguous::chord const&);

    public:
      void operator() (braille::ambiguous::score const& score);     
      void operator() (braille::ambiguous::part const& part,
		       braille::ambiguous::score const& score
		       );
      void operator() (braille::ambiguous::voice const&);
      void operator() (braille::ambiguous::partial_measure const&);
      void operator() (braille::ambiguous::partial_voice const&);

    private:
      double mi_begin_partial_measure;
      double mi_begin_measure;
      double mi_current_note;
      int mi_current_staff;
      double mi_current_part;
    };
  }
}  
#endif
