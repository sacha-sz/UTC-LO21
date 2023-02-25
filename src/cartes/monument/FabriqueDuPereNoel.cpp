#include "FabriqueDuPereNoel.h"
#include "Partie.h"

FabriqueDuPereNoel::FabriqueDuPereNoel() :
        Monument(APRES,
                 "FabriqueDuPereNoel",
                 0,
                 "Si le jet de de est casse vous gagnez 3 pieces",
                 "../../assets/monuments/FabriqueDuPereNoel.png") {
    /// Constructeur de Centre commercial
}

void FabriqueDuPereNoel::declencher_effet(unsigned int possesseur, int bonus) const {
    Partie *partie = Partie::get_instance();
    Joueur *joueur = partie->get_tab_joueurs()[possesseur];

    cout << "Activation de l'effet de la Fabrique du Pere Noel du joueur \"" << joueur->get_nom() << "\"" << endl;

    joueur->set_argent(joueur->get_argent() + 3);
    partie->set_de_1(Partie::lancer_de());
    if (partie->get_de_2() != 0) {
        partie->set_de_2(Partie::lancer_de());
    }
}

void FabriqueDuPereNoel::activer() {
    set_image("../../assets/monuments/FabriqueDuPereNoel.png");
}

void FabriqueDuPereNoel::desactiver() {
    set_image("../../assets/monuments/FabriqueDuPereNoel.png");
}