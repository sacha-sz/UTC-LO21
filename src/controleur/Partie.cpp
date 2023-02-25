#include "Partie.h"
#define REP_ED_MIN 1
#define REP_ED_MAX 4

#define REP_EXT_MIN 1
#define REP_EXT_MAX 4

Partie::Handler Partie::handler=Partie::Handler();

Partie* Partie::get_instance() {
    if (handler.instance == nullptr) {
        int rep_ed = -1;
        EditionDeJeu * edition;
        vector<EditionDeJeu *> listing_extension;

        cout << "/********\tMenu\t********/" << endl;
        while (!(REP_ED_MIN <= rep_ed && rep_ed <= REP_ED_MAX)) {
            cout << "\nVeuillez-choisir une edition :\n"
                    "\t1. Standard\n"
                    "\t2. Deluxe\n"
                    "\t3. Custom\n"
                    "\t4. Quitter\n"
                    "Votre choix :" << endl;
            cin >> rep_ed;
        }

        if (rep_ed == 1) {
            edition = new EditionDeJeu("Standard");
            int rep_ext = -1;
            while (!(REP_EXT_MIN <= rep_ext && rep_ext <= REP_EXT_MAX)) {
                cout << "Vous avez choisi l'edition standard\n"
                        "Vous pouvez jouer avec des extensions\n"
                        "Avec laquelle voulez-vous jouer ?\n"
                        "\t1. Green-Valley\n"
                        "\t2. Marina\n"
                        "\t3. Les deux (Marina + Green-Valley)\n"
                        "\t4. Aucune\n"
                        "Votre choix :" << endl;
                cin >> rep_ext;
            }
            if (rep_ext == 1)
                listing_extension.push_back(new EditionDeJeu("GreenValley"));
            else if (rep_ext == 2)
                listing_extension.push_back(new EditionDeJeu("Marina"));
            else if (rep_ext == 3) {
                listing_extension.push_back(new EditionDeJeu("GreenValley"));
                listing_extension.push_back(new EditionDeJeu("Marina"));
            }
            else
                cout << "Vous avez choisi de jouer sans extension"<< endl;


        } else if (rep_ed == 2) {
            edition = new EditionDeJeu("Deluxe");
        } else if (rep_ed == 3) {
            edition = new EditionDeJeu("Custom");
        } else {
            cout << "Vous avez choisi de quitter le jeu" << endl;
            exit(0);
        }
        if(rep_ed != REP_ED_MAX)
            handler.instance = new Partie(edition, listing_extension);

        delete edition;

        for (auto & extension : listing_extension)
            delete extension;
    }

    return handler.instance;
}


