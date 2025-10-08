#pragma once
#include "Entraineur.hpp"

class MaitrePokemon : public Entraineur {
public:
    MaitrePokemon(std::string nom);

    // Multiplie tous les dégâts de ses Pokémon par 1.25
    float getBoostAttaque() const;
};
