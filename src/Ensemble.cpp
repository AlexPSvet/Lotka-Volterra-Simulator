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

int Ensemble::getPosition(int o) const {
  for (int i = 0; i < card; i++) {
    if (t[i] == o) {
      return i;
    }
  }
  return -1;
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
  for (int j = i; j<card-1; j++) {
    t[j] = t[j+1];
  }
  card--;
}

int Ensemble::tire() {
  if (card == 0) {
    throw runtime_error("Peut pas tirer un élément d'une liste vide.");
  }
  int i = rand() % card;
  int element = t[i];
  erase(i);
  return element;
}


