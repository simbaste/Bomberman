#include <cmath>
#include <iostream>
#include "Ia.hpp"

#define BOMB_ASSETS "assets/file/bomb.jpg"

Position::Position(unsigned int Mx, unsigned int My)
  : x(Mx), y(My)
{
}

Ia::Ia(unsigned int x, unsigned int y, Direction d, Map *map, Elem *elem, std::vector<Character*> *_perso)
  : Character(x, y, d, map, elem, _perso), oldX(50), oldY(50)
{
  mesh->setMD2Animation(irr::scene::EMAT_RUN);
}

Ia::~Ia() {}

bool	Ia::lastPos()
{
  for (unsigned int i = 0; i < _pos.size(); i++) {
    if (_posX == _pos[i].x && _posY == _pos[i].y)
      return true;
  }
  return false;
}

bool	 Ia::movLast()
{
  if (_direction == Direction::LEFT || _direction == Direction::RIGHT) {
    if (_map->getCell(_posY - 1, _posX) == Tile::EMPTY) {
      _direction = Direction::DOWN;
      return true;
    } else if (_map->getCell(_posY + 1, _posX) == Tile::EMPTY) {
      _direction = Direction::UP;
      return true;
    }
  } else if (_direction == Direction::DOWN || _direction == Direction::UP) {
    if (_map->getCell(_posY, _posX + 1) == Tile::EMPTY) {
      _direction = Direction::RIGHT;
      return true;
    } else if (_map->getCell(_posY, _posX - 1) == Tile::EMPTY) {
      _direction = Direction::LEFT;
      return true;
    }
  }
  return false;
}

void		Ia::simpleDirection()
{
  bool		isOk = false;

  if (lastPos()) {
    isOk = movLast();
  }
  if (!isOk) {
    if (_map->getCell(_posY, _posX + 1) == Tile::EMPTY) {
      _direction = Direction::RIGHT;
    } else if (_map->getCell(_posY - 1, _posX) == Tile::EMPTY) {
      _direction = Direction::DOWN;
    } else if (_map->getCell(_posY, _posX - 1) == Tile::EMPTY) {
      _direction = Direction::LEFT;
    } else if (_map->getCell(_posY + 1, _posX) == Tile::EMPTY) {
      _direction = Direction::UP;
    }
  }
}

void	Ia::myDirection()
{
  if (((_direction == Direction::RIGHT) &&
       (_map->getCell(_posY, _posX + 1) != Tile::EMPTY))
      || ((_direction == Direction::DOWN) &&
	  (_map->getCell(_posY - 1, _posX) != Tile::EMPTY))
      || ((_direction == Direction::LEFT) &&
	  (_map->getCell(_posY, _posX - 1) != Tile::EMPTY))
      || ((_direction == Direction::UP) &&
	  (_map->getCell(_posY + 1, _posX) != Tile::EMPTY))) {
    simpleDirection();
  }
}

Direction	Ia::lookCharacter()
{
  for (unsigned int i = _posY + 1; i < _map->getMap().size(); i++) {
    if (_map->getCell(i, _posX) == Tile::CHARACTER) {
      return Direction::UP;
    }
  }
  for (unsigned int i = _posY - 1; i > 0; i--) {
    if (_map->getCell(i, _posX) == Tile::CHARACTER) {
      return Direction::DOWN;
    }
  }
  for (unsigned int i = _posX + 1; i < _map->getMap()[0].size(); i++) {
    if (_map->getCell(_posY, i) == Tile::CHARACTER) {
      return Direction::RIGHT;
    }
  }
  for (unsigned int i = _posX - 1; i > 0; i--) {
    if (_map->getCell(_posY, i) == Tile::CHARACTER) {
      return Direction::LEFT;
    }
  }
  return Direction::NOP;
}

void	Ia::dropBomber()
{
  if (_nbBomb > 0)
    if (_map->getCell(_posY - 1, _posX) == Tile::BLOCK ||
	_map->getCell(_posY + 1, _posX) == Tile::BLOCK ||
	_map->getCell(_posY, _posX - 1) == Tile::BLOCK ||
	_map->getCell(_posY, _posX + 1) == Tile::BLOCK) {
      _map->putBomb(device, *this);
      _map->setCell(_posY, _posX, Tile::BOMB);
    }
}

