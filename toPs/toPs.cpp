#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

/** /
bool is_readable( const std::string & file ) 
{ 
    std::ifstream fichier( file.c_str() ); 
    return !fichier.fail(); 
} 
/**/

// Dans un premier temps le nom du fichier d'entrée sans l'extention

/**
 * idée : parcourir le fichier ps et "rempalcer" les 'textedit' par 'line:column'
 * pb : les espaces qui rempalcerai le surplus de charactères sont ils ignorés ? --> ignoré
 * pb : dans le cas où le nombre de char pour coder 'line:column' est trop grand il faut reécrire tout le fichier ps ...--> ce cas ne devrai pas arriver, j'attends toujours le contre exemple, mais bon c'est une vraie question 
 * Toujours reécrire le fichier ps est peut être un peu trop couteux non ?
 */ 

int main (int argc, char* argv[]) {
  std::string file_name;
  if (argc > 1)
    file_name = argv[1];
  else {
    std::cout << "ligne de commande :" << std::endl << "\t" << argv[0] << " <nom_fichier_sans_extention>" << std::endl ;
    return 0;
  }
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
	char sentence[8192];
	std::string textedit;
	size_t found;
	std::string s_line_column;
	int line, column;
	int ps_fs_pos, ps_sd_pos;
	int i, j;

	// On cherche le premier textedit
	c = (char) ips_file.get();
	while (c != EOF ){
	  
	  if ( '0' <= c && c <= '9' ) {
	    ps_fs_pos =  (int) ips_file.tellg() - 1;
	    
	    ips_file.getline(sentence,8192,'\n');
	    textedit = sentence; 
	    found = textedit.find("textedit:",0);
	    if (found != std::string::npos){
	      ps_sd_pos = ips_file.tellg();
	      
	      ips_file.seekg(ps_fs_pos);
	      ips_file.getline(sentence,8192,':');
	      ips_file.getline(sentence,8192,':');
	      ips_file.getline(sentence,8192,':');
	      std::istringstream iss1( sentence );
	      iss1 >> line;
	      ips_file.getline(sentence,8192,':');
	      std::istringstream iss2( sentence );
	      iss2 >> column;
	      
	      // open the .ly at the position line:column
	      i = line;
	      j = column;
	      
	      lily_file.seekg(0, std::ios::beg);
	      
	      l = lily_file.get();
	      // go to : line
	      while (l != EOF && i > 1){
		if (l == '\n') 
		  i--;
		l = lily_file.get();
	      }
	      if (l == EOF)
		std::cerr << "Pb ! " << std::endl ;
	      
	      // go to : column
	      while (l != EOF && l != '\n' && j > 0) {
		j--;
		l = lily_file.get();
	      }
	      if (l == EOF || l == '\n')
		std::cerr << "Pb ! " << std::endl ;
	      
	      // go to : comment
	      lily_file.getline(sentence,8192,'{'); // better '%' and after '{' ?
	      lily_file.get(sentence,8192,'%');
	      s_line_column = sentence;
	      
	      // write line:column in the .ps
	      ips_file.seekg(ps_fs_pos);
	      ips_file.getline(sentence,8192,'(');
	      ops_file.seekp(ips_file.tellg());
	      ops_file << s_line_column << ") mark_URI " ;
	      // fill with space
	      ips_file.seekg(ops_file.tellp());
	      if (ops_file.tellp() > ps_sd_pos)
		std::cerr << "Pb !" << std::endl ; 

	      // completion of the line 
	      j = ps_sd_pos - ops_file.tellp() -1; 
	      for (i=0 ; i<j ; i++)
		ops_file.write(" ",1);
	      
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
  return 0; 
}

