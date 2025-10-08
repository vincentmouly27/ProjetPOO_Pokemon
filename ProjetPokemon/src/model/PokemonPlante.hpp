#pragma once
#include "../model/Pokemon.hpp"

class PokemonPlante : public Pokemon {
public:
    PokemonPlante(std::string nom, std::string type2, int hp, std::string attaque, int degats)
        : Pokemon(nom, "Plante", type2, hp, attaque, degats) {}

    float calculerMultiplicateur(std::string typeAttaque) const override {
        if (typeAttaque == "Feu" || typeAttaque == "Glace" || typeAttaque == "Poison" || typeAttaque == "Vol" || typeAttaque == "Insecte") return 2.0f;
        if (typeAttaque == "Eau" || typeAttaque == "Sol" || typeAttaque == "Roche") return 0.5f;
        return 1.0f;
    }
};
