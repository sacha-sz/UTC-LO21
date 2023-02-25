#include "ChaineTelevision.h"
#include "Partie.h"

using namespace std;

ChaineTelevision::ChaineTelevision():
    Batiment("ChaineTelevision",
             7,
             "Recevez 5 pieces du joueur de votre choix",
             "../../../assets/batiments/Violet/Chaine-de-television.jpg",
             Violet,
             list<unsigned int>{6},
             "special") {
    ///Constructeur de Chaine de Television
}

void ChaineTelevision::declencher_effet(unsigned int possesseur, int bonus) const{
    /// Effet de ChaineTelevision
    // Variables utiles
    const vector<Joueur*> tab_joueurs = Partie::get_instance()->get_tab_joueurs();
    Joueur* j_actuel = tab_joueurs[possesseur];
    cout << "Activation de l'effet de la Chaine de Television du joueur \"" << j_actuel->get_nom()<<"\"" << endl;

    // Choix de joueur
    unsigned int j_echange = Partie::selectionner_joueur(tab_joueurs, possesseur);

    Partie::get_instance()->transfert_argent(j_echange, possesseur, 5);

}

