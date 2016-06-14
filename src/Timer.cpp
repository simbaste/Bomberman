/*
** Timer.cpp for Timer in /home/clementine/rendu/cpp_indie_studio/tests/clem
** 
** Made by Clementine
** Login   <clementine@clementine>
** 
** Started on  Mon May  9 15:16:11 2016 Clementine
** Last update Mon May  9 15:31:34 2016 Clementine
*/

#include "Timer.hpp"

void Timer::start()
{
  _time = clock();
}

unsigned long Timer::elapsedTime()
{
  unsigned long time;

  time = (unsigned long)(clock() - _time);
  return time / CLOCKS_PER_SEC;
}

bool Timer::isTimeout(unsigned long second)
{
  return second >= elapsedTime();
}