bool	Ia::layingBomber()
{
  if (_nbBomb > 0)
    if (_map->getCell(_posY - 1, _posX) == Tile::CHARACTER ||
	_map->getCell(_posY + 1, _posX) == Tile::CHARACTER ||
	_map->getCell(_posY, _posX - 1) == Tile::CHARACTER ||
	_map->getCell(_posY, _posX + 1) == Tile::CHARACTER) {
      _map->putBomb(device, *this);
      _map->setCell(_posY, _posX, Tile::BOMB);
      return true;
    }
  return false;
}

void	Ia::layingBomber1()
{
  if (_nbBomb > 0) {
    if (_direction == Direction::UP) {
      if (_map->getCell(_posY + 1, _posX) != Tile::EMPTY) {
	_map->putBomb(device, *this);
	_map->setCell(_posY, _posX, Tile::BOMB);
	(rand() % 2 == 0) ? (_direction = Direction::LEFT) : (_direction = Direction::RIGHT);
      }
    } else if (_direction == Direction::DOWN) {
      if (_map->getCell(_posY - 1, _posX) != Tile::EMPTY) {
	_map->putBomb(device, *this);
	_map->setCell(_posY, _posX, Tile::BOMB);
	(rand() % 2 == 0) ? (_direction = Direction::RIGHT) : (_direction = Direction::LEFT);
      }
    } else if (_direction == Direction::LEFT) {
      if (_map->getCell(_posY, _posX - 1) == Tile::CHARACTER) {
	_map->putBomb(device, *this);
	_map->setCell(_posY, _posX, Tile::BOMB);
	(rand() % 2 == 0) ? (_direction = Direction::DOWN) : (_direction = Direction::UP);
      }
    } else if (_direction == Direction::RIGHT) {
      if (_map->getCell(_posY, _posX + 1) != Tile::EMPTY) {
	_map->putBomb(device, *this);
	_map->setCell(_posY, _posX, Tile::BOMB);
	(rand() % 2 == 0) ? (_direction = Direction::UP) : (_direction = Direction::DOWN);
      }
    }
  }
}
Direction	Ia::seekBomber()
{
  Direction	d;
  Position	pos;

  srand(time(NULL));
  pos.x = _posX;
  pos.y = _posY;
  for (unsigned int i = _posY; i < _map->getMap().size(); i++) {
    if (_map->getCell(i, _posX) == Tile::BOMB) {
      _bombPos.push_back(pos);
      (rand() % 2 == 0) ? (d = Direction::LEFT) : (d = Direction::RIGHT);
      return d;
    }
  }
  for (unsigned int i = _posY; i > 0; i--) {
    if (_map->getCell(i, _posX) == Tile::BOMB) {
      _bombPos.push_back(pos);
      (rand() % 2 == 0) ? (d = Direction::RIGHT) : (d = Direction::LEFT);
      return d;
    }
  }
  for (unsigned int i = _posX; i < _map->getMap()[0].size(); i++) {
    if (_map->getCell(_posY, i) == Tile::BOMB) {
      _bombPos.push_back(pos);
      (rand() % 2 == 0) ? (d = Direction::DOWN) : (d = Direction::UP);
      return d;
    }
  }
  for (unsigned int i = _posX; i > 0; i--) {
    if (_map->getCell(_posY, i) == Tile::BOMB) {
      _bombPos.push_back(pos);
      (rand() % 2 == 0) ? (d = Direction::UP) : (d = Direction::DOWN);
      return d;
    }
  }
  return Direction::NOP;
}

void	Ia::changeDir()
{
  switch (_direction) {
  case Direction::RIGHT:
    _direction = Direction::LEFT;
  case Direction::LEFT:
    _direction = Direction::RIGHT;
  case Direction::UP:
    _direction = Direction::DOWN;
  case Direction::DOWN:
    _direction = Direction::UP;
  case Direction::NOP:
    _direction = Direction::RIGHT;
  }
}

