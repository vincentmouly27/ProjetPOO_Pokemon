#include "../controller/Combat.hpp"
#include "Combat.hpp"
#include <iostream>
#include <typeinfo>
#include "../model/MaitrePokemon.hpp"
#include "../model/Joueur.hpp"
#include "../model/Leader.hpp"

Combat::Combat(Entraineur* joueur, Entraineur* adversaire)
    : joueur(joueur), adversaire(adversaire) {}

void Combat::lancer() {
    std::cout << "\nLe combat commence entre " << joueur->getNom() << " et " << adversaire->getNom() << " !\n";

    while (joueur->aDesPokemons() && adversaire->aDesPokemons()) {
        Pokemon* pokeJoueur = joueur->getPokemonActif();
        Pokemon* pokeAdv = adversaire->getPokemonActif();

        std::cout << "\n>> " << joueur->getNom() << " envoie " << pokeJoueur->getNom()
                  << " (HP: " << pokeJoueur->getHP() << ")\n";
        std::cout << ">> " << adversaire->getNom() << " envoie " << pokeAdv->getNom()
                  << " (HP: " << pokeAdv->getHP() << ")\n";

        // Attaque du joueur
        float mult = pokeAdv->calculerMultiplicateur(pokeJoueur->getType1());
        int degats = static_cast<int>(pokeJoueur->getDegats() * mult);
        std::cout << pokeJoueur->getNom() << " attaque avec " << pokeJoueur->getAttaque()
                  << " (x" << mult << " = " << degats << " dégâts)\n";
        pokeAdv->subirDegats(degats);

        if (pokeAdv->estKO()) {
            std::cout << pokeAdv->getNom() << " est K.O. !\n";
            adversaire->remplacerPokemon();
            continue;
        }

        // Attaque de l'adversaire
        mult = pokeJoueur->calculerMultiplicateur(pokeAdv->getType1());
        degats = static_cast<int>(pokeAdv->getDegats() * mult);

        // Boost des maîtres Pokémon
        if (auto* maitre = dynamic_cast<MaitrePokemon*>(adversaire)) {
            degats = static_cast<int>(degats * maitre->getBoostAttaque());
        }

        std::cout << pokeAdv->getNom() << " réplique avec " << pokeAdv->getAttaque()
                  << " (x" << mult << " = " << degats << " dégâts)\n";
        pokeJoueur->subirDegats(degats);

        if (pokeJoueur->estKO()) {
            std::cout << pokeJoueur->getNom() << " est K.O. !\n";
            joueur->remplacerPokemon();
        }
    }

    // Résultat
    if (joueur->aDesPokemons()) {
        std::cout << "\n🎉 " << joueur->getNom() << " remporte le combat !\n";
        if (auto* j = dynamic_cast<Joueur*>(joueur)) {
            j->enregistrerVictoire();
            if (dynamic_cast<Leader*>(adversaire)) j->ajouterBadge();
            j->ajouterVaincu(adversaire);
        }
        

        
    } else {
        std::cout << "\n💀 " << adversaire->getNom() << " remporte le combat !\n";
        if (auto* j = dynamic_cast<Joueur*>(joueur)) {
            j->enregistrerDefaite();
        }
    }
}
