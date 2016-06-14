#ifndef GAME_HPP_
# define GAME_HPP_

#include <irr/irrlicht.h>
#include <vector>
#include <string>
#include <Sound.hpp>
#include "Event.hpp"
#include "Tools.hpp"

class	Ia;
class	Player;
class	Character;
class	Map;

class Game
{
private:
  std::vector<keyMap *>					KeyBind;
  irr::IrrlichtDevice					*device;
  irr::video::IVideoDriver				*driver;
  irr::scene::ISceneManager				*smgr;
  irr::scene::ICameraSceneNode				*camera;
  irr::video::ITexture					*imgMenu;
  irr::scene::ISceneNode				*skybox;
  irr::gui::IGUIEnvironment				*env;
  irr::core::dimension2d<irr::u32>			taille;
  irr::core::position2d<irr::s32>			position0;
  irr::core::position2d<irr::s32>			position1;
  irr::core::rect<irr::s32>				rectangle;
  irr::gui::IGUIWindow					*win;
  irr::gui::IGUITabControl				*tab;
  irr::gui::IGUITab					*t1;
  irr::gui::IGUIStaticText				*tName1;
  irr::gui::IGUIStaticText				*tName2;
  irr::gui::IGUIStaticText				*tName3;
  std::vector<std::vector<irr::scene::ISceneNode*> >	irrMap;
  std::vector<Character*>				_perso;
  irr::core::dimension2d<irr::u32>			sizeM;
  Sound							sound;
  bool							b;
  Map							*_map;
  int							sizeX;
  int							sizeY;
  int							_nbThreads;
  int							pause;
  int							nbplayer;
  button						*_continue;
  button						*_back;
  button						*_options;
  button						*cancel;
  button						*up1;
  button						*down1;
  button						*left1;
  button						*right1;
  button						*bomb1;
  button						*up2;
  button						*down2;
  button						*left2;
  button						*right2;
  button						*bomb2;
  button						*up3;
  button						*down3;
  button						*left3;
  button						*right3;
  button						*bomb3;
  button						*player1;
  button						*player2;
  button						*player3;

  irr::ITimer                                           *_timer;
public:
  Game(Map *);
  ~Game();
  irr::IrrlichtDevice		*getDevice() const;
  irr::video::IVideoDriver	*getDriver() const;
  irr::scene::ISceneManager	*getSmgr() const;
  irr::gui::IGUIEnvironment	*getEnv() const;
  void				loadMap(int, int, int);
  int				showBomb(Position const &p);
  int				showFire(Position const &p);
  void				lunchCharacter(Event *event, int choice, std::vector<irr::core::stringc> &names);
  void				setEvent(Event *);
  void				setEvent();
  void				bckGame();
  void				initScene();
  void				endScene();
  void				addGround();
  void				getCol(unsigned int i);
  void				addScene();
  void				addCamera();
  void				lunchIa(Event &event);
  bool				play() const;
  int				deleteBomb(const Position&);
  void				refreshAfterUpdate();
  void				explodeBomb(BombInfo &bomb);
  void				makeExplosion(BombInfo &bomb);
  void				explodeCell(BombInfo &bomb, int x, int y);
  Tile				getRandomPowerUp();
  void				soundMenu();
  void				soundMain();
  void				stopSound();
  int				showPowerup(Position const &p, char *file);
  int				loadAssets();
  void				initInfos(std::vector<irr::core::stringc> &);
  void				supScene();
  void				addSkyBox();
  void				textureButton(button *s, const char *img);
  Click				drawPause(Event *event);
  int				initPause(Event *event);
  Click				drawOption(Event *event);
  void				initOption();
  bool				choiceOption(Event *event);
};

#endif /* GAME_HPP_ */
