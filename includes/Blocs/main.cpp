#include <iostream>
#include "Bloc.hpp"
#include "PowerUps.hpp"
#include <vector>

int	main() {
  Bloc		dur(false);
  Bloc		mou(true);
  std::vector<PowerUp*>	list;
  list.push_back(new PowerUpFire);
  list.push_back(new PowerUpFireDown);
  list.push_back(new PowerUpBombUp);
  list.push_back(new PowerUpBombDown);
  list.push_back(new PowerUpSpeed);
  list.push_back(new PowerUpHeart);

  std::cout << "Ceci est un bloc " << (dur.isBreakable() == false ? "Solide" : "Mou") << std::endl;
  std::cout << "Ceci est un bloc " << (mou.isBreakable() == false ? "Solide" : "Mou") << std::endl;

  for (std::vector<PowerUp*>::iterator it = list.begin() ; it != list.end(); ++it) {
    std::cout << "Ceci est un PowerUp " << (*it)->getName() << " qui a pour but de " << std::endl;
    (*it)->doBonus();
    std::cout << std::endl;
  }
}