Partie::Partie(EditionDeJeu* edition, const vector<EditionDeJeu *>& extensions) : nb_monuments_win(edition->get_nb_monuments_win()), joueur_actuel(0), de_1(0), de_2(0) {
    ///Constructeur de Partie

    //Initialisation des variables utiles
    unsigned int max_joueurs = edition->get_nb_joueurs_max();
    unsigned int format = 0;
    unsigned int nb_tas = 0;
    rejouer = false;


    for (auto bat : edition->get_batiment()) {
        for (unsigned int i = 0; i < bat.second; i++) {
            ajout_batiment(bat.first);
        }
    }

    for (auto monu : edition->get_monument()) {
        list_monuments.push_back(monu->clone());
    }

    if (!extensions.empty()) {
        for (auto ext : extensions) {
            for (auto bat : ext->get_batiment()) {
                for (unsigned int i = 0; i < bat.second; i++) {
                    ajout_batiment(bat.first);
                }
            }
            for (auto monu : ext->get_monument()) {
                list_monuments.push_back(monu->clone());
            }

            if (ext->get_nb_joueurs_max() > max_joueurs)
                max_joueurs = ext->get_nb_joueurs_max();


            if (ext->get_nb_monuments_win() > nb_monuments_win)
                nb_monuments_win = ext->get_nb_monuments_win();

        }
    }

    // Initialisation du starter
    vector<Batiment*> starter_bat = get_starter();

    // Ajout des joueurs
    for (unsigned int i = 0; i < max_joueurs; i++) {
        // Si plus de 2 joueurs, l'ajout devient optionnel
        if (i >= 2) {
            cout << "Voulez-vous ajouter un joueur ? (0 : non, 1 : oui)" << endl;
            int choix;
            cin >> choix;
            while (choix != 0 && choix != 1) {
                cout << "Veuillez entrer 0 ou 1" << endl;
                cin >> choix;
            }
            if (choix == 0) {
                break;
            }
        }
        // Info du joueur
        cout << "Nom du joueur " << i + 1 << " : "  << endl;
        string nom;

        bool nom_ok = false;
        do{
            cin >> nom;
            nom_ok = true;
            for (auto joueur : tab_joueurs) {
                if (joueur->get_nom() == nom) {
                    cout << "Ce nom est deja utilise" << endl;
                    nom_ok = false;
                    break;
                }
            }
        } while(!nom_ok);

        int humain = -1;
        while (humain < 0 || 1 < humain ) {
            cout << "Voulez-vous que le joueur soit humain ? (0 : non, 1 : oui)" << endl;
            cin >> humain;
        }


        if (humain) {
            tab_joueurs.push_back(new Joueur(nom, list_monuments, starter_bat, 3));
        }
        // Demande de la strategie IA
        else {
            unsigned int strategie = -1;
            while (strategie < 1 || strategie > 3) {
                cout << "\nQuelle est la strategie du joueur ? (1 : aleatoire, 2 : agressive, 3 : defensif) :" << endl;
                cin >> strategie;
            }
            // Ajout du joueur au tableau de joueurs
            switch (strategie) {
                case 1:
                    tab_joueurs.push_back(new Joueur(nom, list_monuments, starter_bat, 3, aleatoire));
                    break;
                case 2:
                    tab_joueurs.push_back(new Joueur(nom, list_monuments, starter_bat, 3, agressive));
                    break;
                case 3:
                    tab_joueurs.push_back(new Joueur(nom, list_monuments, starter_bat, 3, defensif));
                    break;
                default :
                    throw gameException("Strategie IA invalide");
            }
        }
    }

    pioche = new Pioche(map_to_vector(list_batiments));
    // Demande du format du shop
    while (format < 1 || format > 2) {
        cout << "Quel est le format du shop la partie ? (1 : standard, 2 : extended) :" << endl;
        cout <<"1 : standard :" << endl;
        cout << "\tAvec ce format vous pouvez choisir le nombre de tas de cartes que vous voulez." << endl;
        cout << "2 : extended :" << endl;
        cout << "\tAvec ce format toutes les cartes sont dans le shop." << endl;
        cout << "Votre choix : " << endl;
        cin >> format;
    }

    if (format == 1) {
        while (nb_tas < 9 || nb_tas > list_batiments.size() - 1) {
            cout << "Combien de tas voulez-vous ? (9 <= tas <= " << list_batiments.size() - 1 << ") :" << endl;
            cin >> nb_tas;
        }
    }
    else
        nb_tas = list_batiments.size() + 1;

    // Construction du Shop
    shop = new Shop(nb_tas);

    while (!pioche->est_vide() && shop->get_nb_tas_reel() < shop->get_nb_tas_max()){
        try  {
            shop->completer_shop(pioche->get_carte());
        }
        catch(exception const& e){
            cerr << "ERREUR : " << e.what() << endl;
        }
    }

    cout << "Construction de la partie terminee" << endl;
    cout << "Bon jeu !" << endl;
}

vector<Batiment *> Partie::get_starter() {
    ///Renvoie le starter de la partie
    if (list_batiments.empty()) {
        throw gameException("Aucun batiment dans la liste");
    }
    vector<Batiment*> starter;

    for (auto bat : list_batiments) {
        if (bat.first->get_nom() == "Boulangerie" ||
            bat.first->get_nom() == "ChampBle")
            starter.push_back(bat.first);
        if (starter.size() == 2)
            break;
    }
    return starter;

}


