#include "..\..\include\core\Vie.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

void Vie::ajouterUnite(Unite* u)
{
	_unites.push_back(u);
}

void Vie::renfort(int vitesse)
{
		for(int i=0;i < 20;i++)
		{
			creerUnite((Unite*) 0,vitesse);
		}
}

void Vie::creerUnite(Unite* u,int  vitesse)
{
	core::vector3df positionNode(0);
	int ligne=0; int colonne=0;
	if(u)
	{
		positionNode = u->node()->getPosition();
		ligne = u->ligne();
		colonne = u->colonne();
	}

	scene::ISceneNode* node = _fenetre->creerUnite(_fenetre->tabTextures(randBorne(0,NOMBRE_TEXTURE_UNIT-1)), positionNode.X, 0, positionNode.Z);

	_unites.push_back(new Unite(this,randBorne(_borneInf, _borneSup),node,ligne,colonne));
	deplacerUnite(_unites.back(),vitesse);
	_uniteCentrale = _unites.back();
}

void Vie::evoluerUnites(int temperature, int pression,int luminosite, int vitesse)
{
	int deltaUnite=-1;
	int indiceReproduction=0;
	int nbrFilles = 0;
	
	for(int i=0; i<_unites.size();i++)
	{
		//augmenter l'age de l'unite (enregistrer le delta)
		deltaUnite = _unites[i]->incrementerAge(1);
		if(_unites.size()< MAX_UNITE)
		{
			//calculer l'indice de reproduction et crée autant d'unite que nécessaire selon le delta
			indiceReproduction = calculerIndiceReproduction(temperature, pression,luminosite);
			nbrFilles=_unites[i]->seReproduire(indiceReproduction,deltaUnite);

			for(int j=0; j<nbrFilles;j++)
			{
				creerUnite(_unites[i], vitesse);
			}/**/
		}
	}
	// **** mort  des unités ****

	for(int i=_unites.size()-1; i>=0;i--)         //parcours de la boucle a l'envers pour effacer les unités mortes du vector
	{
		//appliquer la mort si nécéssaire
		if (_unites[i]->etat() == Unite::mort)
		{
			_fenetre->retirer(_unites[i]->ligne(),_unites[i]->colonne());
			delete _unites[i];
			_unites.erase(_unites.begin()+i);
			
		}
	}/**/
	
}

void Vie::deplacerUnite(Unite *uniteDeplace, int vitesse)
{
	int ligne = uniteDeplace->ligne(); //On récupère la position actuel de l'unité déplacé
	int colonne = uniteDeplace->colonne();
	core::vector3df positionNode=_fenetre->grille(ligne,colonne);
	
	if(_fenetre->placementGrille(ligne,colonne))
	{
		Unite* uniteSuivante =0;
		core::vector3df positionSuivante;
		int lignePrec = ligne;
		int colonnePrec = colonne;
		int direction;

		do{   //a cause des coins qui font des segfaults
			direction = randBorne(0,NOMBRE_COTE_UNITE-1);    // on choisit la direction au hasard
			switch(direction)
			{
				case 0:
					ligne++;
					if(ligne >= TAILLE_QUADRILLAGE/2)
					{ligne = ligne - 2;}
					break;
				case 1:
					colonne--;
					//if(colonnePrec%2){ligne++;}     //si la colonne est IMPAIR
					if(colonne <= -TAILLE_QUADRILLAGE/2)
					{
						colonne = colonne + 2;
						ligne--;
					}
					break;
				case 2:
					colonne--;
					//if(!colonnePrec%2){ligne--;}     //si la colonne est PAIR
					if(ligne <= -TAILLE_QUADRILLAGE/2 || colonne <= -TAILLE_QUADRILLAGE/2)
					{
						colonne = colonne + 2;
						ligne++;
					}
					break;
				case 3:
					ligne--;
					if(ligne <= -TAILLE_QUADRILLAGE/2)
					{ligne = ligne + 2;}
					break;
				case 4:
					colonne++;
					//if(!colonnePrec%2){ligne--;}       //si la colonne est PAIR
					if(ligne <= -TAILLE_QUADRILLAGE/2 || colonne >= TAILLE_QUADRILLAGE/2)
					{
						colonne = colonne - 2;
						ligne++;
					}
					break;
				case 5:
					colonne++;
					//if(colonnePrec%2){ligne++;}            //si la colonne est IMPAIR
					if(colonne >= TAILLE_QUADRILLAGE/2)
					{
						colonne = colonne - 2;
						ligne--;
					}
					break;
			}

		}while(ligne >= TAILLE_QUADRILLAGE/2 || ligne < -TAILLE_QUADRILLAGE/2 || colonne < -TAILLE_QUADRILLAGE/2 || colonne >= TAILLE_QUADRILLAGE/2);

		if(_fenetre->placementGrille(ligne,colonne))
		{
			for(int i=0; i<_unites.size();i++)              //on recherche l'unite suivante
			{
				if(_unites[i]->ligne()==ligne && _unites[i]->colonne()==colonne)
				{
					if(_unites[i]->etat() == Unite::mort)
					{
					}
					{
						uniteSuivante = _unites[i];
					}
					break;
				}
			}
		}
		positionSuivante=_fenetre->grille(ligne,colonne);
		uniteDeplace->node()->setPosition(positionSuivante);   //deplacer l'unité pour qu'elle mérite son nom
		uniteDeplace->changerPos(ligne,colonne);
		_fenetre->creerMouvementUnite(uniteDeplace->node(),positionNode, positionSuivante, vitesse);  //crée un effet de déplacement
		_fenetre->placer(ligne,colonne);       //mettre a jour la grille de placement
		if(uniteSuivante)
		{
			deplacerUnite(uniteSuivante, vitesse);
		}
	}
	else
	{
		_fenetre->placer(ligne,colonne);
	}
}

