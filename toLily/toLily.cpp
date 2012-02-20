#include "toLily.hpp"
#include <thread>
#include <boost/range/numeric.hpp>
#include <fstream>
#include "stdlib.h"
namespace music{

void  text_performer::add_articulation(enum articulation arti)const{
    switch (arti){    
    case appoggiatura :
      std::wcout << "\\appoggiatura ";  
      break;
 
    case short_appoggiatura :
      std::wcout << "\\acciaccatura ";
      break;

    case short_trill :
      std::wcout << "\\trill ";
  
      break;

    case extended_short_trill :
      std::wcout << "\\prallprall "; // \startTrillSpan   ->  \stopTrillSpan
      break;
   
    case turn_between_notes :
      std::wcout << "TURN_BETWEEN_NOTES ";
      break;

    case turn_above_or_below_note :
      std::wcout << "\\turn ";  // C'est vraiment celui là ?
      break;

    case inverted_turn_between_notes :
      std::wcout << "INVERTED_TURN_BETWEEN_NOTES  "; //  ???
      break;

    case  inverted_turn_above_or_below_note :
      std::wcout << "INVERTED_TURN_ABOVE_OR_BELOW_NOTE  ";  //   ???
      break;
   
    case staccato :
      std::wcout << "-. ";
      break;

    case staccatissimo :
      std::wcout << "-| ";
      break;

    case mezzo_staccato :
      std::wcout << "-_ ";
      break;
   
    case agogic_accent :
      std::wcout << "AGOGIC_ACCENT  ";  // 4 types différents, lequel mettre ?
      break;

    case accent :
      std::wcout << "-> ";
      break;
   
    case mordent :
      std::wcout << "\\mordent ";
      break;
   
    case extended_mordent :
      std::wcout << "EXTENDED_MORDENT  ";
      break;
   
    case arpeggio_up:
      std::wcout << "ARPEGGIO_UP  ";
      break;

    case  arpeggio_up_multi_staff :
      std::wcout << "ARPEGGIO_UP_MULTI_STAFF ";
      break;
   
    case arpeggio_down:
      std::wcout << "ARPEGGIO_DOWN ";
      break;
    
    case  arpeggio_down_multi_staff :
      std::wcout << "  ";
      break;
   
    default:
      break;
    }

    
  }


  void text_performer::add_note(enum diatonic_step d_step)const{
       
	switch(d_step)
	  {
	  case 0:
	    std::wcout<< " c";// << s_octave.c_str() << note.as_rational().numerator() << "/" << note.as_rational().denominator();
	    break;
	  case 1:
	    std::wcout<< " d";// << s_octave.c_str() << note.as_rational().numerator() << "/" << note.as_rational().denominator();
	    break;
	  case 2:
	    std::wcout<< " e";// << s_octave.c_str() << note.as_rational().numerator() << "/" <<note.as_rational().denominator();
	    break;
	  case 3:
	    std::wcout<< " f";// << s_octave.c_str() << note.as_rational().numerator() << "/" <<note.as_rational().denominator();
	    break;
	  case 4:
	    std::wcout<< " g";// << s_octave.c_str() << note.as_rational().numerator() << "/" <<note.as_rational().denominator();
	    break;
	  case 5:
	    std::wcout<< " a";// << s_octave.c_str() << note.as_rational().numerator() << "/" <<note.as_rational().denominator();
	    break;
	  case 6:
	    std::wcout<< " b";// << s_octave.c_str() << note.as_rational().numerator() << "/" << note.as_rational().denominator();
	    break;
	  default:
	    std::wcout<< " ?";
	    break;
	  }

  }
  
