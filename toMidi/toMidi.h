#ifndef TOMIDI_H
#define TOMIDI_H

//score

struct score {

	struct track *first_track;
};

void add_score(struct score *);

//track

struct track {

	struct note *first_note;
	struct track *next_track;
};

void add_track(struct track *);
void add_note(struct note *, struct track*);
//void create_note(struct note *);

struct sound {
      int is_a_note; //if is_a_note == 0, then struct sound is a rest
	  enum pitch {c, d, e, f, g, a, b};
      int last_note_step;// octave ;
	  enum articulation accent;
    };
	
struct note {
	float begin;
	float end;
	struct sound * s;
	struct note * next_repetition;
	struct note * next_note;
	
    };

	



#endif /* TOMIDI_H*/