#include "listMidi.hpp"

namespace music{
  listMidi::listMidi(){
    std::wcout << "constructeur" << std::endl;
    this->score = new keyWithInfo;
    this->score->previous = NULL;
    this->score->next = NULL;
}
  
  listMidi::~listMidi(){
    struct keyWithInfo *tmp = score;
    struct keyWithInfo *tmpp = NULL;
    while(tmp->next!=NULL)
      tmp = tmp->next;
    while(tmp->previous != NULL){
    tmpp = tmp->previous;
    delete(tmp);
    tmp = tmpp;
    }
  }
  
  void listMidi::addKey(struct keyWithInfo *theKey){
    struct keyWithInfo *tmp=score;
    struct keyWithInfo *tmpp;
    while(tmp!=NULL){
      tmpp = tmp;
      tmp = tmp->next;
    }
    tmpp->next = theKey;
    theKey->previous = tmpp;
  }

  void listMidi::debug(){
    struct keyWithInfo *tmp=score;
    while(tmp!=NULL){
      std::wcout << (int)tmp->toto.octave << std::endl;
      std::wcout << "theBooleans:" << tmp->startRepeat << std::endl;
      tmp = tmp->next;
    }
  }
}
