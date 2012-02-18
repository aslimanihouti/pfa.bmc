#include "toLily.hpp"
#include <thread>
#include <boost/range/numeric.hpp>
#include <fstream>

namespace music{
  toLily::toLily(std::string fileName){
    //std::ofstream ab(fileName.c_str(), std::ios::out | std::ios::trunc);
    //    std::wcout << fileName.c_str() << std::endl;
    //lylyfile = &ab;
    // ab << "\\version \"2.11.44\"" << std::endl;
    //    std::wcout << "constructeur ok" << std::endl;
  }
  toLily::~toLily(){
    //ab.close();
  }


  void
  toLily::operator()(braille::ambiguous::score const& score){
    //   
    //   std::wcout << "open ok" << std::endl;

   std::wcout << "\\version \"2.12.3\"" << std::endl;
   std::wcout << "\\score{" << std::endl;
   std::wcout << "\\relative g{" << std::endl;
    for(braille::ambiguous::part const& part: score.parts) {
      for(braille::ambiguous::staff const& staff: part)
	{
	  std::wcout << "" << std::endl;
	  //std::wcout << "\\relative g{" << std::endl;
//	  std::wcout <<  std::endl << std::endl << " Staff  " << std::endl << std::endl;
	  current_position = zero;
	  std::for_each(staff.begin(), staff.end(), boost::apply_visitor(*this));
	  //	  std::wcout << "}" << std::endl;
	}
    }
    	  std::wcout << "}}" << std::endl;
    //    ab.close();
  }


  void
  toLily::operator()(braille::ambiguous::measure const& measure){
    //for(braille::ambiguous::voice const& voice: measure.voices) {
	std::wcout << "<<";
    for(int j = 0 ; j < measure.voices.size(); j++){
      

      std::wcout << "{";
      //for(braille::ambiguous::partial_measure const& partial_measure: voice) {
      for(int i =0; i < measure.voices[j].size() ; i++){
	for(braille::ambiguous::partial_voice const& partial_voice: (measure.voices[j])[i]) {
	  text_performer perform(12);
	  std::for_each(partial_voice.begin(), partial_voice.end(),boost::apply_visitor(perform));
	}
      }
      std::wcout << "}";
      if(j!=measure.voices.size()-1)
	std::wcout << "\\\\";    
      
    }
    std::wcout << ">> |" << std::endl;
    
  }
}













