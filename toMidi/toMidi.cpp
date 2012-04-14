#include "toMidi.hpp"
#include <smf.h>

namespace music{namespace toMidi{

    void toMidi::unfold_repetitions(){
      std::list<music::noteWithInfo *>::iterator it;
      /*loop 0 : song[0] and song[1] */
      for(int i = 1; i < 2 ; i++){
      
	/*loop 1 : reading the std::list with it (for iterator)*/
	for (it = song[i].begin() ; it!=song[i].end();  it++) { 
	  if((*it)->end_repeat){ //look for the beginnig of this repetition
	    music::noteWithInfo * tmp_end = (*it)++; //tmp_end musn't be inluded in the repetition
	  
	    /*loop 1.1 : get back to the beginning of the first repetition to deal*/ 
	    int beginning_corresponding = 0; // is >0 if another end_repeat is met in the reverse reading, so the begin_repeat won't be considered 
	    while(!(*it)->begin_repeat && !beginning_corresponding){
	      if((*it)->begin_repeat)
		beginning_corresponding--;
	      if((*it)->end_repeat)
		beginning_corresponding++;
	      (*it)--;
	    } //it now points to the beginning of the repetition
	    int nb_repetitions = (*it)->nb_repetitions;
	    std::list<music::noteWithInfo *> repetition; //copy of the repetition
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
	      std::list<music::noteWithInfo *>::iterator rit; //iterator within the repetition
	      rit = repetition.begin();
	      do{
		(*rit)->start_date += no_repetition*repetition_duration;
		(*rit)->end_date += no_repetition*repetition_duration;
	      } while(rit !=repetition.end());
	      //the 'no_repetition'th repetition has its start_date and end_date modified
	      std::list<music::noteWithInfo *>::iterator tmpit;
	      *tmpit = tmp_end;
	      song[i].splice(tmpit, repetition); //insert the repetition list before the pointer tmp_end
	    
	      no_repetition++;
	    }
	  
	    /*end of loop 1.3*/
	  
	  }
	}
	/*end of loop 1*/
      
      }
      /*end of loop 0 */ 
    }
  
    void toMidi::generate_midi_file(){
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
	  midiMessageON[1] = 12*(1+(song[i].front())->note.octave) + (song[i].front())->note.step;//il faut se servir du champs note de la cellule du type song[i]->note
	  midiMessageON[2] = 60;//a-t-on des informations quant a la velocite ?

	  char *midiMessageOFF = (char*)malloc(3*sizeof(char));
	  midiMessageOFF[0] = NOTE_OFF;
	  midiMessageOFF[1] = 12*(1+(song[i].front())->note.octave) + (song[i].front())->note.step;//il faut se servir du champs note de la cellule du type song[i]->note
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

	  free(midiMessageON);
	  free(midiMessageOFF);
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


    
    void toMidi::operator()(braille::ambiguous::score const& score) 
    { 
      /*Only one partition available, if more than one partition the behavior of the program is undeterminated

	Regarder structure score, time_sig pour time 3/4 4/4*/

      mi_begin_measure = 0;
      mi_current_note = 0;
      for (auto const& part: score.parts) {
	(*this)(part, score);
	mi_current_part++;
      }
    }
    
    void toMidi::operator()(braille::ambiguous::part const& part,
			    braille::ambiguous::score const& score
			    )
    {
      for(size_t staff_index = 0 ; staff_index < (int) part.size() ; ++staff_index){
	mi_current_staff = staff_index;
        for(size_t measure_index = 0 ; measure_index < part[staff_index].size() ; ++measure_index ){ 
	  boost::variant<braille::ambiguous::measure> const& this_measure = part[staff_index][measure_index];
	  //	  boost::apply_visitor(*this, this_measure);
      	}
      }

    }
    
    
    
    toMidi::result_type toMidi::operator() (braille::ambiguous::measure const& measure)
     {
      if (measure.voices.size() == 1) {
	 (*this)(measure.voices.front());
      } else {
         for (size_t voice_index = 0; voice_index < measure.voices.size();
	      ++voice_index)
      	{
       	  mi_begin_measure = mi_current_note;
       	  (*this)(measure.voices[voice_index]);
       	} 
       }
    }
  

    void toMidi::operator() (braille::ambiguous::voice const& voice)
    {
      mi_current_note = mi_begin_measure;
      for (size_t partial_measure_index = 0; partial_measure_index < voice.size();
	   ++partial_measure_index)
	{
	  mi_begin_partial_measure = mi_current_note;
	  (*this)(voice[partial_measure_index]);
	}
     }


    void toMidi::operator() (braille::ambiguous::partial_measure const& partial_measure) const
    {
    //   // mi_current_note = mi_begin_partial_measure;
    //   // if (partial_measure.size() == 1) {
    //   //   (*this)(partial_measure.front());
    //   // } else {
    //   //   for (size_t voice_index = 0; voice_index < partial_measure.size();
    //   // 	   ++voice_index)
    //   // 	{
    //   // 	  (*this)(partial_measure[voice_index]);
	  
    //   // 	}
    //   // }
      }
  

    // void toMidi::operator() (braille::ambiguous::partial_voice const& partial_voice) const
    // {
    //   // for (size_t element_index = 0; element_index < partial_voice.size();
    //   // 	 ++element_index)
    //   //   {
    //   // 	boost::apply_visitor(*this, partial_voice[element_index]);
    //   //   }
    // }
  
    // result_type toMidi::operator() (braille::ambiguous::barline const& barline) const{
    //   music::noteWithInfo new_noteWithInfo = new noteWithInfo;

    //   new_noteWithInfo->note = NULL;

    //   new_noteWithInfo->start_date = mi_current_note;
    //   new_noteWithInfo->end_date = mi_current_note;

    //   switch(barline){
    //   case begin_repeat:
    //     new_noteWithInfo->begin_repeat = true;
    //     new_noteWithInfo->end_repeat = false;
    //     break;
    //   case end_repeat:
    //     new_noteWithInfo->begin_repeat = false;
    //     new_noteWithInfo->end_repeat = true;
    //     break;
    //   case default:
    //     throw "error barline";
    //   }
    //   song[mi_current_staff].push_back(new_key);
    // }

    // result_type toMidi::operator() (braille::ambiguous::simile const& simile) const
    // {
    
    // }
  
    // result_type toMidi::operator() (braille::ambiguous::value_distinction const& value_distinction) const
    // {
    
    // }

    // /*  result_type toMidi::operator() (braille::ambiguous::hand_sign const& hand_sign) const
    // {

    // }*/
  
    // result_type toMidi::operator() (braille::ambiguous::rest const& rest) const
    // {
    //   mi_current_note += (rest.as_rational().numerator() / rest.as_rational().denominator() );

    // }
  
    // result_type toMidi::operator() (braille::ambiguous::note const& note) const
    // {
    //   music::noteWithInfo new_noteWithInfo = new noteWithInfo;
    
    //   double note_length = (note.as_rational().numerator() / note.as_rational().denominator() );
    //   // copy note call new, delete must be done later on
    //   new_noteWithInfo->key = copy_note(note);
    //   new_noteWithInfo->start_date = mi_current_note;
    //   new_noteWithInfo->end_date = mi_current_note + key_lenght;
    //   this->song[mi_current_staff].push_back(new_noteWithInfo);
    //   mi_current_note += note_length;

    // }

    // result_type toMidi::operator() (braille::ambiguous::chord const& chord) const 
    // {

    // }

  }
}
