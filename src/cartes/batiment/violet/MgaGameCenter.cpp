#include "MgaGameCenter.h"
#include "Partie.h"

MgaGameCenter::MgaGameCenter() :
        Batiment("MgaGameCenter",
                 7,
                 "Choississez un de vos etablissements qui ne soit pas de type special et activez son effet. Puis fermez le MGA game center.",
                 "../../../assets/batiments/Violet/MgaGameCenter.jpg",
                 Violet,
                 {10},
                 "special") {
    ///Constructeur de MgaGameCenter
}

void MgaGameCenter::declencher_effet(unsigned int possesseur, int bonus) const{
    /// Effet de la classe MGA Game Center
    Partie* instance = Partie::get_instance();
    const vector<Joueur *> &tab_joueurs = instance->get_tab_joueurs();
    Joueur *j_actuel = tab_joueurs[possesseur];

    // On verifie que le joueur possede au moins un batiment non violet
    map<Batiment*, unsigned int> liste_bat_bleu = j_actuel->get_liste_batiment(Bleu);
    map<Batiment*, unsigned int> liste_bat_vert = j_actuel->get_liste_batiment(Vert);
    map<Batiment*, unsigned int> liste_bat_rouge = j_actuel->get_liste_batiment(Rouge);

    if (liste_bat_bleu.empty() && liste_bat_vert.empty() && liste_bat_rouge.empty()) {
        cout << "Vous ne possedez aucun batiment non special !" << endl;
        return;
    }

    Batiment * bat = j_actuel->possede_batiment("MgaGameCenter");

    if (bat != nullptr) {
        cout << "Activation de l'effet du MgaGameCenter du joueur \"" << j_actuel->get_nom()<<"\"" << endl;

        // Selection du batiment du joueur
        Batiment *batiment = j_actuel->selectionner_batiment();
        while (batiment->get_couleur() == Violet) {
            cout << "Vous ne pouvez pas selectionner un batiment violet !" << endl;
            batiment = j_actuel->selectionner_batiment();
        }

        batiment->declencher_effet(possesseur, bonus);

        j_actuel->fermer_batiment(bat);
    }
}
