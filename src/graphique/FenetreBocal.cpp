#include "..\..\include\graphique\FenetreBocal.h"
#include <cwchar>

void FenetreBocal::majBocal()
{
	_driver->beginScene(true, true, video::SColor(255,255,255,255));
	_smgr->drawAll();
	_env->drawAll();
	_driver->endScene();
}

void FenetreBocal::initEngine()
{
	// create a NULL device to detect screen resolution
	IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
	core::dimension2d<u32> deskres = nulldevice->getVideoModeList()->getDesktopResolution();
	nulldevice->drop();
	_largeur = deskres.Width;
	_hauteur=deskres.Height;
	_device = createDevice( video::EDT_DIRECT3D9,deskres,32,true, false, false, this);  //EDT_DIRECT3D9  EDT_SOFTWARE EDT_BURNINGSVIDEO EDT_OPENGL

	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_env = _device->getGUIEnvironment();
	_curseur = _device->getCursorControl();

	_unites = _smgr->addBillboardSceneNode(0, core::dimension2d<f32>(7,7),core::vector3df(0,0,0));

	_device->setWindowCaption(_titre);
	_device->setResizable(false);

	_skin = _env->getSkin();
	//_font = _env->getFont("media/fontlucida.png");
	_petiteFont = _env->getFont("media/font/fontPetit.png");
	_moyenneFont = _env->getFont("media/font/fontMoyen.png");
	_grandeFont = _env->getFont("media/font/fontGrand.png");
	if (_petiteFont)
	{_skin->setFont(_petiteFont);}
	else{_skin->setFont(_env->getBuiltInFont(), gui::EGDF_TOOLTIP);}
}

scene::ISceneNode* FenetreBocal::creerUnite(video::ITexture *texture, int x,int y, int z)
{
	_unite = _smgr->addBillboardSceneNode(_unites, core::dimension2d<f32>(TAILLE_UNITE,TAILLE_UNITE),core::vector3df(x,y,z));
	_unite->setMaterialTexture(0, texture);
	_unite->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	_unite->setMaterialFlag(video::EMF_LIGHTING, false);
	_unite->setMaterialFlag(video::EMF_ZBUFFER, false);
	return _unite;
}

void FenetreBocal::creerMouvementUnite(scene::ISceneNode* unite,core::vector3df depart, core::vector3df fin, u32 vitesse)
{	
	scene::ISceneNodeAnimator* anim = _smgr->createFlyStraightAnimator(depart,fin, vitesse, false,false);
	if (anim)
	{
		unite->addAnimator(anim);
		anim->drop();
	}
}

void FenetreBocal::creerMouvementCamera(scene::ICameraSceneNode* camera,int xDepart, int yDepart, int zDepart, int xFin, int yFin, int zFin, u32 vitesse, bool boucle, bool pingPong)
{	
	scene::ISceneNodeAnimator* animCamera = _smgr->createFlyStraightAnimator(core::vector3df(xDepart,yDepart,zDepart),core::vector3df(xFin,yFin,zFin), vitesse, boucle,pingPong);
	if (animCamera)
	{
		camera->addAnimator(animCamera);
		animCamera->drop();
	}
}

void FenetreBocal::supprimerUnite(scene::ISceneNode* unite)
{
	unite->remove();
}

void FenetreBocal::placerCamera()
{
	// On crée une caméra statique que l'on pourra rendre par la suite statique. ( voir tuto OpenClassRoom)
	 scene::ICameraSceneNode* cam = _smgr->addCameraSceneNode(0, irr::core::vector3df (0,25,0), irr::core::vector3df (0,0,0),-1,true);
}

void FenetreBocal::changerLumiereAmbiance(int r, int g, int b)
{
	_smgr->setAmbientLight(video::SColor(0, r, g, b));
}

