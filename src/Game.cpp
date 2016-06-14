#include <irr/irrlicht.h>
#include <unistd.h>
#include <iostream>
#include <functional>
#include "ThreadPool.hpp"
#include "Character.hpp"
#include "Map.hpp"
#include "Game.hpp"
#include "Ia.hpp"
#include "Player.hpp"
#include "Event.hpp"
#include "Ias.hpp"
#include "Iap.hpp"

Game::Game(Map *map)
{
  if ((device =
       irr::createDevice(irr::video::EDT_OPENGL,
		  irr::core::dimension2d<irr::u32>(1020, 750), 32)) == NULL)
    throw Excep("Impossible de cree la fenete");
  device->setResizable(false);
  if ((driver = device->getVideoDriver()) == NULL)
    throw Excep("Impossible de recupere le driver");
  if (loadAssets() == -1)
    throw Excep("Impossible de load une asset");
  if ((smgr  = device->getSceneManager()) == NULL)
    throw Excep("ERREUR: smgr failed");
  _map = map;
  if ((env = smgr->getGUIEnvironment()) == NULL)
    throw Excep("ERREUR: smgr failed");
  _nbThreads = 0;
  pause = 0;
  b = true;
  nbplayer = 0;
  keyMap *FBind = new keyMap;
  keyMap *SBind = new keyMap;
  keyMap *TBind = new keyMap;
  FBind->UP = irr::EKEY_CODE::KEY_UP;
  FBind->DOWN = irr::EKEY_CODE::KEY_DOWN;
  FBind->RIGHT = irr::EKEY_CODE::KEY_RIGHT;
  FBind->LEFT = irr::EKEY_CODE::KEY_LEFT;
  FBind->BOMB = irr::EKEY_CODE::KEY_SPACE;
  SBind->UP = irr::EKEY_CODE::KEY_KEY_Z;
  SBind->DOWN = irr::EKEY_CODE::KEY_KEY_S;
  SBind->RIGHT = irr::EKEY_CODE::KEY_KEY_D;
  SBind->LEFT = irr::EKEY_CODE::KEY_KEY_Q;
  SBind->BOMB = irr::EKEY_CODE::KEY_KEY_W;
  TBind->UP = irr::EKEY_CODE::KEY_KEY_I;
  TBind->DOWN = irr::EKEY_CODE::KEY_KEY_K;
  TBind->RIGHT = irr::EKEY_CODE::KEY_KEY_L;
  TBind->LEFT = irr::EKEY_CODE::KEY_KEY_J;
  TBind->BOMB = irr::EKEY_CODE::KEY_KEY_N;
  KeyBind.push_back(FBind);
  KeyBind.push_back(SBind);
  KeyBind.push_back(TBind);
}

void		Game::addSkyBox()
{
  if ((skybox = smgr->addSkyBoxSceneNode(
    driver->getTexture(SKYBOX),
    driver->getTexture(SKYBOX),
    driver->getTexture(SKYBOX),
    driver->getTexture(SKYBOX),
    driver->getTexture(SKYBOX),
    driver->getTexture(SKYBOX))) == NULL)
    throw Excep("ERREUR: smgr failed");
}

int		Game::loadAssets()
{
  if (((driver->getTexture(BACKGROUND_MENU)) == NULL)
      || ((driver->getTexture(GROUND)) == NULL)
      || ((driver->getTexture(UNBREAKABLE_WALL)) == NULL)
      || ((driver->getTexture(FIRE_WALL)) == NULL)
      || ((driver->getTexture(BOMB_ASSET)) == NULL)
      || ((driver->getTexture(BOMB_UP_ASSET)) == NULL)
      || ((driver->getTexture(BOMB_DOWN_ASSET)) == NULL)
      || ((driver->getTexture(RANGE_UP_ASSET)) == NULL)
      || ((driver->getTexture(SPEED_UP_ASSET)) == NULL)
      || ((driver->getTexture(KICKBOMB_ASSET)) == NULL)
      || ((driver->getTexture(RANGE_DOWN_ASSET)) == NULL)
      || ((driver->getTexture(SPEED_DOWN_ASSET)) == NULL)
      || ((driver->getTexture(SOLO_BUTTON)) == NULL)
      || ((driver->getTexture(TWO_PLAYERS_BUTTON)) == NULL)
      || ((driver->getTexture(THREE_PLAYERS_BUTTON)) == NULL)
      || ((driver->getTexture(CANCEL_BUTTON)) == NULL)
      || ((driver->getTexture(LOAD_BUTTON)) == NULL)
      || ((driver->getTexture(OPTIONS_BUTTON)) == NULL)
      || ((driver->getTexture(PLAY_BUTTON)) == NULL)
      || ((driver->getTexture(QUIT_BUTTON)) == NULL)
      || ((driver->getTexture(SAVE_BUTTON)) == NULL)
      )
    throw Excep("LOAD FAILED");
  return (0);
}

