#include "Restaurant.h"
#include "Partie.h"

using namespace std;

Restaurant::Restaurant() :
            Batiment("Restaurant",
                     3,
                     "Recevez 2 pieces du joueur qui a lance les des",
                     "../assets/batiments/Rouge/Restaurant.png",
                     Rouge ,
                     list<unsigned int>{ 9,10 },
                     "restaurant") {}


void Restaurant::declencher_effet(unsigned int possesseur, int bonus) const{
    Partie * partie = Partie::get_instance();
    Joueur* joueur_possesseur = partie->get_tab_joueurs()[possesseur];
    //Trouver un joueur qui a cette carte
    if(partie->get_joueur_actuel() != possesseur){
        partie->get_vue_partie()->get_vue_infos()->add_info( "Activation de l'effet du Restaurant du joueur \""+ joueur_possesseur->get_nom() + "\"");
        partie->transfert_argent(partie->get_joueur_actuel(),possesseur, 2 + bonus);
    }
    else{
        throw gameException("On ne peut pas se donner d'argent a soi meme");
    }
}
