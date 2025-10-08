#pragma once
#include "Entraineur.hpp"

class Leader : public Entraineur {
private:
    std::string gymnase;
    std::string medaille;

public:
    Leader(std::string nom, std::string gymnase, std::string medaille);
    ~Leader() override;
    std::string getGymnase() const;
    std::string getMedaille() const;
};
