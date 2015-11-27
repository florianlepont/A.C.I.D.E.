#include "..\..\include\musique\Son.h"


using namespace irrklang;


void Son::jouerSonJeux()
{
	_son = _engine->play2D("media/musique/Saltan.mp3", true, true);
}

void Son::jouerSonMenu()
{
	_son = _engine->play2D("media/musique/Sugar.mp3", true);
} 

