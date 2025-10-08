#pragma once
#include "../model/Pokemon.hpp"

class PokemonFeu : public Pokemon {
public:
    PokemonFeu(std::string nom, std::string type2, int hp, std::string attaque, int degats)
        : Pokemon(nom, "Feu", type2, hp, attaque, degats) {}

    float calculerMultiplicateur(std::string typeAttaque) const override {
        if (typeAttaque == "Eau" || typeAttaque == "Roche" || typeAttaque == "Sol") return 2.0f;
        if (typeAttaque == "Plante" || typeAttaque == "Glace" || typeAttaque == "Insecte" || typeAttaque == "Acier" || typeAttaque == "Fée") return 0.5f;
        return 1.0f;
    }
};