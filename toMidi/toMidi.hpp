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
  
  struct score {
    float t;
    struct note;
    struct score *previous;
    struct score *next;
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
    data->fakescan = true;
  }
  ~text_performer(){}
  
    
    //note management
    
    result_type 
    operator()(braille::ambiguous::note const& note)const{
	

      
      if(!scan){
	
	std::string s_octave = "";
	if( (int) note.octave == 5){
	  s_octave += "'";
	}
	else if( (int) note.octave == 6){
	  s_octave += "''";
	}
	
	else if ( (int) note.octave == 3){
	  s_octave += ",";
	}
	
     
      
      switch(note.step)
	{
	case 0:
	  std::wcout<< " c" << s_octave.c_str()  << note.as_rational().denominator();
	  break;
	case 1:
	  std::wcout<< " d" << s_octave.c_str() << note.as_rational().denominator();
	  break;
	case 2:
	  std::wcout<< " e" << s_octave.c_str() << note.as_rational().denominator();
	  break;
	case 3:
	  std::wcout<< " f" << s_octave.c_str() << note.as_rational().denominator();
	  break;
	case 4:
	  std::wcout<< " g" << s_octave.c_str() << note.as_rational().denominator();
	  break;
	case 5:
	  std::wcout<< " a" << s_octave.c_str() << note.as_rational().denominator();
	  break;
	case 6:
	  std::wcout<< " b" << s_octave.c_str() << note.as_rational().denominator();
	  break;
	default:
	  std::wcout<< " ?" ;
	  break;
 	}
    //   std::wcout << note.octave;
          
    //   if(note.acc){
    // 	switch(*note.acc){
    // 	case 0:
    // 	  std::wcout << " Natural ";
    // 	  break;
    // 	case 1:
    // 	  std::wcout << " flat ";
    // 	  break;
    // 	case 2:
    // 	  std::wcout << " double_flat ";
    // 	  break;
    // 	case 3:
    // 	  std::wcout << " triple_flat ";
    // 	  break;
    // 	case 4:
    // 	  std::wcout << " sharp ";
    // 	  break;
    // 	case 5:
    // 	  std::wcout << " double_sharp ";
    // 	  break;
    // 	case 6:
    // 	  std::wcout << " triple_sharp ";
    // 	  break;
    // 	default:
    // 	  break;
    // 	}      
    // 	}
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
	data->fakescan = false;
    }

    result_type
    operator()(braille::ambiguous::rest const& rest)const{
      if(!scan){
      if(rest.whole_measure)
	std::wcout << " r1  " ;
      else
      std::wcout << "  r" <</* rest.as_rational().numerator() << "/" <<*/ rest.as_rational().denominator() << "" ;
      }
    }
  
  result_type
  operator()(braille::ambiguous::chord const& chord)const{
    data->fakescan = false;
    //std::wcout << "FDLKQJLDFKJQDSF" << (int) chord.base.step << (int) chord.intervals[0].steps  << std::endl;
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
	if(_note - chord.base.step < 0){
	  if(s_octave == ","){
	    s_octave2 += "";
	  }
	  else if (s_octave == "'"){
	    s_octave2 += "''";
	  }
	  else {
	    s_octave2 = s_octave;
	  }
	}
	
	else {
	  s_octave2 = s_octave;
	}
	
	switch((chord.base.step+_note+1)%7)
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
      
      //    std::wcout << " %{CHORD}% " << std::endl;
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
      // std::wcout << " %{SIMILE}% " << std::endl ;
    }
  }
  




    template<typename T> result_type operator()(T const&) const {}
  };


  class toMidi : public boost::static_visitor<void> {
    rational current_position;
    
  private:
    void remove_barline();
    /* If scan is true we will do something different */
    bool scan;
  public:
    struct score *song; 
    toMidi();
    ~toMidi();
    void operator()(braille::ambiguous::score const&);
    void operator()(braille::ambiguous::measure const&);
  };




}
