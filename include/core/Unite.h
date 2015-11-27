#ifndef UNITE
#define UNITE

#include "../graphique/FenetreBocal.h"
#include <iostream>

using namespace std;

class Vie;
int randBorne(int a, int b);

class Unite
{
  public :
	// enum
	  enum etatUnite{
		  mort =0,
		  attente,
		  seReproduit,
		  collision,
		  mange,
		  
	  };

    // constructeurs 
    inline Unite(Vie *vie, int dureeVie,scene::ISceneNode *node,int ligne =0, int colonne = 0, int indiceRepro =0, int age=0, enum etatUnite etat= attente): _indiceReproduction(indiceRepro),_vie(vie),_age(age),_etat(etat),_node(node), _dureeVie(dureeVie),_ligne(ligne),_colonne(colonne)
	{}

	inline ~Unite(void)
	{
		_node->remove(); 
	}

	// accesseurs
	inline int age(void){return _age;}
	inline int indiceReproduction(void){return _indiceReproduction;}
	inline int dureeVie(void){return _dureeVie;}
	inline enum etatUnite etat(void){return _etat;}
	inline scene::ISceneNode *node(void){return _node;}
	inline int ligne(void){return _ligne;}
	inline int colonne(void){return _colonne;}
	

	//modificateurs
	inline void changerEtat( enum etatUnite etat){_etat = etat;}
	inline void changerPos(int ligne, int colonne){_ligne=ligne, _colonne = colonne;}

	// methodes
    int incrementerAge(int delta);
	void incrementerIndiceR(int deltaIndice);
    int seReproduire(int indice,int delta);

  private :
    int _age;        //en seconde
	int _dureeVie;   //en seconde
    enum etatUnite _etat;
	int _indiceReproduction;   //de 0 à 100
	Vie *_vie;
	
	//graphique
	scene::ISceneNode *_node;
	int _ligne;       //placement dans la grille
	int _colonne;


};
#endif
