#include "Leader.hpp"

Leader::Leader(std::string nom, std::string gymnase, std::string medaille)
    : Entraineur(nom), gymnase(gymnase), medaille(medaille) {}

Leader::~Leader() {
    // Le destructeur d'Entraineur s'occupe déjà de libérer les Pokémon
}

std::string Leader::getGymnase() const {
    return gymnase;
}

std::string Leader::getMedaille() const {
    return medaille;
}
