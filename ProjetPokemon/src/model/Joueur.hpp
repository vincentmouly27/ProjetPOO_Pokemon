#pragma once
#include "Entraineur.hpp"

class Joueur : public Entraineur {
private:
    int badges;
    int combatsGagnes;
    int combatsPerdus;
    std::vector<std::string> entraineursVaincus;

public:
    Joueur(std::string nom);

    void ajouterBadge();
    void enregistrerVictoire();
    void enregistrerDefaite();

    int getBadges() const;
    int getCombatsGagnes() const;
    int getCombatsPerdus() const;

    void ajouterVaincu(Entraineur* entraineur);
    std::vector<std::string> getVaincus() const;

};