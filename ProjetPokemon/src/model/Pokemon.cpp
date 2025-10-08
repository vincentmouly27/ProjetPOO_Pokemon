#include "../model/Pokemon.hpp"

Pokemon::Pokemon(std::string nom, std::string type1, std::string type2, int hp, std::string attaque, int degats)
    : nom(nom), type1(type1), type2(type2), hp(hp), attaque(attaque), degats(degats), hpMax(hp) {}

void Pokemon::subirDegats(int degatsReçus) {
    hp -= degatsReçus;
    if (hp < 0) {
        hp = 0;
    }
}

bool Pokemon::estKO() const {
    return hp <= 0;
}

std::string Pokemon::getNom() const {
    return nom;
}

int Pokemon::getHP() const {
    return hp;
}
int Pokemon::getHPMax() const {
    return hpMax;
}


int Pokemon::getDegats() const {
    return degats;
}

std::string Pokemon::getType1() const {
    return type1;
}

std::string Pokemon::getType2() const {
    return type2;
}

std::string Pokemon::getAttaque() const {
    return attaque;
}

void Pokemon::soigner() {
    hp = hpMax;
}