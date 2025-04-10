//
// Created by desarrollo on 3/4/25.
//
#include "Ensemble.hpp"

Ensemble::Ensemble() {
  card = 0;
}

std::ostream& Ensemble::operator<<(std::ostream& out) {
  out<<"{ ";
  for (int i = 0; i < card; i++) {
    out << t[i];
    if (i+1 >= card) {
      out << " }";
    } else {
      out << ", ";
    }
  } return out;
}

bool Ensemble::estVide() const {
  return card == 0;
}

int Ensemble::cardinal() const {
  return card;
}

void Ensemble::ajoute(int o) {
  if (card + 1 > MAXCARD){
    throw invalid_argument("Le cardinal Maximal est depassé");
  } else {
    t[card + 1] = o;
  }
  card++;
}

void Ensemble::erase(int i) {
  for (int j = i; j<card; j++) {
    t[j] = t[j+1];
  }
}

int Ensemble::tire() {
  int o = rand() % card;
  int element = t[o];
  erase(o);
  card--;
  return element;
}