void FenetreBocal::generationScene()
{
	/* fondBocal */ 
	scene::IMeshSceneNode* fondBocal =         // pointeur vers le node
        _smgr->addCubeSceneNode(        // la creation du cube
            20.0f,                             // cote de 10 unites
            0,                                 // parent = racine
            -1,                                // pas d'ID
            core::vector3df(              // le vecteur de position
            0.0f,                          // origine en X
            0.0f,                          // origine en Y
            0.0f));                       // +20 unites en Z

	fondBocal->setMaterialTexture(0, _tabTextures[8]); // on applique la texture
	fondBocal->setMaterialFlag(video::EMF_LIGHTING, true);

	/* murHaut */
	scene::IMeshSceneNode* murHaut =         // pointeur vers le node
		_smgr->addCubeSceneNode(        // la creation du cube
		20.0f,                             // cote de 10 unites
		0,                                 // parent = racine
		-1,                                // pas d'ID
		core::vector3df(              // le vecteur de position
		20.0f,                          // origine en X
		20.0f,                          // origine en Y
		0.0f));                       // +20 unites en Z
     
	murHaut->setMaterialTexture(0, _tabTextures[8]);
	murHaut->setMaterialFlag(video::EMF_LIGHTING, true);

	/* murBas */
	scene::IMeshSceneNode* murBas =         // pointeur vers le node
		_smgr->addCubeSceneNode(        // la creation du cube
		20.0f,                             // cote de 10 unites
		0,                                 // parent = racine
		-1,                                // pas d'ID
		core::vector3df(              // le vecteur de position
		-20.0f,                          // origine en X
		20.0f,                          // origine en Y
		0.0f));                       // +20 unites en Z

	murBas->setMaterialTexture(0, _tabTextures[8]);
	murBas->setMaterialFlag(video::EMF_LIGHTING, true);

	/* murGauche */
	scene::IMeshSceneNode* murGauche =         // pointeur vers le node
		_smgr->addCubeSceneNode(        // la creation du cube
		20.0f,                             // cote de 10 unites
		0,                                 // parent = racine
		-1,                                // pas d'ID
		core::vector3df(              // le vecteur de position
		0.0f,                          // origine en X
		20.0f,                          // origine en Y
		20.0f));                       // +20 unites en Z

	murGauche->setMaterialTexture(0,_tabTextures[8]);
	murGauche->setMaterialFlag(video::EMF_LIGHTING, true);

	/* murDroite */
	scene::IMeshSceneNode* murDroite =         // pointeur vers le node
		_smgr->addCubeSceneNode(        // la creation du cube
		20.0f,                             // cote de 10 unites
		0,                                 // parent = racine
		-1,                                // pas d'ID
		core::vector3df(              // le vecteur de position
		0.0f,                          // origine en X
		20.0f,                          // origine en Y
		-20.0f));                       // +20 unites en Z

	murDroite->setMaterialTexture(0, _tabTextures[8]);
	murDroite->setMaterialFlag(video::EMF_LIGHTING, true);

	placerCamera();
	changerLumiereAmbiance(255,255,255);
}

