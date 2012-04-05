#ifndef TOMIDI_H
#define TOMIDI_H
#include "ambiguous.hpp"
//#include "music.hpp"


//score

struct score {
  struct track *g_clef_track;
  struct track *f_clef_track;
};

void add_score(struct score *);

//track

struct track {
  struct note *first_note;
  struct track *other_track; //maybe useful for simultaneous notes
};

//add a track to the score s
//track to add, 
//clef : "g" or "f",
//score containing the track
void add_track(struct track *, char *, struct score *);

//note

void add_note(struct note *, struct track*);
//void create_note(struct note *);

	
struct note {
  float begin;
  float end;
  braille::ambiguous::note note;
  int begin_repetition;
  int end_repetition;
  int nb_repetitions;
  struct note * next_note;
};

#endif /* TOMIDI_H*/
