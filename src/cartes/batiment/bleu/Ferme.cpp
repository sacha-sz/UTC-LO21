#include "Ferme.h"
#include "Partie.h"

Ferme::Ferme() :
    Batiment("Ferme",
         1,
        "Recevez une piece de la banque",
        "../../../assets/batiments/bleu/Ferme.jpg",
        Bleu,
        list<unsigned int>{2},
        "Betail"){}
///Constructeur de Ferme

void Ferme::declencher_effet(unsigned int possesseur, int bonus) const {


    //creation de l'instance de partie
    Partie * partie = Partie::get_instance();
    Joueur* joueur_actuel = partie->get_tab_joueurs()[possesseur];

    cout << "Activation de l'effet de Ferme du joueur \"" << joueur_actuel->get_nom()<<"\"" << endl;

    //On augmente de un l'argent du joueur pointe
    joueur_actuel->set_argent(joueur_actuel->get_argent() + 1);
}