

switch (){
  
 case appoggiatura :
   sdt::wcout << "\\appoggiatura ";  
   break;
 
 case short_appoggiatura :
   sdt::wcout << "\\acciaccatura ";
   break;

 case short_trill :
   sdt::wcout << "\\trill ";
   break;

 case extended_short_trill :
   sdt::wcout << "EXTENDED_SHORT_TRILL "; // \startTrillSpan   ->  \stopTrillSpan
   break;
   
 case turn_between_notes :
   sdt::wcout << "TURN_BETWEEN_NOTES ";
   break;

 case turn_above_or_below_note :
   sdt::wcout << "\turn ";  // C'est vraiment celui là ?
   break;

 case inverted_turn_between_notes :
   sdt::wcout << "INVERTED_TURN_BETWEEN_NOTES  "; //  ???
   break;

 case  inverted_turn_above_or_below_note :
   sdt::wcout << "INVERTED_TURN_ABOVE_OR_BELOW_NOTE  ";  //   ???
   break;
   
 case staccato :
   sdt::wcout << "-. ";
   break;

 case staccatissimo :
   sdt::wcout << "-| ";
   break;

 case mezzo_staccat :
   sdt::wcout << "-_ ";
   break;
   
 case agogic_accent :
   sdt::wcout << "AGOGIC_ACCENT  ";  // 4 types différents, lequel mettre ?
   break;

 case accent :
   sdt::wcout << "-> ";
   break;
   
 case mordent :
   sdt::wcout << "\\mordent ";
   break;
   
 case extended_mordent :
   sdt::wcout << "EXTENDED_MORDENT  ";
   break;
   
 case arpeggio_up:
   sdt::wcout << "ARPEGGIO_UP  ";
   break;

 case  arpeggio_up_multi_staff :
   sdt::wcout << "ARPEGGIO_UP_MULTI_STAFF ";
   break;
   
  case arpeggio_down:
    sdt::wcout << "ARPEGGIO_DOWN ";
    break;
    
 case  arpeggio_down_multi_staff :
   sdt::wcout << "  ";
   break;
   
 default:
   sdt::wcout << " error type definition ";
   break;
 }










 }