void FenetreBocal::generationMenu()
{
	s32 largeur;
	s32 hauteur;
	//Check box extern

	_tabExtern= _env->addTab(core::rect<s32>(0,0,1000,1200));
	largeur = _largeur/16;
	hauteur = (_hauteur/8);

	_checkExtern = _env->addCheckBox(false,core::rect<s32>(largeur,hauteur,largeur+LARGEUR_CHECK, hauteur + HAUTEUR_TEXTE),0,GUI_ID_CHECK_EXTERN,L"Capteurs externes");
	
	//Gestion du temps
	hauteur = (_hauteur/10);
	s32 hauteurPetit =  hauteur + 10;

	//seconde
	largeur = (29*_largeur/30);
	
	_nombreSeconde=_env->addStaticText(_wstring.c_str(), core::rect<s32>(largeur-LARGEUR_SECONDE-LARGEUR_TEXTE,hauteur,largeur-LARGEUR_TEXTE, hauteur+HAUTEUR_TEXTE), false);
	_nombreSeconde->setOverrideFont(_moyenneFont);
	_env->addStaticText(L"s", core::rect<s32>(largeur-LARGEUR_TEXTE,hauteurPetit,largeur,hauteurPetit+HAUTEUR_TEXTE), false, true);

	largeur = largeur-LARGEUR_SECONDE-LARGEUR_TEXTE;

	//minute

	_nombreMinute=_env->addStaticText(_wstring.c_str(), core::rect<s32>(largeur-LARGEUR_MINUTE-LARGEUR_TEXTE_MIN,hauteur,largeur-LARGEUR_TEXTE_MIN, hauteur+HAUTEUR_TEXTE), false);
	_nombreMinute->setOverrideFont(_moyenneFont);
	_env->addStaticText(L"min", core::rect<s32>(largeur-LARGEUR_TEXTE_MIN,hauteurPetit,largeur,hauteurPetit+HAUTEUR_TEXTE), false, true);

	largeur = largeur-LARGEUR_MINUTE-LARGEUR_TEXTE_MIN;

	//heure
	_nombreHeure=_env->addStaticText(_wstring.c_str(), core::rect<s32>(largeur-LARGEUR_HEURE-LARGEUR_TEXTE,hauteur,largeur-LARGEUR_TEXTE, hauteur+HAUTEUR_TEXTE), false);
	_nombreHeure->setOverrideFont(_moyenneFont);
	_env->addStaticText(L"h", core::rect<s32>(largeur-LARGEUR_TEXTE,hauteurPetit,largeur,hauteurPetit+HAUTEUR_TEXTE), false, true);

	largeur = largeur-LARGEUR_HEURE-LARGEUR_TEXTE;

	//jour
	_wstring= to_wstring((_Longlong) 0);
	_nombreJour=_env->addStaticText(_wstring.c_str(), core::rect<s32>(largeur-LARGEUR_JOUR-LARGEUR_TEXTE,hauteur,largeur-LARGEUR_TEXTE, hauteur+HAUTEUR_TEXTE), false);
	_nombreJour->setOverrideFont(_moyenneFont);
	_env->addStaticText(L"j", core::rect<s32>(largeur-LARGEUR_TEXTE,hauteurPetit,largeur,hauteurPetit+HAUTEUR_TEXTE), false, true);

	largeur = largeur-LARGEUR_JOUR-LARGEUR_TEXTE;	
	
	// Image période
	largeur = 16*(_largeur/20);
	hauteur = (_hauteur/8);
	_periode = _env->addImage(_tabTextures[9],core::position2d<int>(largeur,hauteur));
	
	
	//RECUPERATION NOMBRE DE UNITES
	largeur = (29*_largeur/30);
	hauteur = (_hauteur/2)-HAUTEUR_NOMBRE;
	hauteurPetit =  hauteur + 50;
  
	_nombreUnite=_env->addStaticText(_wstring.c_str(), core::rect<s32>(largeur-LARGEUR_NOMBRE-LARGEUR_TEXTE_NOMBRE,hauteur,largeur-LARGEUR_TEXTE_NOMBRE,hauteur+HAUTEUR_NOMBRE), false);
	_nombreUnite->setOverrideFont(_grandeFont);
	_env->addStaticText(L"unités", core::rect<s32>(largeur-LARGEUR_TEXTE_NOMBRE,hauteurPetit,largeur,hauteurPetit+HAUTEUR_NOMBRE), false, true);

	// Indicateur
	largeur = 5*(_largeur/6);
	hauteur = 2*(_hauteur/3);
	_indicateur=_env->addImage(_tabTextures[14],core::position2d<int>(largeur,hauteur));

	// SCROLLBAR 
	s32 largeurMaxScroll =  _largeur/4 - _largeur/32;

	//Luminosité
	largeur = _largeur/16;
	hauteur = 2*(_hauteur/8);
	_env->addStaticText(L" Luminosite ", core::rect<s32>(largeur,hauteur,largeur+LARGEUR_TEXTE_BAR,hauteur+HAUTEUR_TEXTE), false, true);

	hauteur = hauteur+HAUTEUR_TEXTE;
	largeur = largeur -_largeur/32;
	_scrollbarLuminosite = _env->addScrollBar(true, core::rect<s32>(largeur,hauteur,largeurMaxScroll,hauteur+HAUTEUR_BAR),_tabExtern,GUI_ID_SCROLL_BAR_CHOIX_LUMINOSITE);
	_scrollbarLuminosite->setMax(1000);
	_scrollbarLuminosite->setPos(500);
	_scrollbarLuminosite->setSmallStep(1);

	largeur = largeur +_largeur/15;
	hauteur=hauteur+HAUTEUR_BAR;

	_wstring= to_wstring((_Longlong)_scrollbarLuminosite->getPos());
	_valeurLuminosite=_env->addStaticText(_wstring.c_str(),core::rect<s32>(largeur,hauteur,largeur+LARGEUR_TEXTE_NOMBRE,hauteur+HAUTEUR_TEXTE), false, true);
	_valeurLuminosite->setOverrideFont(_moyenneFont);

	//Temperature
	largeur = _largeur/16;
	hauteur = 3*(_hauteur/8);
	_env->addStaticText(L" Temperature ", core::rect<s32>(largeur,hauteur,largeur+LARGEUR_TEXTE_BAR,hauteur+HAUTEUR_TEXTE), false, true);

	hauteur = hauteur+HAUTEUR_TEXTE;
	largeur = largeur -_largeur/32;
	_scrollbarTemperature = _env->addScrollBar(true, core::rect<s32>(largeur,hauteur,largeurMaxScroll,hauteur+HAUTEUR_BAR),_tabExtern,GUI_ID_SCROLL_BAR_CHOIX_TEMPERATURE);
	_scrollbarTemperature->setMax(60);
	_scrollbarTemperature->setPos(30);
	_scrollbarTemperature->setSmallStep(1);

	largeur = largeur +_largeur/15;
	hauteur=hauteur+HAUTEUR_BAR;
	_wstring= to_wstring((_Longlong)_scrollbarTemperature->getPos());
	_valeurTemperature=_env->addStaticText(_wstring.c_str(),core::rect<s32>(largeur,hauteur,largeur+LARGEUR_TEXTE_NOMBRE,hauteur+HAUTEUR_TEXTE), false, true);
	_valeurTemperature->setOverrideFont(_moyenneFont);
	
	//Pression
	largeur = _largeur/16;
	hauteur = 4*(_hauteur/8);
	_env->addStaticText(L" Pression ", core::rect<s32>(largeur,hauteur,largeur+LARGEUR_TEXTE_BAR,hauteur+HAUTEUR_TEXTE), false, true);

	hauteur = hauteur+HAUTEUR_TEXTE;
	largeur = largeur -_largeur/32;
	_scrollbarPression =_env->addScrollBar(true,  core::rect<s32>(largeur,hauteur,largeurMaxScroll,hauteur+HAUTEUR_BAR), _tabExtern,GUI_ID_SCROLL_BAR_CHOIX_PRESSION);
	_scrollbarPression->setMax(1000);
	_scrollbarPression->setPos(500);
	_scrollbarPression->setSmallStep(1);

	largeur = largeur +_largeur/15;
	hauteur=hauteur+HAUTEUR_BAR;
	_wstring= to_wstring((_Longlong)_scrollbarTemperature->getPos());
	_valeurPression=_env->addStaticText(_wstring.c_str(),core::rect<s32>(largeur,hauteur,largeur+LARGEUR_TEXTE_NOMBRE,hauteur+HAUTEUR_TEXTE), false, true);
	_valeurPression->setOverrideFont(_moyenneFont);

	// Parametre Vitesse temps
	hauteur = 5*(_hauteur/8);
	largeur = _largeur/16 + _largeur/32;
	_boutonLecture = _env->addButton(core::rect<s32>(largeur,hauteur,largeur+LARGEUR_BOUTON,hauteur+HAUTEUR_BOUTON), 0, GUI_ID_BOUTON_LECTURE, L"", L"Redémarrez le temps");
	_boutonLecture->setIsPushButton(true);
	_boutonLecture->setPressed(true);
	_boutonLecture->setImage(_tabTextures[18]);
	_boutonLecture->setPressedImage(_tabTextures[19]);
	_boutonLecture->setUseAlphaChannel(true);
	_boutonLecture->setDrawBorder(false);

	hauteur = hauteur+HAUTEUR_BOUTON+30;
	largeur = largeur - _largeur/22;
	_env->addStaticText(L" Temps de la boucle ", core::rect<s32>(largeur,hauteur,largeur+LARGEUR_TEXTE_VITESSE,hauteur+HAUTEUR_TEXTE), false, true);


	largeur = _largeur/32;
	hauteur = hauteur+HAUTEUR_TEXTE;
	_scrollbarVitesse =_env->addScrollBar(true,  core::rect<s32>(largeur,hauteur,largeurMaxScroll,hauteur+HAUTEUR_BAR), 0,GUI_ID_SCROLL_BAR_CHOIX_VITESSE);
	_scrollbarVitesse->setMin(1);
	_scrollbarVitesse->setMax(100);
	_scrollbarVitesse->setPos(TEMPS_SCENE);

	largeur = largeur +_largeur/15;
	hauteur=hauteur+HAUTEUR_BAR;
	_wstring= to_wstring((_Longlong)_scrollbarVitesse->getPos());
	_valeurVitesse=_env->addStaticText(_wstring.c_str(),core::rect<s32>(largeur,hauteur,largeur+LARGEUR_TEXTE_NOMBRE,hauteur+HAUTEUR_TEXTE), false, true);
	_valeurVitesse->setOverrideFont(_moyenneFont);

	//bouton renfort/restart
	largeur = _largeur/2-LARGEUR_BOUTON/2;
	hauteur  = _hauteur/2-HAUTEUR_BOUTON/2;
	_boutonRenfort = _env->addButton(core::rect<s32>(largeur,hauteur,largeur+LARGEUR_BOUTON,hauteur+HAUTEUR_BOUTON), 0, GUI_ID_BOUTON_RENFORT, L"", L"Renvoyez 20 unités");
	_boutonRenfort->setImage(_tabTextures[21]);
	_boutonRenfort->setEnabled(false);
	_boutonRenfort->setVisible(false);
	_boutonRenfort->setUseAlphaChannel(true);
	_boutonRenfort->setDrawBorder(false);

	//bouton quitter et son
	largeur = _largeur/30;
	hauteur  = 7*(_hauteur/8);
	_boutonSon = _env->addButton(core::rect<s32>(largeur,hauteur,largeur+LARGEUR_BOUTON,hauteur+HAUTEUR_BOUTON), 0, GUI_ID_BOUTON_SON, L"", L"Couper la musique");
	_boutonSon->setIsPushButton(true);
	_boutonSon->setImage(_tabTextures[16]);
	_boutonSon->setPressedImage(_tabTextures[17]);
	_boutonSon->setUseAlphaChannel(true);
	_boutonSon->setDrawBorder(false);

	largeur = largeur+LARGEUR_BOUTON+30;
	_boutonQuitter = _env->addButton(core::rect<s32>(largeur,hauteur,largeur+LARGEUR_BOUTON,hauteur+HAUTEUR_BOUTON), 0, GUI_ID_BOUTON_QUITTER, L"", L"Fermer le bocal");
	_boutonQuitter->setImage(_tabTextures[20]);
	_boutonQuitter->setUseAlphaChannel(true);
	_boutonQuitter->setDrawBorder(false);
}

