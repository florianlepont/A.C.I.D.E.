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
	int _temperature;         //la température a l'intérieur du bocal en degré celsius, peut etre modifié par le cours du temps, un évenement ou un simple changement de paramètres
	int _luminosite;            //la pression a l'intérieur du bocal en ???, peut etre modifié par le cours du temps, un évenement ou un simple changement de paramètres
	int _pression;            //l'humidité a l'intérieur du bocal représenté par une valeur centrée sur 0 les positif etant très humide, les négatif très secs, peut etre modifié par le cours du temps, un évenement ou un simple changement de paramètres
};

#endif
