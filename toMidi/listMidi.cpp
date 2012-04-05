#include "listMidi.hpp"
#include <smf.h>

namespace music{
  void listMidi::unfold_repetitions(){
  }

  void listMidi::create_midi_file(){
    //on deroule les repetitions
    this->unfold_repetitions();

    //on peut commencer le travail
    smf_t *smf;
    smf_track_t *track;
    smf_event_t *eventON;
    smf_event_t *eventOFF;

    smf = smf_new();
    if (smf == NULL) {
      printf("Error creating the smf\n");
      return;
    }
  
    for (int i = 1; i <= 2; i++) {
      track = smf_track_new();
      if (track == NULL) {
	printf("Error creating the tracks\n");
	return;
      }
      
      smf_add_track(smf, track);
    
    
      int number_of_events = std::max(song[0].size(), song[1].size());

      //boucle sur les midi message d'une track
      for (int j = 1; j <= number_of_events; j++) {
	char *midiMessageON = (char*)malloc(3*sizeof(char));
	midiMessageON[0] = NOTE_ON;
	midiMessageON[1] = 0;//il faut se servir du champs note de la cellule du type song[i]->note
	midiMessageON[2] = 60;//a-t-on des informations quant a la velocite ?

	char *midiMessageOFF = (char*)malloc(3*sizeof(char));
	midiMessageOFF[0] = NOTE_OFF;
	midiMessageOFF[1] = 0;//il faut se servir du champs note de la cellule du type song[i]->note
	midiMessageOFF[2] = 60;//a-t-on des informations quant a la velocite ?
	
	//on cree les message
	eventON = smf_event_new_from_pointer(midiMessageON, 3);
	eventOFF = smf_event_new_from_pointer(midiMessageOFF,3);
	
	//on consomme la liste
	song[i].pop_front();
	
	if (eventON == NULL || eventOFF == NULL) {
	  printf("Error creating the event");
	  return;
	}
	
	//on rajoute les message a la track
	smf_track_add_event_seconds(track, eventON, (song[i].front())->start_date);
	smf_track_add_event_seconds(track, eventOFF,(song[i].front())->end_date);
      }
    }
    
    //on sauve le fichier midi
    int ret = smf_save(smf, "test.mid");
    if (ret) {
      printf("Saving failed\n");
      return;
    }

  smf_delete(smf);
  }
}
