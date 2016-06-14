#include <unistd.h>
#include <iostream>
#include <vector>
#include "Map.hpp"
#include "Ia.hpp"
#include "Event.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Sound.hpp"
#include "Menu.hpp"
#include "Excep.hpp"

int	main(int argc __attribute__((unused)),
	     char **argv __attribute__((unused)))
{
  try
    {
      Map		*map = new Map;
      Game		game(map);
      Event		event(game.getDevice(), game.getEnv());
      game.setEvent(&event);
      game.soundMenu();
      Menu		menu(&event, game.getDriver(), game.getSmgr(), game.getEnv());

      menu.start(game);
    }
  catch (const Excep &error)
    {
      std::cerr << error.what() << std::endl;
      return (-1);
    }
  return (0);
}
