#ifndef MACHI_KORO_BATIMENT_H
#define MACHI_KORO_BATIMENT_H

#include "Carte.h"

enum couleur_bat {Bleu, Rouge, Vert, Violet};

class Batiment : public Carte {
    protected:
        couleur_bat couleur;
        std::list<unsigned int> num_activation;
        std::string type;
        Batiment(const std::string& nom, unsigned int prix, const std::string& description_effet, const std::string& path_image, couleur_bat coul, const std::list<unsigned int>& num, const std::string& type_bat);

    public:
        ~Batiment()override=default;
        virtual Batiment* clone() const = 0;
        couleur_bat get_couleur() const {return couleur;};
        const std::list<unsigned int>& get_num_activation() const {return num_activation;};
        std::string get_type() const override {return type;};
};
#endif //MACHI_KORO_BATIMENT_H
