#ifndef ICHARACTER_HPP_
# define ICHARACTER_HPP_

# include <string>
# include "Tools.hpp"

class ICharacter
{
public:
  // Position getters
  virtual ~ICharacter(){}
  virtual int		getX() const = 0;
  virtual int		getY() const = 0;

  // Direction getter
  virtual Direction	getDirection() const = 0;

  // Direction setter
  virtual void		setDirection(Direction) = 0;

  //virtual std::string	getSprite() const = 0;
  //move
};

#endif /* !ICHARACTER_HPP */
