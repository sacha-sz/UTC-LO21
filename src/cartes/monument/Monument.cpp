#include "Monument.h"

using namespace std;

Monument::Monument(Moment_Effet effet_moment, const string& nom, unsigned int prix, const string& description_effet, const string& path_image) :
    Carte(nom, description_effet, prix, path_image) {
    /// Constructeur de Monument

    // Gestion d'erreur moment
    if (effet_moment != AVANT && effet_moment != PENDANT && effet_moment != APRES) {
        throw gameException("Moment_Effet invalide");
    }

    // Gestion d'erreur nom, description_effet et path_image
    if (nom.empty() || description_effet.empty()) {
        throw gameException("Nom ou description_effet invalide");
    }

    // Initialisation de moment
    moment = effet_moment;
}