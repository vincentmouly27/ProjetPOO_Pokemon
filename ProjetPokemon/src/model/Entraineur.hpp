#pragma once
#include <string>
#include <vector>
#include "Pokemon.hpp"

class Entraineur {
protected:
    std::string nom;
    std::vector<Pokemon*> equipe;

public:
    Entraineur(std::string nom);
    virtual ~Entraineur();

    void ajouterPokemon(Pokemon* p);
    Pokemon* getPokemonActif();
    void remplacerPokemon();
    bool aDesPokemons() const;

    std::string getNom() const;
    std::vector<Pokemon*>& getEquipe();
    const std::vector<Pokemon*>& getEquipe() const;

};
