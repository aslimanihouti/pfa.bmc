#include "listMidi.hpp"

namespace music{
  listMidi::listMidi(){
    std::wcout << "constructeur" << std::endl;
    song = std::list::list<keyWithInfo*>;
  }
}
