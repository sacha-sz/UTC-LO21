#include "ParcAttraction.h"
#include "Partie.h"

ParcAttraction::ParcAttraction() :
    Monument(APRES,
             "ParcAttraction",
             16,
             "Si le jet de de est un double vous pouvez rejouer",
             "../../assets/monuments/ParcAttraction-travaux.png") {
    /// Constructeur de ParcAttraction
}

void ParcAttraction::declencher_effet(unsigned int possesseur, int bonus) const {
    Joueur *joueur = Partie::get_instance()->get_tab_joueurs()[possesseur];

    if (Partie::get_instance()->get_de_1() == Partie::get_instance()->get_de_2()) {
        cout << "Activation de l'effet du Parc d'attractions du joueur \"" << joueur->get_nom() << "\"" << endl;
        Partie::get_instance()->rejouer_tour();
    }
}

void ParcAttraction::activer(){
    set_image("../../assets/monuments/ParcAttraction-active.png");
}

void ParcAttraction::desactiver(){
    set_image("../../assets/monuments/ParcAttraction-travaux.png");
}