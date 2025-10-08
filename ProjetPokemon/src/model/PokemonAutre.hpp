#pragma once
#include "../model/Pokemon.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>

class PokemonAutre : public Pokemon {
public:
    PokemonAutre(std::string nom, std::string type1, std::string type2, int hp, std::string attaque, int degats)
        : Pokemon(nom, type1, type2, hp, attaque, degats) {}

    float calculerMultiplicateur(std::string typeAttaque) const override {
        return std::max(multiplicateurPourUnType(type1, typeAttaque),
                        type2.empty() ? 1.0f : multiplicateurPourUnType(type2, typeAttaque));
    }

private:
    float multiplicateurPourUnType(const std::string& defense, const std::string& attaque) const {
        static const std::unordered_map<std::string, std::vector<std::string>> faiblesse = {
            {"Feu", {"Eau", "Roche", "Sol"}},
            {"Eau", {"Plante", "Électrik"}},
            {"Plante", {"Feu", "Glace", "Poison", "Vol", "Insecte"}},
            {"Électrik", {"Sol"}},
            {"Glace", {"Feu", "Combat", "Roche", "Acier"}},
            {"Combat", {"Vol", "Psy", "Fée"}},
            {"Poison", {"Sol", "Psy"}},
            {"Sol", {"Eau", "Plante", "Glace"}},
            {"Vol", {"Électrik", "Glace", "Roche"}},
            {"Psy", {"Insecte", "Spectre", "Ténèbres"}},
            {"Insecte", {"Feu", "Vol", "Roche"}},
            {"Roche", {"Eau", "Plante", "Combat", "Sol", "Acier"}},
            {"Spectre", {"Spectre", "Ténèbres"}},
            {"Dragon", {"Glace", "Dragon", "Fée"}},
            {"Ténèbres", {"Combat", "Insecte", "Fée"}},
            {"Acier", {"Feu", "Combat", "Sol"}},
            {"Fée", {"Poison", "Acier"}}
        };

        static const std::unordered_map<std::string, std::vector<std::string>> resistance = {
            {"Feu", {"Plante", "Glace", "Insecte", "Acier", "Fée"}},
            {"Eau", {"Feu", "Eau", "Glace", "Acier"}},
            {"Plante", {"Eau", "Sol", "Roche"}},
            {"Électrik", {"Vol", "Acier", "Électrik"}},
            {"Glace", {"Glace"}},
            {"Combat", {"Roche", "Insecte", "Ténèbres"}},
            {"Poison", {"Plante", "Fée", "Combat", "Poison", "Insecte"}},
            {"Sol", {"Poison", "Roche"}},
            {"Vol", {"Plante", "Combat", "Insecte"}},
            {"Psy", {"Combat", "Psy"}},
            {"Insecte", {"Plante", "Combat", "Sol"}},
            {"Roche", {"Feu", "Vol", "Poison", "Normal"}},
            {"Spectre", {"Poison", "Insecte"}},
            {"Dragon", {"Feu", "Eau", "Électrik", "Plante"}},
            {"Ténèbres", {"Spectre", "Psy", "Ténèbres"}},
            {"Acier", {"Normal", "Plante", "Glace", "Vol", "Psy", "Insecte", "Roche", "Dragon", "Acier", "Fée"}},
            {"Fée", {"Combat", "Insecte", "Ténèbres", "Dragon"}}
        };

        if (faiblesse.count(defense) && std::find(faiblesse.at(defense).begin(), faiblesse.at(defense).end(), attaque) != faiblesse.at(defense).end())
            return 2.0f;

        if (resistance.count(defense) && std::find(resistance.at(defense).begin(), resistance.at(defense).end(), attaque) != resistance.at(defense).end())
            return 0.5f;

        return 1.0f;
    }
};
