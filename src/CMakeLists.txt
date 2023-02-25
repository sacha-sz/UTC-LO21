cmake_minimum_required(VERSION 3.23)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(cartes)
include_directories(cartes/batiment)
include_directories(cartes/batiment/bleu)
include_directories(cartes/batiment/rouge)
include_directories(cartes/batiment/vert)
include_directories(cartes/batiment/violet)
include_directories(cartes/monument)
include_directories(joueur)
include_directories(controleur)
include_directories(controleur/EditionDeJeu)
include_directories(exception)
include_directories(joueur)

add_executable(src
        main.cpp

        cartes/Carte.cpp
        cartes/Carte.h

        cartes/batiment/Batiment.cpp
        cartes/batiment/Batiment.h

        cartes/monument/Monument.cpp
        cartes/monument/Monument.h

        cartes/monument/Aeroport.cpp
        cartes/monument/Aeroport.h
        cartes/monument/CentreCommercial.cpp
        cartes/monument/CentreCommercial.h
        cartes/monument/Gare.cpp
        cartes/monument/Gare.h
        cartes/monument/ParcAttraction.cpp
        cartes/monument/ParcAttraction.h
        cartes/monument/Port.cpp
        cartes/monument/Port.h
        cartes/monument/TourRadio.cpp
        cartes/monument/TourRadio.h
        cartes/monument/FabriqueDuPereNoel.cpp
        cartes/monument/FabriqueDuPereNoel.h
        cartes/monument/HotelDeVille.cpp
        cartes/monument/HotelDeVille.h

        cartes/batiment/vert/BanqueDeMinivilles.cpp
        cartes/batiment/vert/BanqueDeMinivilles.h
        cartes/batiment/vert/Boulangerie.cpp
        cartes/batiment/vert/Boulangerie.h
        cartes/batiment/vert/EntrepriseDeDemenagement.cpp
        cartes/batiment/vert/EntrepriseDeDemenagement.h
        cartes/batiment/vert/EntrepriseDeTravauxPublics.cpp
        cartes/batiment/vert/EntrepriseDeTravauxPublics.h
        cartes/batiment/vert/Epicerie.h
        cartes/batiment/vert/Epicerie.cpp
        cartes/batiment/vert/FabriqueDeMeubles.h
        cartes/batiment/vert/FabriqueDeMeubles.cpp
        cartes/batiment/vert/Fleuriste.h
        cartes/batiment/vert/Fleuriste.cpp
        cartes/batiment/vert/Fromagerie.h
        cartes/batiment/vert/Fromagerie.cpp
        cartes/batiment/vert/HalleDeMarche.cpp
        cartes/batiment/vert/HalleDeMarche.h
        cartes/batiment/vert/MarcheDeFruitsEtLegumes.h
        cartes/batiment/vert/MarcheDeFruitsEtLegumes.cpp
        cartes/batiment/vert/MoonsterSoda.h
        cartes/batiment/vert/MoonsterSoda.cpp
        cartes/batiment/vert/Superette.h
        cartes/batiment/vert/Superette.cpp
        cartes/batiment/vert/CaveAVin.cpp
        cartes/batiment/vert/CaveAVin.h

        cartes/batiment/violet/Arboretum.cpp
        cartes/batiment/violet/Arboretum.h
        cartes/batiment/violet/CentreAffaires.cpp
        cartes/batiment/violet/CentreAffaires.h
        cartes/batiment/violet/CentreImpots.cpp
        cartes/batiment/violet/CentreImpots.h
        cartes/batiment/violet/ChaineTelevision.cpp
        cartes/batiment/violet/ChaineTelevision.h
        cartes/batiment/violet/EntrepriseRenovation.cpp
        cartes/batiment/violet/EntrepriseRenovation.h
        cartes/batiment/violet/MaisonEdition.cpp
        cartes/batiment/violet/MaisonEdition.h
        cartes/batiment/violet/Stade.cpp
        cartes/batiment/violet/Stade.h
        cartes/batiment/violet/MgaGameCenter.cpp
        cartes/batiment/violet/MgaGameCenter.h

        cartes/batiment/rouge/Cafe.cpp
        cartes/batiment/rouge/Cafe.h
        cartes/batiment/rouge/ClubPrive.cpp
        cartes/batiment/rouge/ClubPrive.h
        cartes/batiment/rouge/Pizzeria.cpp
        cartes/batiment/rouge/Pizzeria.h
        cartes/batiment/rouge/Restaurant5Etoiles.cpp
        cartes/batiment/rouge/Restaurant5Etoiles.h
        cartes/batiment/rouge/Restaurant.cpp
        cartes/batiment/rouge/Restaurant.h
        cartes/batiment/rouge/StandDeHamburger.cpp
        cartes/batiment/rouge/StandDeHamburger.h
        cartes/batiment/rouge/SushiBar.cpp
        cartes/batiment/rouge/SushiBar.h

        cartes/batiment/bleu/PetitBateauDePeche.cpp
        cartes/batiment/bleu/PetitBateauDePeche.h
        cartes/batiment/bleu/Chalutier.cpp
        cartes/batiment/bleu/Chalutier.h
        cartes/batiment/bleu/ChampBle.cpp
        cartes/batiment/bleu/ChampBle.h
        cartes/batiment/bleu/ChampFleur.cpp
        cartes/batiment/bleu/ChampFleur.h
        cartes/batiment/bleu/ChampMais.cpp
        cartes/batiment/bleu/ChampMais.h
        cartes/batiment/bleu/Ferme.cpp
        cartes/batiment/bleu/Ferme.h
        cartes/batiment/bleu/Foret.cpp
        cartes/batiment/bleu/Foret.h
        cartes/batiment/bleu/Mine.cpp
        cartes/batiment/bleu/Mine.h
        cartes/batiment/bleu/Verger.cpp
        cartes/batiment/bleu/Verger.h
        cartes/batiment/bleu/Vignoble.cpp
        cartes/batiment/bleu/Vignoble.h

        controleur/EditionDeJeu/EditionDeJeu.cpp
        controleur/EditionDeJeu/EditionDeJeu.h
        controleur/Pioche.cpp
        controleur/Pioche.h
        controleur/Partie.cpp
        controleur/Partie.h
        controleur/Shop.cpp
        controleur/Shop.h
        controleur/utils.cpp
        controleur/utils.h

        joueur/Joueur.cpp
        joueur/Joueur.h

        exception/gameExeption.h
)