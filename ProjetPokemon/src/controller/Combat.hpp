#pragma once
#include "../model/Entraineur.hpp"
#include "../model/MaitrePokemon.hpp"

class Combat {
private:
    Entraineur* joueur;
    Entraineur* adversaire;

public:
    Combat(Entraineur* joueur, Entraineur* adversaire);
    void lancer();
};
