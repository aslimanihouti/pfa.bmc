#include <fstream>
#include <iostream>
#include <cstring>

 

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
  
  int pos_ips = 0, pos_ops = 0, pos_ly = 0;
  
  
  std::ifstream lily_file(lily_name, std::ios::in);
  if (lily_file){
    std::ifstream ips_file(ps_name, std::ios::binary | std::ios::in | std::ios::out) ;
    if (ips_file) {
      std::ostream ops_file(ips_file.rdbuf());
      if (ops_file) {
	char c = 'a';
	
	// On cherche le premier textedit
	while (c != EOF && ips_file.good()) {
	  c = (char) ips_file.get();
	  if (c != std::EOF) {
	    
	    
	  }	    
	}
	
	
	
	
	
	
      } else  { std::cerr << "err out ps_file failed" << std::endl ; }  
      fichier.close();
    } else  { std::cerr << "err in ps_file failed" << std::endl ; }  
    lily_file.close();
  } else { std::cerr << "err : in lily_file failed" << std::endl ; }
  return 0; 
}


