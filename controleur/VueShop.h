#ifndef MACHI_KORO_VUESHOP_H
#define MACHI_KORO_VUESHOP_H

#include <QWidget>
#include "Shop.h"
#include "VueCarte.h"
#include <QGridLayout>

class VueShop  : public QGridLayout{
    Q_OBJECT
    std::vector<VueCarte *> tab_vue_shop;
    VueCarte *carte_choisie;
    unsigned int largeur;
    QPushButton* bouton_acheter;

public:
    explicit VueShop(Shop* shop, QWidget *parent = nullptr);
    //~VueShop();

public slots:
    void clicked_acheter_event();
    void batiment_clique(VueCarte* vc);
};


#endif //MACHI_KORO_VUESHOP_H
