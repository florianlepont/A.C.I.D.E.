#include "..\..\include\core\Bocal.h"

void Bocal::evoluer(void)
{
	int temperature=-1,pression=-1,luminosite=-1;

	_externUtilise=_fenetre->majAffichageExtern(_interaction->liaisonConnecte()); //vérification que la liaison série est toujours connecté et maj de l'affichage
	if(_externUtilise)
	{
		_interaction->lectureValeurs();    // mise a jour des valeurs par la liaison série
		temperature = _interaction->temperature();
		luminosite = _interaction->photoresistance();
		pression =_interaction->potentiometre();
	}
	else
	{
		_parametre->majParametre(_fenetre->temperature(),_fenetre->pression(),_fenetre->luminosite());
		temperature = _parametre->temperature();
		luminosite = _parametre->luminosite();
		pression =_parametre->pression();
	}
	_vitesseTemps = _fenetre->majVitesseTemps();
	_vitesseDeplacement = 2*_vitesseTemps;
	_lecture = _fenetre->majAffichageEnvironnement(temperature,pression,luminosite);

	if(_lecture)
	{
		//avancer l'heure
		_temps->incrementerTemps();      //incrément du temps, évolution de la periode de la journée
		
		//faire bouger les unités
		_vie->evoluerUnites(temperature,pression,luminosite,_vitesseDeplacement);           // reproduction déplacement et mort des unites selon l'ambiance et la periode
		if(_vie->nombreUnites()==0)
		{_fenetre->pauseForce();}

		//gestion de l'indicateur
		if((_effectifPrecedent - _vie->nombreUnites())< -MARGE_INDICATEUR){_fenetre->indiquerAugmentation();}
		else if((_effectifPrecedent - _vie->nombreUnites())> MARGE_INDICATEUR){_fenetre->indiquerDiminution();}
		else{_fenetre->indiquerStable();}

		_effectifPrecedent=_vie->nombreUnites();
	}

	if(_fenetre->renfort())
	{
		_vie->renfort(_vitesseDeplacement);
		_fenetre->redemarrage();
	}

	reglerEclairage();               
	_fenetre->majAffichageTemps(_temps->jour(),_temps->heure(),_temps->minute(),_temps->seconde(),_temps->periode()); //afficher l'heure dans le bocal
	_fenetre->majAffichageUnites(_vie->nombreUnites());

	_fenetre->majBocal();

}

//regler la luminosité en fonction du temps
void Bocal::reglerEclairage()
{
	int r=0,v=0,b=0;
	int rNuit=118,rAube=247,rJour=255,rCrepu=163;
	int vNuit=136,vAube=184,vJour=255,vCrepu=146;
	int bNuit=245,bAube=252,bJour=240,bCrepu=197;


		if(_temps->heure()<(DEBUT_AUBE_H - LONGUEUR_NUIT_H/2) || _temps->heure()>=(DEBUT_CREPUSCULE_H+LONGUEUR_CREPUSCULE_H/2))
		{
			int cadrant = _temps->calculerCadrant(DEBUT_CREPUSCULE_H+LONGUEUR_CREPUSCULE_H/2,DEBUT_NUIT_H + LONGUEUR_NUIT_H/2,NOMBRE_PHASE_LUMIERE);
			r=rCrepu+cadrant*(rNuit-rCrepu)/NOMBRE_PHASE_LUMIERE;
			v=vCrepu+cadrant*(vNuit-vCrepu)/NOMBRE_PHASE_LUMIERE;
			b=bCrepu+cadrant*(bNuit-bCrepu)/NOMBRE_PHASE_LUMIERE;	
		}
		if(_temps->heure()>=(DEBUT_AUBE_H - LONGUEUR_NUIT_H/2) && _temps->heure()<(DEBUT_AUBE_H + LONGUEUR_AUBE_H/2))
		{
			int cadrant = _temps->calculerCadrant(DEBUT_AUBE_H - LONGUEUR_NUIT_H/2,DEBUT_AUBE_H + LONGUEUR_AUBE_H/2,NOMBRE_PHASE_LUMIERE);
			r=rNuit+cadrant*(rAube-rNuit)/NOMBRE_PHASE_LUMIERE;
			v=vNuit+cadrant*(vAube-vNuit)/NOMBRE_PHASE_LUMIERE;
			b=bNuit+cadrant*(bAube-bNuit)/NOMBRE_PHASE_LUMIERE;
		}
		if(_temps->heure()>=(DEBUT_AUBE_H + LONGUEUR_AUBE_H/2) && _temps->heure()<(DEBUT_JOURNEE_H+LONGUEUR_JOURNEE_H/2))
		{
			int cadrant = _temps->calculerCadrant(DEBUT_AUBE_H + LONGUEUR_AUBE_H/2,DEBUT_JOURNEE_H+LONGUEUR_JOURNEE_H/2,NOMBRE_PHASE_LUMIERE);
			r=rAube+cadrant*(rJour-rAube)/NOMBRE_PHASE_LUMIERE;
			v=vAube+cadrant*(vJour-vAube)/NOMBRE_PHASE_LUMIERE;
			b=bAube+cadrant*(bJour-bAube)/NOMBRE_PHASE_LUMIERE;	
		}
		if(_temps->heure()>=(DEBUT_JOURNEE_H+LONGUEUR_JOURNEE_H/2) && _temps->heure()<(DEBUT_CREPUSCULE_H+LONGUEUR_CREPUSCULE_H/2))
		{
			int cadrant = _temps->calculerCadrant(DEBUT_JOURNEE_H+LONGUEUR_JOURNEE_H/2,DEBUT_CREPUSCULE_H+LONGUEUR_CREPUSCULE_H/2,NOMBRE_PHASE_LUMIERE);
			r=rJour+cadrant*(rCrepu-rJour)/NOMBRE_PHASE_LUMIERE;
			v=vJour+cadrant*(vCrepu-vJour)/NOMBRE_PHASE_LUMIERE;
			b=bJour+cadrant*(bCrepu-bJour)/NOMBRE_PHASE_LUMIERE;	
		}

	_fenetre->changerLumiereAmbiance(r,v,b);

}
