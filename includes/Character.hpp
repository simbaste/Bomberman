#ifndef CHARACTER_HPP_
# define CHARACTER_HPP_

# include <string>
# include <irr/irrlicht.h>
# include "Tools.hpp"
# include "Map.hpp"
# include "ICharacter.hpp"
# include "Game.hpp"
# include "Event.hpp"

class	Map;
struct	Position;

class Character : public ICharacter
{
public:
  Character(unsigned int x = 1, unsigned int y = 1,
	    Direction direction = Direction::RIGHT, Map *map = NULL,
	    Elem *el = NULL, std::vector<Character*> *_perso = NULL);
  ~Character();
  virtual void					DropBomb();
  virtual void					usePowerUp(Tile p);
  virtual void					getPowerUp(Tile p);
  virtual bool					isPowerUp(Tile t);
  virtual void					update();
  virtual void					moveUp();
  virtual void					moveLeft();
  virtual void					moveDown();
  virtual void					moveRight();
  virtual void					setX(int);
  virtual bool					canIGo(unsigned int y, unsigned int x);
  virtual int					getX() const;
  virtual int					getY() const;
  virtual void					setY(int);
  virtual Direction				getDirection() const;
  virtual void					setDirection(Direction);
  virtual std::string const&			getSprite() const;
  virtual void					setSprite(std::string const&);
  virtual std::string const&			getName() const;
  virtual void					setName(std::string const&);
  virtual unsigned int				getRangeBomb() const;
  virtual void					setRangeBomb(unsigned int);
  virtual unsigned int				getNbBomb() const;
  virtual void					setNbBomb(unsigned int);
  virtual int					getSpeed() const;
  virtual void					setSpeed(int);
  virtual int					getHp() const;
  virtual void					setHp(int);
  virtual bool					getKickBomb() const;
  virtual void					setKickBomb(bool);
  virtual bool					getVest() const;
  virtual void					setVest(bool);
  virtual bool					getLineBomb() const;
  virtual void					setLineBomb(bool);
  virtual bool					getGhost() const;
  virtual void					setGhost(bool);
  virtual int					getProgress() const;
  virtual void					setProgress(int);
  virtual bool					getIsPlayer() const;
  virtual void					setIsPlayer(bool);
  virtual int					deleteElem(Position const &);
  virtual void					setMesh(irrAnimMesh *m);
  virtual void					setEvent(Event *e);
  virtual void					setIrrMap(irrMap_t *im);
  virtual void					setSmgr(irrSmgr *sm);
  virtual void					setDriver(irrDriver *dv);
  virtual void					setDevice(irrDevice *dv);
  virtual irrAnimMesh				*getMesh() const;
  virtual Event					*getEvent() const;
  virtual irrMap_t				*getIrrMap() const;
  virtual irrSmgr				*getSmgr() const;
  virtual irrDriver				*getDriver() const;
  virtual irrDevice				*getDevice() const;
  virtual Elem					*getElem() const;
  virtual Sound					*getSound() const;
  virtual std::vector<Character *>		*getPerso() const;
  virtual void					setMap(Map *map);
  virtual bool					dead() const;

protected:
  irrAnimMesh					*mesh;
  Event						*event;
  irrMap_t					*irrMap;
  irrSmgr					*smgr;
  irrDriver					*driver;
  irrDevice					*device;
  Sound						*sound;
  Elem						*elem;
  std::vector<Character *>			*perso;
  int						_posX;
  int						_posY;
  Direction					_direction;
  std::string					_sprite;
  std::string					_nom;
  unsigned int					_rangeBomb;
  unsigned int					_nbBomb;
  float						_speed;
  int						_hp;
  bool						_kickBomb;
  bool						_vest;
  bool						_dead;
  bool						_lineBomb;
  bool						_ghost;
  int						_progress;
  bool						_isPlayer;
  Map						*_map;

};

# include "Map.hpp"

#endif /* !CHARACTER_HPP */
