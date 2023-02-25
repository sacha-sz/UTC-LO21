#include "TourRadio.h"
#include "Partie.h"

TourRadio::TourRadio() :
    Monument(APRES,
             "TourRadio",
             22,
             "Une fois par tour vous pouvez relancer vos des",
             "../../assets/monuments/TourRadio-travaux.png") {
    /// Constructeur de TourRadio
}

void TourRadio::declencher_effet(unsigned int possesseur, int bonus) const {
    Joueur *joueur = Partie::get_instance()->get_tab_joueurs()[possesseur];
    Partie *partie = Partie::get_instance();
    int choix = -1;

    if (partie->get_tab_joueurs()[possesseur]->get_est_ia()) {
        choix = rand() % 8;
    }
    else {
        while (choix != 0 && choix != 1) {
            cout << "Voulez-vous relancer vos des ? (0 : non, 1 : oui)" << endl;
            cin >> choix;
        }
    }

    if(choix == 1) {
        cout << "Activation de l'effet de la Tour radio du joueur \"" << joueur->get_nom() << "\"" << endl;
        partie->set_de_1(Partie::lancer_de());
        if (partie->get_de_2() != 0) {
            partie->set_de_2(Partie::lancer_de());
        }
    }

}

void TourRadio::activer(){
    set_image("../../assets/monuments/TourRadio-active.png");
}

void TourRadio::desactiver(){
    set_image("../../assets/monuments/TourRadio-travaux.png");
}