#include "toMidi.hpp"
#include <smf.h>

namespace music{namespace toMidiPFA{
    void toMidi::debugSongList(){
      std::list<noteWithInfo *>::iterator it;
      for(int i=0;i<2;i++){
	  std::wcout<<"list"<<i<<std::endl;
	  for(it=song[i].begin(); it!=song[i].end(); it++){
	    if((*it)->begin_repeat != true && (*it)->end_repeat != true)
	      std::wcout<<((*it)->note->step)<<std::endl;
	    //song[i].pop_front();
	  }
      }
      std::wcout<<"debug exit"<<std::endl;
    }

    struct braille::ambiguous::note* toMidi::copyNote(braille::ambiguous::note const& note){
      struct braille::ambiguous::note *newNote = new struct braille::ambiguous::note;
      newNote->acc = note.acc;
      newNote->step = note.step;
      newNote->octave = note.octave;
      return newNote;
    }

    void toMidi::unfold_repetitions(){
      std::wcout<<"Entering unfold_repetitions"<<std::endl;
      std::list<noteWithInfo *>::iterator it;
      /*loop 0 : song[0] and song[1] */
      for(int i = 1; i < 2 ; i++){
      
	/*loop 1 : reading the std::list with it (for iterator)*/
	for (it = song[i].begin() ; it!=song[i].end();  it++) { 
	  if((*it)->end_repeat){ //look for the beginnig of this repetition
	    noteWithInfo * tmp_end = (*it)++; //tmp_end musn't be inluded in the repetition
	  
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
	    std::list<noteWithInfo *> repetition; //copy of the repetition
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
	      std::list<noteWithInfo *>::iterator rit; //iterator within the repetition
	      rit = repetition.begin();
	      do{
		(*rit)->start_date += no_repetition*repetition_duration;
		(*rit)->end_date += no_repetition*repetition_duration;
	      } while(rit !=repetition.end());
	      //the 'no_repetition'th repetition has its start_date and end_date modified
	      std::list<noteWithInfo *>::iterator tmpit;
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
      std::wcout<<"Entering generate_midi_file"<< std::endl;
      debugSongList();
      //on deroule les repetitions
      //this->unfold_repetitions();
  
      //on peut commencer le travail
      smf_t *smf;
      smf_tempo_t *theTempo = smf_get_tempo_by_pulses(smf, 80);
      smf_track_t *track;
      smf_event_t *eventON;
      smf_event_t *eventOFF;

      smf = smf_new();
      if (smf == NULL) {
	printf("Error creating the smf\n");
	return;
      }
  
      for (int i = 0; i < 2; i++) {
	track = smf_track_new();
	if (track == NULL) {
	  printf("Error creating the tracks\n");
	  return;
	}
      
	smf_add_track(smf, track);
    
    
	int number_of_events = std::max(song[0].size(), song[1].size());
	std::list<noteWithInfo *>::iterator it;
	//boucle sur les midi message d'une track
	for (it=song[i].begin(); it!=song[i].end(); it++){
	  if((*it)->begin_repeat!=true && (*it)->end_repeat!=true){
	    int midiMessageON[3];
	    midiMessageON[0] = NOTE_ON;
	    midiMessageON[1] = 12*(1+(*it)->note->octave) + (*it)->note->step;//il faut se servir du champs note de la cellule du type song[i]->note
	    midiMessageON[2] = 60;//a-t-on des informations quant a la velocite ?
	    
	    int midiMessageOFF[3];
	    midiMessageOFF[0] = NOTE_OFF;
	    midiMessageOFF[1] = 12*(1+(*it)->note->octave) + (*it)->note->step;//il faut se servir du champs note de la cellule du type song[i]->note
	    midiMessageOFF[2] = 60;//a-t-on des informations quant a la velocite ?
	    
	    //on cree les message
	    //eventON = smf_event_new_from_pointer(midiMessageON, 3);
	    //eventOFF = smf_event_new_from_pointer(midiMessageOFF,3);

	    eventON = smf_event_new_from_bytes(midiMessageON[0],
					       midiMessageON[1],
					       midiMessageON[2]);
	    std::wcout<<"note: "<<midiMessageON[1]<<"start date "<<(*it)->start_date<<" end date"<<(*it)->end_date<<std::endl;

	    eventOFF = smf_event_new_from_bytes(midiMessageOFF[0],
					       midiMessageOFF[1],
					       midiMessageOFF[2]);

	    //on consomme la liste
	    //song[i].pop_front();
	    
	    if (eventON == NULL || eventOFF == NULL) {
	      printf("Error creating the event");
	      return;
	    }
	    
	    //on rajoute les message a la track
	    
	    smf_track_add_event_seconds(track, eventON, (*it)->start_date);
	    smf_track_add_event_seconds(track, eventOFF,(*it)->end_date);
	    
	    //free(midiMessageON);
	    //free(midiMessageOFF);
	  }
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
      std::wcout<<"Entering operator()(braille::ambiguous::score const& score)"<<std::endl; 
      mi_begin_measure = 0;
      mi_current_note = 0;
      for (auto const& part: score.parts) {
	(*this)(part, score);
	mi_current_part++;
      }
      this->generate_midi_file();
    }
    
    void toMidi::operator()(braille::ambiguous::part const& part,
			    braille::ambiguous::score const& score
			    )
    {
      for(size_t staff_index = 0 ; staff_index < (int) part.size() ; ++staff_index){
	mi_current_staff = (int) staff_index;
        for(size_t measure_index = 0 ; measure_index < part[staff_index].size() ; ++measure_index ){ 
	  boost::variant<braille::ambiguous::measure> const& this_measure = part[staff_index][measure_index];
	  boost::apply_visitor(*this, this_measure);
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


    void toMidi::operator() (braille::ambiguous::partial_measure const& partial_measure)
    {
      mi_current_note = mi_begin_partial_measure;
      if (partial_measure.size() == 1) {
        (*this)(partial_measure.front());
      } else {
        for (size_t voice_index = 0; voice_index < partial_measure.size();
      	   ++voice_index)
      	{
      	  (*this)(partial_measure[voice_index]);
	  
      	}
      }
      }
  

    void toMidi::operator() (braille::ambiguous::partial_voice const& partial_voice)
    {
      for (size_t element_index = 0; element_index < partial_voice.size();
      	 ++element_index)
        {
	  boost::apply_visitor(*this, partial_voice[element_index]);
        }
    }
  
   
    toMidi::result_type toMidi::operator() (braille::ambiguous::barline const& barline){
       noteWithInfo * new_noteWithInfo = new noteWithInfo;

      //new_noteWithInfo->note = NULL;

      new_noteWithInfo->start_date = mi_current_note;
      new_noteWithInfo->end_date = mi_current_note;

      switch(barline){
      case music::braille::ambiguous::begin_repeat:
	new_noteWithInfo->begin_repeat = true;
	new_noteWithInfo->end_repeat = false;
	break;
      case music::braille::ambiguous::end_repeat:
        new_noteWithInfo->begin_repeat = false;
        new_noteWithInfo->end_repeat = true;
        break;
      default:
	break;
      }

      song[mi_current_staff].push_back(new_noteWithInfo);
    }

    toMidi::result_type toMidi::operator() (braille::ambiguous::simile const& simile) const
    {
      
    }
  
    toMidi::result_type toMidi::operator() (braille::ambiguous::value_distinction const& value_distinction) const
    {
    
    }

    toMidi::result_type toMidi::operator() (braille::ambiguous::hand_sign const& hand_sign) const
    {

    }
 
    toMidi::result_type toMidi::operator() (braille::ambiguous::rest const& rest)
    {
      mi_current_note += ((double)rest.as_rational().numerator() / (double)rest.as_rational().denominator() );

    }
  
    toMidi::result_type toMidi::operator() (braille::ambiguous::note const& note)
    {
      noteWithInfo *new_noteWithInfo = new noteWithInfo;
      double note_length = ((double)note.as_rational().numerator() / (double)note.as_rational().denominator() );
      std::wcout<<"note_length: "<<note_length<<std::endl;
      // copy note call new, delete must be done later on
      new_noteWithInfo->note = copyNote(note);
      new_noteWithInfo->start_date = mi_current_note;
      new_noteWithInfo->end_date = mi_current_note + note_length;
      song[(int)mi_current_staff].push_back(new_noteWithInfo);
      mi_current_note += note_length;

    }

    toMidi::result_type toMidi::operator() (braille::ambiguous::chord const& chord)
    {

    }

  }


}
