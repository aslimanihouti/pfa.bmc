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
  

class text_performer : public boost::static_visitor<void>

{

private:
  //  std::ofstream &theFile;
  public:
  int a;
  text_performer(int v)//, std::ofstream &theFileB){
  { a = v;
    // theFile = theFileB;
  }
  ~text_performer(){}
  
    
    //note management
    
    result_type 
    operator()(braille::ambiguous::note const& note)const{
    
      switch(note.step)
	{
	case 0:
	  std::wcout<< " c " ;
	  break;
	case 1:
	  std::wcout<< " d " ;
	  break;
	case 2:
	  std::wcout<< " e " ;
	  break;
	case 3:
	  std::wcout<< " f " ;
	  break;
	case 4:
	  std::wcout<< " g " ;
	  break;
	case 5:
	  std::wcout<< " a " ;
	  break;
	case 6:
	  std::wcout<< " b " ;
	  break;
	default:
	  std::wcout<< " ? " ;
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
   
    
    result_type
    operator()(braille::ambiguous::barline const& barline)const{
      /*  switch(barline)
	{
	case 0:
	  std::wcout << " Begin Repeat " ;
	  break;
	case 1:
	  std::wcout << " End Repeat " ; 
	  break;
	default:
	  std::wcout << " Error barline ";

	  }*/
    }

    result_type
    operator()(braille::ambiguous::rest const& rest)const{
      if(rest.whole_measure)
	std::wcout << " r1  " ;
      else
      std::wcout << "  r" <</* rest.as_rational().numerator() << "/" <<*/ rest.as_rational().denominator() << "" ;
    }





    template<typename T> result_type operator()(T const&) const {}
  };


  class toLily : public boost::static_visitor<void> {
    rational current_position;

  public:
    toLily(std::string);
    ~toLily();
    void operator()(braille::ambiguous::score const&);
    void operator()(braille::ambiguous::measure const&);
  };




}
