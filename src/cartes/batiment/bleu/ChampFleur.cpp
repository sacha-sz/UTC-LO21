#include "ChampFleur.h"
#include "Partie.h"

ChampFleur::ChampFleur() :
    Batiment("ChampFleur",
         2,
        "Recevez une piece de la banque",
        "../../../assets/batiments/bleu/ChampFleur.jpg",
        Bleu,
        list<unsigned int>{4},
        "Champ"){}
///Constructeur de ChampFleur

void ChampFleur::declencher_effet(unsigned int possesseur, int bonus) const {

    //creation de l'instance de partie
    Partie * partie = Partie::get_instance();
    Joueur* joueur_actuel = partie->get_tab_joueurs()[possesseur];

    cout << "Activation de l'effet du ChampFleur du joueur \"" << joueur_actuel->get_nom()<<"\"" << endl;

    //On augmente de un l'argent du joueur actuel
    unsigned int argent = joueur_actuel->get_argent();
    joueur_actuel->set_argent(argent + 1);
}