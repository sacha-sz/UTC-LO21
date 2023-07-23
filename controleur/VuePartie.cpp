#include <iostream>

#include "VuePartie.h"
#include "Partie.h"

using namespace std;


VuePartie::VuePartie(QWidget *parent){
    /// Constructeur de VuePartie
    // Attributs principaux
    Partie *partie_actuelle = Partie::get_instance();
    parent_fenetre = parent;
    fenetre_carte = nullptr;
    ajout_supp_1 = nullptr;
    ajout_supp_2 = nullptr;

    map_des.insert(0, new QMovie("../assets/des/0.gif"));
    map_des.insert(1, new QMovie("../assets/des/1.gif"));
    map_des.insert(2, new QMovie("../assets/des/2.gif"));
    map_des.insert(3, new QMovie("../assets/des/3.gif"));
    map_des.insert(4, new QMovie("../assets/des/4.gif"));
    map_des.insert(5, new QMovie("../assets/des/5.gif"));
    map_des.insert(6, new QMovie("../assets/des/6.gif"));
    map_des.insert(7, new QMovie("../assets/des/6.gif"));

    structure = new QVBoxLayout();


    //Création de l'entete de la page (pourquoi pas créer une classe VueEntete?)

    /// ****************************************************************************************************************
    /// ************************************ Création de l'entete de la page *******************************************
    /// ****************************************************************************************************************

    entete = new QHBoxLayout();
    entete_gauche = new QVBoxLayout();

    //Affichage du nom de l'édition de jeu

    label_edj = new QLabel;
    // Permet de séparer les noms des éditions et extensions de jeu par un espace
    string nom_edj;
    for (const auto& it : partie_actuelle->get_nom_edition()){
        if (it != partie_actuelle->get_nom_edition().back()){
            nom_edj += it + " + ";
        }
        else{
            nom_edj += it;
        }
    }
    // Profil de la partie
    label_edj->setText("Profil de la partie : " + QString::fromStdString(nom_edj));
    label_edj->setFixedSize(300, 50);
    label_edj->setAlignment(Qt::AlignCenter);

    entete_gauche->addWidget(label_edj);

    infos_partie = new QLabel();
    string infos_ma_partie = "Nombre de joueurs : " + to_string(partie_actuelle->get_tab_joueurs().size()) + "\nNombre de monuments pour gagner : " + to_string(partie_actuelle->get_nb_monuments_win());
    infos_partie->setText(QString::fromStdString(infos_ma_partie));
    infos_partie->setFixedSize(300, 50);
    entete_gauche->addWidget(infos_partie, 0, Qt::AlignCenter);

    //Affichage du nom du joueur actuel
    label_joueur_actuel = new QLabel;
    string nom_joueur = "Joueur actuel : \"" + partie_actuelle->get_tab_joueurs()[partie_actuelle->get_joueur_actuel()]->get_nom() + "\"";
    label_joueur_actuel->setText(QString::fromStdString(nom_joueur));
    label_joueur_actuel->setFixedSize(300, 30);
    label_joueur_actuel->setAlignment(Qt::AlignCenter);
    label_joueur_actuel->setStyleSheet("QLabel { background-color : transparent; color : green; }");
    entete_gauche->addWidget(label_joueur_actuel, 0, Qt::AlignCenter);

    label_tour_actuel = new QLabel;
    string tour_actuel = "Tour actuel : " + to_string(partie_actuelle->get_compteur_tour() / partie_actuelle->get_tab_joueurs().size() + 1);
    label_tour_actuel->setText(QString::fromStdString(tour_actuel));
    label_tour_actuel->setFixedSize(300, 20);
    label_tour_actuel->setAlignment(Qt::AlignCenter);
    label_tour_actuel->setStyleSheet("QLabel { background-color : transparent; color : blue; }");
    entete_gauche->addWidget(label_tour_actuel, 0, Qt::AlignCenter);

    entete->addLayout(entete_gauche);
    structure->addLayout(entete, 10);

    //Ajout de l'image dans l'entete
    //Affichage de l'image "Machi Koro"
    image_entete = new QLabel;
    auto image = new QPixmap("../assets/annexes/Machi-koro.png");
    image->scaled(300,50, Qt::KeepAspectRatio);
    image_entete->setPixmap(*image);

    entete->addWidget(image_entete, 0, Qt::AlignCenter);


    //Affichage de la valeur des dés

    display_des = new QVBoxLayout;
    layout_de_1 = new QHBoxLayout;
    layout_de_2 = new QHBoxLayout;

    affichage_de_1 = new QLabel("Dé 1 : ");
    affichage_de_2 = new QLabel("Dé 2 : ");
    affichage_de_1->setFixedSize(150, 50);
    affichage_de_2->setFixedSize(150, 50);
    layout_de_1->addWidget(affichage_de_1, 0, Qt::AlignCenter);
    layout_de_2->addWidget(affichage_de_2, 0, Qt::AlignCenter);

    label_de1 = new QLabel;
    animation_de1 = map_des.value((int)partie_actuelle->get_de_1());
    animation_de1->setScaledSize(QSize(50, 50));
    label_de1->setFixedSize(50, 50);
    label_de1->setMovie(animation_de1);
    animation_de1->start();
    if (partie_actuelle->get_de_1() == 7) {
        ajout_supp_1 = new QLabel("+ 1");
        ajout_supp_1->setStyleSheet("QLabel { background-color : transparent; color : red; }");
        ajout_supp_1->setFixedSize(50, 50);
        layout_de_1->addWidget(ajout_supp_1, 0, Qt::AlignCenter);
    }
    layout_de_1->addWidget(label_de1, 0, Qt::AlignCenter);
    layout_de_1->setAlignment(Qt::AlignCenter);

    label_de2 = new QLabel;
    animation_de2 = map_des.value((int)partie_actuelle->get_de_2());
    animation_de2->setScaledSize(QSize(50, 50));
    label_de2->setFixedSize(50, 50);
    label_de2->setMovie(animation_de2);
    animation_de2->start();

    if (partie_actuelle->get_de_2() == 7) {
        ajout_supp_2 = new QLabel("+ 1");
        ajout_supp_2->setStyleSheet("QLabel { background-color : transparent; color : red; }");
        ajout_supp_2->setFixedSize(50, 50);
        layout_de_2->addWidget(ajout_supp_2, 0, Qt::AlignCenter);
    }

    connect(animation_de1, &QMovie::frameChanged, [=, this](int frameNumber) {
        if (frameNumber == animation_de1->frameCount() - 1) {
            animation_de1->stop();
        }
    });

    connect(animation_de2, &QMovie::frameChanged, [=, this](int frameNumber) {
        if (frameNumber == animation_de2->frameCount() - 1) {
            animation_de2->stop();
        }
    });

    layout_de_2->addWidget(label_de2, 0, Qt::AlignCenter);
    layout_de_2->setAlignment(Qt::AlignCenter);

    display_des->addLayout(layout_de_1);
    display_des->addLayout(layout_de_2);

    entete->addLayout(display_des);
    

    //création du bouton au cas où l'on ne veut rien acheter
    bouton_rien_faire = new QPushButton("Ne rien faire");
    bouton_rien_faire->setFixedSize(150, 50);
    bouton_rien_faire->setEnabled(false);
    bouton_rien_faire->setStyleSheet("background-color: blue; color: white;");
    connect(bouton_rien_faire, SIGNAL(clicked()), this, SLOT(ne_rien_faire_bouton()));

    entete->addWidget(bouton_rien_faire, 0, Qt::AlignCenter);

    /// ****************************************************************************************************************
    /// ************************************              FIN                *******************************************
    /// ************************************ Création de l'entete de la page *******************************************
    /// ****************************************************************************************************************

    /// ****************************************************************************************************************
    /// **************************************** MILIEU DE L'AFFICHAGE *************************************************
    /// ****************************************************************************************************************

    ///Affichage du Shop, de la Pioche et des informations

    body = new QHBoxLayout;
    body_gauche = new QVBoxLayout;

    // Pioche
    view_pioche = new VuePioche(partie_actuelle->get_pioche(), nullptr);
    fenetre_pioche = new QWidget;
    fenetre_pioche->setFixedSize(300, 260);
    fenetre_pioche->setLayout(view_pioche);
    body_gauche->addWidget(fenetre_pioche, 100, Qt::AlignCenter);

    // petit espace
    body_gauche->addSpacing(30);
    body->addLayout(body_gauche, 100);


    // Shop
    scroll_shop = new QScrollArea;
    widget_shop = new QWidget;
    view_shop = new VueShop(partie_actuelle->get_shop(), nullptr);
    widget_shop->setLayout(view_shop);
    scroll_shop->setWidget(widget_shop);
    scroll_shop->setWidgetResizable(true);
    int largeur = floor(sqrt(partie_actuelle->get_shop()->get_nb_tas_reel()));
    scroll_shop->setFixedWidth(130 * largeur);
    scroll_shop->setFixedHeight(260);
    scroll_shop->setStyle(QStyleFactory::create("Fusion"));
    body->addWidget(scroll_shop,100, Qt::AlignCenter);

    // Informations sur le tour
    infos = new VueInfo();
    widget_infos = new QWidget;
    widget_infos->setLayout(infos);
    widget_infos->setFixedSize(300, 520);
    body->addWidget(widget_infos, 100, Qt::AlignCenter);


    structure->addLayout(body,50);


    // Boutons de navigation gauche et droite dans les Vues Joueurs
    auto b1 = new QPushButton(parent);
    b1->setFixedSize(200,50);
    b1->setText(QString::fromStdString("(<) Joueur précédent"));
    connect(b1, SIGNAL(clicked()),this, SLOT(g_click()));
    auto b2 = new QPushButton(parent);
    b2->setFixedSize(200,50);
    b2->setText(QString::fromStdString("Joueur suivant (>)"));
    connect(b2, SIGNAL(clicked()),this, SLOT(d_click()));

    // Partie basse avec la vue joueur
    layout = new QHBoxLayout();

    layout->addWidget(b1);

    nb_joueurs = partie_actuelle->get_tab_joueurs().size();
    joueur_affiche = 0;
    vue_joueur = new VueJoueur(Partie::get_instance()->get_tab_joueurs()[joueur_affiche], true, parent);
    vue_joueur->setFixedSize(700,300);
    layout->addWidget(vue_joueur);

    layout->addWidget(b2);

    structure->addLayout(layout,40);
    setLayout(structure);
    // fermeture de la fenetre entraine la fermeture de l'application
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowState(Qt::WindowMaximized);
}


