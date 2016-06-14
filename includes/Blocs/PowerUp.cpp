//
// PowerUp.cpp for bomberman in /Users/thouch_n/rendu/CPP/cpp_indie_studio/include/Blocs
//
// Made by nicolas thouchkaieff
// Login   <thouch_n@epitech.net>
//
// Started on  Fri Apr 29 11:45:11 2016 nicolas thouchkaieff
// Last update Fri Apr 29 13:13:03 2016 nicolas thouchkaieff
//

#include "PowerUp.hpp"

void			PowerUp::setName(std::string const& name) {
  name_ = name;
}

std::string const&	PowerUp::getName() const {
  return name_;
}

PowerUp::PowerUp(std::string const& name, bool breakable)
  : Bloc(breakable), name_(name) {}