bool	Ia::getRight()
{
  if (_map->getCell(_posY, _posX + 1) == Tile::EMPTY ||
      _map->getCell(_posY, _posX + 1) == Tile::CHARACTER ||
      _map->getCell(_posY, _posX + 1) == Tile::INTEL ||
      isPowerUp(_map->getCell(_posY, _posX + 1)) == true ||
      _map->getCell(_posY, _posX + 1) == Tile::EXPLOSION)
    return true;
  if (decision == false)
    changeDir();
  return false;
}

bool	Ia::getDown()
{
  if (_map->getCell(_posY - 1, _posX) == Tile::EMPTY ||
      _map->getCell(_posY - 1, _posX) == Tile::CHARACTER ||
      _map->getCell(_posY - 1, _posX) == Tile::INTEL ||
      isPowerUp(_map->getCell(_posY - 1, _posX)) == true ||
      _map->getCell(_posY - 1, _posX) == Tile::EXPLOSION)
    return true;
  if (decision == false)
    changeDir();
  return false;
}

bool	Ia::getLeft()
{
  if (_map->getCell(_posY, _posX - 1) == Tile::EMPTY ||
      _map->getCell(_posY, _posX - 1) == Tile::CHARACTER ||
      _map->getCell(_posY, _posX - 1) == Tile::INTEL ||
      isPowerUp(_map->getCell(_posY, _posX - 1)) == true ||
      _map->getCell(_posY, _posX - 1) == Tile::EXPLOSION)
    return true;
  if (decision == false)
    changeDir();
  return false;
}

bool	Ia::getUp()
{
  if (_map->getCell(_posY + 1, _posX) == Tile::EMPTY ||
      _map->getCell(_posY + 1, _posX) == Tile::CHARACTER ||
      _map->getCell(_posY + 1, _posX) == Tile::INTEL ||
      isPowerUp(_map->getCell(_posY + 1, _posX)) == true ||
      _map->getCell(_posY + 1, _posX) == Tile::EXPLOSION)
    return true;
  if (decision == false)
    changeDir();
  return false;
}

void	Ia::moveRight()
{
  irr::core::vector3df	r = mesh->getRotation();
  irr::core::vector3df	p = mesh->getPosition();
  Position		Mpos;

  isMoving = true;
  r.Y = 0;
  oldX = oldX + (1 * _speed);
  if (oldX  < 100)
    p.X += 1.0f * _speed;
  else
    {
      while (((int)p.X % 50) != 0)
	p.X += 1.0f;
    }
  mesh->setPosition(p);
  mesh->setRotation(r);
  if (oldX >= 100) {
    if (_map->getCell(_posY, _posX) != Tile::BOMB) {
      _map->setCell(_posY, _posX, Tile::EMPTY);
    }
    oldX = 50;
    _posX += 1;
    decision = true;
    Mpos.x = _posX;
    Mpos.y = _posY;
    p.X = (_posX * 50) - sizeX;
    p.Z = (_posY * 50) - sizeY;
    mesh->setPosition(p);
    _pos.push_back(Mpos);
    if (_map->getCell(_posY, _posX) >= (Tile)7) {
      getPowerUp(_map->getCell(_posY, _posX));
      sound->getSoundPU();
      deleteElem(Mpos);
    }
    _map->setCell(_posY, _posX, Tile::CHARACTER);
  }
}

void	Ia::moveDown()
{
  irr::core::vector3df	r = mesh->getRotation();
  irr::core::vector3df	p = mesh->getPosition();
  Position		Mpos;

  isMoving = true;
  r.Y = 90.0f;
  oldY = oldY - (1 * _speed);
  if (oldY > 0)
    p.Z -= 1.0f * _speed;
  else
    {
      while (((int)p.Z % 50) != 0)
	p.Z -= 1.0f;
    }
  mesh->setPosition(p);
  mesh->setRotation(r);
  if (oldY <= 0) {
    if (_map->getCell(_posY, _posX) != Tile::BOMB) {
      _map->setCell(_posY, _posX, Tile::EMPTY);
    }
    oldY = 50;
    _posY -= 1;
    decision = true;
    Mpos.x = _posX;
    Mpos.y = _posY;
    p.X = (_posX * 50) - sizeX;
    p.Z = (_posY * 50) - sizeY;
    mesh->setPosition(p);
    _pos.push_back(Mpos);
    if (_map->getCell(_posY, _posX) >= (Tile)7) {
      getPowerUp(_map->getCell(_posY, _posX));
      sound->getSoundPU();
      deleteElem(Mpos);
    }
    _map->setCell(_posY, _posX, Tile::CHARACTER);
  }
}

