#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>  // pour std::find
#include <limits>  // pour std::numeric_limits
#include "../controller/Loader.hpp"
#include "../controller/Combat.hpp"
#include "../model/PokemonFeu.hpp"
#include "../model/PokemonEau.hpp"
#include "../model/PokemonPlante.hpp"
#include "../model/PokemonAutre.hpp"


Joueur* creerJoueurInteractif(const std::map<std::string, Pokemon*>& pokedex,
                              const std::vector<std::string>& ordrePokedex) {
    std::string nom;
    std::cout << "\nNom du nouveau joueur : ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nom);

    Joueur* nouveau = new Joueur(nom);
    int choix = -1;
    int count = 0;

    std::vector<std::string> dejaPris;

    while (count < 6) {
        std::cout << "\n--- POKEDEX ---\n";
        for (size_t i = 0; i < ordrePokedex.size(); ++i) {
            const std::string& nomPoke = ordrePokedex[i];
            const Pokemon* p = pokedex.at(nomPoke);
            std::cout << (i + 1) << ". " << p->getNom() << " (" << p->getType1();
            if (!p->getType2().empty()) std::cout << "/" << p->getType2();
            std::cout << ", HP: " << p->getHP()
                      << ", " << p->getAttaque()
                      << " [" << p->getDegats() << " dmg])";
            if (std::find(dejaPris.begin(), dejaPris.end(), p->getNom()) != dejaPris.end()) {
                std::cout << " [Déjà pris]";
            }
            std::cout << "\n";
        }
        std::cout << "0. Terminer l'équipe\n";

        std::cout << "Choix (#) : ";
        std::cin >> choix;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Entrée invalide.\n";
            continue;
        }

        if (choix == 0 && count >= 1) break;

        if (choix >= 1 && choix <= static_cast<int>(ordrePokedex.size())) {
            std::string nomChoisi = ordrePokedex[choix - 1];
            if (std::find(dejaPris.begin(), dejaPris.end(), nomChoisi) != dejaPris.end()) {
                std::cout << "Ce Pokémon est déjà dans ton équipe.\n";
                continue;
            }

            Pokemon* original = pokedex.at(nomChoisi);
            Pokemon* clone = nullptr;

            // clonage sécurisé
            if (original->getType1() == "Feu") {
                auto* feu = dynamic_cast<PokemonFeu*>(original);
                if (feu) clone = new PokemonFeu(*feu);
            } else if (original->getType1() == "Eau") {
                auto* eau = dynamic_cast<PokemonEau*>(original);
                if (eau) clone = new PokemonEau(*eau);
            } else if (original->getType1() == "Plante") {
                auto* plante = dynamic_cast<PokemonPlante*>(original);
                if (plante) clone = new PokemonPlante(*plante);
            } else {
                auto* autre = dynamic_cast<PokemonAutre*>(original);
                if (autre) clone = new PokemonAutre(*autre);
            }

            if (clone) {
                nouveau->ajouterPokemon(clone);
                dejaPris.push_back(nomChoisi);
                count++;
            } else {
                std::cout << "Erreur : clonage échoué pour " << original->getNom() << "\n";
            }
        } else {
            std::cout << "Choix invalide.\n";
        }
    }

    std::cout << "Team complète. Joueur créé avec " << count << " Pokémon !\n";
    return nouveau;
}



void afficherEquipe(Joueur* joueur) {
    std::cout << "\nÉquipe de " << joueur->getNom() << " :\n";
    int i = 1;
    for (auto* p : joueur->getEquipe()) {
        std::cout << "- " << i++ << ". " << p->getNom()
                  << " (" << p->getType1();
        if (!p->getType2().empty())
            std::cout << "/" << p->getType2();
        std::cout << "), HP: " << p->getHP()
                  << ", Attaque: " << p->getAttaque()
                  << " (" << p->getDegats() << ")\n";
    }
}

