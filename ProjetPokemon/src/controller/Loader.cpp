#include "../controller/Loader.hpp"
#include "../model/PokemonFeu.hpp"
#include "../model/PokemonEau.hpp"
#include "../model/PokemonPlante.hpp"
#include "../model/PokemonAutre.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

static Pokemon* creerPokemonDepuisType(const std::string& nom, const std::string& type1, const std::string& type2, int hp, const std::string& attaque, int degats) {
    if (type1 == "Feu") return new PokemonFeu(nom, type2, hp, attaque, degats);
    if (type1 == "Eau") return new PokemonEau(nom, type2, hp, attaque, degats);
    if (type1 == "Plante") return new PokemonPlante(nom, type2, hp, attaque, degats);
    return nullptr; // pour ce test, on gère 3 types seulement
}

std::pair<std::map<std::string, Pokemon*>, std::vector<std::string>>
Loader::chargerPokedex(const std::string& path) {
    std::map<std::string, Pokemon*> pokedex;
    std::vector<std::string> ordre;

    std::ifstream file(path);
    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string nom, type1, type2, hpStr, attaque, degatsStr;
        std::getline(ss, nom, ',');
        std::getline(ss, type1, ',');
        std::getline(ss, type2, ',');
        std::getline(ss, hpStr, ',');
        std::getline(ss, attaque, ',');
        std::getline(ss, degatsStr, ',');

        int hp = std::stoi(hpStr);
        int degats = std::stoi(degatsStr);

        Pokemon* p = nullptr;
        if (type1 == "Feu")
            p = new PokemonFeu(nom, type2, hp, attaque, degats);
        else if (type1 == "Eau")
            p = new PokemonEau(nom, type2, hp, attaque, degats);
        else if (type1 == "Plante")
            p = new PokemonPlante(nom, type2, hp, attaque, degats);
        else 
            p = new PokemonAutre(nom, type1, type2, hp, attaque, degats);

        if (p) {
            pokedex[nom] = p;
            ordre.push_back(nom);
        }
    }

    return {pokedex, ordre};
}




#include <set>

std::vector<std::string> Loader::listerJoueurs(const std::string& path) {
    std::ifstream file(path);
    std::string line;
    std::set<std::string> noms;

    bool premiereLigne = true;
    while (std::getline(file, line)) {
        if (premiereLigne) {
            premiereLigne = false;
            continue; // skip header
        }

        std::stringstream ss(line);
        std::string nom;
        std::getline(ss, nom, ',');
        noms.insert(nom);
    }

    return std::vector<std::string>(noms.begin(), noms.end());
}


Joueur* Loader::chargerJoueurDepuisNom(const std::string& path, const std::string& nomJoueur, const std::map<std::string, Pokemon*>& pokedex) {
    std::ifstream file(path);
    std::string line;
    std::getline(file, line); // ignorer l'en-tête
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string nom;
        std::getline(ss, nom, ',');
        if (nom != nomJoueur) continue;

        Joueur* joueur = new Joueur(nom);
        std::string pokeNom;
        while (std::getline(ss, pokeNom, ',')) {
            if (pokedex.count(pokeNom)) {
                Pokemon* original = pokedex.at(pokeNom);
                Pokemon* clone = nullptr;

                if (original->getType1() == "Feu")
                    clone = new PokemonFeu(*dynamic_cast<PokemonFeu*>(original));
                else if (original->getType1() == "Eau")
                    clone = new PokemonEau(*dynamic_cast<PokemonEau*>(original));
                else if (original->getType1() == "Plante")
                    clone = new PokemonPlante(*dynamic_cast<PokemonPlante*>(original));
                else
                    clone = new PokemonAutre(*dynamic_cast<PokemonAutre*>(original));

                if (clone)
                    joueur->ajouterPokemon(clone);
            }
        }
        return joueur;
    }
    return nullptr;
}

