#include "Character.hpp"
#include <iostream>

Character::Character(unsigned int x, unsigned int y, Direction d, Map *map, Elem *el, std::vector<Character*> *_perso)
  : _posX(x), _posY(y), _direction(d), _sprite(""), _nom(""),
    _rangeBomb(1), _nbBomb(1), _speed(1), _hp(1), _kickBomb(false), _vest(false),
    _lineBomb(false), _ghost(false), _progress(0), _isPlayer(false)
{
  perso = _perso;
  _map = map;
  irrMap = el->irrMap;
  mesh = el->mesh;
  smgr = el->smgr;
  sound = el->sound;
  driver = el->driver;
  device = el->device;
  elem = el;
}

Character::~Character() {}

bool	Character::isPowerUp(Tile t)
{
  switch (t) {
  case Tile::INVINCIBLE:
    return true;
  case Tile::KICKBOMB:
    return true;
  case Tile::GHOST:
    return true;
  case Tile::RANGEDOWN:
    return true;
  case Tile::RANGEUP:
    return true;
  case Tile::SPEEDUP:
    return true;
  case Tile::SPEEDDOWN:
    return true;
  case Tile::BOMBUP:
    return true;
  case Tile::LINEBOMB:
    return true;
  case Tile::BOMBDOWN:
    return true;
  default:
    return false;
  }
  return false;
}

bool    Character::canIGo(unsigned int y, unsigned int x)
{
  if (_map->getCell(y, x) == Tile::EMPTY ||
      _map->getCell(y, x) == Tile::CHARACTER ||
      _map->getCell(y, x) == Tile::EXPLOSION ||
      _map->getCell(y, x) == Tile::INTEL ||
      _map->pushBomb(*this, x, y) ||
      isPowerUp(_map->getCell(y, x)))
    return (true);
  return (false);
}

Elem	*Character::getElem() const {return elem;}

void	Character::DropBomb()
{
  if (_map->getMap()[_posY][_posX] != Tile::BOMB)
    _map->getMap()[_posY][_posX] = Tile::BOMB;
}

void		Character::update() {}
void		Character::moveUp() {}
void		Character::moveLeft() {}
void		Character::moveDown() {}
void		Character::moveRight() {}

int		Character::deleteElem(Position const &p)
{
  if ((*irrMap)[p.y][p.x])
    (*irrMap)[p.y][p.x]->setVisible(false);
  return (0);
}

std::vector<Character *>	*Character::getPerso() const
{
  return perso;
}

bool	Character::dead() const
{
  return _dead;
}

void	Character::usePowerUp(Tile p __attribute__((unused))) {}

void	Character::getPowerUp(Tile p)
{
  switch (p)
    {
    case Tile::RANGEUP:
      _rangeBomb += 1;
      break;
    case Tile::RANGEDOWN:
      if (_rangeBomb > 1)
	_rangeBomb -= 1;
      break;
    case Tile::BOMBUP:
      _nbBomb += 1;
      break;
    case Tile::BOMBDOWN:
      if (_nbBomb > 1)
	_nbBomb -= 1;
      break;
    case Tile::SPEEDUP:
	if (_speed < 2)
	  _speed += 0.4;
      break;
    case Tile::SPEEDDOWN:
      if (_speed > 1)
	_speed -= 0.4;
      break;
    case Tile::INVINCIBLE:
      break;
    case Tile::KICKBOMB:
      _kickBomb = true;
      break;
    case Tile::GHOST:
      break;
    case Tile::LINEBOMB:
      _lineBomb = true;
      break;
    default:
      break;
    }
}

int		Character::getX() const {return _posX;}
void		Character::setX(int pos) {_posX = pos;}

int		Character::getY() const {return _posY;}
void		Character::setY(int pos) {_posY = pos;}

Direction	Character::getDirection() const {return _direction;}
void		Character::setDirection(Direction dir) {_direction = dir;}

std::string const&	Character::getSprite() const {return _sprite;}
void		Character::setSprite(std::string const& sprite) {_sprite = sprite;}

std::string const&	Character::getName() const {return _nom;}
void		Character::setName(std::string const& nom) {_nom = nom;}

unsigned int	Character::getRangeBomb() const {return _rangeBomb;}
void		Character::setRangeBomb(unsigned int range) {_rangeBomb = range;}

unsigned int	Character::getNbBomb() const {return _nbBomb;}
void		Character::setNbBomb(unsigned int nb) {_nbBomb = nb;}

int		Character::getSpeed() const {return _speed;}
void		Character::setSpeed(int speed) {_speed = speed;}

int		Character::getHp() const {return _hp;}
void		Character::setHp(int hp) {_hp = hp;}

bool		Character::getKickBomb() const {return _kickBomb;}
void		Character::setKickBomb(bool kickBomb) {_kickBomb = kickBomb;}

bool		Character::getVest() const {return _vest;}
void		Character::setVest(bool vest) {_vest = vest;}

bool		Character::getLineBomb() const {return _lineBomb;}
void		Character::setLineBomb(bool lineBomb) {_lineBomb = lineBomb;}

bool		Character::getGhost() const {return _ghost;}
void		Character::setGhost(bool ghost) {_ghost = ghost;}

int		Character::getProgress() const {return _progress;}
void		Character::setProgress(int progress) {_progress = progress;}

bool		Character::getIsPlayer() const {return _isPlayer;}
void		Character::setIsPlayer(bool isplayer) {_isPlayer = isplayer;}

void		Character::setMap(Map *map) {_map = map;}
void		Character::setMesh(irrAnimMesh *m) {this->mesh = m;}
void		Character::setEvent(Event *e){event = e;}
void		Character::setIrrMap(irrMap_t *im){ this->irrMap = im;}
void		Character::setSmgr(irrSmgr *sm){ smgr = sm;}
void		Character::setDriver(irrDriver *dv){ driver = dv;}
void		Character::setDevice(irrDevice *dv){  device = dv;}
irrAnimMesh	*Character::getMesh() const{  return mesh;}
Event		*Character::getEvent() const{  return event;}
irrMap_t	*Character::getIrrMap() const{  return irrMap;}
irrSmgr		*Character::getSmgr() const{  return smgr;}
irrDriver	*Character::getDriver() const{  return driver;}
irrDevice	*Character::getDevice() const{  return device;}
Sound		*Character::getSound() const{  return sound;}
