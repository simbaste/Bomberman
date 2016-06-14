#ifndef THREADPOOL_HPP_
# define THREADPOOL_HPP_

#include <vector>
#include <queue>
#include "Game.hpp"
#include "Character.hpp"

class ThreadPool
{
public:
  ThreadPool(unsigned int nbThreads);
  ~ThreadPool();
  void		push(Character *);
  Character	*pop();
  void		init();

private:
  unsigned int			_nbThreads;
  pthread_mutex_t		_mutex;
  pthread_cond_t		_cond;
  std::queue<Character*>	_tasks;
  std::vector<pthread_t>	_threads;
  //  pthread_mutex_t		_mtx;
};

void	*start(void*);

#endif /* !THREADPOOL_HPP_ */
