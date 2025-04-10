#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP

#include <vector>
#include <iostream>
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
    void tire();

    //Operateurs:
    std::ostream& operator<<(std::ostream& out);
  private:
    vector<int> t;
    int card;
};

#endif