Partie::~Partie() {
    /// Destructeur de la classe Partie
    // Destruction des joueurs
    for (auto joueur : tab_joueurs){
        delete joueur;
    }

    // Destruction des batiments
    for (auto batiment : list_batiments){
        delete batiment.first;
    }

    // Destruction des monuments
    for (auto monument : list_monuments){
        delete monument;
    }

    delete shop;
    delete pioche;
}

void Partie::rejouer_tour() {
    rejouer = true;
}


void Partie::ajout_batiment(Batiment *batiment) {
    ///Ajoute un batiment dans la liste des batiments
    bool est_present = false;

    for (auto bat : list_batiments){
        if (bat.first->get_nom() == batiment->get_nom()){
            list_batiments[bat.first] += 1;
            est_present = true;
        }
    }

    if (!est_present){
        list_batiments.insert(pair<Batiment* const, unsigned int>(batiment->clone(), 1));
    }
}

bool Partie::acheter_carte() {
    //fonction qui permet a un joueur donne d'acheter une carte (batiment ou monument)
    int choix = -1;
    int choix_ia = -1;
    bool visit[2] = {false, false};
    bool transaction_fin = false;

    while (!transaction_fin){
        if (!tab_joueurs[joueur_actuel]->get_est_ia()) {
            cout << "Que voulez-vous acheter ? (1 : batiment, 2 : monument, 3 : quitter)" << endl;
            cin >> choix;
            while (choix < 1 || choix > 3) {
                cout << "Veuillez entrer 1, 2 ou 3" << endl;
                cin >> choix;
            }
            if (choix == 3) {
                return false;
            } else if (choix == 1) {
                visit[0] = true;
                transaction_fin = acheter_bat();
            } else if (choix == 2) {
                visit[1] = true;
                transaction_fin = acheter_monu();
            }

            if (!transaction_fin && visit[0]) {
                cout << "Vous n'avez pas assez de ressources pour acheter un batiment" << endl;
                choix = -1;
                while (choix < 0 || choix > 1) {
                    cout << "Voulez-vous acheter un monument ? (0 : non, 1 : oui)" << endl;
                    cin >> choix;
                }
                if (choix == 1) {
                    transaction_fin = acheter_monu();
                }
            }
            else if (!transaction_fin && visit[1]) {
                cout << "Vous n'avez pas assez de ressources pour acheter un monument" << endl;
                choix = -1;
                while (choix < 0 || choix > 1) {
                    cout << "Voulez-vous acheter un batiment ? (0 : non, 1 : oui)" << endl;
                    cin >> choix;
                }
                if (choix == 1) {
                    transaction_fin = acheter_bat();
                }
            }

            if (!transaction_fin) {
                return false;
            }

        } else {
            choix_ia = rand() % 5;
            if (choix_ia == 0) {
                visit[0] = true;
                transaction_fin = acheter_bat();
            } else {
                visit[1] = true;
                transaction_fin = acheter_monu();
            }

            if (!transaction_fin && !visit[0]) {
                visit[0] = true;
                transaction_fin = acheter_bat();
            }
            else if (!transaction_fin && !visit[1]) {
                visit[1] = true;
                transaction_fin = acheter_monu();
            }

            if (!transaction_fin) {
                return false;
            }
        }
    }
    return true;
}

