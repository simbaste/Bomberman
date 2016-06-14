#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <iostream>
# include <cmath>		// TEST
# include "Character.hpp"
# include "Event.hpp"
# include "Game.hpp"
# include "Tools.hpp"

class Player : public Character
{
public:
  bool			move(Direction);
  //virtual std::string	getSprite() const;
  void			update(/*irr::scene::IAnimatedMeshSceneNode *mesh, Event &event,
			       irrMap_t &irrmap, irr::scene::ISceneManager *smgr,
			       irr::video::IVideoDriver *driver,
			       irr::IrrlichtDevice *device*/);
  Player(unsigned int x = 1, unsigned int y = 1,
	 Direction direction = Direction::RIGHT,
	 Map *map = NULL, Elem *elem = NULL, std::vector<Character*> *_perso = NULL, struct keyMap *bind = NULL);
  ~Player();
  virtual void		moveUp();
  virtual void		moveLeft();
  virtual void		moveDown();
  virtual void		moveRight();
private:
  irr::EKEY_CODE	key;
  bool			is_moving;
  struct keyMap		*keyMap;
  float			oldx;
  float			oldy;
};

#endif /* !PLAYER_HPP */