Game::~Game()
{
  device->drop();
}

irr::scene::ISceneManager	*Game::getSmgr() const {return smgr;}

irr::video::IVideoDriver	*Game::getDriver() const {return driver;}

irr::gui::IGUIEnvironment	*Game::getEnv() const
{
  return env;
}

void			Game::soundMenu()
{
  sound.getSoundMenu();
}

void			Game::soundMain()
{
  sound.getSoundMain();
}

void			Game::stopSound()
{
  sound.stopAllSounds();
}

irr::IrrlichtDevice	*Game::getDevice() const
{
  return device;
}

void		Game::initOption()
{
  if ((imgMenu = driver->getTexture(BACKGROUND_MENU)) == NULL)
    throw Excep("ERREUR: smgr failed");

  player1 = env->addButton(irr::core::rect<irr::s32>(130, 95, 270, 170),
		      0, GUI_ID_PLAYER1, L"", L"start new Game");

  player2 = env->addButton(irr::core::rect<irr::s32>(290, 95, 430, 170),
		      0, GUI_ID_PLAYER2, L"", L"start new Game");

  player3 = env->addButton(irr::core::rect<irr::s32>(450, 95, 590, 170),
		      0, GUI_ID_PLAYER3, L"", L"start new Game");

  up1 = env->addButton(irr::core::rect<irr::s32>(130, 185, 270, 260),
		      0, GUI_ID_UP1, L"", L"start new Game");
  down1 = env->addButton(irr::core::rect<irr::s32>(130, 265, 270, 340),
			0, GUI_ID_DOWN1, L"", L"Load a game");
  left1 = env->addButton(irr::core::rect<irr::s32>(130, 345, 270, 420),
			0, GUI_ID_LEFT1, L"", L"Game options");
  right1 = env->addButton(irr::core::rect<irr::s32>(130, 425, 270, 500),
			 0, GUI_ID_RIGHT1, L"", L"Exits program");
  bomb1 = env->addButton(irr::core::rect<irr::s32>(130, 505, 270, 580),
			0, GUI_ID_BOMB1, L"", L"Exits program");
  cancel = env->addButton(irr::core::rect<irr::s32>(130, 590, 630, 665),
			0, GUI_ID_CANCEL, L"", L"Exits program");

  up2 = env->addButton(irr::core::rect<irr::s32>(290, 185, 430, 260),
		      0, GUI_ID_UP2, L"", L"start new Game");
  down2 = env->addButton(irr::core::rect<irr::s32>(290, 265, 430, 340),
			0, GUI_ID_DOWN2, L"", L"Load a game");
  left2 = env->addButton(irr::core::rect<irr::s32>(290, 345, 430, 420),
			0, GUI_ID_LEFT2, L"", L"Game options");
  right2 = env->addButton(irr::core::rect<irr::s32>(290, 425, 430, 500),
			 0, GUI_ID_RIGHT2, L"", L"Exits program");
  bomb2 = env->addButton(irr::core::rect<irr::s32>(290, 505, 430, 580),
			0, GUI_ID_BOMB2, L"", L"Exits program");

  up3 = env->addButton(irr::core::rect<irr::s32>(450, 185, 590, 260),
		      0, GUI_ID_UP3, L"", L"start new Game");
  down3 = env->addButton(irr::core::rect<irr::s32>(450, 265, 590, 340),
			0, GUI_ID_DOWN3, L"", L"Load a game");
  left3 = env->addButton(irr::core::rect<irr::s32>(450, 345, 590, 420),
			0, GUI_ID_LEFT3, L"", L"Game options");
  right3 = env->addButton(irr::core::rect<irr::s32>(450, 425, 590, 500),
			 0, GUI_ID_RIGHT3, L"", L"Exits program");
  bomb3 = env->addButton(irr::core::rect<irr::s32>(450, 505, 590, 580),
			0, GUI_ID_BOMB3, L"", L"Exits program");

  textureButton(player1, PLAYER1_BUTTON);
  textureButton(player2, PLAYER2_BUTTON);
  textureButton(player3, PLAYER3_BUTTON);

  textureButton(up1, UP_BUTTON);
  textureButton(down1, DOWN_BUTTON);
  textureButton(left1, LEFT_BUTTON);
  textureButton(right1, RIGHT_BUTTON);
  textureButton(bomb1, BOMB_BUTTON);
  textureButton(cancel, CANCEL_BUTTON);

  textureButton(up2, UP_BUTTON);
  textureButton(down2, DOWN_BUTTON);
  textureButton(left2, LEFT_BUTTON);
  textureButton(right2, RIGHT_BUTTON);
  textureButton(bomb2, BOMB_BUTTON);

  textureButton(up3, UP_BUTTON);
  textureButton(down3, DOWN_BUTTON);
  textureButton(left3, LEFT_BUTTON);
  textureButton(right3, RIGHT_BUTTON);
  textureButton(bomb3, BOMB_BUTTON);
}

