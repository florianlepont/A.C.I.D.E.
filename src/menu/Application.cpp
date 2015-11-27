#include "..\..\include\menu\Application.h"
#include <iostream>
#include <time.h>

using namespace std;

void Application::lancer(void)
{
	//pour avoir un vrai aléatoire
	srand (time(NULL));

	while(1)
	{
		int startTime = 0;
		int endTime = 0;

		if(_menu->lancerMenu())
		{
			creerBocal("truc"/*(string)_menu->nomPartie()*/,_menu->port(),_menu->nbrUnite(),_menu->population(),_menu->minVie(),_menu->maxVie(), _menu->seconde(), _menu->minute(),_menu->heure());
		}
		if(_bocal)
		{
			_bocal->fenetreBocal()->device()->getTimer()->start();
			while(_bocal->fenetreBocal()->device()->run())
			{
				startTime = _bocal->fenetreBocal()->device()->getTimer()->getTime();
				if(startTime-endTime >= _bocal->vitesseTemps() )
				{
					_bocal->evoluer();
					endTime = _bocal->fenetreBocal()->device()->getTimer()->getTime();
				}
			}
			fermerBocal();
			
		}
		else{break;}
	}
}

void Application::creerBocal(string nomPartie, int port, int nombreUnite, int population, int minVie, int maxVie, int seconde, int minute, int heure, int pression, int temperature, int luminosite)
{
	delete _menu;
	_menu =0;

	_nomPartie = nomPartie;

	_fenetreBocal = new FenetreBocal(L"Le Bocal");
	_bocal = new Bocal(_fenetreBocal, port, nombreUnite, population, minVie, maxVie, seconde, minute, heure, pression, temperature, luminosite);

}

void Application::fermerBocal()
{
	delete _bocal;
	delete _fenetreBocal;
	_fenetreBocal=0;
	_bocal=0;
	_menu = new Menu();
}