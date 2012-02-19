

switch (){
  
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
   std::wcout << "EXTENDED_SHORT_TRILL "; // \startTrillSpan   ->  \stopTrillSpan
   break;
   
 case turn_between_notes :
   std::wcout << "TURN_BETWEEN_NOTES ";
   break;

 case turn_above_or_below_note :
   std::wcout << "\turn ";  // C'est vraiment celui là ?
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

 case mezzo_staccat :
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
   std::wcout << " error type definition ";
   break;
 }









switch (accidental){
 case natural :
   std::wcout << "NATURAL "; // Rien ?  "\key note \minor"  ?
   break;
 case flat:
   std::wcout << "es ";
   break;
 case double_flat:
   std::wcout << "eses ";
   break;
 case triple_flat:
   std::wcout << "TRIPLE_FLAT ";
   break;
 case sharp:
   std::wcout << "is ";
   break;
 case double_sharp:
   std::wcout << "isis ";
   break;
 case triple_sharp:
  std::wcout << "TRIPLE_SHARP ";
   break;
 default:
   break;
 }
