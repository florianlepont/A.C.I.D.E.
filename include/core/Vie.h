#ifndef VIE
#define VIE

#include "Unite.h"
#include <vector>
using namespace std;

//define
#define VALEUR_REPRODUCTION_MAX 18
#define NOMBRE_VAR_ENVIRONNEMENT 3

#define ALPHA_VALEURCENTRALE_LUMINOSITE 525
#define ALPHA_VALEURCENTRALE_TEMPERATURE 26
#define ALPHA_VALEURCENTRALE_PRESSION 500
#define ALPHA_ECART_LUMINOSITE 500
#define ALPHA_ECART_TEMPERATURE 50
#define ALPHA_ECART_PRESSION 500

#define LAMBDA_VALEURCENTRALE_LUMINOSITE  600
#define LAMBDA_VALEURCENTRALE_TEMPERATURE 25
#define LAMBDA_VALEURCENTRALE_PRESSION 200
#define LAMBDA_ECART_LUMINOSITE 200
#define LAMBDA_ECART_TEMPERATURE 10
#define LAMBDA_ECART_PRESSION 50


#define KAPPA_VALEURCENTRALE_LUMINOSITE 500
#define KAPPA_VALEURCENTRALE_TEMPERATURE 30
#define KAPPA_VALEURCENTRALE_PRESSION 500
#define KAPPA_ECART_LUMINOSITE 50
#define KAPPA_ECART_TEMPERATURE 5
#define KAPPA_ECART_PRESSION 50


#define PSI_VALEURCENTRALE_LUMINOSITE 110
#define PSI_VALEURCENTRALE_TEMPERATURE 75
#define PSI_VALEURCENTRALE_PRESSION 800
#define PSI_ECART_LUMINOSITE 75
#define PSI_ECART_TEMPERATURE 20
#define PSI_ECART_PRESSION 200

class Bocal;

class Vie
{
  public :

	 //enum
	 enum population
	 {
		 alpha = 0,
		 lambda,
		 kappa,
		 psi,
	 };

    // constructeurs
    inline Vie(Bocal *bocal, FenetreBocal* fenetre, int nombreUnites,int population, int borneInf = 15, int borneSup = 25): _bocal(bocal),_fenetre(fenetre),_population((enum population)population), _borneInf(borneInf), _borneSup(borneSup)
	{
		_uniteCentrale=0;
		for(int i=0;i <= nombreUnites-1;i++)
		{
			creerUnite((Unite*) 0,VITESSE_DEPLACEMENT);
		}
	}

	inline Vie(const Vie& vie)
	{
		_bocal = vie.bocal();

		for(int i=0;i<=vie.nombreUnites()-1;i++)
		{
			creerUnite(_unites[i],VITESSE_DEPLACEMENT);
		}
	}

	// destructeur
	inline ~Vie(void)
	{
		for(int i=0;i<_unites.size();i++)
		{
			delete _unites[i];
		}
	}

	//accesseurs
	inline int nombreUnites(void)const{return _unites.size();}
	inline Bocal* bocal(void)const{return _bocal;}
	inline int borneSup(void){return _borneSup;}
	inline int borneInf(void){return _borneInf;}
	inline Unite* unite(int i){return _unites[i];}
	inline FenetreBocal* fenetre(void){return _fenetre;}

	//methodes
    void creerUnite(Unite* u, int vitesse);
    void evoluerUnites(int temperature, int pression,int luminosite, int vitesse);
    void ajouterUnite(Unite* u);
	int calculerIndiceReproduction(int temperature, int pression,int luminosite);
	void deplacerUnite(Unite *uniteDeplace, int vitesse);
	void renfort(int vitesse);
	float valeurCentreeEnX(float valeurCentrale, float ecart,float X);

  private :
	Bocal *_bocal; //pointeur sur le bocal auquel appartient l'environnement
	FenetreBocal* _fenetre;
	Unite *_uniteCentrale; //pointeur sur la derniere unité crée (celle en (0,0)) 
	enum population _population;
	int _borneInf;   //en seconde
	int _borneSup;   //en seconde
    vector<Unite*> _unites;
};
#endif