bool Partie::acheter_monu() {
    //fonction qui permet a un joueur donne d'acheter un monument
    Monument* mon_picked;
    Joueur *joueur_act = tab_joueurs[joueur_actuel];
    int choix = -1;
    unsigned int pos = 1;
    vector<Monument*> monuments_dispo;

    if (!tab_joueurs[joueur_actuel]->get_est_ia()) {
        cout << "Quel est le numero du monument que vous voulez acheter?" << endl;
        cout << "0 : Annuler" << endl;
        for (auto mon_act: joueur_act->get_liste_monument()) {
            if (!mon_act.second && mon_act.first->get_prix() <= joueur_act->get_argent()) {
                cout << pos << " : " << mon_act.first->get_nom() << endl;
                pos++;
                monuments_dispo.push_back(mon_act.first);
            }
        }

        if (monuments_dispo.empty()) {
            cout << "Vous ne pouvez pas acheter de monument" << endl;
            return false;
        }

        while (choix < 0 || choix > monuments_dispo.size()) {
            cout << "Votre choix : " << endl;
            cin >> choix;
        }

        if (choix == 0)
            return false;

        mon_picked = monuments_dispo[choix - 1];

        joueur_act->activer_monument(mon_picked);
        joueur_act->set_argent(joueur_act->get_argent() - mon_picked->get_prix());
    } else {
        for (auto mon_act: joueur_act->get_liste_monument()) {
            if (!mon_act.second && mon_act.first->get_prix() <= joueur_act->get_argent()) {
                monuments_dispo.push_back(mon_act.first);
            }
        }

        if (monuments_dispo.empty()) {
            return false;
        }

        mon_picked = monuments_dispo[rand() % monuments_dispo.size()];

        joueur_act->activer_monument(mon_picked);
        joueur_act->set_argent(joueur_act->get_argent() - mon_picked->get_prix());
    }

    cout << "\n\nLe joueur \"" << tab_joueurs[joueur_actuel]->get_nom() << "\" a active le monument " << mon_picked->get_nom() << "\n\n";

    return true;
}

bool Partie::acheter_bat() {
    //fonction qui permet a un joueur donne d'acheter un batiment
    Batiment* bat_picked;
    Joueur *joueur_act = tab_joueurs[joueur_actuel];
    int choix = -1;
    vector<Batiment*> bat_shop = shop->get_contenu_v();
    bool doublon = true;

    if (!tab_joueurs[joueur_actuel]->get_est_ia()) {
        cout << "Quel est le numero du batiment que vous voulez acheter?" << endl;
        cout << "0 : Annuler" << endl;
        shop->affiche_shop();

        // on verifie que le shop contient au moins un batiment achetable
        for (auto bat: bat_shop) {
            if (bat->get_couleur() == Violet){
                if (!joueur_act->possede_batiment(bat->get_nom())){
                    doublon = false;
                }
            }
        }

        if (doublon){
            cout << "Vous ne pouvez pas acheter de batiment" << endl;
            return false;
        }

        while (choix < 0 || choix > bat_shop.size() || doublon) {
            doublon = false;
            cout << "Votre choix : " << endl;
            cin >> choix;

            bat_picked = bat_shop[choix - 1];
            if (bat_picked->get_couleur() == Violet){
                if (joueur_act->possede_batiment(bat_picked->get_nom())){
                    cout << "Vous ne pouvez pas acheter plusieurs batiments violets identiques" << endl;
                    doublon = true;
                }
            }
        }

        if (choix == 0)
            return false;

        if (bat_picked->get_prix() > joueur_act->get_argent()) {
            cout << "Vous n'avez pas assez d'argent pour acheter ce batiment" << endl;
            return false;
        }

    } else {
        strat_IA strat = tab_joueurs[joueur_actuel]->get_strategie();
        vector<Batiment*> bat_shop_couleur;
        vector<Batiment*> bat_shop_prix_ok;
        for (auto bat_act: bat_shop) {
            if (bat_act->get_prix() <= joueur_act->get_argent()) {
                bat_shop_prix_ok.push_back(bat_act);
            }
        }

        if (strat == agressive) {
            for (auto bat_act: bat_shop) {
                if (bat_act->get_couleur() == Rouge && bat_act->get_prix() <= joueur_act->get_argent()) {
                    bat_shop_couleur.push_back(bat_act);
                }
            }
        }
        else if (strat == defensif) {
            for (auto bat_act: bat_shop) {
                if (bat_act->get_couleur() == Bleu && bat_act->get_prix() <= joueur_act->get_argent()) {
                    bat_shop_couleur.push_back(bat_act);
                }
            }
        }

        if (bat_shop_couleur.empty() && bat_shop_prix_ok.empty()) {
            return false;
        }
        else if (bat_shop_couleur.empty()) {
            bat_picked = bat_shop_prix_ok[rand() % bat_shop_prix_ok.size()];
        }
        else {
            bat_picked = bat_shop_couleur[rand() % bat_shop_couleur.size()];
        }
    }

    joueur_act->ajouter_batiment(bat_picked);

    try {
        shop->acheter_batiment(bat_picked);
    }
    catch(exception const& e){
        cerr << "ERREUR : " << e.what() << endl;
    }

    joueur_act->set_argent(joueur_act->get_argent() - bat_picked->get_prix());
    if (bat_picked->get_nom() == "BanqueDeMinivilles") {
        joueur_act->set_argent(joueur_act->get_argent() + 5);
    }

    cout << "\nLe joueur \"" << tab_joueurs[joueur_actuel]->get_nom() << "\" a achete la carte " << bat_picked->get_nom() << "\n\n";

    return true;
}


