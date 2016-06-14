//
// ISave.hpp for bomberman in /Users/thouch_n/rendu/CPP/cpp_indie_studio/save
//
// Made by nicolas thouchkaieff
// Login   <thouch_n@epitech.net>
//
// Started on  Tue May 17 10:14:02 2016 nicolas thouchkaieff
// Last update Thu Jun  2 10:41:16 2016 nicolas thouchkaieff
//

#include "Bomb.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Ia.hpp"

class ISave {
public:
  virtual int	loadGame(std::string const& filename, std::vector<Bomb*>& bombs,
			 std::vector<Character*>& characters, Map& map) = 0;
  virtual int	saveGame(std::string const& filename, std::vector<Bomb*> const& bombs,
			 std::vector<Character*> const& characters, Map const& map) = 0;

  virtual ~ISave() {}
};
