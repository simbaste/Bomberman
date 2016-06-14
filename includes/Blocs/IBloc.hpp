//
// IBloc.hpp for bomberman in /Users/thouch_n/rendu/CPP/cpp_indie_studio/include
//
// Made by nicolas thouchkaieff
// Login   <thouch_n@epitech.net>
//
// Started on  Fri Apr 29 10:18:22 2016 nicolas thouchkaieff
// Last update Fri Apr 29 11:49:07 2016 nicolas thouchkaieff
//

#ifndef IBLOC_HPP_
# define IBLOC_HPP_

#include <iostream>
#include <string>

class		IBloc {
public:
  virtual bool	isBreakable() const = 0;
  virtual	~IBloc() {}
};

#endif
