#include "Console.hpp"

void Console::print() {
    Grid& grid = game->getPopulation().getGrid();
    int lenght = grid.getGridLenght();
    for (int y = 0; y < lenght; y++) {
        for (int x = 0; x < lenght; x++) {
            int entityId = grid[y * lenght + x];
            if (entityId == -1) {
                cout << "-";
            } else {
                Entity* entity = game->getPopulation().get(entityId);
                entity->operator<<(cout);
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Console::drawGrid() {
    Grid& grid = game->getPopulation().getGrid();
    int length = grid.getGridLenght();
    const int PIXEL_SIZE = 100;         

    int imgWidth = length * PIXEL_SIZE;
    int imgHeight = length * PIXEL_SIZE;

    ostringstream filename;
    filename << "img" << setfill('0') << setw(3) << compteurFichier << ".ppm";
    compteurFichier++;
    cout << "Ecriture dans le fichier : " << filename.str() << endl;

    ofstream fic(filename.str(), ios::out | ios::trunc);
    fic << "P3" << endl << imgWidth << " " << imgHeight << endl << "255" << endl;

    for (int y = 0; y < length; y++) {
        for (int py = 0; py < PIXEL_SIZE; py++) {
            for (int x = 0; x < length; x++) {
                int entityId = grid[y * length + x];
                int r, g, b;

                if (entityId == -1) {
                    r = g = b = 255;
                } else {
                    Entity* entity = game->getPopulation().get(entityId);
                    Type t = entity->getType();

                    switch (t) {
                        case Type::rabbit: r = 0; g = 108; b = 255; break; // vert
                        case Type::fox: r = 255; g = 0; b = 0; break; // rouge
                        default: r = g = b = 128; break; // gris
                    }
                }

                for (int px = 0; px < PIXEL_SIZE; px++) {
                    fic << r << " " << g << " " << b << " ";
                }
            }

            fic << endl;
        }
    }
    
    fic.close();
}

string Console::toString(Type type) {
    switch (type) {
        case Type::rabbit:
            return "rabbit";
        case Type::fox:
            return "fox";
    }
    return "NaN";
}

void Console::checkInput(string text, int& reponse) {
    while (true) {
        cout << text;
        if (cin >> reponse) {
            break;
        } else {
            cout << "Entrée non valide. Saisir un nombre." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Console::setParams() {
    EntityParams params;

    vector<Type> types = ALL_TYPES;
    for (Type type : types) {
        string typeStr = toString(type);
        cout << " --- CONFIGURATION POUR LE TYPE " << typeStr << " ---" << endl;
        int entityNumberStart, foodToReproduce, foodMin, foodMax, foodPerMove, foodValue, probReproduce, minFreeCases;
        checkInput("Saisir le nombre d'animals initiales : ", entityNumberStart);
        checkInput("Saisir la valeur minimale de nourriture de l'entité : ", foodMin);
        checkInput("Saisir la valeur maximale de nourriture de l'entité : ", foodMax);
        checkInput("Saisir la valeur minimale de nourriture pour se reproduire : ", foodToReproduce);
        checkInput("Saisir la nourriture donnée par mouvement : ", foodPerMove);
        checkInput("Saisir la valeur en nourriture : ", foodValue);
        checkInput("Saisir la probabilité pour se reproduite (En pourcentage) : ", probReproduce);
        checkInput("Saisir le nombre minimale de cases vides aux alentours de l'entité pour se reproduire : ", minFreeCases);
        
        vector<Type> preys;
        while (true) {
            cout << "Liste entités : " << endl;
            for (int i = 0; i < types.size(); i++) {
                Type preyType = types[i];
                cout << i+1 << ". " << toString(preyType) << endl;
            }
            cout << "Saisir un numéro de type pour ajouter comme proie de " << typeStr << " (ou -1 pour continuer) : ";
            int choiseIndex;
            cin >> choiseIndex;
            if (choiseIndex == -1) {
                break;
            }
            choiseIndex--;
            Type choix = types[choiseIndex];
            preys.push_back(choix);
            cout << "Le type " << toString(choix) << " est enregistré comme proie de " << typeStr << "!" << endl;
        }

        TypeParams typeParams(entityNumberStart, foodMin, foodMax, foodToReproduce, foodPerMove, foodValue, probReproduce, minFreeCases, preys);
        params.addType(type, typeParams);
        cout << " --- CONFIGURATION DE " << typeStr << " ENREGISTRÉ! ---" << endl;
    }

    game = new Game(params, TAILLE_GRID);
}

void Console::setGame(Game* game) {
    this->game = game;
}

void Console::simulation() {
    game->start();
    while (true) {
        print();
        drawGrid();
        int nextMove;
        cout << "Appuyer -1 pour redémarrer la simulation, -2 pour sortir, ou un autre nombre sinon : ";
        cin >> nextMove;
        if (nextMove == -1) {
            game->stop();
            game->start();
            continue;
        } else if (nextMove == -2) {
            game->stop();
            return;
        }
        game->next();
    }
}

void Console::start() {
    // Default params
    EntityParams params;

    TypeParams rabbitParams(
        20,   // entityInit
        5,   // foodMin
        20,   // foodMax
        15,   // foodToReproduceLevel
        1,    // foodPerMove
        6,    // foodValue
        45,   // probReproduce
        3,    // minFreeBirth
        {}    // preys
    );

    TypeParams foxParams(
        20,               // entityInit
        5,                // foodMin
        20,               // foodMax
        10,               // foodToReproduceLevel
        -1,               // foodPerMove
        15,               // foodValue
        80,               // probReproduce
        4,                // minFreeBirth
        {Type::rabbit}    // preys
    );

    params.addType(Type::rabbit, rabbitParams);
    params.addType(Type::fox, foxParams);
    
    game = new Game(params, TAILLE_GRID);

    // Custom params
    // setParams();

    simulation();

    system("convert -delay 10 -loop 0 *.ppm animation.gif");
    system("rm *.ppm");

    stop();
}

void Console::stop() {
    delete game;
}

Game* Console::getGame() {
    return game;
}