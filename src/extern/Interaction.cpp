#include "..\..\include\extern\Interaction.h"


#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <stdlib.h>     /* atoi */
#include <string>


void Interaction::lectureValeurs(){

	char donneeEntrante[256] = "";			//On crée un e_SPace mémoire pour le Buffer
	int tailleDonnee = 256;

	int lectureResultat = 0;
	int reception = 0;


	if(_serialPort->IsConnected())   // Si on est connecté
	{
		lectureResultat =_serialPort->ReadData(donneeEntrante,tailleDonnee); // on lit la donnée di_SPo sur la liaison 
		reception=atoi(donneeEntrante);

		if ((reception >= 10000) && (reception < 20000)) {
		_photoresistance = reception - 10000;
		}

		else if ((reception >= 20000) && (reception < 30000)) {
		_temperature = reception - 20000;
		}

		else if ((reception >= 30000) && (reception < 40000)) {
		_potentiometre = reception - 30000;
		}

		/*else if ((reception >= 40000) && (reception < 40000)) {
		tilt = reception - 40000;
		}*/
		
		/*std::cout <<"photoresistance : "<< photoResistance << std::endl;
		std::cout <<"temperature : "<< temperature << std::endl;
		std::cout <<"potar : "<< potar << std::endl;
		std::cout <<"tilt : "<< tilt << std::endl;*/

		Sleep(20);
	}
}