void VuePartie::d_click(){
    Partie *partie_actuelle = Partie::get_instance();
    /// Slot bouton droit
    joueur_affiche = (joueur_affiche + 1) % nb_joueurs;
    // Récupération de l'ancienne vue
    VueJoueur *old = vue_joueur;
    // Création de la nouvelle
    if(partie_actuelle->get_joueur_actuel() == joueur_affiche){
        vue_joueur = new VueJoueur(partie_actuelle->get_tab_joueurs()[joueur_affiche],true, parent_fenetre);
    }
    else{
        vue_joueur = new VueJoueur(partie_actuelle->get_tab_joueurs()[joueur_affiche],false,  parent_fenetre);
    }

    // Remplacement par la nouvelle
    layout->replaceWidget(old, vue_joueur);
    vue_joueur->setFixedSize(700,300);
    delete old;
    // Mise à jour de l'affichage
    update();
}


void VuePartie::g_click(){
    Partie *partie_actuelle = Partie::get_instance();
    /// Slot bouton droit
    joueur_affiche = (joueur_affiche + nb_joueurs - 1) % nb_joueurs;
    // Récupération de l'ancienne vue
    VueJoueur *old = vue_joueur;
    // Création de la nouvelle
    if(partie_actuelle->get_joueur_actuel() == joueur_affiche){
        vue_joueur = new VueJoueur(partie_actuelle->get_tab_joueurs()[joueur_affiche],true, parent_fenetre);
    }
    else{
        vue_joueur = new VueJoueur(partie_actuelle->get_tab_joueurs()[joueur_affiche],false,  parent_fenetre);
    }

    // Remplacement par la nouvelle
    layout->replaceWidget(old, vue_joueur);
    vue_joueur->setFixedSize(700,300);
    delete old;
    // Mise à jour de l'affichage
    update();
}

