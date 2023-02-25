#include "Boulangerie.h"
#include "Partie.h"

Boulangerie::Boulangerie()
        : Batiment("Boulangerie",
                   1,
                   "Recevez 1 piece de la banque.",
                   "../../../assets/batiments/Vert/Boulangerie.jpg",
                   Vert,
                   {2, 3},
                   "commerce") {}

void Boulangerie::declencher_effet(unsigned int possesseur, int bonus) const {
    /// Effet de la Boulangerie
    unsigned int j_act_index =  Partie::get_instance()->get_joueur_actuel();
    Joueur* j_actuel = Partie::get_instance()->get_tab_joueurs()[j_act_index];

    cout << "Activation de l'effet de la carte Boulangerie du joueur \"" << j_actuel->get_nom() << "\"" << endl;

    j_actuel->set_argent(j_actuel->get_argent() + 1 + bonus);
}