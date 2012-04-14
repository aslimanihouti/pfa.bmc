#ifndef TO_MIDI_H
#define TO_MIDI_H

#include "ambiguous.hpp"
#include "music.hpp"
#include "noteWithInfo.hpp"

#define NOTE_ON 0x90
#define NOTE_OFF 0x80

namespace music{namespace toMidiPFA{

  
    class toMidi : public boost::static_visitor<void> {
    typedef bool result_type;

    public:
      std::list<music::noteWithInfo *>song[2];    
  
    public:
      void unfold_repetitions();
      void generate_midi_file();

    public:
      result_type operator() (braille::ambiguous::measure const&);
      result_type operator() (braille::ambiguous::barline const&) const;
      result_type operator() (braille::ambiguous::simile const&) const;
      result_type operator() (braille::ambiguous::value_distinction const&) const;
      result_type operator() (braille::hand_sign const&) const;
      result_type operator() (braille::ambiguous::rest const&);
      result_type operator() (braille::ambiguous::note const&);
      result_type operator() (braille::ambiguous::chord const&);

    private:
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
      double mi_current_staff;
      double mi_current_part;
    };
  }
}  
#endif
