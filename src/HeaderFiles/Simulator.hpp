#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

// Répartition des animaux au début de la simulation dans la grille.
static const int INIT_ENTITIES[] = {20, 7};

class Simulator {
    public:
        void next();
        void start();
        void stop();
    private:
};

#endif