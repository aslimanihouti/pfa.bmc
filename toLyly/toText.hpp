/*
 * Braille -> Text
 *
 */


#include "ambiguous.hpp"
//#include "midi.hpp"

namespace music {

class text_performer : public boost::static_visitor<void>

  {
    int a ;
    
  public:
    text_performer(int v){
      a=v;
    }
    ~text_performer(){}
    
    
    //note management
    
    result_type 
    operator()(braille::ambiguous::note const& note)const{
    
      switch(note.step)
	{
	case 0:
	  std::wcout<< " C " ;
	  break;
	case 1:
	  std::wcout<< " D " ;
	  break;
	case 2:
	  std::wcout<< " E " ;
	  break;
	case 3:
	  std::wcout<< " F " ;
	  break;
	case 4:
	  std::wcout<< " G " ;
	  break;
	case 5:
	  std::wcout<< " A " ;
	  break;
	case 6:
	  std::wcout<< " B " ;
	  break;
	default:
	  std::wcout<< " ? " ;
	  break;
	}
      std::wcout << note.octave;
          
      if(note.acc){
	switch(*note.acc){
	case 0:
	  std::wcout << " Natural ";
	  break;
	case 1:
	  std::wcout << " flat ";
	  break;
	case 2:
	  std::wcout << " double_flat ";
	  break;
	case 3:
	  std::wcout << " triple_flat ";
	  break;
	case 4:
	  std::wcout << " sharp ";
	  break;
	case 5:
	  std::wcout << " double_sharp ";
	  break;
	case 6:
	  std::wcout << " triple_sharp ";
	  break;
	default:
	  break;
	}      
	}
    }
   
    
    result_type
    operator()(braille::ambiguous::barline const& barline)const{
      switch(barline)
	{
	case 0:
	  std::wcout << " Begin Repeat " ;
	  break;
	case 1:
	  std::wcout << " End Repeat " ; 
	  break;
	default:
	  std::wcout << " Error barline ";

	}
    }

    result_type
    operator()(braille::ambiguous::rest const& rest)const{
       if(rest.whole_measure)
	std::wcout << " r1  " ;
      else
      std::wcout << "  r" << rest.as_rational().numerator() << "/" << rest.as_rational().denominator() << "" ; 
    }





    template<typename T> result_type operator()(T const&) const {}
  };


  class toText: public boost::static_visitor<void> {
    rational current_position;
  public:
    toText();
    ~toText();


    void operator()(braille::ambiguous::score const&);
    void operator()(braille::ambiguous::measure const&);


  };




}
