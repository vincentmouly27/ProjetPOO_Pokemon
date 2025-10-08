#include "Entraineur.hpp"

Entraineur::Entraineur(std::string nom) : nom(nom) {}

Entraineur::~Entraineur() {
    // Libération de la mémoire pour chaque Pokémon
    for (Pokemon* p : equipe) {
        delete p;
    }
    equipe.clear();
}

void Entraineur::ajouterPokemon(Pokemon* p) {
    if (equipe.size() < 6) {
        equipe.push_back(p);
    }
}

Pokemon* Entraineur::getPokemonActif() {
    if (!equipe.empty()) {
        return equipe.front();
    }
    return nullptr;
}

void Entraineur::remplacerPokemon() {
    if (!equipe.empty()) {
        delete equipe.front();
        equipe.erase(equipe.begin());
    }
}

bool Entraineur::aDesPokemons() const {
    return !equipe.empty();
}

std::string Entraineur::getNom() const {
    return nom;
}

std::vector<Pokemon*>& Entraineur::getEquipe() {
    return equipe;
}
const std::vector<Pokemon*>& Entraineur::getEquipe() const {
    return equipe;
}



