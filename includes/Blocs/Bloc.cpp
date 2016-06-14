//
// Bloc.cpp for bomberman in /Users/thouch_n/rendu/CPP/cpp_indie_studio/include/Blocs
//
// Made by nicolas thouchkaieff
// Login   <thouch_n@epitech.net>
//
// Started on  Fri Apr 29 10:50:11 2016 nicolas thouchkaieff
// Last update Fri Apr 29 11:27:41 2016 nicolas thouchkaieff
//

#include "Bloc.hpp"

bool  Bloc::isBreakable() const {
  return breakable_;
}

void  Bloc::setBreakable(bool breakable) {
  breakable_ = breakable;
}

Bloc::Bloc(bool breakable) : breakable_(breakable) {}

Bloc::Bloc(Bloc const& other) : breakable_(other.breakable_) {}

Bloc&  Bloc::operator=(Bloc const& other) {
  if (this != &other)
    breakable_ = other.breakable_;
  return *this;
}
