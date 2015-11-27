#ifndef MENU
#define MENU
#include "Fenetre.h"

#define NOMBRE_TEXTURE_MENU 2
#define LARGEUR_MENU 640
#define HAUTEUR_MENU 480
#define LARGEUR_BOUTON 150
#define HAUTEUR_BOUTON 50
#define LARGEUR_TEXTE 200
#define HAUTEUR_TEXTE 20
#define LARGEUR_SAISIE 200
#define HAUTEUR_SAISIE 40
#define LARGEUR_SAISIE_C 40
#define HAUTEUR_SAISIE_C 30
#define LARGEUR_CHECK 150
#define HAUTEUR_CHECK 20
#define LARGEUR_SPINBOX 35
#define HAUTEUR_SPINBOX 30

class Menu: public Fenetre
{
public:
	//enum
	 enum fenetres
	{
    	enum_fenetrePrincipale =0,
		enum_fenetreNouvellePartie,
		enum_fenetreChargerPartie,
	};

	enum id_menu
	{
		GUI_ID_BOUTON_QUITTER,
		GUI_ID_BOUTON_NOUVELLE_PARTIE,
		GUI_ID_BOUTON_CHARGER_PARTIE,
		GUI_ID_BOUTON_ENREGISTRER,
		GUI_ID_BOUTON_LANCER_BOCAL,
		GUI_ID_BOUTON_RETOUR_MENU,
		GUI_ID_BOUTON_PARAM,
		GUI_ID_BOUTON_H_PLUS,
		GUI_ID_BOUTON_H_MOINS,
		GUI_ID_BOUTON_M_PLUS,
		GUI_ID_BOUTON_M_MOINS,
		GUI_ID_BOUTON_S_PLUS,
		GUI_ID_BOUTON_S_MOINS,
		GUI_ID_TEXTE_NOM_PARTIE,
		GUI_ID_TEXTE_MIN_VIE,
		GUI_ID_TEXTE_MAX_VIE,
		GUI_ID_TEXTE_NBR_UNIT,
		GUI_ID_CHOIX_HEURE,
		GUI_ID_CHOIX_MINUTE,
		GUI_ID_CHOIX_SECONDE,
		GUI_ID_CHOIX_USB,
	};

	 static const wchar_t* tabPopulations[];

	//constructeur
	inline Menu(const wchar_t* titre = L"Menu ACIDE"):Fenetre(titre)
	{
		initEngine();

		_fenetre = enum_fenetrePrincipale;

		//options
		_lancementBocal = false;
		_population = 0;
		_minVie=15;
		_maxVie=25;
		_nbrUnite=20;
		_heure = 0;
		_minute = 0;
		_seconde = 0;
		_port =1;
		_nomPartie = L"Defaut";

		//textures
		//chargement textures
		_tabTextures[0] = _driver->getTexture("media/menu/imageMenu.jpg");
		_tabTextures[1] = _driver->getTexture("media/menu/imageMenu2.jpg");
	};

	inline ~Menu(void)
	{};

	//	accesseur
	inline const wchar_t *nomPartie(void){return _nomPartie;}
	inline int population(void){return _population;}
	inline int minVie(void){return _minVie;}
	inline int maxVie(void){return _maxVie;}
	inline int nbrUnite(void){return _nbrUnite;}
	inline int minute(void){return _minute;}
	inline int seconde(void){return _seconde;}
	inline int heure(void){return _heure;}
	inline int port(void){return _port;}

	//moficateur
	inline void modifierNomPartie(const wchar_t *nomPartie){_nomPartie = nomPartie;}
	inline void modifierPopulation(int population){_population = population;}
	inline void modifierLancementBocal(bool lancement){_lancementBocal = lancement;}

	//methodes
	void initEngine(void);              // création d'un engine Irrlicht et reInitialisation des options
	void fenetrePrincipale(void);
	void fenetreNouvellePartie(void);
	void fenetreChargerPartie(void);
	bool lancerMenu(void);

	//event receiver
    virtual bool OnEvent(const SEvent& event);
	
	

private:
	//widget
	enum fenetres _fenetre;
	gui::IGUIEditBox *_saisie;
	gui::IGUIEditBox *_texteMinVie;
	gui::IGUIEditBox *_texteMaxVie;
	gui::IGUIEditBox *_texteNbrUnit;
	gui::IGUIComboBox *_box;
	gui::IGUIEditBox *_choixHeure;
	gui::IGUIEditBox *_choixMinute;
	gui::IGUIEditBox *_choixSeconde;
	gui::IGUITab *_tabParamAvance; 
	gui::IGUICheckBox 	*_checkParamAvance;

	gui::IGUIEditBox *_choixPort;

	//textures
	video::ITexture* _tabTextures[NOMBRE_TEXTURE_MENU];

	//options bocal
	const wchar_t *_nomPartie;
	int _population;
	int _minVie;
	int _maxVie;
	int _nbrUnite;
	int _heure;
	int _minute;
	int _seconde;
	int _port;

	bool _lancementBocal;
};

#endif