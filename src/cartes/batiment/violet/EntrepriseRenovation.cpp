#include "EntrepriseRenovation.h"
#include "Partie.h"

EntrepriseRenovation::EntrepriseRenovation() :
        Batiment("EntrepriseRenovation",
                 1,
                 "Choississez un de vos etablissements qui ne soit pas de type special. Tous les etablissements identiques de tous les joueurs sont fermes. Puis recevez une piece de la banque pour chaque etablissement ferme.",
                 "../../../assets/batiments/Violet/Entreprise-de-renovation.jpg",
                 Violet,
                 list<unsigned int>{10},
                 "special") {
    ///Constructeur de EntrepriseRenovation
}

void EntrepriseRenovation::declencher_effet(unsigned int possesseur, int bonus) const{
    /// Effet de la classe Entreprise de Renovation
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

    cout << "Activation de l'effet de l'entreprise de renovation du joueur \"" << j_actuel->get_nom()<<"\"" << endl;

    // Selection du batiment du joueur
    Batiment *batiment;
    batiment = j_actuel->selectionner_batiment();
    while (batiment->get_couleur() == Violet) {
        cout << "Vous ne pouvez pas selectionner un batiment violet !" << endl;
        batiment = j_actuel->selectionner_batiment();
    }

    int nb_fermes = 0;
    // Fermeture des batiments correspondants
    for (auto joueur : tab_joueurs){
        for (auto& couleur : joueur->get_liste_batiment()) {
            if (couleur.first == Violet)
                continue;
            for (auto bat: couleur.second) {
                if (bat.first->get_nom() == batiment->get_nom()) {
                    for (int nb = 0; nb < bat.second; nb++) {
                        // Fermeture des batiments
                        joueur->fermer_batiment(batiment);
                        nb_fermes++;
                    }
                }
            }
        }
    }
    cout << nb_fermes << "batiments " << batiment->get_nom() << " ont ete fermes" << endl;
    cout << j_actuel->get_nom() << " va recevoir " << nb_fermes << "pieces" << endl;
    j_actuel->set_argent(j_actuel->get_argent() + nb_fermes);
    cout << j_actuel->get_nom() << "possede maintenant " << j_actuel->get_argent() << " pieces" <<endl;
}