void VuePartie::update_vue_joueur() {
    Partie *partie_actuelle = Partie::get_instance();
    /// Fonction pour mettre à jour la vue joueur actuelle
    // Récupération de l'ancienne vue
    VueJoueur *old = vue_joueur;
    // Création de la nouvelle
    vue_joueur = new VueJoueur(partie_actuelle->get_tab_joueurs()[partie_actuelle->get_joueur_actuel()],true,  parent_fenetre);

    // Remplacement par la nouvelle
    layout->replaceWidget(old, vue_joueur);
    vue_joueur->setFixedSize(700,300);
    delete old;
    // Mise à jour de l'affichage
    update();
}

void VuePartie::update_des() {
    unsigned int de1 = Partie::get_instance()->get_de_1();
    unsigned int de2 = Partie::get_instance()->get_de_2();

    if (ajout_supp_1 != nullptr) {
        delete ajout_supp_1;
        ajout_supp_1 = nullptr;
    }

    if (ajout_supp_2 != nullptr) {
        delete ajout_supp_2;
        ajout_supp_2 = nullptr;
    }

    // Mise à jour des dés
    animation_de1 = map_des.value((int)de1);
    animation_de1->setSpeed(180);
    animation_de1->setScaledSize(QSize(50, 50));
    label_de1->setFixedSize(50, 50);
    label_de1->setMovie(animation_de1);
    animation_de1->start();

    if (de1 == 7) {
        ajout_supp_1 = new QLabel("+ 1");
        ajout_supp_1->setStyleSheet("QLabel { background-color : transparent; color : red; }");
        ajout_supp_1->setFixedSize(50, 50);
        layout_de_1->addWidget(ajout_supp_1, 0, Qt::AlignCenter);
    }

    label_de2 = new QLabel;
    animation_de2 = map_des.value((int)de2);
    animation_de2->setSpeed(180);
    animation_de2->setScaledSize(QSize(50, 50));
    label_de2->setFixedSize(50, 50);
    label_de2->setMovie(animation_de2);
    animation_de2->start();

    if (de2 == 7) {
        ajout_supp_2 = new QLabel("+ 1");
        ajout_supp_2->setStyleSheet("QLabel { background-color : transparent; color : red; }");
        ajout_supp_2->setFixedSize(50, 50);
        layout_de_2->addWidget(ajout_supp_2, 0, Qt::AlignCenter);
    }

    connect(animation_de1, &QMovie::frameChanged, [=, this](int frameNumber) {
        if (frameNumber == animation_de1->frameCount() - 1) {
            animation_de1->stop();
        }
    });

    connect(animation_de2, &QMovie::frameChanged, [=, this](int frameNumber) {
        if (frameNumber == animation_de2->frameCount() - 1) {
            animation_de2->stop();
        }
    });

    update();
}


