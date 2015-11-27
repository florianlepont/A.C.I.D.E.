#ifndef BOCAL
#define BOCAL

#include "Vie.h"
#include "Temps.h"
#include "../extern/Interaction.h"
#include "../extern/Parametre.h"

#define NOMBRE_PHASE_LUMIERE 20

using namespace std;

class Bocal
{
  public :		
  //constructeurs
	  inline Bocal(FenetreBocal* fenetre, int port =1, int nombreUnite = 20, int population = 0, int minVie = 15, int maxVie = 25, int seconde = 0, int minute=0, int heure=0, int pression = 0, int temperature = 20, int luminosite = 0):_fenetre(fenetre),_effectifPrecedent(nombreUnite),_externUtilise(false),_lecture(true),_vitesseTemps(TEMPS_SCENE), _vitesseDeplacement(VITESSE_DEPLACEMENT)
  {
	  _fenetre->generationScene();
	  _fenetre->generationMenu();
	  _vie = new Vie(this,_fenetre,nombreUnite,population,minVie,maxVie);
	  _temps = new Temps(this,seconde,minute,heure);
	  _parametre = new Parametre(this, pression, temperature, luminosite);
	  _interaction = new Interaction(this,port);
  }

  inline Bocal(const Bocal& bocal)
  {
	 _vie = bocal.vie();
	 _temps = bocal.temps();
	 _parametre = bocal.parametre();
	 _interaction = bocal.interaction();
	 _fenetre = bocal.fenetreBocal();
  }

  //destructeur
  inline ~Bocal(void)
  {
	  if(_vie) delete _vie;
	  if(_temps) delete _temps;
	  if(_parametre) delete _parametre;
	  if(_interaction) delete _interaction;
  }

  //methodes
  void evoluer(void);
  void reglerEclairage(void);

  //modificateur
  inline void lierFenetre(FenetreBocal *fenetre){_fenetre = fenetre;}

  //accesseurs
  inline Vie* vie(void)const {return _vie;}
  inline Temps* temps(void)const{return _temps;}
  inline Parametre* parametre(void)const{return _parametre;}
  inline Interaction* interaction(void)const{return _interaction;}
  inline FenetreBocal* fenetreBocal(void)const{return _fenetre;}
  inline int vitesseTemps(void){return _vitesseTemps;}

  private :
	Vie* _vie;
	Temps* _temps;
    Parametre* _parametre;
    Interaction* _interaction;
	FenetreBocal* _fenetre;

	int _effectifPrecedent;
	int _vitesseTemps;
	int _vitesseDeplacement;

	bool _externUtilise;
	bool _lecture;
	
};
#endif


