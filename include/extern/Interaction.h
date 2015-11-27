#ifndef INTER
#define INTER

#include "environnement.h"
#include  "liaisonSerie.h"

#include <iostream>
#include <vector>


using namespace std;

class Interaction :
	public Environnement
{
public:
	inline Interaction(Bocal *bocal, int port):Environnement(bocal), _temperature(0)
	{
		_portSerie[0]= "\\\\.\\COM0";        //3 (florian) 5(carmy-eden) 4(carmy-delphes)
		_portSerie[1]= "\\\\.\\COM1";
		_portSerie[2]= "\\\\.\\COM2";
		_portSerie[3]= "\\\\.\\COM3";
		_portSerie[4]= "\\\\.\\COM4";
		_portSerie[5]= "\\\\.\\COM5";
		_portSerie[6]= "\\\\.\\COM6";
		_portSerie[7]= "\\\\.\\COM7";
		_portSerie[8]= "\\\\.\\COM8";
		_portSerie[9]= "\\\\.\\COM9";

		_serialPort = new Serial(_portSerie[port]);  // On crée un nouvel objet sérial  
	};
	inline ~Interaction(void){
		if(_serialPort)delete _serialPort;
	};
	void lectureValeurs();

	//accesseurs
	inline int temperature(void){return _temperature;}
	inline int photoresistance(void){return _photoresistance;}
	inline int potentiometre(void){return _potentiometre;}
	inline bool liaisonConnecte(void){return _serialPort->IsConnected();}

private:
	Serial* _serialPort;
	int _temperature;        
	int _photoresistance;
	int _potentiometre;
	char *_portSerie[10];
};

#endif