void VuePartie::update_nom_joueur(){
    // Mise à jour du nom du joueur actuel dans l'entete
    Partie* partie_actuelle = Partie::get_instance();
    QLabel* old_nom_joueur = label_joueur_actuel;
    label_joueur_actuel = new QLabel();
    string nom_joueur = "Joueur actuel : \"" + partie_actuelle->get_tab_joueurs()[partie_actuelle->get_joueur_actuel()]->get_nom() + "\"";
    label_joueur_actuel->setText(QString::fromStdString(nom_joueur));
    label_joueur_actuel->setFixedSize(300, 50);
    label_joueur_actuel->setAlignment(Qt::AlignCenter);
    label_joueur_actuel->setStyleSheet("QLabel { background-color : transparent; color : green;}");
    entete_gauche->addWidget(label_joueur_actuel);

    QLabel* old_tour = label_tour_actuel;
    label_tour_actuel = new QLabel();
    string tour_actuel = "Tour actuel : " + to_string(partie_actuelle->get_compteur_tour() / partie_actuelle->get_tab_joueurs().size() + 1);
    label_tour_actuel->setText(QString::fromStdString(tour_actuel));
    label_tour_actuel->setFixedSize(300, 20);
    label_tour_actuel->setAlignment(Qt::AlignCenter);
    label_tour_actuel->setStyleSheet("QLabel { background-color : transparent; color : blue; }");
    entete_gauche->addWidget(label_tour_actuel);

    delete old_tour;
    delete old_nom_joueur;
    update();
}

