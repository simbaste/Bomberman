#ifndef EVENT_HPP_
# define EVENT_HPP_

#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <irr/irrlicht.h>
#include <irr/IEventReceiver.h>
#include <stdint.h>
#include <vector>
#include "Tools.hpp"

class Event : public irr::IEventReceiver
{
private:
  bool				KeyIsDown[irr::KEY_KEY_CODES_COUNT];
  irr::IrrlichtDevice		*device;
  irr::gui::IGUIEnvironment	*env;
  Click				value;
  bool				is_moving;
  irr::EKEY_CODE		lastKey;

public:
  Event(irr::IrrlichtDevice *Device, irr::gui::IGUIEnvironment *e);
  ~Event() {};

  virtual bool			OnEvent(const irr::SEvent& event);
  virtual bool			IsKeyDown(irr::EKEY_CODE keyCode) const;
  Click				getChoice();
  bool				getMoving();
  void				setMoving(irr::scene::IAnimatedMeshSceneNode *mesh);
  irr::EKEY_CODE		getLastKey();
  // Methode pour Changer les bind de touche
};

#endif /* !EVENT_HPP_ */