void	Ia::moveLeft()
{
  irr::core::vector3df	r = mesh->getRotation();
  irr::core::vector3df	p = mesh->getPosition();
  Position		Mpos;

  isMoving = true;
  r.Y = 180.0f;
  oldX = oldX - (1 * _speed);
  if (oldX > 0)
    p.X -= 1.0f * _speed;
  else
    {
      while (((int)p.X % 50) != 0)
	p.X -= 1.0f;
    }
  mesh->setPosition(p);
  mesh->setRotation(r);
  if (oldX <= 0) {
    if (_map->getCell(_posY, _posX) != Tile::BOMB) {
      _map->setCell(_posY, _posX, Tile::EMPTY);
    }
    oldX = 50;
    _posX -= 1;
    decision = true;
    Mpos.x = _posX;
    Mpos.y = _posY;
    p.X = (_posX * 50) - sizeX;
    p.Z = (_posY * 50) - sizeY;
    mesh->setPosition(p);
    _pos.push_back(Mpos);
    if (_map->getCell(_posY, _posX) >= (Tile)7) {
      getPowerUp(_map->getCell(_posY, _posX));
      sound->getSoundPU();
      deleteElem(Mpos);
    }
    _map->setCell(_posY, _posX, Tile::CHARACTER);
  }
}

void	Ia::moveUp()
{
  irr::core::vector3df	r = mesh->getRotation();
  irr::core::vector3df	p = mesh->getPosition();
  Position		Mpos;

  r.Y = -90.0f;
  oldY = oldY + (1 * _speed);
  if (oldY < 100)
    p.Z += 1.0f * _speed;
  else
    {
      while (((int)p.Z % 50) != 0)
	{
	  p.Z += 1.0f;
	}
    }
  mesh->setPosition(p);
  mesh->setRotation(r);
  if (oldY >= 100) {
    if (_map->getCell(_posY, _posX) != Tile::BOMB) {
      _map->setCell(_posY, _posX, Tile::EMPTY);
    }
    oldY = 50;
    _posY += 1;
    decision = true;
    Mpos.x = _posX;
    Mpos.y = _posY;
    p.X = (_posX * 50) - sizeX;
    p.Z = (_posY * 50) - sizeY;
    mesh->setPosition(p);
    _pos.push_back(Mpos);
    if (_map->getCell(_posY, _posX) >= (Tile)7) {
      getPowerUp(_map->getCell(_posY, _posX));
      sound->getSoundPU();
      deleteElem(Mpos);
    }
    _map->setCell(_posY, _posX, Tile::CHARACTER);
  }
}

bool	Ia::movePuwerUp()
{
  switch (_direction) {
  case Direction::RIGHT:
    if (getRight()) {
      moveRight();
      return true;
    }
  case Direction::DOWN:
    if (getDown()) {
      moveDown();
      return true;
    }
  case Direction::LEFT:
    if (getLeft()) {
      moveLeft();
      return true;
    }
  case Direction::UP:
    if (getUp()) {
      moveUp();
      return true;
    }
  default:
    isMoving = false;
  }
  return false;
}

bool	Ia::moveIa()
{
  switch (_direction) {
  case Direction::RIGHT:
    if (getRight()) {
      moveRight();
      return true;
    }
  case Direction::DOWN:
    if (getDown()) {
      moveDown();
      return true;
    }
  case Direction::LEFT:
    if (getLeft()) {
      moveLeft();
      return true;
    }
  case Direction::UP:
    if (getUp()) {
      moveUp();
      return true;
    }
  default:
    isMoving = false;
    mesh->setMD2Animation(irr::scene::EMAT_STAND);
  }
  return false;
}

