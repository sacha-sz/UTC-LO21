#include "Arboretum.h"
#include "Partie.h"

Arboretum::Arboretum():
        Batiment("Arboretum",
                 3,
                 "Rassemblez les pieces de tous les joueurs puis redistribuez les de maniere egale entre tous. La banque completera s'il manque des pieces pour une redistribution egale.",
                 "../../../assets/batiments/Violet/Arboretum.jpg",
                 Violet,
                 list<unsigned int>{11, 12, 13},
                 "special") {
    ///Constructeur de l'Arboretum
}



void Arboretum::declencher_effet(unsigned int possesseur, int bonus) const{
    /// Effet de l'arboretum
    unsigned int somme_totale = 0;
    vector<Joueur*> tab_joueurs = Partie::get_instance()->get_tab_joueurs();
    cout << "Activation de l'effet du Arboretum du joueur \"" << tab_joueurs[possesseur]->get_nom()<<"\"" << endl;

    // Calcul de l'argent total
    for (auto joueur : tab_joueurs){
        somme_totale += joueur->get_argent();
    }
    while (somme_totale%tab_joueurs.size() != 0){
        somme_totale++;
    }

    // Argent a repartir
    unsigned int montant_par_joueur = somme_totale / tab_joueurs.size();
    // Repartition
    for (auto joueur : tab_joueurs){
        joueur->set_argent(montant_par_joueur);
    }
    cout << "Tous les joueurs ont maintenant " << montant_par_joueur << " credits !" << endl;
}