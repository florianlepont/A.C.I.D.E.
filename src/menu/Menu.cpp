#include "..\..\include\menu\Menu.h"
#include <iostream>
#include <cwchar>

using namespace std;

const wchar_t* Menu::tabPopulations[] = {L"Alpha", L"Lambda", L"Kappa", L"Psi"};  // A maintenir équivalent avec l'enum de Vie.h

bool Menu::lancerMenu(void)
{
	fenetrePrincipale();

	while(_device->run())
	{
		if (_device->isWindowActive())
		{
			_device->run();
			_driver->beginScene(true, true, video::SColor(255,255,255,255));
			_env->drawAll();
			_driver->endScene();
		}
	}
	fermerEngine();
	return _lancementBocal;
}

void Menu::initEngine()
{
	//irrlicht
	_device = createDevice(video::EDT_DIRECT3D9,core::dimension2d<u32>(LARGEUR_MENU,HAUTEUR_MENU),32,false, false, false, this);
	_driver = _device->getVideoDriver();
	_env = _device->getGUIEnvironment();

	_device->setWindowCaption(_titre);
	_device->setResizable(false);
	_skin = _env->getSkin();
	_font = _env->getFont("media/font/fontlucida.png");
	if (_font)
	{_skin->setFont(_font);}
	_skin->setFont(_env->getBuiltInFont(), gui::EGDF_TOOLTIP);
}

void Menu::fenetrePrincipale(void)
{
	int margeBouton = 10; //30 si bouton charger partie

	_env->addImage(_tabTextures[0],core::position2d<int>(2,2));
	_env->addButton(core::rect<s32>(LARGEUR_MENU/2-LARGEUR_BOUTON/2,HAUTEUR_MENU/2-HAUTEUR_BOUTON-margeBouton,LARGEUR_MENU/2+LARGEUR_BOUTON/2,HAUTEUR_MENU/2-margeBouton), 0, GUI_ID_BOUTON_NOUVELLE_PARTIE,L"Nouvelle partie", L"Demarrer une nouvelle partie");
	//_env->addButton(core::rect<s32>(LARGEUR_MENU/2-LARGEUR_BOUTON/2,HAUTEUR_MENU/2-HAUTEUR_BOUTON/2,LARGEUR_MENU/2+LARGEUR_BOUTON/2,HAUTEUR_MENU/2+HAUTEUR_BOUTON/2), 0, GUI_ID_BOUTON_CHARGER_PARTIE,L"Reprendre partie", L"Charger une ancienne partie");	
	_env->addButton(core::rect<s32>(LARGEUR_MENU/2-LARGEUR_BOUTON/2,HAUTEUR_MENU/2+margeBouton,LARGEUR_MENU/2+LARGEUR_BOUTON/2,HAUTEUR_MENU/2+margeBouton+HAUTEUR_BOUTON), 0, GUI_ID_BOUTON_QUITTER,L"Quitter", L"Quitter ACIDE");
	
}

