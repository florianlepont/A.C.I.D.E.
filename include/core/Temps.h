#ifndef TEMPS
#define TEMPS

#define INCREMENT_TEMPS 1 //valeur en seconde !! voir incrementerTemps() (si modification recalculer la vitesse max)
#define DUREE_MINUTE 60   
#define DUREE_HEURE 60
#define DUREE_JOUR 24

#define DEBUT_NUIT_H 21
#define DEBUT_AUBE_H 5
#define DEBUT_JOURNEE_H 8
#define DEBUT_CREPUSCULE_H 18

#define LONGUEUR_NUIT_H 8
#define LONGUEUR_AUBE_H 3
#define LONGUEUR_JOURNEE_H 10
#define LONGUEUR_CREPUSCULE_H 3

class Bocal;

class Temps
{
  public :
	// enum
	  enum periodeTemps{
		  nuit =0,
		  aube,
		  journee,
		  crepuscule,
	  };

    // déclarer le constructeur et le destructeur
    Temps(Bocal *bocal, int seconde = 0 ,int minute = 0,int heure =0, int jour=0): _bocal(bocal),_minute(minute),_seconde(seconde),_heure(heure), _jour(jour), _vitesseTemps(1),_periode(calculPeriode()){}

	//méthodes
	int incrementerTemps(void);
	enum periodeTemps calculPeriode(void);
	void afficherTemps(void);
	int calculerCadrant(double borneA, double borneB, int nombreCadrant);

	//accesseurs
	inline Bocal* bocal(void){return _bocal;}
	inline enum periodeTemps periode(void){return _periode;}
	inline int seconde(void){return _seconde;}
    inline int minute(void){return _minute;}
    inline int heure(void){return _heure;}
    inline int jour(void){return _jour;}
    

  private :
	Bocal *_bocal; //pointeur sur le bocal auquel appartient l'environnement
	int _seconde;
    int _minute;
    int _heure;
    int _jour;
    int _vitesseTemps;  //valeur à 1
	enum periodeTemps _periode;

};
#endif

