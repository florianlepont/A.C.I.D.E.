#ifndef ENV
#define ENV

class Bocal;

class Environnement
{
public:
	inline Environnement(Bocal *bocal): _bocal(bocal){};
	inline ~Environnement(void){};

	inline Bocal* bocal(void){return _bocal;}

protected:
	Bocal *_bocal; //pointeur sur le bocal auquel appartient l'environnement
};

#endif
