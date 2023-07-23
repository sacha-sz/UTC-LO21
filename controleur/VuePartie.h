#ifndef MACHI_KORO_VUEPARTIE_H
#define MACHI_KORO_VUEPARTIE_H

#include "VueCarte.h"
#include "VueJoueur.h"
#include "Joueur.h"
#include "VueShop.h"
#include "VuePioche.h"
#include "VueInfo.h"
#include <QFormLayout>
#include <QtGui>
#include <QMovie>
#include <QStyleFactory>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "Pioche.h"

class VuePartie : public QWidget
{
    Q_OBJECT
public:

    explicit VuePartie(QWidget *parent = nullptr);
    ~VuePartie();

    /// Update de la vue
    void update_vue_joueur();
    void update_vue_partie();
    void update_vue_shop();
    void update_vue_pioche();
    void update_vue_info();
    void set_bouton_rien_faire(bool b) {bouton_rien_faire->setEnabled(b);}
    void update_des();
    void set_vue_carte(QWidget* vue_carte) {fenetre_carte = vue_carte;}
    void update_nom_joueur();

    /// Getters
    [[nodiscard]] QWidget* get_vue_carte() const {return fenetre_carte;}
    [[nodiscard]] VueJoueur* get_vue_joueur() const {return vue_joueur;}
    [[nodiscard]] VueInfo* get_vue_infos() const {return infos;}

private:
    unsigned int nb_joueurs;
    unsigned int joueur_affiche;
    std::vector<VueCarte *> tab_vue_shop;
    //Labels sur la page
    QLabel* label_edj;

    QLabel* label_joueur_actuel;
    // Dés
    QMap<unsigned int, QMovie*> map_des;
    QMovie* animation_de1;
    QMovie* animation_de2;
    QLabel* label_de1;
    QLabel* label_de2;
    QLabel* ajout_supp_1;
    QLabel* ajout_supp_2;

    //Images
    QLabel* image_entete;
    QLabel *affichage_de_1;
    QLabel *affichage_de_2;
    //partitionnement de la page
    QVBoxLayout *structure;

    QHBoxLayout *layout;
    QHBoxLayout *entete;
    QVBoxLayout *entete_gauche;
    /// Haut de la page
    QVBoxLayout *display_des;
    QLabel * infos_partie;
    QLabel* label_tour_actuel;

    QHBoxLayout* layout_de_1;
    QHBoxLayout* layout_de_2;
    QHBoxLayout *body;
    QVBoxLayout *body_gauche;
    VueJoueur* vue_joueur;
    QWidget *parent_fenetre;
    QWidget *fenetre_carte;
    QPushButton* bouton_rien_faire;
    /// Milieu de la page
    //Pioche à gauche
    QWidget *fenetre_pioche;

    VuePioche* view_pioche;

    //Shop au centre
    VueShop* view_shop;

    QScrollArea* scroll_shop;
    QWidget* widget_shop;
    //Infos à droite
    VueInfo *infos;

    QWidget* widget_infos;

public slots:
    // Slots qui gèrent les clics sur les vues joueurs
    void d_click();
    void g_click();
    void ne_rien_faire_bouton();
};

#endif //MACHI_KORO_VUEPARTIE_H
