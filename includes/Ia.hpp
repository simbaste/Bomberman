#ifndef IA_HPP_
# define IA_HPP_

# include <vector>
# include <irr/irrlicht.h>
# include "Game.hpp"
# include "IMap.hpp"
# include "Event.hpp"
# include "Character.hpp"
# include "Tools.hpp"

class	Map;

class	Ia : public Character
{
protected:
  std::vector<Position> _pos;
  std::vector<Position> _bombPos;
  bool			isMoving;
  bool			decision;
  int			sizeX;
  int			sizeY;
  int			_check;
  Pos			_p;
  int			oldX;
  int			oldY;
  float			_x;
  float			_y;

protected:
  virtual bool		lastPos();
  virtual bool		getRight();
  virtual bool		getLeft();
  virtual bool		getUp();
  virtual bool		getDown();
  virtual void		changeDir();
  virtual bool		isDead();
  virtual bool		movLast();
  virtual void		simpleDirection();
  virtual void		myDirection();
  virtual Direction	lookCharacter();
  virtual void		dropBomber();
  virtual bool		layingBomber();
  virtual void		layingBomber1();
  virtual Direction	seekBomber();
  virtual bool		movePuwerUp();
  virtual bool		takePowerUp();
  virtual bool		moveIa();
  virtual Direction	lookPowerUp();
  virtual void		deviation();
  virtual void		layingBomberPU();

public:
  Ia(unsigned int x = 1, unsigned int y = 1, Direction d = Direction::RIGHT, Map *map = NULL, Elem *elem = NULL,   std::vector<Character*> *_perso = NULL);
  ~Ia();
  virtual void		update();
  virtual void		moveUp();
  virtual void		moveLeft();
  virtual void		moveDown();
  virtual void		moveRight();
};

#endif /* !IA_HPP_ */
