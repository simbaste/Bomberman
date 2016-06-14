#include "ThreadPool.hpp"
#include <iostream>

pthread_mutex_t		_mtx;

ThreadPool::ThreadPool(unsigned int nbThreads) : _nbThreads(nbThreads)
{
  pthread_mutex_init(&_mutex, NULL);
  pthread_mutex_init(&_mtx, NULL);
  std::cout << "Cond Init : " << pthread_cond_init(&_cond, NULL) << std::endl;
}

ThreadPool::~ThreadPool()
{
}

void		ThreadPool::push(Character *perso)
{
  pthread_mutex_lock(&_mutex);
  _tasks.push(perso);
  pthread_cond_broadcast(&_cond);
  pthread_mutex_unlock(&_mutex);
}

Character	*ThreadPool::pop()
{
  Character	*perso;

  pthread_mutex_lock(&_mutex);
  while (_tasks.empty())
    pthread_cond_wait(&_cond, &_mutex);
  perso = _tasks.front();
  _tasks.pop();
  pthread_mutex_unlock(&_mutex);
  return perso;
}

void		ThreadPool::init()
{
  for (unsigned int i = 0; i < _nbThreads; ++i) {
    pthread_t	thread;
    pthread_create(&thread, NULL, start, this);
    pthread_detach(thread);
    _threads.push_back(thread);
  }
}

void		*start(void *data)
{
  ThreadPool	*threadPool = reinterpret_cast<ThreadPool*>(data);
  bool		dead = false;

  while (true)
    {
      pthread_mutex_lock(&_mtx);
      Character	*perso = threadPool->pop();
      perso->update();
      dead = perso->dead();
      pthread_mutex_unlock(&_mtx);
      if (dead == true)
	{
	  pthread_exit(NULL);
	}
    }
  return (void*)0;
}
