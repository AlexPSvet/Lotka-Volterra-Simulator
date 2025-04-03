//
// Created by desarrollo on 3/4/25.
//
#include <cstdlib>
#include "HeaderFiles/Ensemble.hpp"

Ensemble::Ensemble(){
  t = {};
  card = 0;
}

std::ostream& Ensemble::operator<<(std::ostream& out){
  out<<"{ ";
  for (int i = 0; i < card; i++) {
    if (i+1 >= card) {
      out << t[i] << " }";
    } else {
      out << t[i] << ", ";
    }
  } return out;
}

bool Ensemble::estVide() const{
  return card == 0;
}

int Ensemble::cardinal() const{
  return card;
}

void Ensemble::ajoute(int o) {
  if (card + 1 > MAXCARD){
    throw invalid_argument("Le cardinal Maximal est depassé");
  } else {
    t.push_back(o);
  }
}

void Ensemble::tire(){
  int o = rand() % card + 1;
  for (int i = 0; i < card; i++){
    if (t[i] == o){
      t.erase(t.begin()+i);
      break;
    }
  }
}


