#ifndef FENETRE
#define FENETRE
#include <string>
#include "irrlicht.h"

using namespace irr;
using namespace std;

class Fenetre : public IEventReceiver
{
public:

	// constructeur
	Fenetre(const wchar_t* titre = L"Menu ACIDE"):_titre(titre)
	{
		//irrlicht
		_device = 0;
		_driver = 0;
		_env = 0;
		_smgr = 0;

	};
	inline ~Fenetre(void)
	{
		if(_device){_device->drop();}
	};

	//accesseurs
	inline IrrlichtDevice *device(void){return _device;}
	inline gui::IGUIFont *font(void){return _font;}
	inline gui::IGUISkin *skin(void){return _skin;}
	inline video::IVideoDriver *driver(void){return _driver;}
	inline gui::IGUIEnvironment *env(void){return _env;}
	inline scene::ISceneManager *smgr(void){return _smgr;}

	//methodes
	virtual void initEngine(void) =0;
	inline void fermerEngine(void)           //supprimer et reInitialiser le pointeur sur l'engine d'Irrlicht
	{
		_device->drop();
		_device=0;
	}

protected:
	IrrlichtDevice * _device;
	video::IVideoDriver* _driver;
	gui::IGUIEnvironment* _env;
	const wchar_t* _titre;
	gui::IGUISkin* _skin;
	gui::IGUIFont* _font;
	gui::IGUIFont* _petiteFont;
	gui::IGUIFont* _moyenneFont;
	gui::IGUIFont* _grandeFont;
	scene::ISceneManager* _smgr;

	wstring _wstring;
};



#endif

