//
// Bomb.cpp for Bomb in /home/dauvoi_l/rendu/CPP/cpp_indie_studio/includes
//
// Made by root
// Login   <dauvoi_l@epitech.net>
//
// Started on  Tue May 24 12:09:11 2016 root
//

#include <iostream>
#include "Character.hpp"
#include "Bomb.hpp"

Bomb::Bomb(Character * owner, int sizeX, int sizeY,
	   unsigned int timeToExplode)
{
  _owner = owner;
  _device = _owner->getDevice();
  _timer = _device->getTimer();
  _range = _owner->getRangeBomb();
  this->setPosition(_owner->getX(), _owner->getY());
  this->setTimeToExplode(timeToExplode);
  this->setTimer(_timer->getTime());
  _show = false;
  _explosion = false;
  _exploded = false;
  _timeExplosion = 500;
  _sizeX = sizeX;
  _sizeY = sizeY;

  _graphics = _owner->getElem();
  addBomb(_posX, _posY);
  _direction = 0;
  _progressX = 50;
  _progressY = 50;
  _isMoving = false;
}

Bomb::Bomb(Character &owner, int sizeX, int sizeY, unsigned int timeToExplode)
{
  _owner = &owner;
  _device = _owner->getDevice();
  _timer = _device->getTimer();
  _range = _owner->getRangeBomb();
  this->setPosition(_owner->getX(), _owner->getY());
  this->setTimeToExplode(timeToExplode);
  this->setTimer(_timer->getTime());
  _show = false;
  _explosion = false;
  _exploded = false;
  _timeExplosion = 500;
  _sizeX = sizeX;
  _sizeY = sizeY;
  _graphics = _owner->getElem();
  addBomb(_posX, _posY);

  _direction = 0;
  _progressX = 50;
  _progressY = 50;
  _isMoving = false;
}

Bomb::~Bomb()
{
  deleteBomb();
  deleteExplosion();
}

void	Bomb::setPosition(unsigned int posX, unsigned int posY)
{
  _posX = posX;
  _posY = posY;
}

unsigned int	Bomb::getRangeBomb() const {return _range;}
unsigned int	Bomb::getX() const {return _posX;}
unsigned int	Bomb::getY() const {return _posY;}
Character	*Bomb::getOwner() {return _owner;}
void		Bomb::setTimeToExplode(unsigned int t) {_timeToExplode = t;}
void		Bomb::setTimer(unsigned int t) {_timeStarted = t;}
void		Bomb::setTimeExplosion(unsigned int t) {_timeExplosion = t;}
unsigned int	Bomb::getStartTimer() const {return _timeStarted;}
unsigned int	Bomb::getTimeToExplode() const {return _timeToExplode;}
unsigned int	Bomb::getTimeExplosion() const {return _timeExplosion;}

void		Bomb::startExplosion()
{
  (_owner->getSound())->getSoundExp();
  _timeStarted = _timer->getTime();
  _explosion = true;
  _exploded = true;
}

void		Bomb::setSizeX(int x) {_sizeX = x;}
void		Bomb::setSizeY(int y) {_sizeY = y;}
int		Bomb::getSizeX() const {return _sizeX;}
int		Bomb::getSizeY() const {return _sizeY;}

void		Bomb::setRangeBomb(unsigned int range) {_range = range;}
void		Bomb::setX(unsigned int x) {_posX = x;}
void		Bomb::setY(unsigned int y) {_posY = y;}
void		Bomb::setExplosion(bool ex) {_explosion = ex;}
void		Bomb::setExploded(bool ex) {_exploded = ex;}
bool		Bomb::getExplosion() const {return _explosion;}
bool		Bomb::getExploded() const {return _exploded;}

bool		Bomb::isFlamming() const { return _explosion; }

bool		Bomb::isEndFlamming()
{
  if ((_timeStarted + _timeExplosion) <=  _timer->getTime())
    return (true);
  return (false);
}

bool		Bomb::isShow() const { return _show; }
void		Bomb::showBomb() { _show = true; }
void		Bomb::setShow(bool show) { _show = show; }

