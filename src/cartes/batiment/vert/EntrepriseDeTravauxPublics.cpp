#include "EntrepriseDeTravauxPublics.h"
#include "Partie.h"

EntrepriseDeTravauxPublics::EntrepriseDeTravauxPublics()
        : Batiment("EntrepriseDeTravauxPublics",
                   2,
                   "Vous devez retourner une de vos cartes monuments sur sa face en travaux. Ce faisant, vous recevez 8 pieces de la banque.",
                   "../../../assets/batiments/Vert/Entreprise-de-travaux-publics.jpg",
                   Vert,
                   {4},
                   "entreprise") {}

void EntrepriseDeTravauxPublics::declencher_effet(unsigned int possesseur, int bonus) const {
    /// Effet de l'EntrepriseDeTravauxPublics

    /// DESACTIVATION DU MONUMENT

    Joueur* j_actuel = Partie::get_instance()->get_tab_joueurs()[possesseur];

    vector<Monument*> monuments_jouables = j_actuel->get_monument_jouables();
    for (auto mon : monuments_jouables) {
        if (mon->get_nom() == "HotelDeVille" || mon->get_nom() == "FabriqueDuPereNoel") {
            auto it = find(monuments_jouables.begin(), monuments_jouables.end(), mon);
            if (it != monuments_jouables.end()) {
                monuments_jouables.erase(it);
            }
        }
    }

    if (monuments_jouables.empty()) {
        cout << "Le joueur n'a pas de monument jouable." << endl;
        return;
    }

    cout << "Activation de l'effet de la carte Entreprise de travaux publics du joueur \"" << j_actuel->get_nom() << "\"" << endl;

    int choix = -1;
    if (j_actuel->get_est_ia()){
        choix = rand() % monuments_jouables.size();
    } else {
        cout << "Choisissez un monument jouable a retourner : " << endl;
        for (unsigned int i = 0; i < monuments_jouables.size(); i++) {
            cout << i << " : " << monuments_jouables[i]->get_nom() << endl;
        }
        while (choix < 0 || choix >= monuments_jouables.size()) {
            cout << "Votre choix : ";
            cin >> choix;
        }
    }

    // On desactive le monument
    j_actuel->desactiver_monument(monuments_jouables[choix]);

    /// TRANSACTION AVEC LA BANQUE
    // On donne 8 pieces au joueur actuel
    j_actuel->set_argent(j_actuel->get_argent() + 8 + bonus);
}