#include "toLily.hpp"
#include <thread>
#include <boost/range/numeric.hpp>
#include <fstream>
#include "stdlib.h"
namespace music{
  toLily::toLily(std::string fileName){
   
  }
  toLily::~toLily(){
    //free(data);
  }

  void toLily::remove_barline(){
    data->end_repeat = false;
    data->begin_repeat = false;
  }
  void
  toLily::operator()(braille::ambiguous::score const& score){
    //   
    //   std::wcout << "open ok" << std::endl;
    data = new backend;
    data->begin_repeat = false;
    data->end_repeat = false;

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
	  //	  std::for_each(staff.begin(), staff.end(), boost::apply_visitor(*this));
	  //	  std::for_each(staff.begin(), staff.end(), boost::apply_visitor(*this));


	  for (int i = 0; i < staff.size(); i ++){
	    staff[i]();
	    
	    if(data->begin_repeat && data->end_repeat){
	      std::wcout << ">> \\bar \":|:\" " << std::endl;
	    }
	    else if(data->begin_repeat){
	      std::wcout << ">> \\bar \"|:\" " << std::endl;
	    }
	    else if(data->end_repeat){
	      std::wcout << ">> \\bar \":|\"" << std::endl;
	    }
	    else {
	      std::wcout << ">> |" << std::endl;
	    }
	    remove_barline();
	    }
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
	      printf(" adresse text_performer %p",data);
	  text_performer perform(12,data);
	  std::for_each(partial_voice.begin(), partial_voice.end(),boost::apply_visitor(perform));
	}
      }
      std::wcout << "}";
      if(j!=measure.voices.size()-1)
	std::wcout << "\\\\";    
      
    }
  }
}













