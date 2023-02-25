#ifndef MACHI_KORO_PIOCHE_H
#define MACHI_KORO_PIOCHE_H

#include <vector>
#include <random>
#include <stack>
#include <algorithm>

#include "Batiment.h"
#include "gameExeption.h"

class Pioche {
    friend class Batiment;

    private:
        std::stack<Batiment *> contenu;

    public:
        explicit Pioche(const vector<Batiment*>& batiments);
        Pioche() = default;
        ~Pioche() = default;
        bool est_vide() {return contenu.empty();};
        Batiment* get_carte(); // retourne la carte du dessus de la pioche
};

#endif //MACHI_KORO_PIOCHE_H
