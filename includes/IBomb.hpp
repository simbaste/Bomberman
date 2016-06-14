#ifndef IBOMB_HPP_
# define IBOMB_HPP_

#include "Character.hpp"

class IBomb
x{
public:
  virtual ~IBomb() {}
  virtual Character	*getOwner() = 0;
  virtual unsigned int	getX() const = 0;
  virtual unsigned int	getY() const = 0;
  virtual void		setPosition(unsigned int posX, unsigned int posY) = 0;
};

#endif
