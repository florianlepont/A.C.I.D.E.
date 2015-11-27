#include "..\..\include\core\Unite.h"

int randBorne(int a, int b)
{
	return a + (rand() % (b - a +1));
}

int Unite::seReproduire(int indice,int delta)
{
	int nbrFille = 0;
	int deltaIndice = delta*indice;
	incrementerIndiceR(deltaIndice);
	if(_indiceReproduction>=100)
	{
		nbrFille=nbrFille + _indiceReproduction/100;
		_indiceReproduction=0;
	}
	return nbrFille;
}

void Unite::incrementerIndiceR(int deltaIndice)
{
	_indiceReproduction = _indiceReproduction + deltaIndice;
}

int Unite::incrementerAge(int delta)
{
	_age = _age + delta;
	if (_age >= _dureeVie)
	{
		_etat=mort;
		return _dureeVie - (_age - delta);   //retourner le temps qu'il reste a vivre a l'unite avant sa mort effective
	}
	return delta;
}
