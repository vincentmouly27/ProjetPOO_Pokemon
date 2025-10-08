#include "Joueur.hpp"
#include <iostream>
#include <algorithm>  // pour std::find
#include "Leader.hpp"
#include "MaitrePokemon.hpp"



Joueur::Joueur(std::string nom)
    : Entraineur(nom), badges(0), combatsGagnes(0), combatsPerdus(0) {}

void Joueur::ajouterBadge() {
    badges++;
}

void Joueur::enregistrerVictoire() {
    combatsGagnes++;
}

void Joueur::enregistrerDefaite() {
    combatsPerdus++;
}

int Joueur::getBadges() const {
    return badges;
}

int Joueur::getCombatsGagnes() const {
    return combatsGagnes;
}

int Joueur::getCombatsPerdus() const {
    return combatsPerdus;
}

void Joueur::ajouterVaincu(Entraineur* entraineur) {
    std::string nom = entraineur->getNom();
    std::string type;

    if (dynamic_cast<Leader*>(entraineur)) type = "Leader";
    else if (dynamic_cast<MaitrePokemon*>(entraineur)) type = "Maître";
    else if (dynamic_cast<Joueur*>(entraineur)) type = "Joueur";
    else type = "Inconnu";

    std::string identite = nom + " (" + type + ")";

    if (std::find(entraineursVaincus.begin(), entraineursVaincus.end(), identite) == entraineursVaincus.end()) {
        entraineursVaincus.push_back(identite);
    }
}
std::vector<std::string> Joueur::getVaincus() const {
    return entraineursVaincus;
}