void FenetreBocal::majAffichageTemps(int jour, int heure, int minute, int seconde, int periode)
{
	_wstring = to_wstring((_Longlong)jour);
	_nombreJour->setText(_wstring.c_str());
	_wstring = to_wstring((_Longlong)heure);
	_nombreHeure->setText(_wstring.c_str());
	_wstring = to_wstring((_Longlong)minute);
	_nombreMinute->setText(_wstring.c_str());
	_wstring = to_wstring((_Longlong)seconde);
	_nombreSeconde->setText(_wstring.c_str());
	_periode->setImage(_tabTextures[9+periode]);
}

void FenetreBocal::majAffichageUnites(int nbrUnite)
{
	_wstring = to_wstring((_Longlong)nbrUnite);
	_nombreUnite->setText(_wstring.c_str());
	if(_musique){_son->son()->setVolume(1.0*(float)nbrUnite/(float)MAX_UNITE);}
}

int FenetreBocal::majVitesseTemps()
{
	return _scrollbarVitesse->getPos();
}

bool FenetreBocal::majAffichageEnvironnement(int temp, int pression, int lumi)
{
	//Scroll bar
	_wstring = to_wstring((_Longlong)pression);   
	_valeurPression->setText(_wstring.c_str());
	_scrollbarPression->setPos(pression);
	_wstring = to_wstring((_Longlong)temp);   
	_valeurTemperature->setText(_wstring.c_str());
	_scrollbarTemperature->setPos(temp);
	_wstring= to_wstring((_Longlong)lumi);   
	_valeurLuminosite->setText(_wstring.c_str());
	_scrollbarLuminosite->setPos(lumi);

	bool pause = _boutonLecture->isPressed();

	if(pause){_son->son()->setIsPaused(true);}
	else{_son->son()->setIsPaused(false);}

	return !pause;


}

