/*
** Timer.hpp for Timer in /home/clementine/rendu/cpp_indie_studio/tests/clem
** 
** Made by Clementine
** Login   <clementine@clementine>
** 
** Started on  Mon May  9 11:30:44 2016 Clementine
** Last update Mon May  9 15:46:19 2016 Clementine
*/

#ifndef TIMER_HPP_
# define TIMER_HPP_

#include <ctime>

class Timer
{
public:
  Timer() {}
  ~Timer() {}
  
  void		start();
  bool		isTimeout(unsigned long second);
  unsigned long	elapsedTime();
  
private:
  clock_t _time;
};

#endif /* !TIMER_HPP_ */
