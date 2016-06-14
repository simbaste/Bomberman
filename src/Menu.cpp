#include <iostream>
#include "Menu.hpp"
#include "Excep.hpp"

Menu::Menu(Event *event, irr::video::IVideoDriver *dr,
	   irrSmgr *s, irr::gui::IGUIEnvironment *e)
  : event(event), driver(dr), smgr(s), env(e), play(NULL), playN(NULL), quit(NULL), option(NULL), load(NULL), cancelN(NULL), cancelP(NULL), one(NULL), two(NULL), three(NULL), ia(NULL)
{
  if ((imgMenu = driver->getTexture(BACKGROUND_MENU)) == NULL)
    throw Excep("Impossible de charger une texture");
  b = true;
  p = true;
  d = true;
}

Menu::~Menu()
{
}

void	Menu::textureButton(button *s, const char *img)
{
  s->setImage(driver->getTexture(img));
  s->setUseAlphaChannel(true);
  s->setDrawBorder(false);
}

void	Menu::initButtonMain()
{
  if ((play = env->addButton(irr::core::rect<irr::s32>(130, 185, 630, 260),
			     0, GUI_ID_PLAY, L"", L"start new Game")) == NULL)
    throw Excep("Impossible de cree le boutton");
  if ((load = env->addButton(irr::core::rect<irr::s32>(130, 320, 630, 395),
			     0, GUI_ID_LOAD, L"", L"Load a game")) == NULL)
    throw Excep("Impossible de cree le boutton");
  if ((option = env->addButton(irr::core::rect<irr::s32>(130, 455, 630, 530),
			       0, GUI_ID_OPTION, L"", L"Game options")) == NULL)
    throw Excep("Impossible de cree le boutton");
  if ((quit = env->addButton(irr::core::rect<irr::s32>(130, 590, 630, 665),
			     0, GUI_ID_QUIT, L"", L"Exits program")) == NULL)
    throw Excep("Impossible de cree le boutton");
}

Click	Menu::mainMenu()
{
  if ((imgMenu = driver->getTexture(BACKGROUND_MENU)) == NULL)
    throw Excep("Impossible de charger la texture");
  return Click::NOP;
}
void	Menu::initMainMenu()
{
  initButtonMain();
  textureButton(play, PLAY_BUTTON);
  textureButton(load, LOAD_BUTTON);
  textureButton(option, OPTIONS_BUTTON);
  textureButton(quit, QUIT_BUTTON);
}

void	Menu::initPlayMenu()
{
  if ((one = env->addButton(rect(130, 185, 630, 260),
			    0, GUI_ID_ONE_PLAYER, L"", L"Play solo")) == NULL)
    throw Excep("Impossible de charger la texture");
  if ((two = env->addButton(rect(130, 320, 630, 395),
			    0, GUI_ID_TWO_PLAYERS, L"", L"Play at two")) == NULL)
    throw Excep("Impossible de charger la texture");
  if ((ia = env->addButton(rect(X_IA_BUTTON, Y_IA_BUTTON, X_IA_BUTTON_END, Y_IA_BUTTON_END),
			   0, GUI_ID_IA_PLAYERS, L"", L"Play IA")) == NULL)
    throw Excep("Impossible de charger la texture");
  if ((three = env->addButton(rect(130, 455, 630, 530),
			      0, GUI_ID_THREE_PLAYERS, L"", L"Play at three")) == NULL)
    throw Excep("Impossible de charger la texture");
  if ((cancelP = env->addButton(rect(130, 590, 630, 665),
				0, GUI_ID_CANCEL_P, L"", L"Return to main menu")) == NULL)
    throw Excep("Impossible de charger la texture");
  textureButton(one, SOLO_BUTTON);
  textureButton(two, TWO_PLAYERS_BUTTON);
  textureButton(three, THREE_PLAYERS_BUTTON);
  textureButton(cancelP,CANCEL_BUTTON);
  textureButton(ia, IA_BUTTON);
}

