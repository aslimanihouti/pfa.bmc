#include <fstream>
#include <iostream>
#include <cstring>

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
  
  /**/
  //  int pos_ips = 0, pos_ops = 0, pos_ly = 0;
  
  
  std::ifstream lily_file(lily_name.c_str, std::ios::in);
  if (lily_file){
    std::ifstream ips_file(ps_name.c_str, std::ios::binary | std::ios::in | std::ios::out) ;
    if (ips_file) {
      std::ostream ops_file(ips_file.rdbuf());
      if (ops_file) {
	char line[2048];
	size_t found;
	std::string compteur;
	
	// On cherche le premier textedit
	while (ips_file.getline(line, 2048)) {
	  // Peut il en avoir plusieurs ? es ce que ça termine toujours par '\n'
	  // Le textedit peut il être coupé en deux ? (une partie dans une ligne l'autre dans l'autre ?)
	  compteur = line; 
	  found = compteur.find("textedit",0);
	  
	  if (found != std::string::npos){
	    std::cout << "position du curseur ips : " << ips_file.tellg() << std::endl ; 
	    
	    
	  }
	}
	
	
	
	
      } else  { std::cerr << "err out ps_file failed" << std::endl ; }  
      ips_file.close();
    } else  { std::cerr << "err in ps_file failed" << std::endl ; }  
    lily_file.close();
  } else { std::cerr << "err : in lily_file failed" << std::endl ; }
  // */
  return 0; 
}