void Menu::fenetreNouvellePartie(void)
{
	int margeBouton = 30;
	int hauteurBox = 60;
	int margeBox = 120;
	int margeParam = 50;
	int hauteurParam = 130;
	int interligneParam = 5;
	int decalageTexteParam = 5;
	int hauteurLigne1 = 0;
	int hauteurLigne2 = HAUTEUR_SAISIE_C+interligneParam;
	int hauteurLigne3 = 2*HAUTEUR_SAISIE_C+2*interligneParam;
	int hauteurLigne5 = 4*HAUTEUR_SAISIE_C+3*interligneParam;
	int largeurMenu = 350;
	int hauteurMenu = 5*HAUTEUR_SAISIE_C+4*interligneParam;
	int largeurTexte1 = 180;
	int largeurTexte2 = 215;
	int largeurTexte3 = 20;
	int largeurTexte4 = 120;
	int largeurTexte5 = 35;
	int largeurTexte6 = 200;

	_env->addImage(_tabTextures[1],core::position2d<int>(2,2));
    
	//choix du nom de partie
	_saisie = _env->addEditBox(L"", core::rect<s32>(LARGEUR_MENU/2-margeBox/2-LARGEUR_SAISIE,hauteurBox,LARGEUR_MENU/2-margeBox/2,hauteurBox+HAUTEUR_SAISIE),true,0,GUI_ID_TEXTE_NOM_PARTIE);
	_env->addStaticText(L"Entrez votre nom de partie :", core::rect<s32>(LARGEUR_MENU/2-margeBox/2-LARGEUR_TEXTE,hauteurBox-HAUTEUR_TEXTE,LARGEUR_MENU/2-margeBox/2,hauteurBox));

	//choix du type de population
	_box = _env->addComboBox(core::rect<s32>(LARGEUR_MENU/2+margeBox/2,hauteurBox,LARGEUR_MENU/2+margeBox/2+LARGEUR_BOUTON,hauteurBox+HAUTEUR_BOUTON)); //Création menu déroulant
	_box->addItem(Menu::tabPopulations[0]);              // ajout premier element
	_box->addItem(Menu::tabPopulations[1]);
	_box->addItem(Menu::tabPopulations[2]);
	_box->addItem(Menu::tabPopulations[3]);

	//parametres avancés
	_checkParamAvance = _env->addCheckBox(false,core::rect<s32>(margeParam,hauteurParam,margeParam + LARGEUR_CHECK,hauteurParam+HAUTEUR_CHECK),0,GUI_ID_BOUTON_PARAM,L"Paramètre avancés"); 
	_tabParamAvance = _env->addTab(core::rect<s32>(margeParam,hauteurParam+HAUTEUR_CHECK+2*interligneParam,margeParam+largeurMenu,hauteurParam+HAUTEUR_CHECK+2*interligneParam+hauteurMenu));
	_tabParamAvance->setVisible(false);

	//ligne 1
	_env->addStaticText(L"Nombre d'unités au départ :", core::rect<s32>(0,hauteurLigne1+decalageTexteParam,largeurTexte1,HAUTEUR_SAISIE_C+hauteurLigne1+decalageTexteParam), false, true, _tabParamAvance);
	_texteNbrUnit= _env->addEditBox(L"",core::rect<s32>(largeurTexte1,hauteurLigne1,largeurTexte1+LARGEUR_SAISIE_C,hauteurLigne1+HAUTEUR_SAISIE_C),true,_tabParamAvance,GUI_ID_TEXTE_NBR_UNIT);
	_texteNbrUnit->setText(L"20");
	//ligne 2
	_env->addStaticText(L"Espérance de vie des unités entre ", core::rect<s32>(0,hauteurLigne2+decalageTexteParam,largeurTexte2,HAUTEUR_SAISIE_C+hauteurLigne2+decalageTexteParam), false, true, _tabParamAvance);
	_texteMinVie= _env->addEditBox(L"",core::rect<s32>(largeurTexte2,hauteurLigne2,largeurTexte2+LARGEUR_SAISIE_C,HAUTEUR_SAISIE_C+hauteurLigne2),true,_tabParamAvance,GUI_ID_TEXTE_MIN_VIE);
	_texteMinVie->setText((L"15"));
	_env->addStaticText(L" et ", core::rect<s32>(largeurTexte2+LARGEUR_SAISIE_C,hauteurLigne2+decalageTexteParam,largeurTexte2+LARGEUR_SAISIE_C+largeurTexte3,HAUTEUR_SAISIE_C+hauteurLigne2+decalageTexteParam), false, true, _tabParamAvance);
	_texteMaxVie= _env->addEditBox(L"",core::rect<s32>(largeurTexte2+LARGEUR_SAISIE_C+largeurTexte3,hauteurLigne2,largeurTexte2+2*LARGEUR_SAISIE_C+largeurTexte3,HAUTEUR_SAISIE_C+hauteurLigne2),true,_tabParamAvance,GUI_ID_TEXTE_MAX_VIE);
	_texteMaxVie->setText(L"25");
	//ligne 3
	_env->addStaticText(L"Heure de départ : ", core::rect<s32>(0,hauteurLigne3+decalageTexteParam,largeurTexte4,HAUTEUR_SAISIE_C+hauteurLigne3+decalageTexteParam), false, true, _tabParamAvance);
	_choixHeure=_env->addEditBox(L"0", core::rect<s32>(largeurTexte4,hauteurLigne3,largeurTexte4+LARGEUR_SPINBOX,HAUTEUR_SPINBOX+hauteurLigne3), false, _tabParamAvance,GUI_ID_CHOIX_HEURE);

	_env->addStaticText(L" h ", core::rect<s32>(largeurTexte4+LARGEUR_SPINBOX,hauteurLigne3+decalageTexteParam,largeurTexte5+largeurTexte4+LARGEUR_SPINBOX,HAUTEUR_SAISIE_C+hauteurLigne3+decalageTexteParam), false, true, _tabParamAvance);
	_choixMinute=_env->addEditBox(L"0", core::rect<s32>(largeurTexte5+largeurTexte4+LARGEUR_SPINBOX,hauteurLigne3,largeurTexte5+largeurTexte4+2*LARGEUR_SPINBOX,HAUTEUR_SPINBOX+hauteurLigne3), false, _tabParamAvance,GUI_ID_CHOIX_MINUTE);

	_env->addStaticText(L" min ", core::rect<s32>(largeurTexte5+largeurTexte4+2*LARGEUR_SPINBOX,hauteurLigne3+decalageTexteParam,2*largeurTexte5+largeurTexte4+2*LARGEUR_SPINBOX,HAUTEUR_SAISIE_C+hauteurLigne3+decalageTexteParam), false, true, _tabParamAvance);
	_choixSeconde=_env->addEditBox(L"0", core::rect<s32>(2*largeurTexte5+largeurTexte4+2*LARGEUR_SPINBOX,hauteurLigne3,2*largeurTexte5+largeurTexte4+3*LARGEUR_SPINBOX,HAUTEUR_SPINBOX+hauteurLigne3), false, _tabParamAvance,GUI_ID_CHOIX_SECONDE);

	_env->addStaticText(L" sec ", core::rect<s32>(2*largeurTexte5+largeurTexte4+3*LARGEUR_SPINBOX,hauteurLigne3+decalageTexteParam,3*largeurTexte5+largeurTexte4+3*LARGEUR_SPINBOX,HAUTEUR_SAISIE_C+hauteurLigne3+decalageTexteParam), false, true, _tabParamAvance);
	
	//ligne 5
	_env->addStaticText(L"Port usb pour la liaison série : ", core::rect<s32>(0,hauteurLigne5+decalageTexteParam,largeurTexte6,HAUTEUR_SAISIE_C+hauteurLigne5+decalageTexteParam), false, true, _tabParamAvance);
	_choixPort=_env->addEditBox(L"1", core::rect<s32>(largeurTexte6,hauteurLigne5,largeurTexte6+LARGEUR_SPINBOX,HAUTEUR_SPINBOX+hauteurLigne5), false, _tabParamAvance,GUI_ID_CHOIX_USB);


	//Boutons
	_env->addButton(core::rect<s32>(LARGEUR_MENU-margeBouton-LARGEUR_BOUTON,HAUTEUR_MENU-margeBouton-HAUTEUR_BOUTON,LARGEUR_MENU-margeBouton,HAUTEUR_MENU-margeBouton), 0, GUI_ID_BOUTON_LANCER_BOCAL, L"Lancer Bocal", L"Lancement");
	_env->addButton(core::rect<s32>(margeBouton,HAUTEUR_MENU-margeBouton-HAUTEUR_BOUTON,margeBouton+LARGEUR_BOUTON,HAUTEUR_MENU-margeBouton), 0, GUI_ID_BOUTON_RETOUR_MENU, L"Retour Menu", L"Retour menu");

	_fenetre=enum_fenetreNouvellePartie;
}

