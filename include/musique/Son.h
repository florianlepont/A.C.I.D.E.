#include <stdio.h>
#include <irrKlang.h>

#if defined(WIN32)
#include <conio.h>
#else
#include "conio.h"
#endif

using namespace irrklang;

class Son {
	public:

		inline Son(void)
		{
			_engine = createIrrKlangDevice();  // start the sound engine with default parameters
			_son=0;
		}

		inline ~Son(void)
		{
			_son->drop();
			_engine->drop();
		}

		void jouerSonJeux(void);
		void jouerSonMenu(void);

		inline ISoundEngine* engine(void){return _engine;}
		inline ISound* son(void){return _son;}

	private:
		ISound *_son;
		ISoundEngine *_engine;

};