  void text_performer::add_accidental_lily(boost::optional<accidental> acci)const {
    if(acci){
    
    switch (*acci){
    case natural :
      std::wcout << ""; // Rien ?  "\key note \minor"  ?
      break;
    case flat:
      std::wcout << "es";
      break;
    case double_flat:
      std::wcout << "eses";
      break;
    case triple_flat:
    std::wcout << "TRIPLE_FLAT "; // seem to be not implemented in lilypond
      break;
    case sharp:
      std::wcout << "is";
      break;
    case double_sharp:
      std::wcout << "isis";
      break;
    case triple_sharp:
      std::wcout << "TRIPLE_SHARP ";  // seem to be not implemented in lilypond
      break;
    default:
      break;
    }
    }

  }
  
  void text_performer::add_octave_chord(int octave,std::string previous_octave)const {

  }
  void text_performer::add_octave(int octave)const{
	
    std::string s_octave = "";
    if(octave == 5){
      s_octave += "'";
    }
    else if( octave == 6){
      s_octave += "''";
    }
    else if( octave == 7){
      s_octave += "'''";
    }
    else if (octave == 2){
      s_octave += ",,";
    }
    else if (octave == 1){
      s_octave += ",,,";
    }
    else if (octave == 0){
      s_octave += ",,,,";
    }
    else if ( octave == 3){
      s_octave += ",";
    }
    else if (octave == 4){
      s_octave += "";
    }
    else {
      std::wcout << "OCTAVE OUT OF BOUND" << std::endl;
    }
    std::wcout << s_octave.c_str();
  }

  void text_performer::add_duration(rational duration)const{
    if(duration.numerator() == 1){
     
	std::wcout <<duration.denominator();
     
    }
    else{
     
	std::wcout <<duration.denominator()/2 << ".";
     
    }
  }


  
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
	  std::wcout << "\\partial 8"; 
	  staff_count++;
	  current_position = zero;

	  	    for (int i = 0; i < staff.size(); i ++){
	  //	    for (int i = 0; i < 9; i ++){
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
    std::wcout << "\\midi {} \n \\layout {}";
    std::wcout << "}" << std::endl;

    //    std::wcout << "}" << std::endl;
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
	  //	      std::wcout << " ( ";
	  for(int k = 0; k < (measure.voices[j])[i].size(); k++){
	    //   std::wcout << " [ ";
	    // true if there is a new partial voices
	    if( k == 0  && 1 != ((measure.voices[j])[i]).size() ){
	      //if(1 != ((measure.voices[j])[i]).size()){
	      std::wcout << " << ";
	    }
	    text_performer perform(data,false);
	    bool first_note = true;
	    for(int l = 0; l < (((measure.voices[j])[i])[k]).size() ; l++ ){
	      // std::wcout << " |- ";
	      struct backend * fakedata = new backend;
	      fakedata->fakescan = false;
	      boost::apply_visitor(text_performer(fakedata,true),(((measure.voices[j])[i])[k])[l]);
	      if(fakedata->fakescan && first_note && 1 != ((measure.voices[j])[i]).size() ){
		  std::wcout << "{";
		  first_note = false;
	      } 
	      boost::apply_visitor(perform,(((measure.voices[j])[i])[k])[l]);

	      fakedata->fakescan = false;
	      for(int m = l+1; m < (((measure.voices[j])[i])[k]).size() ; m++ ){
		boost::apply_visitor(text_performer(fakedata,true),(((measure.voices[j])[i])[k])[m]);
	      }
	      if(!(fakedata->fakescan) && 1 != ((measure.voices[j])[i]).size()){
		std::wcout << " }";
		if( k!= ((measure.voices[j])[i]).size() -1)
		  std::wcout << "\\\\";    
	      }
	      //std::wcout << " -| ";
	    }
	    if( k == ((measure.voices[j])[i]).size()-1 && 1 != ((measure.voices[j])[i]).size() ){
	      //if(1 != ((measure.voices[j])[i]).size() ){
	      std::wcout << " >> ";
	    }
	    //std::wcout << " ] ";
	    
	  }
	  //  std::wcout << " ) ";
	}
	std::wcout << " }";
	if(j!=measure.voices.size()-1)
	  std::wcout << "\\\\";    
      }
    }
  }
}














