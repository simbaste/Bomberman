//
// Bloc.hpp for bomberman in /Users/thouch_n/rendu/CPP/cpp_indie_studio/include
//
// Made by nicolas thouchkaieff
// Login   <thouch_n@epitech.net>
//
// Started on  Fri Apr 29 10:24:48 2016 nicolas thouchkaieff
// Last update Fri Apr 29 11:01:28 2016 nicolas thouchkaieff
//

#ifndef BLOC_HPP_
# define BLOC_HPP_

#include "IBloc.hpp"

class	Bloc : public IBloc {
protected:
  bool		breakable_;
  // formatexture	texture_;
  // pos ? (inutile)

  public:
  void		setBreakable(bool breakable);
  bool		isBreakable() const;

public:
  Bloc(bool breakable = false);
  Bloc(Bloc const& other);
  Bloc&		operator=(Bloc const& other);
  ~Bloc() {}
};

#endif /* !BLOC_HPP_ */