Click		Game::drawOption(Event *event)
{
  initOption();
  sizeM = imgMenu->getSize();
  position0.X = 0;
  position0.Y = 0;
  position1.X = sizeM.Width;
  position1.Y = sizeM.Height;
  rectangle.UpperLeftCorner = position0;
  rectangle.LowerRightCorner = position1;
  driver->draw2DImage(imgMenu, position0, rectangle, 0,
		      irr::video::SColor(255, 255, 255, 255), true);
  player1->draw();
  player2->draw();
  player3->draw();

  up1->draw();
  down1->draw();
  left1->draw();
  right1->draw();
  bomb1->draw();

  up2->draw();
  down2->draw();
  left2->draw();
  right2->draw();
  bomb2->draw();

  up3->draw();
  down3->draw();
  left3->draw();
  right3->draw();
  bomb3->draw();

  cancel->draw();
  switch (event->getChoice()) {
  case Click::UP1:
    return Click::UP1;
  case Click::DOWN1:
    return Click::DOWN1;
  case Click::LEFT1:
    return Click::LEFT1;
  case Click::RIGHT1:
    return Click::RIGHT1;
  case Click::BOMB1:
    return Click::BOMB1;
  case Click::UP2:
    return Click::UP2;
  case Click::DOWN2:
    return Click::DOWN2;
  case Click::LEFT2:
    return Click::LEFT2;
  case Click::RIGHT2:
    return Click::RIGHT2;
  case Click::BOMB2:
    return Click::BOMB2;
  case Click::UP3:
    return Click::UP3;
  case Click::DOWN3:
    return Click::DOWN3;
  case Click::LEFT3:
    return Click::LEFT3;
  case Click::RIGHT3:
    return Click::RIGHT3;
  case Click::BOMB3:
    return Click::BOMB3;
  case Click::CANCEL:
    return Click::CANCEL;
  default:
    break ;
  }
  return Click::NOP;
}

