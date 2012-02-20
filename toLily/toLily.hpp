/*
 * Braille -> Text
 *
 */

#include <fstream>
#include "ambiguous.hpp"
#include <string>
#include <iostream>
//#include "midi.hpp"

namespace music {
  
  struct backend {
    // Repeat
    bool begin_repeat;
    bool end_repeat;
    // FakeScan
    bool fakescan;
    int number_note;
    // Octave
    int last_note_step;

  };


  class text_performer : public boost::static_visitor<void>

  {

  private:

  public:
    struct backend * data;
    /* If scan is true we will do something different */
    bool scan;
    text_performer(struct backend * _data, bool _scan)//, std::ofstream &theFileB){
    { 
      scan = _scan;
      data = _data;
      data->number_note = 0;
    }
    ~text_performer(){}

    void add_articulation(enum articulation arti)const;
    void add_note(enum diatonic_step d_step)const;
    void add_accidental_lily(boost::optional<accidental> acci)const;
    void add_octave_chord(int octave,std::string previous_octave)const;
    void add_octave(int octave)const;
    void add_duration(rational duration)const;
    //note management
    
    result_type 
    operator()(braille::ambiguous::note const& note)const{
      data->fakescan = true;
      data->number_note++;
      if(!scan){
	add_note(note.step);
	add_accidental_lily(note.acc);
	int _octave = note.octave;
	add_octave(_octave);
	add_duration(note.as_rational());
   	for(int i = 0; i < note.articulations.size();i++){
	  add_articulation(note.articulations[i]);
	}
      }
      
    }
   
    
    result_type
    operator()(braille::ambiguous::barline const& barline)const{
      switch(barline)
	{
	  data->fakescan = false;
	case 0:
	  if(scan)
	    data->begin_repeat = true;
	  break;
	case 1:
	  if(!scan)
	    data->end_repeat = true;
	  break;
	default:
	  std::wcout << " Error barline ";

	}

    }

    result_type
    operator()(braille::ambiguous::rest const& rest)const{
      data->fakescan = true;
      if(!scan){
       
	if(rest.whole_measure)
	  std::wcout << " r1  " ;
	else
	  std::wcout <<" r" <</* rest.as_rational().numerator() << "/" <<*/ rest.as_rational().denominator() << "" ;
      }
    }
  
    result_type
    operator()(braille::ambiguous::chord const& chord)const{

      
      if(!scan){

	std::wcout << "<";
      	std::string s_octave = "";
	if( (int) chord.base.octave == 5){
	  s_octave += "'";
	}
	else if( (int) chord.base.octave == 6){
	  s_octave += "''";
	}
	
	else if ( (int) chord.base.octave == 3){
	  s_octave += ",";
	}
	
      
	switch(chord.base.step)
	  {
	  case 0:
	    std::wcout<< " c" << s_octave.c_str(); 
	    break;
	  case 1:
	    std::wcout<< " d" << s_octave.c_str();
	    break;
	  case 2:
	    std::wcout<< " e" << s_octave.c_str();
	    break;
	  case 3:
	    std::wcout<< " f" << s_octave.c_str();
	    break;
	  case 4:
	    std::wcout<< " g" << s_octave.c_str();
	    break;
	  case 5:
	    std::wcout<< " a" << s_octave.c_str();
	    break;
	  case 6:
	    std::wcout<< " b" << s_octave.c_str() ;
	    break;
	  default:
	    std::wcout<< " ?" ;
	    break;
 
	  }
      
	for(int i = 0; i < chord.intervals.size(); i++){
	 
	  int _note = chord.intervals[i].steps;
	  std::string  s_octave2 = "";
	  int new_note = chord.base.step-_note;
	  if(new_note < 0){
	    if(s_octave == "''"){
	      s_octave2 = "'";
	    }
	    else if (s_octave == "'"){
	      s_octave2 = "";
	    }
	    else if (s_octave == ""){
	      s_octave2 = ",";
	    }
	    else {
	      s_octave2 = ",,";
	    }
	  }
	
	  else {
	    s_octave2 = s_octave;
	  }
	  
	  if(new_note<0){
	    new_note = 7 + new_note;
	  }
	  switch((new_note)%7)
	    {
	    case 0:
	      std::wcout<< " c" << s_octave2.c_str(); 
	      break;
	    case 1:
	      std::wcout<< " d" << s_octave2.c_str();
	      break;
	    case 2:
	      std::wcout<< " e" << s_octave2.c_str();
	      break;
	    case 3:
	      std::wcout<< " f" << s_octave2.c_str();
	      break;
	    case 4:
	      std::wcout<< " g" << s_octave2.c_str();
	      break;
	    case 5:
	      std::wcout<< " a" << s_octave2.c_str();
	      break;
	    case 6:
	      std::wcout<< " b" << s_octave2.c_str() ;
	      break;
	    default:
	      std::wcout<< " ?" ;
	      break;
 
	    }
	}
      std::wcout << ">" << chord.as_rational().denominator();
      
      
    }
  }
  
  result_type
  operator()(braille::ambiguous::value_distinction const& value_distinction) const{
    if(!scan){
      //std::wcout << " %{VALUE_DISTINCTION}% " << std::endl ;
    }
  }
  
  result_type
  operator()(braille::ambiguous::hand_sign const& hand_sign) const{
    if(!scan){
      //std::wcout << " %{HAND_SIGN}% " << std::endl;
    }
  }

  result_type
  operator()(braille::ambiguous::simile const& simile) const{
    if(!scan){
      //std::wcout << " %{SIMILE}% " << std::endl ;
    }
  }
  




    template<typename T> result_type operator()(T const&) const {}
  };


  class toLily : public boost::static_visitor<void> {
    rational current_position;

  private:
    void remove_barline();
    /* If scan is true we will do something different */
    bool scan;
  public:
    struct backend * data; 
    toLily();
    ~toLily();
    void operator()(braille::ambiguous::score const&);
    void operator()(braille::ambiguous::measure const&);
  };




}
