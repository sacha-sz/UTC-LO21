#ifndef MACHI_KORO_JOUEUR_H
#define MACHI_KORO_JOUEUR_H
#include "VueCarte.h"

#include <map>
#include <vector>
#include <algorithm>

#include "Monument.h"
#include "Batiment.h"
#include "gameExeption.h"

enum strat_IA {aleatoire, agressive, defensif, none};
// Agressive : l'IA veut construire des batiments de couleur rouge
// Defensif : l'IA desire construire des batiments de couleur bleue
// Aleatoire : va construire ou pas un batiment au hasard
// None : n'est pas une IA

class Joueur {
    private:
        /*** Attributs de la classe ***/
        const std::string nom;
        unsigned int argent;
        bool est_ia;
        strat_IA strategie;

        std::vector<Batiment*> liste_batiment_fermes;

        std::map<Monument*, bool> liste_monument;
        std::map<couleur_bat, std::map<Batiment*, unsigned int>> liste_batiment;

    public:
        /*** Constructeurs et destructeur ***/
        Joueur(const std::string& nom, const std::vector<Monument *>&list_mon, const std::vector<Batiment *>&list_bat, unsigned int arg_depart, strat_IA stratIa=none);
        ~Joueur();

        /***** Getters *****/
        [[nodiscard]] unsigned int get_argent() const {return argent;};

        [[nodiscard]] bool get_est_ia() const {return est_ia;};

        [[nodiscard]] strat_IA get_strategie() const {return strategie;};

        [[nodiscard]] const std::string& get_nom() const {return nom;};
        [[nodiscard]] const std::map<Monument*, bool>& get_liste_monument() const {return liste_monument;};

        [[nodiscard]] std::map<couleur_bat, std::map<Batiment*, unsigned int>> get_liste_batiment() const {return liste_batiment;};
        std::map<Batiment*, unsigned int> get_liste_batiment(couleur_bat couleur) {return liste_batiment[couleur];};

        [[nodiscard]] std::vector<unsigned int> get_repartition_argent() const;
        [[nodiscard]] std::vector<Monument*> get_monument_jouables() const;
        [[nodiscard]] std::vector<Batiment* > get_liste_batiment_fermes() const {return liste_batiment_fermes;};


        /***** Setters *****/
        void set_argent(unsigned int arg) {argent = arg;};

        /***** Autres methodes *****/
        [[nodiscard]] unsigned int count_type(const std::string& type) const;

        void activer_monument(Monument *mon);
        void desactiver_monument(Monument *mon);
        void ajouter_batiment(Batiment *bat);
        void retirer_batiment(Batiment *bat);

        virtual void fermer_batiment(Batiment *bat);
        virtual void ouvrir_batiment(Batiment *bat);

        [[nodiscard]] Monument* possede_monument(const std::string& nom_mon) const;

        [[nodiscard]] Batiment* selectionner_batiment() const;
        [[nodiscard]] Monument* selectionner_monument() const;

        [[nodiscard]] Batiment* possede_batiment(const std::string& nom_bat) const;
};

#endif //MACHI_KORO_JOUEUR_H
