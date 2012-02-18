#include "toLily.hpp"
#include <thread>
#include <boost/range/numeric.hpp>
#include <fstream>

namespace music{
  toLily::toLily(std::string fileName){
    //std::ofstream ab(fileName.c_str(), std::ios::out | std::ios::trunc);
    std::wcout << fileName.c_str() << std::endl;
    //lylyfile = &ab;
    // ab << "\\version \"2.11.44\"" << std::endl;
    std::wcout << "constructeur ok" << std::endl;
  }
  toLily::~toLily(){
    //ab.close();
 }


  void
  toLily::operator()(braille::ambiguous::score const& score){
    //   
   std::wcout << "open ok" << std::endl;
   //ab << "\\version \"2.11.44\"" << std::endl;

    for(braille::ambiguous::part const& part: score.parts) {
      for(braille::ambiguous::staff const& staff: part)
	{
	  std::wcout <<  std::endl << std::endl << " Staff  " << std::endl << std::endl;
	  current_position = zero;
	  std::for_each(staff.begin(), staff.end(), boost::apply_visitor(*this));

	}
    }
    //    ab.close();
  }


  void
  toLily::operator()(braille::ambiguous::measure const& measure){
    for(braille::ambiguous::voice const& voice: measure.voices) {
      for(braille::ambiguous::partial_measure const& partial_measure: voice) {
	for(braille::ambiguous::partial_voice const& partial_voice: partial_measure) {
	  text_performer perform(12);
	  std::for_each(partial_voice.begin(), partial_voice.end(),boost::apply_visitor(perform));
	}
	
      }
      std::wcout << " > " ;    
    }
     std::wcout << " | " ;    
  }



}













