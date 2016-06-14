#ifndef IAS_HPP_
# define IAS_HPP_

#include "Character.hpp"
#include "Ia.hpp"

class Ias : public Ia
{
public:
  Ias(unsigned int x = 1, unsigned int y = 1,
	       Direction d = Direction::LEFT, Map *map = NULL,
	       Elem *elem = NULL, std::vector<Character*> *_perso = NULL);
  ~Ias();
  void	update();
};

# endif /* IAS_HPP_ */
