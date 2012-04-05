
void add_score(struct score *s){

	s->g_clef_track = malloc(sizeof(struct track)); //portee clef de sol
	s->f_clef_track = malloc(sizeof(struct track)); //portee clef de fa

}

void add_track(struct track *t){

	t->first_note = malloc(sizeof(struct note));

}


void add_note(struct note * n, struct track * t){

		last_note(t)->next_note = n;
	
}

//void create_note(struct note * n, ){}