vector<Batiment*> Partie::map_to_vector(const map<Batiment*, unsigned int>& map_batiments){
    /// Retourne un vecteur avec l'adresse des batiments
    vector<Batiment*> vector_batiments;

    for (auto batiment : map_batiments){
        for(unsigned int i = 0; i < batiment.second; i++){
            vector_batiments.push_back(batiment.first);
        }
    }

    // Melange du vecteur
    // Obtention d'un nombre aleatoire (seed)
    random_device rd;
    mt19937 g(rd());

    // Melange du vecteur avec le seed
    shuffle(vector_batiments.begin(), vector_batiments.end(), g);

    return vector_batiments;
}

bool Partie::est_gagnant(unsigned int j) const {
    ///Fonction pour verifier si un joueur a gagne
    Joueur * joueur = tab_joueurs[j];
    return joueur->get_monument_jouables().size() >= nb_monuments_win;
}

bool Partie::transfert_argent(unsigned int indice_joueur1, unsigned int indice_joueur2, unsigned int somme){
    //methode qui permet d'echanger une somme d'argent entre deux joueurs
    // Transfert de l'argent du joueur 1 au joueur 2

    Joueur *joueur1 = tab_joueurs[indice_joueur1];
    Joueur *joueur2 = tab_joueurs[indice_joueur2];
    if(somme == 0){
        return false;
    }

    if(joueur1->get_argent() < somme){
        unsigned int argent_joueur1 = joueur1->get_argent();
        joueur1->set_argent(0);
        joueur2->set_argent(joueur2->get_argent() + argent_joueur1);
    }
    else if(joueur1->get_argent() >= somme){
        joueur1->set_argent(joueur1->get_argent() - somme);
        joueur2->set_argent(joueur2->get_argent() + somme);
    }
    return true;
}

void Partie::jouer_partie() {
    joueur_actuel = 0;
    bool fin_partie = false;
    /// Tant que le joueur precedent n'a pas gagne on continue la partie

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nBienvenue dans Miniville !" << endl;
    cout << "Vous allez jouer avec " << tab_joueurs.size() << " joueurs." << endl;
    cout << "Le but du jeu est d'obtenir " << nb_monuments_win << " monuments." << endl;
    cout << "Bon jeu !\n\n" << endl;

    while (!fin_partie) {
        jouer_tour();
        fin_partie = est_gagnant(joueur_actuel);
        if (!rejouer && !fin_partie){
            joueur_actuel = (joueur_actuel + 1) % tab_joueurs.size();
        }
    }

    /// On affiche le gagnant
    cout << "Le gagnant est " << tab_joueurs[joueur_actuel]->get_nom() << endl;
    cout << "Voici son etat final : " << endl;
    tab_joueurs[joueur_actuel]->afficher_joueur();

    cout << "Felicitations !!!" << endl;
}

