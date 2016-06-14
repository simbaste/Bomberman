#include "Game.hpp"
#include "Player.hpp"

Player::Player(unsigned int x, unsigned int y,  Direction direction, Map *map, Elem *elem, std::vector<Character*> *_perso, struct keyMap *bind) : Character(x, y, direction, map, elem, _perso)
{
  is_moving = true;
  oldx = 25;
  oldy = 25;
  _dead = false;
  _isPlayer = true;
  keyMap = bind;
  key = irr::EKEY_CODE::KEY_F1;
}

Player::~Player()
{

}

bool	Player::move(Direction dir)
{
  switch (dir)
    {
    case Direction::UP:
      if (canIGo(_posY + 1, _posX))
	return (true);
      return (false);
    case Direction::DOWN :
      if (canIGo(_posY -1, _posX))
	return (true);
      return (false);
    case Direction::RIGHT:
      if (canIGo(_posY, _posX + 1))
	return (true);
      return (false);
    case Direction::LEFT:
      if (canIGo(_posY, _posX - 1))
	return (true);
      return (false);
    case Direction::NOP:
      return (false);
    }
  return (false);
}

void		Player::moveUp()
{
  irr::core::vector3df	p = mesh->getPosition();
  Position		pos;
  int			tmp;

  if (oldx > 40)
    {
      while (oldx > 40)
	{
	  oldx--;
	  p.X--;
	}
    }
  else if (oldx < 10)
    {
      while (oldx < 10)
	{
	  oldx++;
	  p.X++;
	}
    }
  if (oldy <= 40 || move(Direction::UP))
    {
      tmp = oldy;
      oldy += _speed;
      if ((oldy > 40) && !(move(Direction::UP)))
	{
	  oldy = 40;
	  p.Z = p.Z + (40 - tmp);
	}
      else
	p.Z += _speed;
      if (oldy >= 50)
	{
	  oldy = oldy - 50.0f;;
	  if (_map->getCell(_posY, _posX) != Tile::BOMB)
	    _map->setCell(_posY, _posX, Tile::EMPTY);
	  _posY += 1;
	  if (_map->getCell(this->_posY, this->_posX) >= (Tile)8) {
	    getPowerUp(_map->getCell(this->_posY, this->_posX));
	    sound->getSoundPU();
	    pos.x = _posX;
	    pos.y = _posY;
	    deleteElem(pos);
	  }
	  _map->setCell(_posY, _posX, Tile::CHARACTER);
	}
      mesh->setPosition(p);
    }
}

void		Player::moveLeft()
{
  irr::core::vector3df	p = mesh->getPosition();
  Position		pos;
  int			tmp;

  if (oldy > 40)
    {
      while (oldy > 40)
	{
	  oldy--;
	  p.Z--;
	}
    }
  else if (oldy < 10)
    {
      while (oldy < 10)
	{
	  oldy++;
	  p.Z++;
	}
    }
  if (oldx >= 10 || move(Direction::LEFT))
    {
      tmp = oldx;
      oldx -= _speed;
      if ((oldx < 10) && !move(Direction::LEFT))
	{
	  oldx = 10;
	  p.X = p.X - (10 - tmp);
	}
      else
	p.X -= _speed;
      if (oldx < 0)
	{
	  oldx = 50 - abs(oldx);
	  if (_map->getCell(_posY, _posX) != Tile::BOMB)
	    _map->setCell(_posY, _posX, Tile::EMPTY);
	  _posX -= 1;
	  if (_map->getCell(this->_posY, this->_posX) >= (Tile)8) {
	    getPowerUp(_map->getCell(this->_posY, this->_posX));
	    sound->getSoundPU();
	    pos.x = _posX;
	    pos.y = _posY;
	    deleteElem(pos);
	  }
	  _map->setCell(_posY, _posX, Tile::CHARACTER);
	}
      mesh->setPosition(p);
    }
}

