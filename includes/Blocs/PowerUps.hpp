//
// PowerUps.hpp for bomberman in /Users/thouch_n/rendu/CPP/cpp_indie_studio/include/Blocs
//
// Made by nicolas thouchkaieff
// Login   <thouch_n@epitech.net>
//
// Started on  Fri Apr 29 12:15:47 2016 nicolas thouchkaieff
// Last update Fri Apr 29 12:44:58 2016 nicolas thouchkaieff
//

#include "PowerUp.hpp"

/*
** PowerUp : Fire
** Bonus : Increase the bomb blast radius.
*/

class	PowerUpFire : public PowerUp {
public:
  void	doBonus() const {
    std::cout << " - Increase the bomb blast radius." << std::endl;
  };

public:
  PowerUpFire() : PowerUp("Fire", false) {}
  ~PowerUpFire() {}
};

/*
** PowerUp : FireDown
** Bonus : Decrease the bomb blast radius.
*/

class	PowerUpFireDown : public PowerUp {
public:
  void	doBonus() const {
    std::cout << " - Decrease the bomb blast radius." << std::endl;
  };

public:
  PowerUpFireDown() : PowerUp("FireDown", false) {}
  ~PowerUpFireDown() {}
};

/*
** PowerUp : BombUp
** Bonus : Increase the number of bombs that can be set at one time.
*/

class	PowerUpBombUp : public PowerUp {
public:
  void	doBonus() const {
    std::cout << " - Increase the number of bombs that can be set at one time." << std::endl;
  };

public:
  PowerUpBombUp() : PowerUp("BombUp", false) {}
  ~PowerUpBombUp() {}
};

/*
** PowerUp : BombDown
** Bonus : Decrease the number of bombs that can be set at one time.
*/

class	PowerUpBombDown : public PowerUp {
public:
  void	doBonus() const {
    std::cout << " - Decrease the number of bombs that can be set at one time." << std::endl;
  };

public:
  PowerUpBombDown() : PowerUp("BombDown", false) {}
  ~PowerUpBombDown() {}
};

/*
** PowerUp : Speed
** Bonus : Increase the movement speed of the player.
*/

class	PowerUpSpeed : public PowerUp {
public:
  void	doBonus() const {
    std::cout << " - Increase the movement speed of the player." << std::endl;
  };

public:
  PowerUpSpeed() : PowerUp("Speed", false) {}
  ~PowerUpSpeed() {}
};

/*
** PowerUp : Heart
** Bonus : Add one HP to the player's total.
*/

class	PowerUpHeart : public PowerUp {
public:
  void	doBonus() const {
    std::cout << " - Add one HP to the player's total." << std::endl;
  };

public:
  PowerUpHeart() : PowerUp("Heart", false) {}
  ~PowerUpHeart() {}
};
