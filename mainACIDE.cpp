#include "irrlicht.h"
#include <iostream>
#include "include\core\Bocal.h"
#include "include\menu\Application.h"

using namespace std;
using namespace irr;

#ifdef _IRR_WINDOWS_
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") //empeche la console windows de s'ouvrir en conservant l'indépendance de la plateforme
#endif

int main(void)
{
	Application *app;
	app = new Application();
	app->lancer();
	delete app;

	//while(1){}
	return 0;
}