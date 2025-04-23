#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP

#include <iostream>
#include <cstdlib>

using namespace std;

const int MAXCARD = 10e3;

struct Ensemble {
  public:
    //Constructeurs:
    Ensemble();

    //Gets:
    bool estVide() const;
    int cardinal() const;
    int getPosition(int o) const;

    //Ajoute:
    void ajoute(int o);
    int tire();
    void setValue(int i, int o);

    //Methode aditionels:
    void erase(int i);

    //Operateurs:
    std::ostream& operator<<(std::ostream& out);
    int operator[](int i) const;
  private:
    int t[MAXCARD];
    int card;
};

#endif
