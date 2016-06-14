#include <iostream>
#include <fstream>
#include "Character.hpp"
#include "Map.hpp"
#include "Ia.hpp"

Map::Map() {}

Map::~Map() {}

void		Map::lock() { pthread_mutex_lock(&_mtx); }
void		Map::unlock() { pthread_mutex_unlock(&_mtx); }
void		Map::setCell(int x, int y, Tile newContent) { _map[x][y] = newContent; }
Tile		Map::getCell(int x, int y) { return (_map[x][y]); }

mapVector	Map::getMap() const { return (_map); }

void		Map::loadMapFromFile(const std::string& filename)
{
  std::ifstream				file(filename, std::ios::in);
  std::vector<Tile>			mapLine;
  std::string				line;

  if (!_map.empty())
    {
      while (!_map.empty())
	_map.pop_back();
    }
  while (std::getline(file, line)) {
    mapLine = getFileLine(line);
    _map.push_back(mapLine);
  }
  this->printMap();
}

Tile		Map::getTileFromInt(char tile)
{
  switch (tile) {
  case '0':
    return (Tile::EMPTY);
  case '1':
    return (Tile::BLOCK);
  case '2':
    return (Tile::WALL);
  case '3':
    return (Tile::CHARACTER);
  case '4':
    return (Tile::INTEL);
    //case '4':
    //return (Tile::POWERUP);
  default:
    return (Tile::EMPTY);
    }
}

std::vector<Tile>	Map::getFileLine(std::string line)
{
  std::vector<Tile>	mapLine;

  for (unsigned int i = 0; i < line.size(); ++i)
    mapLine.push_back(getTileFromInt(line[i]));
  return (mapLine);
}

void			Map::printMap()
{
  for (unsigned int i = 0; i < _map.size(); i++)
    {
      for (unsigned int j = 0; j < _map[i].size(); j++)
	{
	  switch (static_cast<int>(_map[i][j]))
	    {
	    case static_cast<int>(Tile::EMPTY): printf("."); break;
	    case static_cast<int>(Tile::BLOCK): printf("x"); break;
	    case static_cast<int>(Tile::WALL): printf("\033[1;32m0\033[0m"); break;
	    case static_cast<int>(Tile::CHARACTER): printf("\033[1;31mC\033[0m"); break;
	    case static_cast<int>(Tile::INTEL): printf("\033[1;43mA\033[0m"); break;
	    case static_cast<int>(Tile::BOMB): printf("\033[1;34mB\033[0m"); break;
	    case static_cast<int>(Tile::EXPLOSION): printf("E"); break;
	    case static_cast<int>(Tile::EXPLOSION_POWERUP): printf("L"); break;
	    case static_cast<int>(Tile::BOMBUP): printf("P"); break;
	    case static_cast<int>(Tile::RANGEUP): printf("P"); break;
	    }
	}
      std::cout << std::endl;
    }
}

void		Map::supMap()
{
  for (unsigned int i = 0; i < _map.size(); i++) {
    for (unsigned int j = 0; j < _map[i].size(); j++) {
      _map[i].pop_back();
    }
  }
  for (std::vector<std::vector<Tile>>::iterator it = _map.begin(); it != _map.end(); ++it) {
    _map.erase(it);
  }
}

void		Map::initMap(int sizeX, int sizeY)
{
  this->createBlankMap(sizeX, sizeY, -1);
}

int		v(int maxSize, int pos)
{
  if (pos < 0)
    return (0);
  if (pos >= maxSize)
    return maxSize - 1;
  return pos;
}

void		Map::putPlayer(int sizeX, int sizeY, int nbPlayer)
{
  int		posX;
  int		posY;
  int		save;

  save = 4;
  while (save != 0)
    {
      posX = rand() % sizeX - 1;
      posY = rand() % sizeY - 1;
      if ((_map[v(sizeX, posX)][v(sizeY, posY)] != Tile::CHARACTER)
	   && (_map[v(sizeX, posX)][v(sizeY, posY)] != Tile::WALL)
	  && (_map[v(sizeX, posX)][v(sizeY, posY)] != Tile::INTEL))
	{
	  if (nbPlayer < save)
	    _map[v(sizeX, posX)][v(sizeY, posY)] = Tile::INTEL;
	  else
	    _map[v(sizeX, posX)][v(sizeY, posY)] = Tile::CHARACTER;
	  save--;
	}
    }
}

