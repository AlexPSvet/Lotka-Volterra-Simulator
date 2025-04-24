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

string Console::toString(Type type) {
    switch (type) {
        case Type::rabbit:
            return "rabbit";
        case Type::fox:
            return "fox";
    }
    return "NaN";
}

EntityParams Console::getParams() {
    EntityParams params;

    vector<Type> types = ALL_TYPES;
    for (Type type : types) {
        string typeStr = toString(type);
        cout << " --- CONFIGURATION POUR LE TYPE " << typeStr << " ---" << endl;
        int entityNumberStart, foodToReproduce, foodValue, probReproduce, minFreeCases;
        cout << "Saisir le nombre d'animals initiales : ";
        cin >> entityNumberStart;
        cout << "Saisir la valeur minimale de nourriture pour se reproduire : ";
        cin >> foodToReproduce;
        cout << "Saisir la valeur en nourriture : ";
        cin >> foodValue;
        cout << "Saisir la probabilité pour se reproduite (En pourcentage) : ";
        cin >> probReproduce;
        cout << "Saisir le nombre minimale de cases vides aux alentours de l'entité pour se reproduire : ";
        cin >> minFreeCases;
        
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

        TypeParams typeParams(entityNumberStart, foodToReproduce, foodValue, probReproduce, foodValue, probReproduce, preys);
        params.addType(type, typeParams);
        cout << " --- CONFIGURATION DE " << typeStr << " ENREGISTRÉ! ---" << endl;
    }

    return params;
}

void Console::start() {
    EntityParams params = getParams();
    game = new Game(params, TAILLE_GRID);

    game->start();
    cout << game->getPopulation().getEntities().size() << " ENTITIES." << endl;

    cout << "GAME START :" << endl;
    print();
    cout << "NEXT STEPS :" << endl;

    for (int i = 0; i < 50; i++) {
        game->moveType(Type::rabbit);
        game->moveType(Type::fox);
        print();
        cout << game->getPopulation().getEntities().size() << " ENTITIES." << endl;
    }
    
    cout << "EXIT..." << endl;

    game->stop();
    delete game;
}