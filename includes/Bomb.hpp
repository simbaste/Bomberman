#ifndef BOMB_HPP_
# define BOMB_HPP_

#include <vector>
#include <irr/irrlicht.h>
#include "IBomb.hpp"
#include "Sound.hpp"

#include "Tools.hpp"

typedef std::vector<irr::scene::ISceneNode *> meshVector;
typedef irr::scene::ISceneNode*  mesh;
class Bomb : public IBomb
{
public:
  Bomb(Character *owner, int sizeX, int sizeY,
       unsigned int timeToEXplode = 4000);
  Bomb(Character &owner, int sizeX, int sizeY,
       unsigned int timeToEXplode = 4000);
  ~Bomb();
  void		setPosition(unsigned int posX, unsigned int posY);

  unsigned int	getRangeBomb() const;
  void		setRangeBomb(unsigned int range);

  unsigned int	getX() const;
  void		setX(unsigned int x);
  unsigned int	getY() const;
  void		setY(unsigned int y);
  void		setSizeX(int x);
  void		setSizeY(int y);
  int		getSizeY() const;
  int		getSizeX() const;

  Character	*getOwner();
  void		setTimeToExplode(unsigned int t);
  void		setTimer(unsigned int t);
  void		setTimeExplosion(unsigned int t);

  unsigned int  getStartTimer() const;
  unsigned int	getTimeToExplode() const ;
  unsigned int	getTimeExplosion() const ;

  bool		isExploded();

  bool		isShow() const;
  void		showBomb();
  void		setShow(bool show);

  void		startExplosion();
  bool	        isFlamming() const;
  bool		isEndFlamming();
  void		setExplosion(bool ex);
  void		setExploded(bool ex);
  bool		getExplosion() const;
  bool		getExploded() const;

  //NEW VERSION :
  int		addBomb(int x, int y);
  int		addFire(int x, int y);
  void		clearCell(int x, int y);
  void		deleteBomb();
  void		deleteExplosion();
  int		addPowerup(int x, int y, Tile &tile);
  const char	*getPowerupFile(Tile &tile);

  void		move();
  bool		startMoving(int direction);
  bool		isMoving() const;
  int		getDirection() {return _direction;}
private:
  irr::ITimer			*_timer;
  irr::IrrlichtDevice		*_device;
  Character			*_owner;
  unsigned int			_range;
  unsigned int			_posX;
  unsigned int			_posY;
  unsigned int			_timeStarted;
  unsigned int			_timeToExplode;
  unsigned int			_timeExplosion;
  bool				_show;
  bool				_explosion;
  bool				_exploded;
  mesh				_bombMesh;
  meshVector			_explosionMesh;
  int				_sizeX;
  int				_sizeY;
  Elem				*_graphics;
  //  Sound				_sound;
  int				_direction;
  int				_progressX;
  int				_progressY;
  bool				_isMoving;
};
#endif
