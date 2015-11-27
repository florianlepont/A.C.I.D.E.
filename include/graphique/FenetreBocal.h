#pragma once
#include "../menu/Fenetre.h"
#include "../musique/Son.h"
#include <iostream>

#define NOMBRE_TEXTURE_UNIT 8
#define NOMBRE_TEXTURE_AUTRE 22-8

#define TAILLE_UNITE 1
#define NOMBRE_COTE_UNITE 6
#define TEMPS_SCENE 50
#define VITESSE_DEPLACEMENT TEMPS_SCENE*2

#define MAX_UNITE 600
#define MIN_UNITE 0

#define LIMITE_BOCAL 19
#define TAILLE_QUADRILLAGE ((LIMITE_BOCAL*2)/TAILLE_UNITE+1)

#define PI 3.14159
#define DIFFERENCE_MINIMAL 0.25
#define MARGE_INDICATEUR 10

#define LARGEUR_JOUR 50
#define LARGEUR_HEURE 50
#define LARGEUR_MINUTE 50
#define LARGEUR_SECONDE 50
#define LARGEUR_TEXTE 20
#define LARGEUR_TEXTE_MIN 45
#define HAUTEUR_TEXTE 30
#define LARGEUR_CHECK 250
#define LARGEUR_NOMBRE 180
#define HAUTEUR_NOMBRE 100
#define LARGEUR_TEXTE_NOMBRE 120
#define LARGEUR_BAR 300
#define HAUTEUR_BAR 30
#define LARGEUR_TEXTE_BAR 150
#define LARGEUR_BOUTON 50
#define HAUTEUR_BOUTON 50
#define LARGEUR_TEXTE_VITESSE 400


