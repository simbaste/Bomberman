#ifndef IAP_HPP_
# define IAP_HPP_

#include "Character.hpp"
#include "Ia.hpp"

class Iap : public Ia
{
public:
  Iap(unsigned int x = 1, unsigned int y = 1,
	       Direction d = Direction::RIGHT, Map *map = NULL,
	       Elem *elem = NULL, std::vector<Character*> *_perso = NULL);
  ~Iap();
  void	update();
};

# endif /* IAP_HPP_ */
