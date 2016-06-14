#ifndef MAP_HPP_
# define MAP_HPP_

#include <mutex>
#include "IMap.hpp"
#include "Bomb.hpp"
#include "Game.hpp"

class Bomb;

class Map : public IMap
{
public:
		Map();
		~Map();
  void		setCell(int x, int y, Tile newContent);
  Tile		getCell(int x, int y);
  mapVector	getMap() const;
  void		loadMapFromFile(const std::string& filename);
  void		initMap(int sizeX, int sizeY);
  void		getMapSize() const;
  void		printMap();
  void		createBlankMap(int sizeX, int sizeY, int nbPlayer);
  void		lock();
  void		unlock();

  void		putBomb(irr::IrrlichtDevice *device, Character &owner);
  void		checkBomb();
  Position	showBomb();

  int		explodeCell(unsigned int index, int y, int x);
  void		explodeBomb(unsigned int index);
  void		clearCell(unsigned int index, int y, int x);
  void		clearExplode(unsigned int index);
  int		findBomb(unsigned int x, unsigned int y);
  bool		pushBomb(Character &pusher, unsigned int destX, unsigned int destY);
  bool		canMove(int x, int y, int direction);

  void		putPlayer(int sizeX, int sizeY, int nbPlayer);

  bool		canIWallIt(int sizeX, int sizeY, int i, int j);
  bool		canIBlockIt(int sizeX, int sizeY, int i, int j);
  void		fillBlock(int sizeX, int sizeY);
  bool		isNear(int sizeX, int sizeY,
		       int i, int j, Tile tile, int incr);
  Tile		randomPowerup();
  bool		isPowerup(unsigned int y, unsigned int x);
  void		supMap();
private:
  Tile			getTileFromInt(char tile);
  std::vector<Tile>     getFileLine(std::string line);

private:
  mapVector		_map;
  pthread_mutex_t	_mtx;
public:
  std::vector<Bomb * >	_bomb;
};

#endif
