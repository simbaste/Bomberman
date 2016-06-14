#include <iostream>
#include "Iap.hpp"

Iap::Iap(unsigned int x, unsigned int y, Direction d, Map *map, Elem *elem, std::vector<Character*> *_perso)
  : Ia(x, y, d, map, elem, _perso)
{
  Position Mpos(x, y);
  oldX = 50;
  oldY = 50;
  isMoving = true;
  _check = 0;
  decision = true;
  _dead = false;
  _speed = 1;
  sizeY = (map->getMap().size() * 50) / 2;
  sizeX = (map->getMap()[0].size() * 50) / 2;
  _isPlayer = false;
  _pos.push_back(Mpos);
}

Iap::~Iap() {}

void	Iap::update()
{
  irr::core::vector3df	p = mesh->getPosition();
  Direction		d;

  if ((_dead == true)
      || (_map->getCell(mC(p.Z, sizeY), mC(p.X, sizeX)) == Tile::EXPLOSION)
      || (_map->getCell(mC(p.Z, sizeY), mC(p.X, sizeX)) == Tile::EXPLOSION_POWERUP))
    {
      if (_dead == false)
	{
	  mesh->setVisible(false);
	  for (std::vector<Character *>::iterator it = (*perso).begin(); it != (*perso).end();)
	    {
	      if (this == *it) {
		it = (*perso).erase(it);
	      } else
		it++;
	    }
	}
      std::cout << "IA DEAD" << std::endl;
      _dead = true;
      return;
    }
  if (decision) {
    decision = false;
    if (!layingBomber()) {
      if (rand() % 5 == 3)
	dropBomber();
    }
    layingBomberPU();
    if (_pos.size() > 50) {
      for (unsigned i = 0; i < 15; i++)
	_pos.erase(_pos.begin());
    }
    if (rand() % 3 == 0)
      deviation();
    if ((d = lookPowerUp()) != Direction::NOP) {
      _direction = d;
    } else if ((d = lookCharacter()) != Direction::NOP) {
      _direction = d;
      layingBomber1();
    }
    if ((d = seekBomber()) != Direction::NOP) {
      _direction = d;
    }
  }
  if (isDead()) {
    if (isMoving == false) {
      isMoving = true;
      mesh->setMD2Animation(irr::scene::EMAT_RUN);
    }
    if (!takePowerUp()) {
      myDirection();
      moveIa();
    } else
      movePuwerUp();
  } else {
    isMoving = false;
    mesh->setMD2Animation(irr::scene::EMAT_STAND);
  }
}
