#include "Ensemble.hpp"

Ensemble::Ensemble() {
	card = 0;
}

std::ostream& Ensemble::operator<<(std::ostream& out) {
	out << "{ ";
	for (int i = 0; i < card; i++) {
		out << t[i];
		if (i+1 < card) {
			out << ", ";
		}
	}
	out << " }"; 
	return out;
}

int Ensemble::operator[](int i) const {
	return t[i];
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
	if (card > MAXCARD){
		throw invalid_argument("Le cardinal Maximal est depassé");
	} else {
		t[card] = o;
	}
	card++;
}

void Ensemble::erase(int i) {
	for (int j = i; j<card-1; j++) {
		t[j] = t[j+1];
	}
	card--;
}

void Ensemble::set(int value, int amount) {
    for (int i = 0; i < amount; i++) {
        t[i] = value;
    }
	card = amount;
}

void Ensemble::clear() {
	card = 0;
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

void Ensemble::setValue(int i, int o) {
	t[i] = o;
}