bool		Bomb::isExploded()
{
  if (_exploded == true)
      return (_exploded);
  if ((_timeStarted + _timeToExplode) <=  _timer->getTime())
    {
      _exploded = true;
      return (true);
    }
  return (false);
}

void		Bomb::deleteBomb()
{
  if (_bombMesh)
    {
      _bombMesh->remove();
      _bombMesh = NULL;
    }
}

void		Bomb::deleteExplosion()
{
  unsigned int	i = 0;
  unsigned int	size = _explosionMesh.size();

  while (i < size)
    {
      if (_explosionMesh[i])
	_explosionMesh[i]->remove();
      ++i;
    }
  _explosionMesh.clear();
}

int		Bomb::addFire(int x, int y)
{
  irrNode	*fire;

  if ((fire = (_owner->getSmgr())->addCubeSceneNode(SIZE_FIRE)) == NULL)
    return (-1);
  fire->setPosition(irrVector((x * 50) - _sizeX, 50, (y * 50) - _sizeY));
  fire->setMaterialTexture(0, (_owner->getDriver())->getTexture(FIRE_WALL));
  fire->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _explosionMesh.push_back(fire);
  return (0);
}

const char	*Bomb::getPowerupFile(Tile &tile)
{
  switch (tile)
    {
    case Tile::RANGEUP:
      return RANGE_UP_ASSET;

    case Tile::BOMBUP:
      return BOMB_UP_ASSET;

    case Tile::SPEEDUP:
      return SPEED_UP_ASSET;

    case Tile::KICKBOMB:
      return KICKBOMB_ASSET;

    case Tile::SPEEDDOWN:
      return SPEED_DOWN_ASSET;

    case Tile::BOMBDOWN:
      return BOMB_DOWN_ASSET;

    case Tile::RANGEDOWN:
      return RANGE_DOWN_ASSET;

    default :
      return RANGE_UP_ASSET;
    }
}

void		Bomb::clearCell(int x, int y)
{
  if (((*(_owner->getIrrMap()))[y][x]) != NULL)
    {
      ((*(_owner->getIrrMap()))[y][x])->setVisible(false);
      ((*(_owner->getIrrMap()))[y][x]) = NULL;
    }
}

int		Bomb::addPowerup(int x, int y, Tile &tile)
{
  irrNode	*powerup;

  if ((powerup = (_owner->getSmgr())->addCubeSceneNode(SIZE_POWERUP)) == NULL)
    return (-1);
  powerup->setPosition(irrVector((x * 50) - _sizeX, 50, (y * 50) - _sizeY));
  powerup->setMaterialTexture(0, (_owner->getDriver())->getTexture(getPowerupFile(tile)));
  powerup->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  (*(_owner->getIrrMap()))[y][x] = powerup;
  return (0);

}

int		Bomb::addBomb(int x, int y)
{
  irrNode	*bomb;

  if ((bomb = (_owner->getSmgr())->addCubeSceneNode(SIZE_BOMB)) == NULL)
    return (-1);
  bomb->setPosition(irrVector((x * 50) - _sizeX, 50, (y * 50) - _sizeY));
  bomb->setMaterialTexture(0, (_owner->getDriver())->getTexture("assets/file/bomb.jpg"));
  bomb->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _bombMesh = bomb;
  return (0);
}
// 1 UP
// 2 DOWN
// 3 RIGHT
// 4 LEFT

void		Bomb::move()
{
  irrVector pos = _bombMesh->getPosition();

  switch (_direction)
    {
    case 1:
      pos.Z += 50;
      _bombMesh->setPosition(pos);
      _posY++;
      break;
    case 2:
      pos.Z -= 50;
      _bombMesh->setPosition(pos);
      _posY--;
      break;
    case 3:
      pos.X += 50;
      _bombMesh->setPosition(pos);
      _posX++;
      break;
    case 4:
      pos.X -= 50;
      _bombMesh->setPosition(pos);
      _posX--;
      break;
    default:
      std::cout << "ERROR" << std::endl;
      break;
    }
}

bool		Bomb::isMoving() const
{
  return (_isMoving);
}

bool		Bomb::startMoving(int direction)
{
  _direction = direction;
  _isMoving = true;
  move();
  return (true);
}
