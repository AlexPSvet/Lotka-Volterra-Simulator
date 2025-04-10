#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP

#include <iostream>
#include <cstdlib>

using namespace std;

int MAXCARD = 10e3;

struct Ensemble{
  public:
    //Constructeurs:
    Ensemble();


    //Gets:
    bool estVide() const;
    int cardinal() const;

    //Ajoute:
    void ajoute(int o);
    int tire();

    //Methode aditionels:
    void erase(int i);

    //Operateurs:
    std::ostream& operator<<(std::ostream& out);

  private:
    int t[MAXCARD];
    int card;
};

#endif