void Partie::jouer_tour() {
    unsigned int de_casse;
    unsigned int de_1_temp, de_2_temp;
    bool centre_c_act = false;
    bool centre_c_possesseur = false;
    vector <Monument*> monuments_joueurs = tab_joueurs[joueur_actuel]->get_monument_jouables();
    rejouer = false;

    cout << "----------------------------------------------------" << endl;
    cout << "\t\t\tDebut du tour" << endl;
    cout << "Joueur actuel : " << tab_joueurs[joueur_actuel]->get_nom() << endl;
    cout << "----------------------------------------------------" << endl;

    de_1 = lancer_de();
    de_1_temp = de_1;
    de_2 = 0;
    de_casse = (rand() % 50) + 1;


    // Si le joueur a un centre commercial
    auto it_cc = find_if(monuments_joueurs.begin(), monuments_joueurs.end(), [](Monument* m){return m->get_nom() == "CentreCommercial";});
    if (it_cc != monuments_joueurs.end()){
        // Si le monument est trouve, on le joue
        try{
            monuments_joueurs[it_cc - monuments_joueurs.begin()]->declencher_effet(joueur_actuel);
        }
        catch(exception const& e){
            cerr << "ERREUR : " << e.what() << endl;
        }
        centre_c_act = true;
    }

    /// Monument avant le jet de de
    auto it_gare = find_if(monuments_joueurs.begin(), monuments_joueurs.end(), [](Monument* m){return m->get_nom() == "Gare";});
    if (it_gare != monuments_joueurs.end()){
        // Si le monument est trouve, on le joue
        try{
            monuments_joueurs[it_gare - monuments_joueurs.begin()]->declencher_effet(joueur_actuel);
        }
        catch(exception const& e){
            cerr << "ERREUR : " << e.what() << endl;
        }
    }

    cout << "------------" << endl;
    cout << "| DE 1 : " << de_1 << " |" << endl;
    cout << "------------" << endl;

    if (de_2 != 0) {
        cout << "------------" << endl;
        cout << "| DE 2 : " << de_2 << " |" << endl;
        cout << "------------" << endl;
        de_2_temp = de_2;
    }

    auto it_tr = find_if(monuments_joueurs.begin(), monuments_joueurs.end(), [](Monument* m){return m->get_nom() == "TourRadio";});
    if (it_tr != monuments_joueurs.end()){
        // Si le monument est trouve, on le joue
        try{
            monuments_joueurs[it_tr - monuments_joueurs.begin()]->declencher_effet(joueur_actuel);
        }
        catch(exception const& e){
            cerr << "ERREUR : " << e.what() << endl;
        }
    }

    if (de_1_temp != de_1) {
        cout << "------------" << endl;
        cout << "| DE 1 : " << de_1 << " |" << endl;
        cout << "------------" << endl;
    }
    if (de_2 != 0 && de_2_temp != de_2) {
        cout << "------------" << endl;
        cout << "| DE 2 : " << de_2 << " |" << endl;
        cout << "------------" << endl;
    }

    de_1_temp = de_1;
    de_2_temp = de_2;

    /// Monument apres le jet de de
    for (auto mon : monuments_joueurs) {
        if (mon->get_nom() == "Port" &&  ((de_1 + de_2) >= 10) ||
            mon->get_nom() == "FabriqueDuPereNoel" && de_casse == 1){
            try{
                mon->declencher_effet(joueur_actuel);
                if (de_1_temp != de_1) {
                    cout << "------------" << endl;
                    cout << "| DE 1 : " << de_1 << " |" << endl;
                    cout << "------------" << endl;
                }
                if (de_2 != 0 && de_2_temp != de_2) {
                    cout << "------------" << endl;
                    cout << "| DE 2 : " << de_2 << " |" << endl;
                    cout << "------------" << endl;
                }
            }
            catch(exception const& e){
                cerr << "ERREUR : " << e.what() << endl;
            }
        }
    }

    /// Activations des effets des batiments
    /// En premier ce sont les batiments rouges des autres joueurs

    unsigned int j_act_paiement = (joueur_actuel + tab_joueurs.size() - 1) % tab_joueurs.size();

    while (j_act_paiement != joueur_actuel) {
        // Regarde si le joueur possede un centre commercial
        vector<Monument*> monuments_j_act = tab_joueurs[j_act_paiement]->get_monument_jouables();
        for (auto mon : monuments_j_act) {
            if (mon->get_nom() == "CentreCommercial") {
                centre_c_possesseur = true;
            }
        }

        for (auto it : tab_joueurs[j_act_paiement]->get_liste_batiment(Rouge)) {
            if (find(it.first->get_num_activation().begin(), it.first->get_num_activation().end(), de_1 + de_2) != it.first->get_num_activation().end()) {
                if (it.first->get_type() == "restaurant" && centre_c_possesseur) {
                    for (unsigned int effectif = 0; effectif < it.second; effectif++) {
                        try{
                            it.first->declencher_effet(j_act_paiement, 1);
                        }
                        catch(exception const& e){
                            cerr << "ERREUR : " << e.what() << endl;
                        }
                    }
                } else {
                    for (unsigned int effectif = 0; effectif < it.second; effectif++) {
                        try{
                            it.first->declencher_effet(j_act_paiement);
                        }
                        catch(exception const& e){
                            cerr << "ERREUR : " << e.what() << endl;
                        }
                    }
                }
            }
        }

        j_act_paiement = (j_act_paiement + tab_joueurs.size() - 1) % tab_joueurs.size();
    }


    /// Ensuite ce sont les batiments violets du joueur actuel
    for (auto it : tab_joueurs[joueur_actuel]->get_liste_batiment(Violet)) {
        if (find(it.first->get_num_activation().begin(), it.first->get_num_activation().end(), de_1 + de_2) != it.first->get_num_activation().end()) {
            for (unsigned int effectif = 0; effectif < it.second; effectif++) {
                try{
                    it.first->declencher_effet(joueur_actuel);
                }
                catch(exception const& e){
                    cerr << "ERREUR : " << e.what() << endl;
                }
            }
        }
    }

    /// Puis, les batiments bleus de tous les joueurs
    for (int i = 0; i < tab_joueurs.size(); i++) {
        for (auto it : tab_joueurs[i]->get_liste_batiment(Bleu)) {
            if (find(it.first->get_num_activation().begin(), it.first->get_num_activation().end(), de_1 + de_2) != it.first->get_num_activation().end()) {
                for (unsigned int effectif = 0; effectif < it.second; effectif++) {
                    try{
                        it.first->declencher_effet(i);
                    }
                    catch(exception const& e){
                        cerr << "ERREUR : " << e.what() << endl;
                    }
                }
            }
        }
    }

    /// Enfin, les batiments verts du joueur actuel
    for (auto it : tab_joueurs[joueur_actuel]->get_liste_batiment(Vert)) {
        if (find(it.first->get_num_activation().begin(), it.first->get_num_activation().end(), de_1 + de_2) != it.first->get_num_activation().end()) {
            if (it.first->get_type() == "commerce" && centre_c_act) {
                for (unsigned int effectif = 0; effectif < it.second; effectif++) {
                    try{
                        it.first->declencher_effet(joueur_actuel, 1);
                    }
                    catch(exception const& e){
                        cerr << "ERREUR : " << e.what() << endl;
                    }
                }
            } else {
                for (unsigned int effectif = 0; effectif < it.second; effectif++) {
                    try{
                        it.first->declencher_effet(joueur_actuel);
                    }
                    catch(exception const& e){
                        cerr << "ERREUR : " << e.what() << endl;
                    }
                }
            }
        }
    }
    /// Fin des effets des batiments


    /// Debut de la phase de construction
    auto it_hdv = find_if(monuments_joueurs.begin(), monuments_joueurs.end(), [](Monument* m){return m->get_nom() == "HotelDeVille";});
    if (it_hdv != monuments_joueurs.end()){
        // Si le monument est trouve, on le joue
        try{
            monuments_joueurs[it_hdv - monuments_joueurs.begin()]->declencher_effet(joueur_actuel);
        }
        catch(exception const& e){
            cerr << "ERREUR : " << e.what() << endl;
        }
    }

    cout << "Le joueur \"" << tab_joueurs[joueur_actuel]->get_nom() << "\" va proceder a ses achats, voici son etat : " << endl;
    tab_joueurs[joueur_actuel]->afficher_joueur();
    cout << "Cartes du shop : " << endl;
    shop->affiche_shop_simple();

    if (!acheter_carte()) {
        cout << "Vous n'avez rien achete" << endl;
        if (tab_joueurs[joueur_actuel]->get_argent() < 2)
            tab_joueurs[joueur_actuel]->set_argent(2);

        auto it_earo = find_if(monuments_joueurs.begin(), monuments_joueurs.end(), [](Monument* m){return m->get_nom() == "Aeroport";});
        if (it_earo != monuments_joueurs.end()){
            // Si le monument est trouve, on le joue
            try{
                monuments_joueurs[it_earo - monuments_joueurs.begin()]->declencher_effet(joueur_actuel);
            }
            catch(exception const& e){
                cerr << "ERREUR : " << e.what() << endl;
            }
        }

    }
    /// Fin de la phase de construction


    /// Ouverture des batiments
    for (auto bat : tab_joueurs[joueur_actuel]->get_liste_batiment_fermes()) {
        if (find(bat->get_num_activation().begin(), bat->get_num_activation().end(), de_1 + de_2) != bat->get_num_activation().end()) {
            try {
                tab_joueurs[joueur_actuel]->ouvrir_batiment(bat);
            }
            catch(exception const& e){
                cerr << "ERREUR : " << e.what() << endl;
            }
        }
    }


    /// Fin du tour

    auto it_parc = find_if(monuments_joueurs.begin(), monuments_joueurs.end(), [](Monument* m){return m->get_nom() == "ParcAttraction";});
    if (it_parc != monuments_joueurs.end() && de_1 == de_2){
        // Si le monument est trouve, on le joue
        try{
            monuments_joueurs[it_parc - monuments_joueurs.begin()]->declencher_effet(joueur_actuel);
        }
        catch(exception const& e){
            cerr << "ERREUR : " << e.what() << endl;
        }
    }

    while (!pioche->est_vide() && shop->get_nb_tas_reel() < shop->get_nb_tas_max()) {
        try {
            shop->completer_shop(pioche->get_carte());
        }
        catch (exception const& e) {
            cerr << "ERREUR : " << e.what() << endl;
        }
    }

    cout << "----------------------------------------------------" << endl;
    cout << "\t\t\tFin du tour" << endl;
    cout << "----------------------------------------------------" << endl;
}


