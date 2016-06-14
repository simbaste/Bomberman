#ifndef IMAP_HPP_
# define IMAP_HPP_

#include <irr/irrlicht.h>
#include <vector>
#include <string>
#include "Tools.hpp"
class Character;
class IMap
{
public:
  virtual		~IMap(){}

  //map setters
  virtual void		setCell(int x, int y, Tile newContent) = 0;

  //map getters
  virtual Tile		getCell(int x, int y) = 0;
  virtual mapVector	getMap() const = 0;
  virtual void		getMapSize() const = 0;

  //map loaders
  virtual void		loadMapFromFile(const std::string& filename) = 0;
  virtual void		initMap(int sizeX, int sizeY) = 0;

  virtual void		putBomb(irrDevice *device, Character &owner) = 0;
};

#endif