bool		Map::isNear(int sizeX, int sizeY,
			    int i, int j, Tile tile, int incr)
{
  if ((_map[v(sizeX, i - incr)][v(sizeY, j)] != tile)
      && (_map[v(sizeX, i + incr)][v(sizeY, j)] != tile)
      && (_map[v(sizeX, i)][v(sizeY, j + incr)] != tile)
      && (_map[v(sizeX, i)][v(sizeY, j - incr)] != tile))
    {
      return true;
    }
  return (false);
}

bool		Map::canIWallIt(int sizeX, int sizeY, int i, int j)
{
  if (((_map[v(sizeX, i)][v(sizeY, j)] != Tile::CHARACTER)
       && (_map[v(sizeX, i)][v(sizeY, j)] != Tile::WALL)
       && (_map[v(sizeX, i)][v(sizeY, j)] != Tile::INTEL))
      && (isNear(sizeX, sizeY, i, j, Tile::WALL, 1))
      && (isNear(sizeX, sizeY, i, j, Tile::CHARACTER, 1))
      && (isNear(sizeX, sizeY, i, j, Tile::INTEL, 1))
      && (isNear(sizeX, sizeY, i, j, Tile::CHARACTER, 2))
      && (isNear(sizeX, sizeY, i, j, Tile::INTEL, 2)))
    return (true);
  return false;
}

bool		Map::canIBlockIt(int sizeX, int sizeY, int i, int j)
{
  if (((_map[v(sizeX, i)][v(sizeY, j)] != Tile::CHARACTER)
       && (_map[v(sizeX, i)][v(sizeY, j)] != Tile::WALL)
       && (_map[v(sizeX, i)][v(sizeY, j)] != Tile::INTEL))
      && (isNear(sizeX, sizeY, i, j, Tile::CHARACTER, 1))
      && (isNear(sizeX, sizeY, i, j, Tile::INTEL, 1))
      && (isNear(sizeX, sizeY, i, j, Tile::CHARACTER, 2))
      && (isNear(sizeX, sizeY, i, j, Tile::INTEL, 2)))
    return (true);
  return false;
}

void		Map::fillBlock(int sizeX, int sizeY)
{
  for (int i = 0; i < sizeX; i++)
    {
      for (int j = 0; j < sizeY; j++)
	{
	  if ((rand() % 5) == 3)
	    {
	      if (canIWallIt(sizeX, sizeY, i, j))
		_map[i][j] = Tile::WALL;
	      else if (canIBlockIt(sizeX, sizeY, i, j))
		_map[i][j] = Tile::BLOCK;
	    }
	  else if (((rand() % 5) == 2) || ((rand() % 5) == 3))
	    {
	      if ((_map[v(sizeX, i)][v(sizeY, j)] != Tile::CHARACTER)
		  && (_map[v(sizeX, i)][v(sizeY, j)] != Tile::WALL)
		  && (_map[v(sizeX, i)][v(sizeY, j)] != Tile::INTEL))
	      _map[i][j] = Tile::EMPTY;
	    }
	  else
	    {
	      if (canIBlockIt(sizeX, sizeY, i, j))
		_map[i][j] = Tile::BLOCK;
	    }
	}
    }
}

void		Map::createBlankMap(int sizeX, int sizeY, int nbPlayer)
{
  std::vector<Tile>	mapLine;

  srand(time(NULL));
  if (!_map.empty())
    {
      while (!_map.empty())
	_map.pop_back();
    }
  for (int i = 0; i < sizeX; i++)
    {
      mapLine.clear();
      for (int j = 0; j < sizeY; j++)
	{
	  if ((i == 0) || (i == sizeX -1)
	      || (j == 0) || (j == sizeY -1))
	    mapLine.push_back(Tile::WALL);
	  else
	    mapLine.push_back(Tile::EMPTY);
	}
      _map.push_back(mapLine);
    }
  if (nbPlayer >= 0)
    putPlayer(sizeX, sizeY, nbPlayer);
  fillBlock(sizeX, sizeY);
  this->printMap();
}

void		Map::getMapSize() const {}

void		Map::putBomb(irr::IrrlichtDevice *, Character &owner)
{
  Bomb		*newBomb;

  owner.setNbBomb(owner.getNbBomb() - 1);
  newBomb = new Bomb(owner, ((_map[0].size() * 50) / 2),
		     ((_map.size() * 50) / 2));
  _bomb.push_back(newBomb);
  setCell(newBomb->getY(), newBomb->getX(), Tile::BOMB);
}