void Loader::sauvegarderJoueur(const Joueur* joueur, const std::string& path) {
    std::ofstream file(path, std::ios::app); // mode append

    if (!file) {
        std::cerr << "Erreur : impossible d'ouvrir " << path << " pour écrire.\n";
        return;
    }

    file << joueur->getNom();
    for (Pokemon* p : joueur->getEquipe()) {
        file << "," << p->getNom();
    }
    file << "\n";
}
std::vector<std::pair<std::string, std::string>> Loader::listerLeaders(const std::string& path) {
    std::ifstream file(path);
    std::string line;
    std::vector<std::pair<std::string, std::string>> leaders;

    bool premiereLigne = true;
    while (std::getline(file, line)) {
        if (premiereLigne) {
            premiereLigne = false;
            continue;
        }

        std::stringstream ss(line);
        std::string nom, gymnase, medaille;
        std::getline(ss, nom, ',');
        std::getline(ss, gymnase, ',');
        std::getline(ss, medaille, ',');

        leaders.emplace_back(nom, medaille);
    }

    return leaders;
}


Leader* Loader::chargerLeaderDepuisNom(const std::string& path, const std::string& nomLeader, const std::map<std::string, Pokemon*>& pokedex) {
    std::ifstream file(path);
    std::string line;

    std::getline(file, line); // ignorer l'en-tête
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string nom, gymnase, medaille;
        std::getline(ss, nom, ',');
        std::getline(ss, gymnase, ',');
        std::getline(ss, medaille, ',');

        if (nom != nomLeader) continue;

        Leader* leader = new Leader(nom, gymnase, medaille);
        std::string pokeNom;
        while (std::getline(ss, pokeNom, ',')) {
            if (pokedex.count(pokeNom)) {
                Pokemon* original = pokedex.at(pokeNom);
                Pokemon* clone = nullptr;

                if (original->getType1() == "Feu")
                    clone = new PokemonFeu(*dynamic_cast<PokemonFeu*>(original));
                else if (original->getType1() == "Eau")
                    clone = new PokemonEau(*dynamic_cast<PokemonEau*>(original));
                else if (original->getType1() == "Plante")
                    clone = new PokemonPlante(*dynamic_cast<PokemonPlante*>(original));
                else
                    clone = new PokemonAutre(*dynamic_cast<PokemonAutre*>(original));

                if (clone) leader->ajouterPokemon(clone);
            }
        }

        return leader;
    }

    return nullptr;
}

std::vector<std::string> Loader::listerMaitres(const std::string& path) {
    std::ifstream file(path);
    std::string line;
    std::set<std::string> noms;

    bool premiereLigne = true;
    while (std::getline(file, line)) {
        if (premiereLigne) {
            premiereLigne = false;
            continue;
        }
        std::stringstream ss(line);
        std::string nom;
        std::getline(ss, nom, ',');
        noms.insert(nom);
    }

    return std::vector<std::string>(noms.begin(), noms.end());
}

MaitrePokemon* Loader::chargerMaitreDepuisNom(const std::string& path, const std::string& nomRecherche, const std::map<std::string, Pokemon*>& pokedex) {
    std::ifstream file(path);
    std::string line;
    std::getline(file, line); // ignorer entête

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string nom;
        std::getline(ss, nom, ',');
        if (nom != nomRecherche) continue;

        MaitrePokemon* maitre = new MaitrePokemon(nom);
        std::string pokeNom;
        while (std::getline(ss, pokeNom, ',')) {
            if (pokedex.count(pokeNom)) {
                Pokemon* original = pokedex.at(pokeNom);
                Pokemon* clone = nullptr;

                if (original->getType1() == "Feu")
                    clone = new PokemonFeu(*dynamic_cast<PokemonFeu*>(original));
                else if (original->getType1() == "Eau")
                    clone = new PokemonEau(*dynamic_cast<PokemonEau*>(original));
                else if (original->getType1() == "Plante")
                    clone = new PokemonPlante(*dynamic_cast<PokemonPlante*>(original));
                else
                    clone = new PokemonAutre(*dynamic_cast<PokemonAutre*>(original));

                if (clone) maitre->ajouterPokemon(clone);
            }
        }

        return maitre;
    }

    return nullptr;
}