bool		Game::choiceOption(Event *event)
{
  bool		back;

  back = false;
  while (play() && back == false)
    {
      back = false;
      initScene();
      switch(drawOption(event)) {
      case Click::UP1:
	KeyBind[0]->UP = event->getLastKey();
      break ;
      case Click::DOWN1:
	KeyBind[0]->DOWN = event->getLastKey();
      break ;
      case Click::LEFT1:
	KeyBind[0]->LEFT = event->getLastKey();
      break ;
      case Click::RIGHT1:
	KeyBind[0]->RIGHT = event->getLastKey();
      break ;
      case Click::BOMB1:
	KeyBind[0]->BOMB = event->getLastKey();
      break ;
      case Click::UP2:
	KeyBind[1]->UP = event->getLastKey();
      break ;
      case Click::DOWN2:
	KeyBind[1]->DOWN = event->getLastKey();
      break ;
      case Click::LEFT2:
	KeyBind[1]->LEFT = event->getLastKey();
      break ;
      case Click::RIGHT2:
	KeyBind[1]->RIGHT = event->getLastKey();
      break ;
      case Click::BOMB2:
	KeyBind[1]->BOMB = event->getLastKey();
      break ;
      case Click::UP3:
	KeyBind[2]->UP = event->getLastKey();
      break ;
      case Click::DOWN3:
	KeyBind[2]->DOWN = event->getLastKey();
      break ;
      case Click::LEFT3:
	KeyBind[2]->LEFT = event->getLastKey();
      break ;
      case Click::RIGHT3:
	KeyBind[2]->RIGHT = event->getLastKey();
      break ;
      case Click::BOMB3:
	KeyBind[2]->BOMB = event->getLastKey();
      break ;
      case Click::CANCEL:
	back = true;
      break ;
      default:
	break ;
      }
      endScene();
    }
  return back;
}
g
void		Game::setEvent(Event *event)
{
  device->setEventReceiver(event);
}

void		Game::endScene()
{
  driver->endScene();
}

void		Game::initScene()
{
  driver->beginScene(true, true, irr::video::SColor(0, 120, 120, 120));
}

