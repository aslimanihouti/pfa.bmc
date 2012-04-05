#include "listMidi.hpp"
#include <smf.h>

namespace music{

  void listMidi::unfold_repetitions(){
    std::list<struct keyWithInfo *>::iterator it;
    /*loop 0 : song[0] and song[1] */
    for(int i = 1; i < 2 ; i++){
      
      /*loop 1 : reading the std::list with it (for iterator) */
      for (it = song[i].begin() ; it!=song[i].end();  it++) { 
	if((*it)->endRepeat){ //look for the beginnig of this repetition
	  struct keyWithInfo * tmp_end = (*it)++; //tmp_end musn't be inluded in the repetition
	  
	  /*loop 1.1 : get back to the beginning of the first repetition to deal*/ 
	  int beginning_corresponding = 0; // is >0 if another endRepeat is met in the reverse reading, so the startRepeat won't be considered 
	  while(!(*it)->startRepeat && !beginning_corresponding){
	    if((*it)->startRepeat)
	      beginning_corresponding--;
	    if((*it)->endRepeat)
	      beginning_corresponding++;
	    (*it)--;
	  } //it now points to the beginning of the repetition
	  int nb_repetitions = (*it)->nb_repetitions;
	  std::list<struct keyWithInfo *> repetition; //copy of the repetition
	  /*end of loop 1.1*/
	  
	  /*loop 1.2 : get the repetition duration*/
	  float repetition_duration = 0;
	  while((*it)!=tmp_end){
	    repetition_duration+=((*it)->end_date - (*it)->start_date);
	    repetition.push_back((*it));
	    (*it)++;
	  }
	  /*end of loop 1.2*/
	  
	  /* loop 1.3 : insert one or more repetition(s) after tmp_end */
	  
	  int no_repetition = 1; 
	  //useful to redefine the dates of the keyWithInfo elements. starts at 1 and will ++ until nb_repetitions
	  
	  while(no_repetition <= nb_repetitions){	   
	    std::list<struct keyWithInfo *>::iterator rit; //iterator within the repetition
	    rit = repetition.begin();
	    do{
	      (*rit)->start_date += no_repetition*repetition_duration;
	      (*rit)->end_date += no_repetition*repetition_duration;
	    } while(rit !=repetition.end());
	    //the 'no_repetition'th repetition has its start_date and end_date modified
	    
	    song[i].splice(tmp_end, repetition); //insert the repetition list before the pointer tmp_end
	    
	    no_repetition++;
	  }
	  
	  /*end of loop 1.3*/
	  
	}
      }
      /*end of loop 1*/
      
    }
    /*end of loop 0 */ 
  }
  
  void listMidi::generate_midi_file(){
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