int		Map::findBomb(unsigned int x, unsigned int y)
{
  unsigned int	i;

  i = 0;
  while (i < _bomb.size())
    {
      if ((_bomb[i]->getX() == x)
	  && (_bomb[i]->getY() == y))
	return (i);
      ++i;
    }
  return (-1);
}

int		Map::explodeCell(unsigned int index, int y, int x)
{
  int		tmp = 0;

  if (_map[y][x] == Tile::WALL)
    return (1);
  _bomb[index]->clearCell(x, y);
  _bomb[index]->addFire(x, y);
  if (_map[y][x] == Tile::BOMB)
    {
      if ((tmp = findBomb(x, y)) == -1)
	std::cout << "ERROR" << std::endl;
      _bomb[tmp]->getOwner()->setNbBomb((_bomb[tmp]->getOwner())->getNbBomb() + 1);
      _bomb[tmp]->startExplosion();
      explodeBomb(tmp);
      return (0);
    }
  if (_map[y][x] == Tile::BLOCK)
    {
      _map[y][x] = Tile::EXPLOSION_POWERUP;
      return (1);
    }
  _map[y][x] = Tile::EXPLOSION;
  return (0);
}

void		Map::explodeBomb(unsigned int index)
{
  int		x = _bomb[index]->getX();
  int		y = _bomb[index]->getY();
  int		range = _bomb[index]->getRangeBomb();
  int		back = 0;

  _bomb[index]->addFire(x, y);
  _map[y][x] = Tile::EXPLOSION;
  _bomb[index]->deleteBomb();
  for (int i = 1; i < range + 1; i++)
    if ((back != 1))
      back = explodeCell(index, y, x + i);
  back = 0;
  for (int i = 1; i < range + 1; i++)
    if ((back != 1))
      back = explodeCell(index, y, x - i);
  back = 0;
  for (int i = 1; i < range + 1; i++)
    if ((back != 1))
      back = explodeCell(index, y + i, x);
  back = 0;
  for (int i = 1; i < range + 1; i++)
    if ((back != 1))
      back = explodeCell(index, y - i, x);
}

bool		Map::isPowerup(unsigned int y, unsigned int x)
{
  switch (getCell(y, x))
    {
    case Tile::INVINCIBLE :
      return (true);
    case Tile::KICKBOMB	  :
      return (true);
    case Tile::SPEEDUP    :
      return (true);
    case Tile::SPEEDDOWN  :
      return (true);
    case Tile::GHOST	  :
      return (true);
    case Tile::RANGEDOWN  :
      return (true);
    case Tile::RANGEUP	  :
      return (true);
    case Tile::BOMBUP     :
      return (true);
    case Tile::LINEBOMB   :
      return (true);
    case Tile::BOMBDOWN   :
      return (true);
    default:
      return (false);
    }
  return (false);
}

Tile		Map::randomPowerup()
{
  int		i;

  i = rand() % 7;
  switch (i)
    {
    case 0:
      return Tile::SPEEDUP;
    case 1:
      return Tile::BOMBUP;
    case 2:
      return Tile::RANGEUP;
    case 3:
      return Tile::RANGEDOWN;
    case 4:
      return Tile::BOMBDOWN;
    case 5:
      return Tile::SPEEDDOWN;
    case 6:
      return Tile::KICKBOMB;
    default:
      return Tile::RANGEUP;
    }
}

void		Map::clearCell(unsigned int index, int y, int x)
{
  if (_map[y][x] == Tile::EXPLOSION)
    {
      _bomb[index]->clearCell(x, y);
      _map[y][x] = Tile::EMPTY;
    }
  else if (_map[y][x] == Tile::EXPLOSION_POWERUP)
    {
      if ((rand() % 3) == 1)
	{
	  _map[y][x] = randomPowerup();
	  _bomb[index]->clearCell(x, y);
	  _bomb[index]->addPowerup(x, y, _map[y][x]);
	}
      else
	{
	  _map[y][x] = Tile::EMPTY;
	  _bomb[index]->clearCell(x, y);
	}
    }
  else
    {
      _map[y][x] = Tile::EMPTY;
      _bomb[index]->clearCell(x, y);
    }
}

