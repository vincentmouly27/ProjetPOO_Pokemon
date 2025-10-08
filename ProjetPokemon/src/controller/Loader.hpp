#pragma once
#include <string>
#include <map>
#include "../model/Pokemon.hpp"
#include "../model/Joueur.hpp"
#include "../model/Leader.hpp"
#include "../model/MaitrePokemon.hpp"

class Loader {
public:
    static std::pair<std::map<std::string, Pokemon*>, std::vector<std::string>>
        chargerPokedex(const std::string& path);
    static std::vector<std::string> listerMaitres(const std::string& path);
    static MaitrePokemon* chargerMaitreDepuisNom(const std::string& path, const std::string& nom, const std::map<std::string, Pokemon*>& pokedex);

    static std::vector<std::pair<std::string, std::string>> listerLeaders(const std::string& path); // nom, médaille
    static Leader* chargerLeaderDepuisNom(const std::string& path, const std::string& nomLeader, const std::map<std::string, Pokemon*>& pokedex);
    static std::vector<std::string> listerJoueurs(const std::string& path);
    static Joueur* chargerJoueurDepuisNom(const std::string& path, const std::string& nomJoueur, const std::map<std::string, Pokemon*>& pokedex);
    static void sauvegarderJoueur(const Joueur* joueur, const std::string& path);

};