void	Menu::initNameMenu()
{
  if ((playN = env->addButton(rect(100, 550, 600, 625),
			      0, GUI_ID_PLAY_N, L"", L"start new Game")) == NULL)
    throw Excep("Impossible de charger la texture");
  if ((cancelN = env->addButton(rect(100, 661, 600, 736),
				0, GUI_ID_CANCEL_N, L"", L"Return to main menu")) == NULL)
    throw Excep("Impossible de charger la texture");
  textureButton(playN, PLAY_BUTTON);
  textureButton(cancelN, CANCEL_BUTTON);
  if ((nameP1 = env->addEditBox(L"Player1", rect(420,200,870,265), true, 0, GUI_ID_SET_NAME_ONE)) == NULL)
    throw Excep("Impossible de charger la texture");
  if ((nameP2 = env->addEditBox(L"Player2", rect(420,307,870,372), true, 0, GUI_ID_SET_NAME_TWO)) == NULL)
    throw Excep("Impossible de charger la texture");
  if ((nameP3 = env->addEditBox(L"Player3", rect(420,414,870,479), true, 0, GUI_ID_SET_NAME_THREE)) == NULL)
    throw Excep("Impossible de charger la texture");
}

void			Menu::dropItem(button *b)
{
  if (b != NULL)
    {
      b->drop();
      b = NULL;
    }
}

void			Menu::dropMenu()
{
  dropItem(play);
  dropItem(playN);
  dropItem(quit);
  dropItem(option);
  dropItem(load);
  dropItem(cancelN);
  dropItem(cancelP);
  dropItem(one);
  dropItem(two);
  dropItem(three);
  dropItem(ia);
}

Click			Menu::drawMainMenu()
{
  initMainMenu();
  sizeM = imgMenu->getSize();
  position0.X = 0;
  position0.Y = 0;
  position1.X = sizeM.Width;
  position1.Y = sizeM.Height;
  rectangle.UpperLeftCorner = position0;
  rectangle.LowerRightCorner = position1;
  driver->draw2DImage(imgMenu, position0, rectangle, 0,
		      irr::video::SColor(255, 255, 255, 255), true);
  play->draw();
  load->draw();
  option->draw();
  quit->draw();
  if (event->getChoice() == Click::PLAY) {
    return Click::PLAY;
  } else if (event->getChoice() == Click::OPTION) {
    return Click::OPTION;
  } else if (event->getChoice() == Click::LOAD) {
    return Click::LOAD;
  } else if (event->getChoice() == Click::QUIT) {
    std::cout << "QUIT" << std::endl;
    return Click::QUIT;
  }
  return Click::NOP;
}

Click		Menu::drawPlayMenu()
{
  initPlayMenu();
  sizeM = imgMenu->getSize();
  position0.X = 0;
  position0.Y = 0;
  position1.X = sizeM.Width;
  position1.Y = sizeM.Height;
  rectangle.UpperLeftCorner = position0;
  rectangle.LowerRightCorner = position1;
  driver->draw2DImage(imgMenu, position0, rectangle, 0,
		      irr::video::SColor(255, 255, 255, 255), true);
  one->draw();
  two->draw();
  three->draw();
  cancelP->draw();
  ia->draw();
  switch(event->getChoice()) {
  case Click::ONE:
      return Click::ONE;
  case Click::TWO:
      return Click::TWO;
  case Click::THREE:
      return Click::THREE;
  case Click::CANCEL:
      return Click::CANCEL;
  case Click::IA:
      return Click::IA;
  default:
    break ;
  }
  return Click::NOP;
}

void		Menu::isName(bool _b)
{
  b = _b;
}