void		Map::clearExplode(unsigned int index)
{
  int		x = _bomb[index]->getX();
  int		y = _bomb[index]->getY();
  int		range = _bomb[index]->getRangeBomb();

  clearCell(index, y, x);
  for (int i = 1; i < range + 1; i++)
    {
      if ((_map[y][x + i] == Tile::EXPLOSION)
	  || (_map[y][x + i] == Tile::EXPLOSION_POWERUP))
	clearCell(index, y, x + i);
      else
	break;
    }
  for (int i = 1; i < range + 1; i++)
    {
      if ((_map[y][x - i] == Tile::EXPLOSION)
	  || (_map[y][x - i] == Tile::EXPLOSION_POWERUP))
	clearCell(index, y, x - i);
      else
	break;
    }
  for (int i = 1; i < range + 1; i++)
    {
      if ((_map[y + i][x] == Tile::EXPLOSION)
	  || (_map[y + i][x] == Tile::EXPLOSION_POWERUP))
	clearCell(index, y + i, x);
      else
	break;
    }
  for (int i = 1; i < range + 1; i++)
    {
      if ((_map[y - i][x] == Tile::EXPLOSION)
	  || (_map[y - i][x] == Tile::EXPLOSION_POWERUP))
	clearCell(index, y - i, x);
      else
	break;
    }
}

void	Map::checkBomb()
{
  for (unsigned int i = 0; i < _bomb.size(); i++)
    {
      if (_bomb[i]->isExploded() == true)
	{
	  if (_bomb[i]->isFlamming() == false)
	    {
	      _bomb[i]->getOwner()->setNbBomb((_bomb[i]->getOwner())->getNbBomb() + 1);
	      _bomb[i]->startExplosion();
	      explodeBomb(i);
	    }
	  else
	    {
	      if (_bomb[i]->isEndFlamming() == true)
		{
		  clearExplode(i);
		  delete (_bomb[i]);
		  _bomb.erase(_bomb.begin() + i);
		  i = 0;
		}
	    }
	}
      else if (_bomb[i]->isMoving())
	{
	  if ((canMove(_bomb[i]->getX(),_bomb[i]->getY(), _bomb[i]->getDirection())) == true)
	    _bomb[i]->startMoving(_bomb[i]->getDirection());
	}
    }
}

//renvoi true si il peu aller dans la case
// 1 UP
// 2 DOWN
// 3 RIGHT
// 4 LEFT

bool	Map::canMove(int x, int y, int direction)
{
  switch (direction)
    {
    case 1:
      if (_map[y + 1][x] == Tile::EMPTY)
	{
	  _map[y + 1][x] = Tile::BOMB;
	  _map[y][x] = Tile::EMPTY;
	  return (true);
	}
      return false;
    case 2:
      if (_map[y - 1][x] == Tile::EMPTY)
	{
	  _map[y - 1][x] = Tile::BOMB;
	  _map[y][x] = Tile::EMPTY;
	  return (true);
	}
      return false;
    case 3:
      if (_map[y][x + 1] == Tile::EMPTY)
	{
	  _map[y][x + 1] = Tile::BOMB;
	  _map[y][x] = Tile::EMPTY;
	  return (true);
	}
      return false;
    case 4:
      if (_map[y][x - 1] == Tile::EMPTY)
	{
	  _map[y][x - 1] = Tile::BOMB;
	  _map[y][x] = Tile::EMPTY;
	  return (true);
	}
	  return false;
    default:
      return false;
    }
}

bool	Map::pushBomb(Character &pusher, unsigned int destX, unsigned int destY)
{
  unsigned int pushX = pusher.getX();
  unsigned int pushY = pusher.getY();
  unsigned int bombX;
  unsigned int bombY;
  int		index;

  if (!pusher.getKickBomb())
    return (false);
  printMap();
  if ((index = findBomb(destX, destY)) == -1)
    return (false);
  bombX = _bomb[index]->getX();
  bombY = _bomb[index]->getY();
  if (bombX == pushX)
    {
      if ((bombY > pushY) && (canMove(bombX, bombY, 1)))
	return (_bomb[index]->startMoving(1)); // UP
      else if ((bombY < pushY) && (canMove(bombX, bombY, 2)))
	return (_bomb[index]->startMoving(2)); // DOWN
      else
	return (false); //ERROR;
    }
  else if (bombY == pushY)
    {
      if ((bombX > pushX) && (canMove(bombX, bombY, 3)))
	return (_bomb[index]->startMoving(3)); // RIGHT
      else if ((bombX < pushX) && (canMove(bombX, bombY, 4)))
	return (_bomb[index]->startMoving(4)); // LEFT
      else
	return (false); //ERROR;
    }
  return (false);
}