bool FenetreBocal::majAffichageExtern(bool externPossible)
{
	_externPossible = externPossible;
	if(_externPossible)
	{
		_checkExtern->setVisible(true);
		return (_checkExtern->isChecked());
	}
	else
	{
		_checkExtern->setChecked(false);
		_checkExtern->setVisible(false);
		return false;
	}
}
void FenetreBocal::pauseForce()
{
	_boutonLecture->setPressed(true);
	_boutonLecture->setToolTipText( L"Redémarrez le temps");
	_boutonLecture->setEnabled(false);
	_boutonRenfort->setEnabled(true);
	_boutonRenfort->setVisible(true);
}

void FenetreBocal::redemarrage()
{
	_renfort=false;
	_boutonRenfort->setVisible(false);
	_boutonRenfort->setEnabled(false);
	_boutonLecture->setEnabled(true);
}

bool FenetreBocal::OnEvent(const SEvent& event)
{
	switch(event.EventType)
	{
		case EET_GUI_EVENT:                             //evenement lié à l'envirronement
			switch(event.GUIEvent.EventType)
			{

			case gui::EGET_SCROLL_BAR_CHANGED:
					switch(event.GUIEvent.Caller->getID())
					{
						case GUI_ID_SCROLL_BAR_CHOIX_PRESSION:
							return true;

						case GUI_ID_SCROLL_BAR_CHOIX_TEMPERATURE:
							return true;


						case GUI_ID_SCROLL_BAR_CHOIX_LUMINOSITE:
							return true;

						case GUI_ID_SCROLL_BAR_CHOIX_VITESSE:
							_wstring= to_wstring((_Longlong)_scrollbarVitesse->getPos());
							_valeurVitesse->setText(_wstring.c_str());
							return true;
					
					}

				case gui::EGET_CHECKBOX_CHANGED :
					switch(event.GUIEvent.Caller->getID())
					{
						case GUI_ID_CHECK_EXTERN:
							_tabExtern->setVisible(!_checkExtern->isChecked());
							return true;
						default:
							return false;
					}

				case gui::EGET_BUTTON_CLICKED:
					switch(event.GUIEvent.Caller->getID())
					{
						case GUI_ID_BOUTON_QUITTER:
							_device->closeDevice(); //Pour fermer fenetre
							return true;

						case GUI_ID_BOUTON_SON:
							if(_boutonSon->isPressed())
							{
								_boutonSon->setPressed(true);
								_boutonSon->setToolTipText( L"Remettre la musique");
								_musique=false; 
								_son->son()->setVolume(0); //Pour couper le son

							}
							else
							{
								_boutonSon->setPressed(false);
								_boutonSon->setToolTipText( L"Couper la musique");
								_musique = true; 
							}
							return true;

						case GUI_ID_BOUTON_LECTURE:
							if(_boutonLecture->isPressed())
							{
								_boutonLecture->setPressed(true);
								_boutonLecture->setToolTipText( L"Redémarrez le temps");
							}
							else
							{
								_boutonLecture->setPressed(false);
								_boutonLecture->setToolTipText( L"Arreter le temps");
							}
							return true;
						case GUI_ID_BOUTON_RENFORT:
							_renfort = true;
							return true;
						default:
							return false;
					}
					return false;

				default:
					return false;
			}
		case EET_KEY_INPUT_EVENT:                     //evenement lié au clavier
			if(event.KeyInput.PressedDown == false)  // vérifie que la touche est relevé pour évité les rebonds
			{
				switch(event.KeyInput.Key)
				{
					case KEY_ESCAPE:
						_device->closeDevice();
						return true;
					case KEY_SPACE:
						if(_boutonLecture->isPressed())
							{
								_boutonLecture->setPressed(true);
								_boutonLecture->setToolTipText( L"Redémarrez le temps");
							}
						else
							{
								_boutonLecture->setPressed(false);
								_boutonLecture->setToolTipText( L"Arreter le temps");
							}
						return true;
					default:
						return false;
				}
			}
			return false;
		default:
			return false;
	}

}