Click		Menu::drawNameMenu(int nbPlayers)
{
  if (b == true) {
    b = false;
    initNameMenu();
  }
  sizeM = imgMenu->getSize();
  position0.X = 0;
  position0.Y = 0;
  position1.X = sizeM.Width;
  position1.Y = sizeM.Height;
  rectangle.UpperLeftCorner = position0;
  rectangle.LowerRightCorner = position1;
  driver->draw2DImage(imgMenu, position0, rectangle, 0,
		      irr::video::SColor(255, 255, 255, 255), true);
  playN->draw();
  cancelN->draw();
  for (int i = 0; i < nbPlayers; i++) {
    switch (i) {
    case 0:
      imgp1 = driver->getTexture(PLAYER1_LABEL);
      position0.X = 45;
      position0.Y = 200;
      driver->draw2DImage(imgp1, position0);
      nameP1->draw();
      break ;
    case 1:
      imgp2 = driver->getTexture(PLAYER2_LABEL);
      position0.X = 45;
      position0.Y = 307;
      driver->draw2DImage(imgp2, position0);
      nameP2->draw();
      break ;
    case 2:
      imgp3 = driver->getTexture(PLAYER3_LABEL);
      position0.X = 45;
      position0.Y = 414;
      driver->draw2DImage(imgp3, position0);
      nameP3->draw();
      break ;
    }
  }
  switch (event->getChoice()) {
  case Click::PLAY:
    return Click::PLAY;
  case Click::CANCEL:
    return Click::CANCEL;
  default:
    break ;
  }
  return Click::NOP;
}

irr::core::stringc	Menu::getNameP1()
{
  irr::core::stringc	s;
  s = nameP1->getText();
  return s;
}

irr::core::stringc	Menu::getNameP2()
{
  irr::core::stringc	s;
  s = nameP2->getText();
  return s;
}

irr::core::stringc	Menu::getNameP3()
{
  irr::core::stringc	s;
  s = nameP3->getText();
  return s;
}

bool			Menu::verif()
{
  for (unsigned int i = 0; i < names.size(); i++) {
    if (names[i].empty())
      names[i] = "Prosper";
  }
  return true;
}

bool			Menu::choicePlayers(Game &game)
{
  bool			back;

  back = false;
  game.soundMain();
	std::cout << "la" << std::endl;
  while (game.play() && back == false)
    {
      back = false;
      game.initScene();
      isName(true);
      switch (drawPlayMenu()) {
      case Click::ONE:
	back = lunchGame(1, game);
	break;
      case Click::TWO:
	back = lunchGame(2, game);
	break;
      case Click::THREE:
	back = lunchGame(3, game);
	break;
      case Click::IA:
	back = lunchGame(0, game);
	break;
      case Click::CANCEL:
	back = true;
	break ;
      default:
	break ;
      }
      game.endScene();
    }
  return back;
}

bool			Menu::lunchGame(int nbPlayers, Game &game)
{
  bool			back = false;

  while (!names.empty())
    names.pop_back();

  while (game.play() && back == false)
    {
      if (nbPlayers == 0)
	{
	  game.stopSound();
	  game.loadMap(10, 20, nbPlayers);
	  game.lunchCharacter(event, nbPlayers, names);
	  back = true;
	}
      game.initScene();
      switch (drawNameMenu(nbPlayers)) {
      case Click::CANCEL:
	back = true;
	break ;
      case Click::PLAY:
	for (int i = 0; i < nbPlayers; i++) {
	  switch (i) {
	  case 0:
	    names.push_back(getNameP1());
	    break ;
	  case 1:
	    names.push_back(getNameP2());
	    break ;
	  case 2:
	    names.push_back(getNameP3());
	    break;
	  default:
	    break ;
	  }
	}
	if (verif()) {
	  std::cout << "Start Game name = " << names[0].c_str() << std::endl;
	  game.stopSound();
	  game.loadMap(10, 20, nbPlayers);
	  game.lunchCharacter(event, nbPlayers, names);
	  back = true;
	}
	break;
      default:
	break;
      }
      game.endScene();
    }
  return back;
}
