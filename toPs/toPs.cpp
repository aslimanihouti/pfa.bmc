#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

//#include "toPs.hpp"

//namespace music { namespace brailleToPs {



bool is_readable( const std::string & file ) 
{ 
    std::ifstream fichier( file.c_str() ); 
    return !fichier.fail(); 
} 

// Dans un premier temps le nom du fichier d'entrée sans l'extention
//toPs::toPs(std::string input_lily_file, std::string output_ps_file_name) {

/**
 * idée : parcourir le fichier ps et "rempalcer" les 'textedit' par 'line:column'
 * pb : les espaces qui rempalcerai le surplus de charactères sont ils ignorés ?
 * pb : dans le cas où le nombre de char pour coder 'line:column' est trop grand il faut reécrire tout le fichier ps ... 
 * Toujours reécrire le fichier ps est peut être un peu trop couteux non ?
 */ 

int main (int argc, char* argv[]) {
  std::string file_name("foo");
  if (argc > 1)
    file_name = argv[1];
  
  std::string lily_name(file_name);
  std::string ps_name(file_name);
  lily_name += ".ly";
  ps_name   += ".ps";



  
  std::cout << "arg : "          << file_name << std::endl;
  std::cout << "fichier lily : " << lily_name << std::endl;
  std::cout << "fichier ps   : " << ps_name   << std::endl;
  
  /** /
  if ( is_readable(lily_name){
    // Create .ps
    systeme( "lilypond --ps " << lily_name );
 // */

  /**/
  //  int pos_ips = 0, pos_ops = 0, pos_ly = 0;
  //int debug = 0;
  
  std::ifstream lily_file(lily_name.c_str(), std::ios::in);
  if (lily_file){
    
    std::ifstream ips_file(ps_name.c_str(), std::ios::binary | std::ios::in | std::ios::out) ;
    if (ips_file) {
      std::ostream ops_file(ips_file.rdbuf());
      if (ops_file) {
	char c, l;
	char sentence[8192]; // (un peu moins) Moche pour le moment mais je changerai après
	std::string textedit;
	size_t found;
	std::string s_line, s_column;
	int line, column, ps_fs_pos, ps_sd_pos;
	
	// On cherche le premier textedit
	c = (char) ips_file.get();
	while (c != EOF ){
	  
	  if ( '0' <= c && c <= '9' ) {
	    ips_file.getline(sentence,8192,'\n');
	    textedit = sentence; 
	    found = textedit.find("textedit:",0);
	    if (found != std::string::npos){
	      ps_sd_pos = ips_file.tellg();
	      //	      ps_fs_pos = ps_fs_pos - textedit.size() + found;
	      
	      std::cerr << "le texte " << ps_fs_pos << "-" << ps_sd_pos << " : " << c << textedit << std::endl ;
	      /** /
	      lily_file.get(sentence,8192,'{'); // better '%' and after '{'
	      lily_file.get(); // discard '{'
	      lily_file.get(sentence,8192,':');
	      std::istringstream iss3( sentence );
	      iss3 >> line;
	      lily_file.get(); // discard ':'	      
	      lily_file.get(sentence,8192,'%');
	      std::istringstream iss4( sentence );
	      iss4 >> column;
	      found = textedit.find(".ly:",0);
	      
	      
	      



	      // open the .ly at the position line:column
	      lily_file.seekg(0, std::ios::beg);
	      
	      l = lily_file.get();
	      // Go to : line
	      while (l != EOF && line > 1){
		if (l == '\n') 
		  line--;
		l = lily_file.get();
	      }
	      if (l == EOF)
		std::cerr << "Pb ! " << std::endl ;
	      
	      // Go to : column
	      while (l != EOF && l != '\n' && column > 1) {
		column--;
		l = lily_file.get();
	      }
	      if (l == EOF || l == '\n')
		std::cerr << "Pb ! " << std::endl ;
	      
	      std::cout << "A la position " << line << ":" << column << " on trouve le char : '" << l << "'." << std::endl ; 

	      // Go to : comment
	      lily_file.get(sentence,8192,'{'); // better '%' and after '{'
	      lily_file.get(); // discard '{'
	      lily_file.get(sentence,8192,':');
	      std::istringstream iss3( sentence );
	      iss3 >> line;
	      lily_file.get(); // discard ':'	      
	      lily_file.get(sentence,8192,'%');
	      std::istringstream iss4( sentence );
	      iss4 >> column;
	      
	      std::cout << "line:column correspondant : " << line << ":" << column << std::endl ; 
	      // write line:column in the .ps
	      ops_file.seekp(ps_fs_pos);
	      ops_file << line << ":" << column << ") mark_URI " ;
	      ips_file.seekg(ops_file.tellp());
	      if (ops_file.tellp() > ps_sd_pos)
		std::cerr << "Pb !" << std::endl ; 
	      c = ips_file.get(); 
	      // completion of the line
	      while ( c != EOF && c != '\n'){
		ops_file << " " ;
		c = ips_file.get(); 
		
	      }		
	      
	      
	      // */	      
	      
	      
	    }
	    
	  }
	  else {
	    while (!(c==EOF || c=='\n')) {
	      c = (char) ips_file.get();
	    }
	  }
	  c = (char) ips_file.get();
	}
	
	
      } else  { std::cerr << "err out ps_file failed" << std::endl ; }  
      ips_file.close();
    } else  { std::cerr << "err in ps_file failed" << std::endl ; }  
    lily_file.close();
  } else { std::cerr << "err : in lily_file failed" << std::endl ; }
  // */
  return 0; 
}



//}}
