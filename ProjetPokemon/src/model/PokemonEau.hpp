#pragma once
#include "../model/Pokemon.hpp"

class PokemonEau : public Pokemon {
public:
    PokemonEau(std::string nom, std::string type2, int hp, std::string attaque, int degats)
        : Pokemon(nom, "Eau", type2, hp, attaque, degats) {}

    float calculerMultiplicateur(std::string typeAttaque) const override {
        if (typeAttaque == "Plante" || typeAttaque == "Électrik") return 2.0f;
        if (typeAttaque == "Feu" || typeAttaque == "Eau" || typeAttaque == "Glace" || typeAttaque == "Acier") return 0.5f;
        return 1.0f;
    }
};
