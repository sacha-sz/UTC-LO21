#include "CentreAffaires.h"
#include "Partie.h"

CentreAffaires::CentreAffaires():
    Batiment("CentreAffaires",
             8,
             "Vous pouvez echanger avec le joueur de votre choix un etablissement qui n'est pas de type special",
             "../../../assets/batiments/Violet/Centre-d-'affaires.jpg",
             Violet,
             list<unsigned int>{6},
             "special") {
    ///Constructeur de Centre d'Affaires
}



void CentreAffaires::declencher_effet(unsigned int possesseur, int bonus) const {
    /// Effet du Centre d'affaires
    const vector<Joueur *> &tab_joueurs = Partie::get_instance()->get_tab_joueurs();
    Joueur *j_actuel = tab_joueurs[possesseur];

    // On verifie que le joueur possede au moins un batiment non violet
    map<Batiment*, unsigned int> liste_bat_bleu = j_actuel->get_liste_batiment(Bleu);
    map<Batiment*, unsigned int> liste_bat_vert = j_actuel->get_liste_batiment(Vert);
    map<Batiment*, unsigned int> liste_bat_rouge = j_actuel->get_liste_batiment(Rouge);

    if (liste_bat_bleu.empty() && liste_bat_vert.empty() && liste_bat_rouge.empty()) {
        cout << "Vous ne possedez aucun batiment non special !" << endl;
        return;
    }

    bool exist_joueur_echange = false;
    for (auto &joueur : tab_joueurs) {
        // On verifie que le joueur possede au moins un batiment non violet
        liste_bat_bleu = joueur->get_liste_batiment(Bleu);
        liste_bat_vert = joueur->get_liste_batiment(Vert);
        liste_bat_rouge = joueur->get_liste_batiment(Rouge);

        if ((!liste_bat_bleu.empty() || !liste_bat_vert.empty() || !liste_bat_rouge.empty()) && joueur != j_actuel) {
            exist_joueur_echange = true;
            break;
        }
    }

    if (!exist_joueur_echange) {
        cout << "Aucun joueur ne possede de batiment non special !" << endl;
        return;
    }

    cout << "Activation de l'effet du Centres des Affaires du joueur \"" << j_actuel->get_nom()<<"\"" << endl;

    // Choix du joueur
    unsigned int num_joueur;
    Joueur *joueur_echange;

    do{
        num_joueur = Partie::selectionner_joueur(tab_joueurs, possesseur);
        joueur_echange = tab_joueurs[num_joueur];

        // On verifie que le joueur possede au moins un batiment non violet
        liste_bat_bleu = joueur_echange->get_liste_batiment(Bleu);
        liste_bat_vert = joueur_echange->get_liste_batiment(Vert);
        liste_bat_rouge = joueur_echange->get_liste_batiment(Rouge);

        if (liste_bat_bleu.empty() && liste_bat_vert.empty() && liste_bat_rouge.empty()) {
            cout << "Le joueur \"" << joueur_echange->get_nom() << "\" ne possede aucun batiment non special !" << endl;
        }

    } while (liste_bat_bleu.empty() && liste_bat_vert.empty() && liste_bat_rouge.empty());


    cout << "Vous allez procede a un echange avec " << joueur_echange->get_nom() << endl;

    // Selection des batiments
    Batiment *batiment_a_donner, *batiment_a_recevoir;
    batiment_a_donner = j_actuel->selectionner_batiment();
    while (batiment_a_donner->get_couleur() == Violet) {
        cout << "Vous ne pouvez pas selectionner un batiment violet !" << endl;
        batiment_a_donner = j_actuel->selectionner_batiment();
    }
    batiment_a_recevoir = joueur_echange->selectionner_batiment();
    while (batiment_a_recevoir->get_couleur() == Violet) {
        cout << "Vous ne pouvez pas selectionner un batiment violet !" << endl;
        batiment_a_recevoir = joueur_echange->selectionner_batiment();
    }
    cout << "Le joueur " << j_actuel->get_nom() << " va echanger le batiment " << batiment_a_donner->get_nom() << " avec le batiment " << batiment_a_recevoir->get_nom() << " de " << joueur_echange->get_nom() << endl;

    // Echange des batiments
    // Gestion du batiment 2 dans l'echange
    joueur_echange->retirer_batiment(batiment_a_recevoir);
    j_actuel->ajouter_batiment(batiment_a_recevoir);
    // Gestion du batiment 1 dans l'echange
    j_actuel->retirer_batiment(batiment_a_donner);
    joueur_echange->ajouter_batiment(batiment_a_donner);
}




