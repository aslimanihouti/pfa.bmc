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
    if(!scan){
      //      std::wcout << " %{CHORD}% " << std::endl;
    }
  }
  
  result_type
  operator()(braille::ambiguous::value_distinction const& value_distinction) const{
    if(!scan){
      // std::wcout << " %{VALUE_DISTINCTION}% " << std::endl ;
    }
  }
  
  result_type
  operator()(braille::ambiguous::hand_sign const& hand_sign) const{
    if(!scan){
      // std::wcout << " %{HAND_SIGN}% " << std::endl;
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