bool	Ia::takePowerUp()
{
  if (isPowerUp(_map->getCell(_posY, _posX + 1))) {
    _direction = Direction::RIGHT;
    return true;
  } else if (isPowerUp(_map->getCell(_posY - 1, _posY))) {
    _direction = Direction::DOWN;
    return true;
  } else if (isPowerUp(_map->getCell(_posY, _posY - 1))) {
    _direction = Direction::LEFT;
    return true;
  } else if (isPowerUp(_map->getCell(_posY + 1, _posY))) {
    _direction = Direction::UP;
    return true;
  }
  return false;
}

void	Ia::layingBomberPU()
{
  if (_nbBomb > 0)
    if (isPowerUp(_map->getCell(_posY - 1, _posX)) ||
	isPowerUp(_map->getCell(_posY + 1, _posX)) ||
	isPowerUp(_map->getCell(_posY, _posX - 1)) ||
	isPowerUp(_map->getCell(_posY, _posX + 1))) {
      _map->putBomb(device, *this);
      _map->setCell(_posY, _posX, Tile::BOMB);
    }
}

void	Ia::deviation()
{
  if (_direction == Direction::LEFT || _direction == Direction::RIGHT) {
    if (_map->getCell(_posY - 1, _posX) == Tile::EMPTY) {
      _direction = Direction::DOWN;
      return ;
    } else if (_map->getCell(_posY + 1, _posX) == Tile::EMPTY) {
      _direction = Direction::UP;
      return ;
    }
  } else if (_direction == Direction::DOWN || _direction == Direction::UP) {
    if (_map->getCell(_posY, _posX + 1) == Tile::EMPTY) {
      _direction = Direction::RIGHT;
      return ;
    } else if (_map->getCell(_posY, _posX - 1) == Tile::EMPTY) {
      _direction = Direction::LEFT;
      return ;
    }
  }
}

Direction	Ia::lookPowerUp()
{
  for (unsigned int i = _posY; i < _map->getMap().size(); i++) {
    if (isPowerUp(_map->getCell(i, _posX))) {
      return Direction::UP;
    }
  }
  for (unsigned int i = _posY; i > 0; i--) {
    if (isPowerUp(_map->getCell(i, _posX))) {
      return Direction::DOWN;
    }
  }
  for (unsigned int i = _posX; i < _map->getMap()[0].size(); i++) {
    if (isPowerUp(_map->getCell(_posY, i))) {
      return Direction::RIGHT;
    }
  }
  for (unsigned int i = _posX; i > 0; i--) {
    if (isPowerUp(_map->getCell(_posY, i))) {
      return Direction::LEFT;
    }
  }
  return Direction::NOP;
}

bool	Ia::isDead()
{
  if (_check >= 100) {
    for (unsigned i = 0; i < _bombPos.size(); i++)
      _bombPos.erase(_bombPos.begin());
    _check = 0;
  }
  switch (_direction) {
  case Direction::UP:
    for (unsigned int i = 0; i < _bombPos.size(); i++)
      if (_bombPos[i].x == _posX && _bombPos[i].y == _posY + 1) {
	_check++;
	return false;
      }
  case Direction::DOWN:
    for (unsigned int i = 0; i < _bombPos.size(); i++)
      if (_bombPos[i].x == _posX && _bombPos[i].y == _posY - 1) {
	_check++;
	return false;
      }
  case Direction::LEFT:
    for (unsigned int i = 0; i < _bombPos.size(); i++)
      if (_bombPos[i].x == _posX - 1 && _bombPos[i].y == _posY) {
	_check++;
	return false;
      }
  case Direction::RIGHT:
    for (unsigned int i = 0; i < _bombPos.size(); i++)
      if (_bombPos[i].x == _posX + 1 && _bombPos[i].y == _posY) {
	_check++;
	return false;
      }
  case Direction::NOP:
    break;
  }
  return true;
}

void	Ia::update() {}