bool		Game::play() const
{
  return device->run();
}
void				Game::addGround()
{
  std::vector<irr::scene::ISceneNode*>	lineMap;
  irr::scene::ISceneNode        *cube;
  int				i;
  int				j;

  if (!irrMap.empty())
    {
      while (!irrMap.empty())
	irrMap.pop_back();
    }
  sizeY = (_map->getMap().size() * 50) / 2;
  sizeX = (_map->getMap()[0].size() * 50) / 2;
  for (unsigned int i = 0; i < _map->getMap().size(); i++) {
    for (unsigned j = 0; j < _map->getMap()[0].size(); j++) {
      lineMap.push_back(NULL);
    }
    irrMap.push_back(lineMap);
  }
  for (i = -sizeY; i < sizeY; i+=50) {
    for (j = -sizeX; j < sizeX; j+=50) {
      cube = smgr->addCubeSceneNode(50);
      cube->setPosition(irr::core::vector3df(j, 0, i));
      cube->setMaterialTexture(0, driver->getTexture(GROUND));
      cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
  }
}

void				Game::supScene()
{
  for (unsigned int i = 0; i < irrMap.size(); i++) {
    for (unsigned int j = 0; j < irrMap[0].size(); j++) {
      if (irrMap[i][j]) {
	irrMap[i][j]->drop();
      }
    }
  }
}

void				Game::getCol(unsigned int i)
{
  irr::scene::ISceneNode                *cube;
  irr::scene::IAnimatedMeshSceneNode    *perso;
  irr::scene::IAnimatedMeshMD2		*sydney;
  Character				*Char;
  Elem					elem;
  int					x(0);
  int					z(0);
  unsigned int                           j;

  srand(time(0));
  for (j = 0; j < _map->getMap()[i].size(); j++) {
    x = (j * 50) - sizeX;
    z = (i * 50) - sizeY;
    if (_map->getCell(i, j) == Tile::BLOCK || _map->getCell(i, j) == Tile::WALL) {
      if (_map->getCell(i, j) == Tile::BLOCK) {
	cube = smgr->addCubeSceneNode(50);
	irrMap[i][j] = cube;
	cube->setPosition(irr::core::vector3df(x, 50, z));
	cube->setMaterialTexture(0, driver->getTexture(BREAKABLE_WALL));
	cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      } else {
	cube = smgr->addCubeSceneNode(50);
	irrMap[i][j] = cube;
	cube->setPosition(irr::core::vector3df(x, 50, z));
	cube->setMaterialTexture(0, driver->getTexture(UNBREAKABLE_WALL));
	cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      }
    } else if (_map->getCell(i, j) == Tile::CHARACTER) {
      nbplayer++;
      if ((sydney = (irr::scene::IAnimatedMeshMD2*)smgr->getMesh("./assets/file/sydney.md2")) == NULL)
	throw Excep("ERREUR: smgr failed");
      perso = smgr->addAnimatedMeshSceneNode(sydney);
      perso->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      switch (nbplayer) {
      case 1:
	perso->setMaterialTexture( 0, driver->getTexture("./assets/file/Perso1.tga"));
	break ;
      case 2:
	perso->setMaterialTexture( 0, driver->getTexture("./assets/file/Perso2.jpg"));
	break ;
      case 3:
	perso->setMaterialTexture( 0, driver->getTexture("./assets/file/Perso3.png"));
	break ;
      default:
	break ;
      }
      elem.mesh = perso;
      elem.irrMap = &irrMap;
      elem.sound = &sound;
      elem.smgr = smgr;
      elem.driver = driver;
      elem.device = device;
      _nbThreads++;
      Char = new Player(j, i, Direction::LEFT, _map, &elem, &_perso, KeyBind[nbplayer - 1]);
      _perso.push_back(Char);
      perso->setPosition(irr::core::vector3df(x, 49, z));
    } else if (_map->getCell(i, j) == Tile::INTEL) {
      if ((sydney = (irr::scene::IAnimatedMeshMD2*)smgr->getMesh("./assets/file/sydney.md2")) == NULL)
	throw Excep("ERREUR: smgr failed");
      perso = smgr->addAnimatedMeshSceneNode(sydney);
      perso->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      perso->setMaterialTexture( 0, driver->getTexture("./assets/file/Perso4.jpg"));
      elem.mesh = perso;
      elem.irrMap = &irrMap;
      elem.sound = &sound;
      elem.smgr = smgr;
      elem.driver = driver;
      elem.device = device;
      _nbThreads++;
      if (rand() % 2)
	Char = new Iap(j, i, Direction::LEFT, _map, &elem, &_perso);
      else
	Char = new Ias(j, i, Direction::LEFT, _map, &elem, &_perso);
      _perso.push_back(Char);
      perso->setPosition(irr::core::vector3df(x, 50, z));
    }
  }
}

void		Game::addScene()
{
  device->getCursorControl()->setVisible(false);
  smgr->getParameters()->setAttribute(irr::scene::COLLADA_CREATE_SCENE_INSTANCES, true);
  driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
  smgr->addLightSceneNode(0, irr::core::vector3df(200, 200, 200),
			  irr::video::SColorf(1.0f, 1.0f, 1.0f), 2000);
  smgr->setAmbientLight(irr::video::SColorf(0.3f, 0.3f, 0.3f));
  for (unsigned int i = 0; i < _map->getMap().size(); i++) {
    getCol(i);
  }
}

void		Game::initInfos(std::vector<irr::core::stringc> &names)
{
  win = env->addWindow(irr::core::rect<irr::s32>(0, 0, 1020, 187), false, L"Games infos", 0, GUI_ID_DIALOG);
  tab = env->addTabControl(irr::core::rect<irr::s32>(2, 20, 1020, 187-7), win, true, true);
  t1 = tab->addTab(L"Score");
  for (unsigned int i = 0; i < names.size(); i++) {
    switch (i) {
    case 0:
      tName1 = env->addStaticText(L"Prosper:", irr::core::rect<irr::s32>(22,48,40,66), false, false, t1);
    case 1:
      tName2 = env->addStaticText(L"Simba:", irr::core::rect<irr::s32>(22,82,40,96), false, false, t1);
    case 2:
      tName3 = env->addStaticText(L"Foudre:", irr::core::rect<irr::s32>(22,108,40,126), false, false, t1);
    }
  }
}

void		Game::loadMap(int y, int x, int nbPlayers)
{
  _map->supMap();
  _map->createBlankMap(y, x, nbPlayers);
}

void		Game::lunchCharacter(Event *event, int choice __attribute__((unused)),
				     std::vector<irr::core::stringc> &names)
{
  addSkyBox();
  addGround();
  addScene();
  addCamera();
  ThreadPool	tp(_nbThreads);
  tp.init();
  sound.getSoundGame();
  initInfos(names);
  _map->printMap();
  _timer = device->getTimer();
  for (unsigned int i = 0; i < names.size(); i++)
    {
      _perso[i]->setName(names[i].c_str());
    }
  while (play() && _perso.size() > 1)
    {
      if (event->IsKeyDown(irr::EKEY_CODE::KEY_ESCAPE))
	if ((initPause(event)) == 2) {
	  smgr->drawAll();
	  endScene();
	  break ;
	}
      initScene();
      for (unsigned int i = 0; i < _perso.size(); i++) {
	_perso[i]->setEvent(event);
	tp.push(_perso[i]);
      }
      _map->checkBomb();
      smgr->drawAll();
      endScene();
    }
  if (_perso.size() == 0)
    std::cout << "Egalité ! " << std::endl;
  else
    std::cout << _perso.front()->getName() << " win !" << std::endl;
  _perso.clear();
  device->getCursorControl()->setVisible(true);
  nbplayer = 0;
  _nbThreads = 0;
  while (!_map->_bomb.empty())
    _map->_bomb.pop_back();
  smgr->clear();
}

void		Game::addCamera()
{
  camera = smgr->addCameraSceneNode();
  camera->setPosition(irr::core::vector3df(0, (sizeX + 200), -(sizeY + 100)));
}

void	Game::textureButton(button *s, const char *img)
{
  s->setImage(driver->getTexture(img));
  s->setUseAlphaChannel(true);
  s->setDrawBorder(false);
}

Click		Game::drawPause(Event *event)
{
  irr::video::ITexture			*imgMenu = NULL;
  if ((imgMenu = driver->getTexture(BACKGROUND_MENU)) == NULL)
    throw Excep("ERREUR: smgr failed");
  irr::core::dimension2d<irr::u32>	sizeM;
  sizeM = imgMenu->getSize();
  irr::core::position2d<irr::s32>	position0;
  irr::core::position2d<irr::s32>	position1;
  irr::core::rect<irr::s32>		rectangle;

  position0.X = 0;
  position0.Y = 0;
  position1.X = sizeM.Width;
  position1.Y = sizeM.Height;
  rectangle.UpperLeftCorner = position0;
  rectangle.LowerRightCorner = position1;
  driver->draw2DImage(imgMenu, position0, rectangle, 0,
		      irr::video::SColor(255, 255, 255, 255), true);
  _continue->draw();
  _back->draw();
  _options->draw();
  switch (event->getChoice()) {
  case Click::CONTINUE:
    return Click::CONTINUE;
  case Click::BACK:
    return Click::BACK;
  case Click::OPTIONS:
    return Click::OPTIONS;
  default:
    break ;
  }
  return Click::NOP;
}

int		Game::initPause(Event *event)
{
  _timer->stop();
  device->getCursorControl()->setVisible(true);
  _continue = env->addButton(rect(130, 255, 630, 330),
			     0, GUI_ID_CONTINUE, L"", L"Continue the game");
  _back= env->addButton(rect(130, 455, 630, 530),
			0, GUI_ID_BACK, L"", L"Back to main menu");
  _options = env->addButton(rect(130, 590, 630, 665),
			    0, GUI_ID_PAUSE_OPTION, L"", L"Options");
  textureButton(_continue, CONTINUE_BUTTON);
  textureButton(_back, QUIT_BUTTON);
  textureButton(_options, OPTIONS_BUTTON);
  bool back = false;
  while ((play() && back == false))
    {
      initScene();
       switch (drawPause(event))
	 {
	case Click::CONTINUE:
	    _timer->start();
	    device->getCursorControl()->setVisible(false);
	    return 1;
	case Click::BACK:
	    _timer->start();
	    back = true;
	    return 2;
	case Click::OPTIONS:
	  choiceOption(event);
	  _timer->start();
	  return 1;
	  break ;
	default:
	  break ;
	}
      endScene();
    }
  return (0);
}
