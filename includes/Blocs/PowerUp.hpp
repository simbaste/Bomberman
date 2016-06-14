//
// PowerUp.hpp for bomberman in /Users/thouch_n/rendu/CPP/cpp_indie_studio/include/Blocs
//
// Made by nicolas thouchkaieff
// Login   <thouch_n@epitech.net>
//
// Started on  Fri Apr 29 11:17:23 2016 nicolas thouchkaieff
// Last update Fri Apr 29 12:16:19 2016 nicolas thouchkaieff
//

#ifndef POWERUP_HPP_
# define POWERUP_HPP_

#include "Bloc.hpp"

class	PowerUp : public Bloc {
protected:
  std::string	name_;
  // son id_ ?

  /* Garde l'attribut breakable_,
     si jamais le powerup peut etre detruit par une bombe
  (Et peut etre texture_ ) */

public:
  void			setName(std::string const& name);
  std::string const&	getName() const;

public:
  virtual void	doBonus() const = 0;

public:
  PowerUp(std::string const& name, bool breakable = false);
  virtual ~PowerUp() {}
};

#endif /* !POWERUP_HPP_ */