class FenetreBocal :
	public Fenetre
{
public:

	enum idBocal
	{
		GUI_ID_SCROLL_BAR_CHOIX_PRESSION=0,
		GUI_ID_SCROLL_BAR_CHOIX_TEMPERATURE,
		GUI_ID_SCROLL_BAR_CHOIX_LUMINOSITE,
		GUI_ID_SCROLL_BAR_CHOIX_VITESSE,
		GUI_ID_CHECK_EXTERN,
		GUI_ID_BOUTON_QUITTER,
		GUI_ID_BOUTON_SON,
		GUI_ID_BOUTON_LECTURE,
		GUI_ID_BOUTON_RENFORT,
	};

	//constructeur
	inline FenetreBocal(const wchar_t* titre = L"Bocal"):Fenetre(titre),_musique(true),_renfort(false)
	{
		initEngine();

		//son
		_son = new Son();
		_son->jouerSonJeux();

		f32 Xpos =-LIMITE_BOCAL;
		f32 Zpos =0;
		bool pair=true;

		for(int j=0; j<TAILLE_QUADRILLAGE;j++)                       //initialisation de la grille de placement à vide
		{
			for(int i=0; i<TAILLE_QUADRILLAGE;i++)
			{
				_placementGrille[i][j]=0;
			}
		}

		for(int j=TAILLE_QUADRILLAGE/2; j<TAILLE_QUADRILLAGE;j++)     //calcul des positions du cadran à droite
		{
			for(int i=0; i<TAILLE_QUADRILLAGE;i++)
			{
				_grille[i][j].X=Xpos;
				_grille[i][j].Y=0;
				_grille[i][j].Z=Zpos;
				Xpos++;
			}
			Zpos=Zpos+TAILLE_UNITE*sin(2*2*PI/NOMBRE_COTE_UNITE-PI);
			if(pair)
			{
				Xpos=-LIMITE_BOCAL+0.5;
				pair=false;
			}
			else
			{
				Xpos=-LIMITE_BOCAL;
				pair=true;
			}
		}
		for(int j=0; j<TAILLE_QUADRILLAGE/2;j++)                  //recopie par symétrie des positions du cadran droit sur le cadran gauche
		{
			for(int i=0; i<TAILLE_QUADRILLAGE;i++)
			{
				_grille[i][j].X=_grille[i][TAILLE_QUADRILLAGE-1-j].X;
				_grille[i][j].Z=-_grille[i][TAILLE_QUADRILLAGE-1-j].Z;
			}
		}

		//chargement textures
		_tabTextures[0] = _driver->getTexture("media/unite/UniteBlanche.png");
		_tabTextures[1] = _driver->getTexture("media/unite/UniteNoire.png");
		_tabTextures[2] = _driver->getTexture("media/unite/UniteJaune.png");
		_tabTextures[3] = _driver->getTexture("media/unite/UniteOrange.png");
		_tabTextures[4] = _driver->getTexture("media/unite/UniteBleu.png");
		_tabTextures[5] = _driver->getTexture("media/unite/UniteVerte.png");
		_tabTextures[6] = _driver->getTexture("media/unite/UniteRose.png");
		_tabTextures[7] = _driver->getTexture("media/unite/UniteRouge.png");
		_tabTextures[8] = _driver->getTexture("media/bocal/murs.jpg");
		_tabTextures[9] = _driver->getTexture("media/bocal/nuit.png");
		_tabTextures[10] = _driver->getTexture("media/bocal/aube.png");
		_tabTextures[11] = _driver->getTexture("media/bocal/jour.png");
		_tabTextures[12] = _driver->getTexture("media/bocal/crepuscule.png");
		_tabTextures[13] = _driver->getTexture("media/bocal/augmentation.png");
		_tabTextures[14] = _driver->getTexture("media/bocal/stable.png");
		_tabTextures[15] = _driver->getTexture("media/bocal/diminution.png");
		_tabTextures[16] = _driver->getTexture("media/bouton/sonDesactive.png");
		_tabTextures[17] = _driver->getTexture("media/bouton/sonActive.png");
		_tabTextures[18] = _driver->getTexture("media/bouton/pause.png");
		_tabTextures[19] = _driver->getTexture("media/bouton/play.png");
		_tabTextures[20] = _driver->getTexture("media/bouton/shutDown.png");
		_tabTextures[21] = _driver->getTexture("media/bouton/restart.png");
	};
	
	inline ~FenetreBocal(void)
	{
		delete _son;
	};

	//accesseurs
	inline video::ITexture* tabTextures(int indice){return _tabTextures[indice];}
	inline core::vector3df grille(int ligne, int colonne){return _grille[ligne+TAILLE_QUADRILLAGE/2][colonne+TAILLE_QUADRILLAGE/2];}
	inline int placementGrille(int ligne, int colonne){return _placementGrille[ligne+TAILLE_QUADRILLAGE/2][colonne+TAILLE_QUADRILLAGE/2];}
	inline int temperature(void){return _scrollbarTemperature->getPos();}
	inline int luminosite(void){return _scrollbarLuminosite->getPos();}
	inline int pression(void){return _scrollbarPression->getPos();}
	inline bool renfort(){return _renfort;}


	//modificateurs
	inline void placer(int ligne, int colonne){_placementGrille[ligne+TAILLE_QUADRILLAGE/2][colonne+TAILLE_QUADRILLAGE/2]=1;}
	inline void retirer(int ligne, int colonne){_placementGrille[ligne+TAILLE_QUADRILLAGE/2][colonne+TAILLE_QUADRILLAGE/2]=0;}
	void pauseForce(void);
	void redemarrage(void);
	//image indicateur
	inline void indiquerAugmentation(void){_indicateur->setImage(_tabTextures[13]);}
	inline void indiquerStable(void){_indicateur->setImage(_tabTextures[14]);}
	inline void indiquerDiminution(void){_indicateur->setImage(_tabTextures[15]);}

	//methodes d'initialisation
	void initEngine(void);
	void generationScene();
	void generationMenu();
	void placerCamera();

	//event receiver
    virtual bool OnEvent(const SEvent& event);
	
	//methodes d'affichage 
	void majBocal();

	// ... Menu Bocal
	void majAffichageTemps(int jour, int heure, int minute, int seconde, int periode);
	void majAffichageUnites(int nbrUnite);
	bool majAffichageEnvironnement(int temp, int pression, int lumi);
	bool majAffichageExtern(bool externPossible);
	int majVitesseTemps(void);

	// ... Définit la lumière d'ambiance.
	void changerLumiereAmbiance(int r, int g, int b);

	// ... gestion unités
	scene::ISceneNode* creerUnite(video::ITexture *texture, int x=0 ,int y=0 , int z=0);
	void creerMouvementUnite(scene::ISceneNode* unite,core::vector3df depart,  core::vector3df fin, u32 vitesse);
	void creerMouvementCamera(scene::ICameraSceneNode* camera,int xDepart, int yDepart, int zDepart, int xFin, int yFin, int zFin, u32 vitesse, bool boucle = false, bool pingPong = false);
	void supprimerUnite(scene::ISceneNode* unite);

private:
	//scene
		gui::ICursorControl *_curseur;
		scene::ISceneNode *_unite;
		scene::ISceneNode *_unites;
		core::vector3df _grille[TAILLE_QUADRILLAGE][TAILLE_QUADRILLAGE];   // _grille[ligne][colonne]
		char _placementGrille[TAILLE_QUADRILLAGE][TAILLE_QUADRILLAGE];    // _placementGrille[ligne][colonne], 1: la place est occupé 0: la place est libre
		video::ITexture* _tabTextures[NOMBRE_TEXTURE_UNIT+NOMBRE_TEXTURE_AUTRE];
		Son *_son;

	//menu bocal
		bool _externPossible;
		bool _musique;
		bool _renfort;

		f32 _largeur;
		f32 _hauteur;
		gui::IGUIStaticText *_nombreJour;
		gui::IGUIStaticText *_nombreHeure;
		gui::IGUIStaticText *_nombreMinute;
		gui::IGUIStaticText *_nombreSeconde;
		gui::IGUIStaticText *_nombreUnite;

		gui::IGUIStaticText *_valeurPression;
		gui::IGUIStaticText *_valeurTemperature;
		gui::IGUIStaticText *_valeurLuminosite;
		gui::IGUIStaticText *_valeurVitesse;

		gui::IGUITab *_tabExtern; 
		gui::IGUICheckBox 	*_checkExtern;

		gui::IGUIScrollBar* _scrollbarLuminosite;
		gui::IGUIScrollBar* _scrollbarTemperature;
		gui::IGUIScrollBar* _scrollbarPression;
		gui::IGUIScrollBar* _scrollbarVitesse;

		gui::IGUIButton* _boutonQuitter;
		gui::IGUIButton* _boutonSon;
		gui::IGUIButton* _boutonLecture;
		gui::IGUIButton* _boutonRenfort;

		gui::IGUIImage *_periode;
		gui::IGUIImage *_indicateur;
	
};