void afficherStats(Joueur* joueur) {
    std::cout << "\nStats de " << joueur->getNom() << " :\n";
    std::cout << " - Badges : " << joueur->getBadges() << "\n";
    std::cout << " - Victoires : " << joueur->getCombatsGagnes() << "\n";
    std::cout << " - Défaites : " << joueur->getCombatsPerdus() << "\n";
}
int main() {
    std::system("chcp 65001 > nul");  // Active UTF-8 dans la console Windows

    auto [pokedex, ordrePokedex] = Loader::chargerPokedex("src/controller/pokemon.csv");

    // Sélection du joueur au lancement
    std::vector<std::string> nomsJoueurs = Loader::listerJoueurs("src/controller/joueur.csv");
    int choix = -1;

    std::cout << "=== Sélection du joueur ===\n";
    for (size_t i = 0; i < nomsJoueurs.size(); ++i) {
        std::cout << i + 1 << ". " << nomsJoueurs[i] << "\n";
    }
    while (choix < 1 || choix > static_cast<int>(nomsJoueurs.size())) {
        std::cout << "Choix (#) : ";
        std::cin >> choix;
    }

    Joueur* joueur = Loader::chargerJoueurDepuisNom("src/controller/joueur.csv", nomsJoueurs[choix - 1], pokedex);
    if (!joueur) {
        std::cerr << "Erreur de chargement du joueur.\n";
        return 1;
    }

    // Menu principal
    while (choix != 0) {
        std::cout << "\n======= MENU POKÉMON =======\n";
        std::cout << "1. Afficher mon équipe\n";
        std::cout << "2. Voir mes stats\n";
        std::cout << "3. Changer l’ordre de mes Pokémon\n";
        std::cout << "4. Soigner tous mes Pokémon\n";
        std::cout << "5. Combattre un autre joueur\n";
        std::cout << "6. Combattre un Leader\n";
        std::cout << "7. Combattre un Maître Pokémon\n";
        std::cout << "8. Créer un nouveau joueur\n";
        std::cout << "9. Changer de joueur\n";
        std::cout << "10. Intéragir avec ses Pokémon\n";
        std::cout << "11. Intéragir avec les entraîneurs vaincus\n";
        std::cout << "0. Quitter\n";
        std::cout << "Choix : ";
        std::cin >> choix;

        switch (choix) {
            case 1:
                afficherEquipe(joueur);
                break;

            case 2:
                afficherStats(joueur);
                break;

            case 3: {
                std::vector<Pokemon*>& equipe = joueur->getEquipe();
                if (equipe.size() < 2) {
                    std::cout << "Tu dois avoir au moins 2 Pokémon pour changer leur ordre.\n";
                    break;
                }
                std::cout << "\n=== Équipe actuelle ===\n";
                for (size_t i = 0; i < equipe.size(); ++i) {
                    std::cout << i + 1 << ". " << equipe[i]->getNom()
                              << " (HP: " << equipe[i]->getHP()
                              << "/" << equipe[i]->getHPMax() << ")\n";
                }
                int from, to;
                std::cout << "Déplacer quel Pokémon (#) ? ";
                std::cin >> from;
                std::cout << "Le mettre en quelle position (#) ? ";
                std::cin >> to;
                if (from < 1 || from > equipe.size() || to < 1 || to > equipe.size()) {
                    std::cout << "Position invalide.\n";
                    break;
                }
                Pokemon* p = equipe[from - 1];
                equipe.erase(equipe.begin() + (from - 1));
                equipe.insert(equipe.begin() + (to - 1), p);
                std::cout << "✅ Ordre mis à jour !\n";
                break;
            }

            case 4: {
                std::string nomTemp = joueur->getNom();
                delete joueur;
                joueur = Loader::chargerJoueurDepuisNom("src/controller/joueur.csv", nomTemp, pokedex);
                std::cout << "\nToute ton équipe a été soignée !\n";
                break;
            }

            case 5: {
                auto autres = Loader::listerJoueurs("src/controller/joueur.csv");
                autres.erase(std::remove(autres.begin(), autres.end(), joueur->getNom()), autres.end());

                if (autres.empty()) {
                    std::cout << "Aucun autre joueur disponible.\n";
                    break;
                }

                std::cout << "\n=== Choisis un adversaire ===\n";
                for (size_t i = 0; i < autres.size(); ++i)
                    std::cout << i + 1 << ". " << autres[i] << "\n";

                int choixAdv;
                std::cout << "Choix (#) : ";
                std::cin >> choixAdv;

                Joueur* adversaire = Loader::chargerJoueurDepuisNom("src/controller/joueur.csv", autres[choixAdv - 1], pokedex);
                Combat combat(joueur, adversaire);
                combat.lancer();           
                delete adversaire;
                break;
            }

            case 6: {
                auto leaders = Loader::listerLeaders("src/controller/leaders.csv");
                std::cout << "\n=== Choisis un leader ===\n";
                for (size_t i = 0; i < leaders.size(); ++i)
                    std::cout << i + 1 << ". " << leaders[i].first << " (Médaille : " << leaders[i].second << ")\n";

                int choixLeader;
                std::cout << "Choix (#) : ";
                std::cin >> choixLeader;

                Leader* leader = Loader::chargerLeaderDepuisNom("src/controller/leaders.csv", leaders[choixLeader - 1].first, pokedex);
                Combat combat(joueur, leader);
                combat.lancer();
                delete leader;
                break;
            }

            case 7: {
                if (joueur->getBadges() < 3) {
                    std::cout << "⚠️ Il te faut au moins 3 badges pour affronter un Maître Pokémon.\n";
                    break;
                }

                auto maitres = Loader::listerJoueurs("src/controller/maitres.csv");
                std::cout << "\n=== Choisis un Maître Pokémon ===\n";
                for (size_t i = 0; i < maitres.size(); ++i)
                    std::cout << i + 1 << ". " << maitres[i] << "\n";

                int choixMaitre;
                std::cout << "Choix (#) : ";
                std::cin >> choixMaitre;

                MaitrePokemon* maitre = Loader::chargerMaitreDepuisNom("src/controller/maitres.csv", maitres[choixMaitre - 1], pokedex);
                Combat combat(joueur, maitre);
                combat.lancer();
                delete maitre;
                break;
            }

            case 8:
                Loader::sauvegarderJoueur(creerJoueurInteractif(pokedex, ordrePokedex), "src/controller/joueur.csv");
                break;

            case 9: {
                std::vector<std::string> noms = Loader::listerJoueurs("src/controller/joueur.csv");
                std::cout << "\n=== Nouveau joueur ===\n";
                for (size_t i = 0; i < noms.size(); ++i)
                    std::cout << i + 1 << ". " << noms[i] << "\n";

                int nvChoix;
                std::cout << "Choix (#) : ";
                std::cin >> nvChoix;

                delete joueur;
                joueur = Loader::chargerJoueurDepuisNom("src/controller/joueur.csv", noms[nvChoix - 1], pokedex);
                std::cout << "✅ Tu joues maintenant avec " << joueur->getNom() << " !\n";
                break;
            }
            case 10: {
                std::vector<Pokemon*>& equipe = joueur->getEquipe();
                if (equipe.empty()) {
                    std::cout << "Tu n'as aucun Pokémon dans ton équipe.\n";
                    break;
                }

                std::cout << "\n=== Avec quel Pokémon veux-tu interagir ? ===\n";
                for (size_t i = 0; i < equipe.size(); ++i) {
                    std::cout << i + 1 << ". " << equipe[i]->getNom()
                            << " (Type : " << equipe[i]->getType1();
                    if (!equipe[i]->getType2().empty()) std::cout << "/" << equipe[i]->getType2();
                    std::cout << ")\n";
                }

                int choixPoke = -1;
                std::cout << "Choix (#) : ";
                std::cin >> choixPoke;

                if (choixPoke < 1 || choixPoke > static_cast<int>(equipe.size())) {
                    std::cout << "Choix invalide.\n";
                    break;
                }

                Pokemon* p = equipe[choixPoke - 1];
                std::string type = p->getType1();

                std::cout << p->getNom() << " te regarde... ";

                if (type == "Feu") std::cout << "il est bouillant d'énergie ! 🔥\n";
                else if (type == "Eau") std::cout << "il semble calme comme un lac. 💧\n";
                else if (type == "Plante") std::cout << "il frémit doucement comme une feuille au vent. 🍃\n";
                else if (type == "Électrik") std::cout << "il crépite d’impatience ⚡\n";
                else if (type == "Spectre") std::cout << "il te fixe sans cligner des yeux... 👻\n";
                else std::cout << "il a l’air content de te voir. 😊\n";

                break;
            }

            case 11: {
                std::vector<std::string> vaincus = joueur->getVaincus();

                if (vaincus.empty()) {
                    std::cout << "\nTu n’as encore vaincu aucun entraîneur...\n";
                    break;
                }

                std::cout << "\n=== Entraîneurs vaincus ===\n";
                for (size_t i = 0; i < vaincus.size(); ++i) {
                    std::cout << i + 1 << ". " << vaincus[i] << "\n";
                }

                int choix = -1;
                std::cout << "Choisis un entraîneur à interpeller : ";
                std::cin >> choix;

                if (choix < 1 || choix > static_cast<int>(vaincus.size())) {
                    std::cout << "Choix invalide.\n";
                    break;
                }

                std::string cible = vaincus[choix - 1];

                std::cout << "\nComment veux-tu t’adresser à " << cible << " ?\n";
                std::cout << "1. Humble\n";
                std::cout << "2. Provocation\n";

                int ton = 0;
                std::cout << "Choix : ";
                std::cin >> ton;

                if (ton == 1) {
                    std::cout << "Bien joué " << cible << ", on s’est bien battus !\n";
                } else if (ton == 2) {
                    std::cout << "Oh " << cible << ", ça vient d'où ? T'es nul, je t'ai écrasé !\n";
                } else {
                    std::cout << "Choix invalide.\n";
                }

                break;
            }



            case 0:
                std::cout << "Au revoir, dresseur !\n";
                break;

            default:
                std::cout << "Choix invalide.\n";
        }
    }

    delete joueur;
    for (auto& pair : pokedex) delete pair.second;

    std::cout << "Appuie sur Entrée pour quitter...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}