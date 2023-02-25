#include "Stade.h"
#include "Partie.h"

Stade::Stade() :
Batiment("Stade",
         6,
         "Recevez 2 pieces de la part de chaque autre joueur",
         "../../../assets/batiments/Violet/Stade.jpg",
         Violet,
         list<unsigned int>{6},
         "special") {
    ///Constructeur de Stade
}

void Stade::declencher_effet(unsigned int possesseur, int bonus) const{
    /// Effet de la classe Stade
    cout << "Activation de l'effet du stade." << endl;

    // Variables utiles
    const vector<Joueur*> tab_joueurs = Partie::get_instance()->get_tab_joueurs();
    Joueur* j_actuel = tab_joueurs[possesseur];
    cout << "Activation de l'effet du Stade du joueur \"" << j_actuel->get_nom()<<"\"" << endl;

    // Pour chaque joueur de la partie
    for (int i = 0; i < tab_joueurs.size(); i++) {
        // Si le joueur est different du joueur actuel
        if (i != possesseur) {
            Partie::get_instance()->transfert_argent(i, possesseur, 2);
        }
    }
    cout << j_actuel->get_nom() << "possede maintenant " << j_actuel->get_argent() << " credits." <<endl;
}