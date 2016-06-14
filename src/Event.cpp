#include <iostream>
#include <irr/irrlicht.h>
#include "Event.hpp"

Event::Event(irr::IrrlichtDevice *Device, irr::gui::IGUIEnvironment *e)
{
  device = Device;
  env = e;
  value = Click::NOP;
  for (uint32_t i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
    KeyIsDown[i] = false;
  is_moving = false;
}

bool Event::OnEvent(const irr::SEvent& event)
{
  if (env->hasFocus(env->getRootGUIElement()->getElementFromId(GUI_ID_SET_NAME_ONE,true)))
    return false;
  if (env->hasFocus(env->getRootGUIElement()->getElementFromId(GUI_ID_SET_NAME_TWO,true)))
    return false;
  if (env->hasFocus(env->getRootGUIElement()->getElementFromId(GUI_ID_SET_NAME_THREE,true)))
    return false;
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
      if (event.KeyInput.PressedDown == false)
	is_moving = false;
      else
	lastKey = event.KeyInput.Key;
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
      return true;
    }
  else if (event.EventType == irr::EET_GUI_EVENT)
    {
      irr::s32	id = event.GUIEvent.Caller->getID();
      if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
	{
	  switch (id) {
	  case GUI_ID_QUIT:
	    value = Click::QUIT;
	    return true;
	  case GUI_ID_CONTINUE:
	    value = Click::CONTINUE;
	    return true;
	  case GUI_ID_BACK:
	    value = Click::BACK;
	    return true;
	  case GUI_ID_PAUSE_OPTION:
	    value = Click::OPTIONS;
	    return true;
	  case GUI_ID_LOAD:
	    value = Click::LOAD;
	    return true;
	  case GUI_ID_IA_PLAYERS:
	    value = Click::IA;
	    return (true);
	  case GUI_ID_CANCEL_N:
	    value = Click::CANCEL;
	    return true;
	  case GUI_ID_CANCEL:
	    value = Click::CANCEL;
	    return true;
	  case GUI_ID_CANCEL_P:
	    value = Click::CANCEL;
	    return true;
	  case GUI_ID_UP1:
	    value = Click::UP1;
	    return true;
	  case GUI_ID_DOWN1:
	    value = Click::DOWN1;
	    return true;
	  case GUI_ID_LEFT1:
	    value = Click::LEFT1;
	    return true;
	  case GUI_ID_RIGHT1:
	    value = Click::RIGHT1;
	    return true;
	  case GUI_ID_BOMB1:
	    value = Click::BOMB1;
	    return true;
	  case GUI_ID_UP2:
	    value = Click::UP2;
	    return true;
	  case GUI_ID_DOWN2:
	    value = Click::DOWN2;
	    return true;
	  case GUI_ID_LEFT2:
	    value = Click::LEFT2;
	    return true;
	  case GUI_ID_RIGHT2:
	    value = Click::RIGHT2;
	    return true;
	  case GUI_ID_BOMB2:
	    value = Click::BOMB2;
	    return true;
	  case GUI_ID_UP3:
	    value = Click::UP3;
	    return true;
	  case GUI_ID_DOWN3:
	    value = Click::DOWN3;
	    return true;
	  case GUI_ID_LEFT3:
	    value = Click::LEFT3;
	    return true;
	  case GUI_ID_RIGHT3:
	    value = Click::RIGHT3;
	    return true;
	  case GUI_ID_BOMB3:
	    value = Click::BOMB3;
	    return true;
	  case GUI_ID_OPTION:
	    value = Click::OPTION;
	    return true;
	  case GUI_ID_PLAY:
	    value = Click::PLAY;
	    return true;
	  case GUI_ID_PLAY_N:
	    value = Click::PLAY;
	    return true;
	  case GUI_ID_ONE_PLAYER:
	    value = Click::ONE;
	    return true;
	  case GUI_ID_TWO_PLAYERS:
	    value = Click::TWO;
	    return true;
	  case GUI_ID_THREE_PLAYERS:
	    value = Click::THREE;
	    return true;
	  default:
	    break ;
	  }
	}
    }
  return false;
}

void	Event::setMoving(irr::scene::IAnimatedMeshSceneNode *mesh)
{
  if (is_moving == false)
    {
      is_moving = true;
      mesh->setMD2Animation(irr::scene::EMAT_RUN);
    }
}

bool	Event::getMoving()
{
  return is_moving;
}

bool	Event::IsKeyDown(irr::EKEY_CODE keyCode) const
{
  return KeyIsDown[keyCode];
}

Click	Event::getChoice(){
  Click tmp;

  if (value != Click::NOP)
    {
      tmp = value;
      value = Click::NOP;
    }
  return tmp;
}

irr::EKEY_CODE	Event::getLastKey()
{
  return lastKey;
}
