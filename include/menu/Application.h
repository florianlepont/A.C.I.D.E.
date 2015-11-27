#ifndef APPLI
#define APPLI

#include <string>
#include "Menu.h"
#include "../core/Bocal.h"
#include "../graphique/FenetreBocal.h"

using namespace std;


class Application
{
public:
	//constructeurs
	inline Application(void)
	{
		//menu
		_menu = new Menu();

		//fenetre Bocal
		_fenetreBocal = 0;

		//bocal
		_bocal=0;

		//son
		_son=0;
	};

	inline ~Application(void)
	{
		 if(_bocal){delete _bocal;}
		 if(_menu){delete _menu;}
		 if(_fenetreBocal){delete _fenetreBocal;}
	};

	//accesseurs
	inline Menu* menu(void){return _menu;}
	inline Bocal* bocal(void){return _bocal;}

	//methodes
	void lancer(void);

	// crée le bocal et la fenetre Bocal avec les parametre donné
	void creerBocal(string nomPartie="default",int port =1, int nombreUnite = 20, int population = 0, int minVie = 15, int maxVie = 25, int seconde = 0, int minute=0, int heure=0, int pression = 400, int temperature = 20, int luminosite = 200);
	// détruit le bocal, réinitialise le pointeur et recrée la fenetre menu;
	void fermerBocal(void);

private:
	//Acide
	string _nomPartie;

	//Menu
	Menu *_menu;

	//FenetreBocal
	FenetreBocal *_fenetreBocal;

	//Bocal
	Bocal *_bocal;

	//Son
	Son *_son;
};

#endif