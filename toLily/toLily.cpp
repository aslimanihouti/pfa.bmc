#include "toLily.hpp"
#include <thread>
#include <boost/range/numeric.hpp>
#include <fstream>
#include "stdlib.h"
namespace music{
  
  toLily::toLily(){}
  toLily::~toLily(){
    //free(data);
  }

  void toLily::remove_barline(){
    data->end_repeat = false;
    data->begin_repeat = false;
  }

  void
  toLily::operator()(braille::ambiguous::score const& score){
    int staff_count = 0;
    //   
    //   std::wcout << "open ok" << std::endl;
    data = new backend;
    data->begin_repeat = false;
    data->end_repeat = false;

   std::wcout << "\\version \"2.12.3\"" << std::endl;
   std::wcout << "\\score{" << std::endl;

    for(braille::ambiguous::part const& part: score.parts) {
      	  std::wcout << "<<\n" << std::endl;
      for(braille::ambiguous::staff const& staff: part)
	{
	  if (staff_count==0){
	    std::wcout << "\t\n\\new Staff {\n\t\\clef treble" << std::endl;


	  }
	  else if (staff_count==1){
	    std::wcout << "\t\n\\new Staff {\n\t\\clef bass" << std::endl;


	  }

	  staff_count++;
	  current_position = zero;

	  for (int i = 0; i < staff.size(); i ++){
	    remove_barline();
	    scan=false;
	    boost::apply_visitor(*this,staff[i]);
	    /* The goal here is to see if the next measure begin with a barline
	     * So we will scan the measure to do so
	     */
	    if(i < staff.size() -1){
	      scan = true;
	      boost::apply_visitor(*this,staff[i+1]);
	      scan = false;
	    }
	    if(data->begin_repeat && data->end_repeat){
	      std::wcout << ">> \\bar \":|:\" " << "  %" << i << std::endl;
	    }
	    else if(data->begin_repeat){
	      std::wcout << ">> \\bar \"|:\" " << "  %" << i<< std::endl;
	    }
	    else if(data->end_repeat){
	      std::wcout << ">> \\bar \":|\""<< "  %" << i << std::endl;
	    }
	    else {
	      std::wcout << ">> |" << "  %" << i << std::endl;
	    }
	    
	  }

	  std::wcout << "}\n" << std::endl;
	}
      std::wcout << "\n>>\n" << std::endl;
    }
    std::wcout << "}" << std::endl;
    std::wcout << "}" << std::endl;
  }


  void
  toLily::operator()(braille::ambiguous::measure const& measure){
    if(scan){
      for(braille::ambiguous::voice const& voice: measure.voices) {
	for(braille::ambiguous::partial_measure const& partial_measure: voice) {
	  for(braille::ambiguous::partial_voice const& partial_voice: partial_measure) {
	    text_performer perform(data,scan);
	    std::for_each(partial_voice.begin(), partial_voice.end(),boost::apply_visitor(perform));
	  }
	}
      }
    }
    else {
      std::wcout << "<<";
      for(int j = 0 ; j < measure.voices.size(); j++){
	std::wcout << "{";
	for(int i =0; i < measure.voices[j].size() ; i++){
	  for(int k = 0; k < (measure.voices[j])[i].size(); k++){
	    // true if there is a new partial voices
	    if( k < ((measure.voices[j])[i]).size()-1  && 1 != ((measure.voices[j])[i]).size() ){
	      std::wcout << "<<";
	    }
	    text_performer perform(data,false);
	    for(int l = 0; l < (((measure.voices[j])[i])[k]).size() ; l++ ){
	      struct backend * fakedata = new backend;
	      boost::apply_visitor(text_performer(fakedata,true),(((measure.voices[j])[i])[k])[l]);
	      if( fakedata->fakescan && k < ((measure.voices[j])[i]).size()-1  && 1 != ((measure.voices[j])[i]).size() ) {
		  std::wcout << "{";
	      } 
	      boost::apply_visitor(perform,(((measure.voices[j])[i])[k])[l]);
	      if(fakedata->fakescan && k < ((measure.voices[j])[i]).size()-1  && 1 != ((measure.voices[j])[i]).size()){
		std::wcout << "}";
	      }
	    }
	    if( k < ((measure.voices[j])[i]).size()-1 && 1 != ((measure.voices[j])[i]).size() ){
	      std::wcout << ">>";
	    }
	  }
	}
	std::wcout << "}";
	if(j!=measure.voices.size()-1)
	  std::wcout << "\\\\";    
      }
    }
  }
}














