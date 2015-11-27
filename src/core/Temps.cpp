#include "..\..\include\core\Temps.h"
#include <iostream>

using namespace std;

void Temps::afficherTemps()  //A MODIF : affichage dans la fenetre bocal
{
	cout <<"  jour: "<<_jour<<"   "<< _heure<<":"<<_minute<<":"<< _seconde<<endl;
}


int Temps::incrementerTemps()
{
	int delta = INCREMENT_TEMPS*_vitesseTemps;            //calcul du delta temporel
	_seconde = _seconde + INCREMENT_TEMPS*_vitesseTemps;  //incrément des secondes

	if(_seconde>=DUREE_MINUTE)                                     //test du dépassement de valeur des secondes
	{
		for(int i=1; i<=DUREE_MINUTE;i++)
		{
			if(_seconde>=DUREE_MINUTE*i && _seconde<=DUREE_MINUTE*(i+1))
			{
				_seconde = _seconde-DUREE_MINUTE*i;
				_minute = _minute +i;
				break;
			}
		}
	}
	if(_minute>=DUREE_HEURE)                                     //test du dépassement de valeur des minutes
	{
		for(int i=1; i<=DUREE_HEURE;i++)
		{
			if(_minute>=DUREE_HEURE*i && _minute<=DUREE_HEURE*(i+1))
			{
				_minute = _minute-DUREE_HEURE*i;
				_heure = _heure +i;
				break;
			}
		}
	}
	if(_heure>=DUREE_JOUR)                                     //test du dépassement de valeur des heures
	{
		for(int i=1; i<=DUREE_JOUR;i++)
		{
			if(_heure>=DUREE_JOUR*i && _heure<=DUREE_JOUR*(i+1))
			{
				_heure = _heure-DUREE_JOUR*i;
				_jour = _jour +i;
				break;
			}
		}
	}
	_periode = this->calculPeriode();

	return delta;
}

enum Temps::periodeTemps Temps::calculPeriode()
{
	if (_heure < DEBUT_AUBE_H || _heure >= DEBUT_NUIT_H)
	{
		return nuit;
	}
	else if (_heure >= DEBUT_CREPUSCULE_H)
	{
		return crepuscule;
	}
	else if (_heure >= DEBUT_JOURNEE_H)
	{
		return journee;
	}
	else
	{
		return aube;
	}
}

int Temps::calculerCadrant(double borneA, double borneB, int nombreCadrant)
{
	if(borneB<borneA){borneB=borneB+24+1;}
	double increment = (borneB-borneA)/nombreCadrant;

	double heureF = _heure;
	if(heureF<borneA){heureF=heureF+24;}
	heureF = heureF + 0.01*_minute*100/60 + 0.0001*_seconde*100/60;
	int cadrant=0;
	for(int i=0;i<nombreCadrant;i++)
	{
		if(heureF<(borneA + (i+1)*increment))
		{
			cadrant = i;
			break;
		}
	}
	return cadrant;
}
