#ifndef MACHI_KORO_VUECARTE_H
#define MACHI_KORO_VUECARTE_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include "Carte.h"
#include <iostream>

class VueCarte : public QPushButton
{
Q_OBJECT
public:
    VueCarte(const Carte& c,bool etat, bool est_act = false, QWidget *parent = nullptr);
    ~VueCarte() override = default;

    explicit VueCarte(QWidget *parent = nullptr);
    // affecter une nouvelle carte à la vue
    [[nodiscard]] const Carte* getCarte() const { return carte; }
    [[nodiscard]] QPixmap get_pixmap() const{return pixmap;}
    void set_pixmap(std::string path){pixmap = QPixmap(QString::fromStdString(path));};
    void set_icon(QPixmap pixmap){ButtonIcon = QIcon(pixmap);};
    [[nodiscard]] bool get_est_actif() const{return est_actif;}

private:
    const Carte* carte = nullptr;
    QPixmap pixmap;
    QIcon ButtonIcon;
    std::string path_carte;
    bool est_actif;

signals:
    // quand la vue de carte est cliquée, elle émet un signal en transmettant son adresse
    void carteClicked(VueCarte*);
public slots:
private slots:
    void clickedEvent() { emit carteClicked(this); }
};


#endif //MACHI_KORO_VUECARTE_H