void Menu::fenetreChargerPartie()
{
	int margeBouton = 30;
	int hauteurBox = 70;
	_env->addImage(_tabTextures[1],core::position2d<int>(2,2));
	_fenetre=enum_fenetreChargerPartie;

	gui::IGUIComboBox *box = _env->addComboBox(core::rect<s32>(LARGEUR_MENU/2,hauteurBox,LARGEUR_MENU/2+LARGEUR_BOUTON,hauteurBox+HAUTEUR_BOUTON)); //Création menu déroulant
	_env->addStaticText(L"Choisissez la partie à charger :", core::rect<s32>(LARGEUR_MENU/2-LARGEUR_TEXTE,hauteurBox,LARGEUR_MENU/2,hauteurBox+HAUTEUR_TEXTE));

	box->addItem(L"Cette Partie");
	box->addItem(L"Jambon");
	box->addItem(L"Trololo");

	_env->addButton(core::rect<s32>(LARGEUR_MENU-margeBouton-LARGEUR_BOUTON,HAUTEUR_MENU-margeBouton-HAUTEUR_BOUTON,LARGEUR_MENU-margeBouton,HAUTEUR_MENU-margeBouton), 0, GUI_ID_BOUTON_LANCER_BOCAL, L"Lancer Bocal", L"Lancement");
	_env->addButton(core::rect<s32>(margeBouton,HAUTEUR_MENU-margeBouton-HAUTEUR_BOUTON,margeBouton+LARGEUR_BOUTON,HAUTEUR_MENU-margeBouton), 0, GUI_ID_BOUTON_RETOUR_MENU, L"Retour Menu", L"Retour menu");

}