float Vie::valeurCentreeEnX(float valeurCentrale,float ecart,float X)
{
	float Y;

	Y=-(X-valeurCentrale+ecart)*(X-valeurCentrale-ecart);
	if(Y<0){return 0;}
	return Y*100/(ecart*ecart);
}

int Vie::calculerIndiceReproduction(int temperature, int pression,int luminosite)
{
	float valeurMax=VALEUR_REPRODUCTION_MAX/NOMBRE_VAR_ENVIRONNEMENT;
	float valeur;

	switch(_population)
	{
		case alpha:
			valeur=valeurMax*(valeurCentreeEnX(ALPHA_VALEURCENTRALE_LUMINOSITE,ALPHA_ECART_LUMINOSITE,luminosite)+valeurCentreeEnX(ALPHA_VALEURCENTRALE_TEMPERATURE,ALPHA_ECART_TEMPERATURE,temperature)+valeurCentreeEnX(ALPHA_VALEURCENTRALE_PRESSION,ALPHA_ECART_PRESSION,pression))/100;
			valeur=randBorne(valeur-5,valeur+5);
			break;

		case lambda:
			valeur=valeurMax*(valeurCentreeEnX(LAMBDA_VALEURCENTRALE_LUMINOSITE,LAMBDA_ECART_LUMINOSITE,luminosite)+valeurCentreeEnX(LAMBDA_VALEURCENTRALE_TEMPERATURE,LAMBDA_ECART_TEMPERATURE,temperature)+valeurCentreeEnX(LAMBDA_VALEURCENTRALE_PRESSION,LAMBDA_ECART_PRESSION,pression))/100;
			valeur=randBorne(valeur-5,valeur+5);
			break;

		case kappa:
			valeur=valeurMax*(valeurCentreeEnX(KAPPA_VALEURCENTRALE_LUMINOSITE,KAPPA_ECART_LUMINOSITE,luminosite)+valeurCentreeEnX(KAPPA_VALEURCENTRALE_TEMPERATURE,KAPPA_ECART_TEMPERATURE,temperature)+valeurCentreeEnX(KAPPA_VALEURCENTRALE_PRESSION,KAPPA_ECART_PRESSION,pression)/100);
			valeur = randBorne(valeur-5,valeur+5);
			break;

		case psi:
			valeur=valeurMax*(valeurCentreeEnX(PSI_VALEURCENTRALE_LUMINOSITE,PSI_ECART_LUMINOSITE,luminosite)+valeurCentreeEnX(PSI_VALEURCENTRALE_TEMPERATURE,PSI_ECART_TEMPERATURE,temperature)+valeurCentreeEnX(PSI_VALEURCENTRALE_PRESSION,PSI_ECART_PRESSION,pression))/100;
			valeur=randBorne(valeur-5,valeur+5);
			break;
	}
	if(valeur<0){valeur=0;}
	return valeur;
}


