#include "MaitrePokemon.hpp"

MaitrePokemon::MaitrePokemon(std::string nom)
    : Entraineur(nom) {}

float MaitrePokemon::getBoostAttaque() const {
    return 1.25f;
}