bool Menu::OnEvent(const SEvent& event)
{
    switch(event.EventType)
	{
		case EET_GUI_EVENT:                                //evenement lié à l'envirronement
            switch(event.GUIEvent.EventType)
            {
				case gui::EGET_BUTTON_CLICKED:
					switch(event.GUIEvent.Caller->getID())
					{
						case GUI_ID_BOUTON_QUITTER:
							_device->closeDevice(); //Pour fermer fenetre
							return true;

						case GUI_ID_BOUTON_NOUVELLE_PARTIE:
							_env->clear();
							fenetreNouvellePartie(); 
							return true;

						case GUI_ID_BOUTON_CHARGER_PARTIE:
							_env->clear();
							fenetreChargerPartie(); 
							return true;

						case GUI_ID_BOUTON_RETOUR_MENU:
							_env->clear();
							fenetrePrincipale(); 
							return true;

						case GUI_ID_BOUTON_ENREGISTRER:
							return true;

						case GUI_ID_BOUTON_LANCER_BOCAL:
							modifierLancementBocal(true);
							_device->closeDevice(); //Pour fermer fenetre
							return true;

						default:
							return false;
					}
					return false;

				case gui::EGET_CHECKBOX_CHANGED :
					switch(event.GUIEvent.Caller->getID())
					{
						case GUI_ID_BOUTON_PARAM:
							_tabParamAvance->setVisible(_checkParamAvance->isChecked());
							return true;
						default:
							return false;
					}
				case gui::EGET_COMBO_BOX_CHANGED:
					modifierPopulation(_box->getSelected());
					return true;

				case gui::EGET_EDITBOX_CHANGED:
					switch(event.GUIEvent.Caller->getID())
					{
						case GUI_ID_TEXTE_NOM_PARTIE:
							modifierNomPartie(_saisie->getText());
							return true;
						case GUI_ID_TEXTE_MIN_VIE:
							_minVie = _wtoi(_texteMinVie->getText());
							if(_minVie<0){_minVie = 0;}
							_wstring = to_wstring((_Longlong)_minVie);
							_texteMinVie->setText(_wstring.c_str());
							return true;
						case GUI_ID_TEXTE_MAX_VIE:
							_maxVie = _wtoi(_texteMaxVie->getText());
							if(_maxVie<=0){_maxVie = 5;}
							_wstring = to_wstring((_Longlong)_maxVie);
							_texteMaxVie->setText(_wstring.c_str());
							return true;
						case GUI_ID_TEXTE_NBR_UNIT:
							_nbrUnite = _wtoi(_texteNbrUnit->getText());
							if(_nbrUnite<=4){_nbrUnite = 5;}
							_wstring = to_wstring((_Longlong)_nbrUnite);
							_texteNbrUnit->setText(_wstring.c_str());
							return true;
						case GUI_ID_CHOIX_HEURE:
							_heure = _wtoi(_choixHeure->getText());
							if(_heure<0){_heure = 0;}
							if(_heure>=24){_heure = 23;}
							_wstring = to_wstring((_Longlong)_heure);
							_choixHeure->setText(_wstring.c_str());
							return true;
						case GUI_ID_CHOIX_MINUTE:
							_minute = _wtoi(_choixMinute->getText());
							if(_minute<0){_minute = 0;}
							if(_minute>=60){_minute = 59;}
							_wstring = to_wstring((_Longlong)_minute);
							_choixMinute->setText(_wstring.c_str());
							return true;
						case GUI_ID_CHOIX_SECONDE:
							_seconde = _wtoi(_choixSeconde->getText());
							if(_seconde<0){_seconde = 0;}
							if(_seconde>=60){_seconde = 59;}
							_wstring = to_wstring((_Longlong)_seconde);
							_choixSeconde->setText(_wstring.c_str());
							return true;
						case GUI_ID_CHOIX_USB:
							_port = _wtoi(_choixPort->getText());
							if(_port<0){_port = 1;}
							_wstring = to_wstring((_Longlong)_port);
							_choixPort->setText(_wstring.c_str());
						default:
							return false;
					}
				default:
					return false;
            }
	case EET_KEY_INPUT_EVENT:                            //evenement lié au clavier
			if(event.KeyInput.PressedDown == false)      // vérifie que la touche est relevé pour évité les rebonds
			{
				switch(event.KeyInput.Key)
				{
					case KEY_RETURN:
						if(_fenetre == enum_fenetrePrincipale)
						{
							fenetreNouvellePartie();
						}
						else
						{
							modifierLancementBocal(true);
							_device->closeDevice(); //Pour fermer fenetre
						}
						return true;
					case KEY_ESCAPE:
						_device->closeDevice();
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