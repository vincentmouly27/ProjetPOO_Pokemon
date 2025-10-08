#pragma once
#include <string>

class Pokemon {
protected:
    std::string nom;
    std::string type1;
    std::string type2;
    int hp;
    int hpMax;
    std::string attaque;
    int degats;

public:
    Pokemon(std::string nom, std::string type1, std::string type2, int hp, std::string attaque, int degats);
    virtual ~Pokemon() = default;

    virtual float calculerMultiplicateur(std::string typeAttaque) const = 0; // polymorphisme
    void subirDegats(int degatsReçus);
    bool estKO() const;

    std::string getNom() const;
    int getHP() const;
    int getHPMax() const;
    int getDegats() const;
    std::string getType1() const;
    std::string getType2() const;
    std::string getAttaque() const;
    void soigner();

};
