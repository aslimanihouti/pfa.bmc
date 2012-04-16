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
  int debug = 0;
  
  std::ifstream lily_file(lily_name.c_str(), std::ios::in);
  if (lily_file){
    
    std::ifstream ips_file(ps_name.c_str(), std::ios::binary | std::ios::in | std::ios::out) ;
    if (ips_file) {
      std::ostream ops_file(ips_file.rdbuf());
      if (ops_file) {
	char c = 'a', l;
	char sentence[5000000]; // Moche pour le moment mais je changerai après
	std::string textedit;
	size_t found;
	std::string s_line, s_column;
	int line, column, ps_fs_pos, ps_sd_pos;
	
	// On cherche le premier textedit
	while ( c!= EOF ){
	  while ( c != EOF && c != 't')
	    c = (char) ips_file.get();
	  
	  if (c != EOF) {
	    ps_fs_pos = ips_file.tellg();
	    std::cout << "J'ai trouvé un 't' à la position : " << ps_fs_pos << "(l." << debug << ") : " ; 
	      
	    ips_file.get(sentence,5000000);
	    textedit = sentence;
	    

	    debug ++;
	    std::cout.write(textedit.c_str(),20);
	    std::cout << std::endl ;

	    // On trouve des t mais pas de "textedit" :x
	    found = textedit.find("extedit:",0);
	    if (found != std::string::npos){
	      std::cout << "position du curseur ips : " << ips_file.tellg() << std::endl ; 
	      ips_file.get(); // discard ':'
	      ips_file.get(sentence,5000000,':');  
	      std::istringstream iss1( sentence );
	      iss1 >> line;
	      ips_file.get(); // discard ':'
	      ips_file.get(sentence,5000000,':');
	      std::istringstream iss2( sentence );
	      iss2 >> column;
	      ips_file.get(); // discard ':'
	      ips_file.get(sentence,5000000,')');
	      
	      ps_sd_pos = ips_file.tellg();
	      std::cout << "C'est bien un textedit qui se fini en : " << ps_sd_pos << std::endl ; 	      
	      
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
	      lily_file.get(sentence,5000000,'{'); // better '%' and after '{'
	      lily_file.get(); // discard '{'
	      lily_file.get(sentence,5000000,':');
	      std::istringstream iss3( sentence );
	      iss3 >> line;
	      lily_file.get(); // discard ':'	      
	      lily_file.get(sentence,5000000,'%');
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
	    }
	  }
	  debug ++ ;
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