void VuePartie::update_vue_partie() {
    /// Update du haut de la vue partie
    update_nom_joueur();
    update_des();

    /// Update du milieu de la vue partie
    update_vue_pioche();
    update_vue_shop();
    update_vue_info();

    /// Update du bas de la vue partie
    update_vue_joueur();

    /// Update de la vue partie
    update();
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowIcon(QIcon("../assets/annexes/icon.ico"));
}

void VuePartie::update_vue_shop() {
    Partie* partie_actuelle = Partie::get_instance();
    // On appelle la fonction de mise à jour de l'affichage
    VueShop* old = view_shop;
    QWidget* old_widget = widget_shop;
    QScrollArea* old_scroll = scroll_shop;

    scroll_shop = new QScrollArea;
    widget_shop = new QWidget;
    view_shop = new VueShop(partie_actuelle->get_shop(), nullptr);
    widget_shop->setLayout(view_shop);
    scroll_shop->setWidget(widget_shop);
    scroll_shop->setWidgetResizable(true);
    int largeur = floor(sqrt(partie_actuelle->get_shop()->get_nb_tas_reel()));
    scroll_shop->setFixedWidth(130 * largeur);
    scroll_shop->setFixedHeight(520);
    scroll_shop->setStyle(QStyleFactory::create("Fusion"));
    body->addWidget(scroll_shop,100, Qt::AlignCenter);
    delete old;
    delete old_widget;
    delete old_scroll;
    update();
}

void VuePartie::update_vue_pioche() {
    Partie* partie_actuelle = Partie::get_instance();
    // On appelle la fonction de mise à jour de l'affichage
    VuePioche* old = view_pioche;
    QWidget* old_widget = fenetre_pioche;

    view_pioche = new VuePioche(partie_actuelle->get_pioche(), nullptr);
    fenetre_pioche = new QWidget;
    fenetre_pioche->setFixedSize(300, 260);
    fenetre_pioche->setLayout(view_pioche);
    fenetre_pioche->setStyle(QStyleFactory::create("Fusion"));
    // body_gauche->addWidget(fenetre_pioche, 100, Qt::AlignCenter);
    body->replaceWidget(old_widget, fenetre_pioche);

    delete old;
    delete old_widget;
    update();
}

void VuePartie::update_vue_info () {
    // On appelle la fonction de mise à jour de l'affichage
    VueInfo* old = infos;
    QWidget* old_widget = widget_infos;

    infos = new VueInfo();
    widget_infos = new QWidget;
    widget_infos->setLayout(infos);
    widget_infos->setFixedSize(300, 520);
    body->addWidget(widget_infos, 100, Qt::AlignCenter);

    delete old;
    delete old_widget;
    update();
}

void VuePartie::ne_rien_faire_bouton() {
    // On créer une boite de dialogue pour demander confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation - Ne rien faire", "Voulez-vous vraiment ne rien faire ?\n", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // On appelle la fonction de mise à jour de l'affichage
        Partie* partie_actuelle = Partie::get_instance();
        partie_actuelle->suite_tour(false);
    }
}

VuePartie::~VuePartie() {
    /// Destructeur de VuePartie
    map_des.clear();

    for (auto it : tab_vue_shop) {
        delete it;
    }
    tab_vue_shop.clear();
}