#include "HotelDeVille.h"
#include "Partie.h"

HotelDeVille::HotelDeVille() :
    Monument(APRES,
             "HotelDeVille",
             0,
             "Avant de construire, si vous n'avez pas d'argent vous recevez 1 piece de la banque.",
             "../../assets/monuments/HotelDeVille.jpg") {
    /// Constructeur de HotelDeVille
}

void HotelDeVille::declencher_effet(unsigned int possesseur, int bonus) const {
    Partie * partie = Partie::get_instance();
    Joueur * joueur = partie->get_tab_joueurs()[possesseur];

    if (joueur->get_argent() == 0) {
        cout << "Activation de l'effet de l'Hotel de ville du joueur \"" << joueur->get_nom() << "\"" << endl;
        joueur->set_argent(1);
    }
}

void HotelDeVille::activer() {
    set_image("../../assets/monuments/HotelDeVille.jpg");
}

void HotelDeVille::desactiver() {
    set_image("../../assets/monuments/HotelDeVille.jpg");
}