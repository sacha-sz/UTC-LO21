#include "Pizzeria.h"
#include "Partie.h"

Pizzeria::Pizzeria() :
            Batiment("Pizzeria",
                     1 ,
                     "Recevez 1 piece du joueur qui a lance les des.",
                     "../../../assets/batiments/Rouge/Pizzeria.jpg",
                     Rouge,
                     list<unsigned int>{7},
                     "restaurant"){}

void Pizzeria::declencher_effet(unsigned int possesseur, int bonus) const{
    Partie * partie = Partie::get_instance();
    Joueur* joueur_possesseur = partie->get_tab_joueurs()[possesseur];
    cout << "Activation de l'effet de la Pizzeria du joueur \"" << joueur_possesseur->get_nom()<< "\"" << endl;
    //Trouver un joueur qui a cette carte
    if(partie->get_joueur_actuel() != possesseur){
        partie->transfert_argent(possesseur, partie->get_joueur_actuel(), 1 + bonus);
    }
    else{
        throw gameException("On ne peut pas se donner d'argent a soi meme");
    }
}