unsigned int Partie::selectionner_joueur(const vector<Joueur*>& tab_joueurs, unsigned int joueur_actuel){
    unsigned int count = 0;
    unsigned int selection = 0;

    //cas où la decision doit se faire par une ia
    if(tab_joueurs[joueur_actuel]->get_est_ia()){
        selection = rand() % tab_joueurs.size();
        if(selection == joueur_actuel) selection = (selection + 1)%tab_joueurs.size();
    }
    //cas où c'est un joueur reel qui prend la decision
    else{
        //Affichage de tous les joueus de tab_joueurs
        cout<<"Quel joueur voulez vous choisir parmis la liste suivante :" << endl;
        for(Joueur* curseur:tab_joueurs){
            cout<<count<<" : "<<curseur->get_nom()<<endl;
            count++;
        }

        //Scan de tab_joueurs a la recherche du nom entre
        cout<<"Indice du joueur a selectionner :"<<endl;
        cin >> selection;

        //cas où erreur (nom entre pas dans la liste ou nom entre = joueur actuel)
        if(selection > tab_joueurs.size()) throw invalid_argument("L'indice entre n'est pas valide");
        if(selection == joueur_actuel) throw invalid_argument("On ne peut pas selectionner le joueur actuel");
    }

    cout<<"joueur selectionne : "<<tab_joueurs[selection]->get_nom();
    return selection;
}


unsigned int Partie::lancer_de() {
    srand(time(nullptr));
    return rand() % 6 + 1;
}