void		Player::moveDown()
{
  irr::core::vector3df	p = mesh->getPosition();
  Position		pos;
  int			tmp;

  if (oldx > 40)
    {
      while (oldx > 40)
	{
	  oldx--;
	  p.X--;
	}
    }
  else if (oldx < 10)
    {
      while (oldx < 10)
	{
	  oldx++;
	  p.X++;
	}
    }
  if (oldy >= 10 || move(Direction::DOWN))
    {
      tmp = oldy;
      oldy -= _speed;
      if ((oldy < 10) && !move(Direction::DOWN))
	{
	  oldy = 10;
	  p.Z = p.Z - (10 - tmp);
	}
      else
	  p.Z -= _speed;
      if (oldy < 0)
	{
	  oldy = 50 - abs(oldy);
	  if (_map->getCell(_posY, _posX) != Tile::BOMB)
	    _map->setCell(_posY, _posX, Tile::EMPTY);
	  _posY -= 1;
	  if (_map->getCell(this->_posY, this->_posX) >= (Tile)8) {
	    getPowerUp(_map->getCell(this->_posY, this->_posX));
	    sound->getSoundPU();
	    pos.x = _posX;
	    pos.y = _posY;
	    deleteElem(pos);
	  }
	  _map->setCell(_posY, _posX, Tile::CHARACTER);
	}
      mesh->setPosition(p);
    }
}

void		Player::moveRight()
{
  irr::core::vector3df	p = mesh->getPosition();
  Position		pos;
  int			tmp;

  if (oldy > 40)
    {
      while (oldy > 40)
	{
	  oldy--;
	  p.Z--;
	}
    }
  else if (oldy < 10)
    {
      while (oldy < 10)
	{
	  oldy++;
	  p.Z++;
	}
    }
  if (oldx <= 40 || move(Direction::RIGHT))
    {
      tmp = oldx;
      oldx +=  _speed;
      if ((oldx > 40) && !(move(Direction::RIGHT)))
	{
	  oldx = 40;
	  p.X = p.X + (40 - tmp);
	}
      else
	p.X += _speed;
      if (oldx >= 50)
	{
	  oldx = oldx - 50.0f;
	  if (_map->getCell(_posY, _posX) != Tile::BOMB)
	    _map->setCell(_posY, _posX, Tile::EMPTY);
	  _posX += 1;
	  if (_map->getCell(this->_posY, this->_posX) >= (Tile)8) {
	    getPowerUp(_map->getCell(this->_posY, this->_posX));
	    sound->getSoundPU();
	    pos.x = _posX;
	    pos.y = _posY;
	    deleteElem(pos);
	  }
	  _map->setCell(_posY, _posX, Tile::CHARACTER);
	}
      mesh->setPosition(p);
    }
}

void	Player::update()
{
  irr::core::vector3df	r = mesh->getRotation();
  Position		pos;

  if ((_dead == true)
      || (_map->getCell(_posY,_posX) == Tile::EXPLOSION)
      || (_map->getCell(_posY,_posX) == Tile::EXPLOSION_POWERUP))
    {
      if (_dead == false)
	{
	  _map->setCell(_posY, _posX, Tile::EMPTY);
	  mesh->setVisible(false);
	  for (std::vector<Character *>::iterator it = (*perso).begin(); it != (*perso).end();)
	    {
	      if (this == *it)
		it = (*perso).erase(it);
	      else
		it++;
	    }
	}
      _dead = true;
      return;
    }
  if (event->getMoving() == false)
    mesh->setMD2Animation(irr::scene::EMAT_STAND);
  if (event->IsKeyDown(keyMap->UP)) {
    event->setMoving(mesh);
    _direction = Direction::UP;
    moveUp();
    r.Y = -90.0f;
  } else if (event->IsKeyDown(keyMap->DOWN)) {
    event->setMoving(mesh);
    _direction = Direction::DOWN;
    moveDown();
	r.Y = 90.0f;
  } else if (event->IsKeyDown(keyMap->RIGHT)) {
    event->setMoving(mesh);
    _direction = Direction::RIGHT;
    moveRight();
    r.Y = 0.0f;
  } else if (event->IsKeyDown(keyMap->LEFT)) {
    event->setMoving(mesh);
    _direction = Direction::LEFT;
    moveLeft();
    r.Y = 180.0f;
  }
  if (event->IsKeyDown(keyMap->BOMB)) {
    if (_map->getCell(_posY, _posX) != Tile::BOMB)
      if (_nbBomb > 0)
	_map->putBomb(device, *this);
  }
  mesh->setRotation(r);
}
