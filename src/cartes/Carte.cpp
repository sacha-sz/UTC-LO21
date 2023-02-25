#include "Carte.h"

using namespace std;

Carte::Carte(const string& name, const string& effect_description, unsigned int price, const string& path_picture) {
    /// Constructeur de la classe Carte

    // Gestion des erreurs
    if (name.empty()) {
        throw invalid_argument("Le nom de la carte ne peut pas etre vide");
    }

    if (effect_description.empty()) {
        throw invalid_argument("La description de l'effet de la carte ne peut pas etre vide");
    }

    if (path_picture.empty()) {
        throw invalid_argument("Le chemin de l'image de la carte ne peut pas etre vide");
    }

    // Initialisation des attributs
    nom = name;
    description_effet = effect_description;
    prix = price;
    path_image = path_picture;
}

unsigned int Carte::argent_effet(int a) {
    /// Retourne le maximum entre a et 0

    if (a < 0)
        return 0;
    else
        return (unsigned int) a;
}