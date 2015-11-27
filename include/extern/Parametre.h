#ifndef PARAM
#define PARAM

#include "environnement.h"

class Parametre :
	public Environnement
{
public:
	inline Parametre(Bocal *bocal, int pression = 500, int temperature = 20, int luminosite = 500):Environnement(bocal),_luminosite(luminosite), _temperature(temperature), _pression(pression){};
	inline ~Parametre(void) {};

	void majParametre(int temp, int pression, int lumi);

	//accesseurs
	inline int temperature(void){return _temperature;}
	inline int luminosite(void){return _luminosite;}
	inline int pression(void){return _pression;}

private:
	int _temperature;         //la temp�rature a l'int�rieur du bocal en degr� celsius, peut etre modifi� par le cours du temps, un �venement ou un simple changement de param�tres
	int _luminosite;            //la pression a l'int�rieur du bocal en ???, peut etre modifi� par le cours du temps, un �venement ou un simple changement de param�tres
	int _pression;            //l'humidit� a l'int�rieur du bocal repr�sent� par une valeur centr�e sur 0 les positif etant tr�s humide, les n�gatif tr�s secs, peut etre modifi� par le cours du temps, un �venement ou un simple changement de param�tres
};

#endif
