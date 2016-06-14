#ifndef TOOLS_HPP_
# define TOOLS_HPP_

#include <vector>
#include <string>
#include <vector>
#include <irr/irrlicht.h>
#include <irr/IEventReceiver.h>
#include "Sound.hpp"
#include "Excep.hpp"
typedef irr::gui::IGUIButton		button;
typedef irr::core::rect<irr::s32>	rect;

# define irrMap_t                std::vector<std::vector<irr::scene::ISceneNode*> >

# define mC(x, y) (((x) + (y)) / 50)

//EVENT

enum class      Click : uint16_t
{
  QUIT  = 101,
    ONE = 102,
    TWO = 103,
    THREE = 104,
    OK = 105,
    CANCEL = 106,
    PLAY = 107,
    OPTION = 108,
    LOAD = 109,
    NAME_ONE = 110,
    NAME_TWO = 111,
    NAME_THREE = 112,
    IA = 113,
    CONTINUE,
    UP1,
    DOWN1,
    LEFT1,
    RIGHT1,
    BOMB1,
    UP2,
    DOWN2,
    LEFT2,
    RIGHT2,
    BOMB2,
    UP3,
    DOWN3,
    LEFT3,
    RIGHT3,
    BOMB3,
    BACK,
    OPTIONS,
    NOP
    };

enum
  {
    GUI_ID_PLAY,
    GUI_ID_PLAY_N,
    GUI_ID_IA_PLAYERS,
    GUI_ID_OPTION,
    GUI_ID_LOAD,
    GUI_ID_QUIT,
    GUI_ID_UP1,
    GUI_ID_DOWN1,
    GUI_ID_LEFT1,
    GUI_ID_RIGHT1,
    GUI_ID_BOMB1,
    GUI_ID_UP2,
    GUI_ID_DOWN2,
    GUI_ID_LEFT2,
    GUI_ID_RIGHT2,
    GUI_ID_BOMB2,
    GUI_ID_UP3,
    GUI_ID_DOWN3,
    GUI_ID_LEFT3,
    GUI_ID_RIGHT3,
    GUI_ID_BOMB3,
    GUI_ID_PLAYER1,
    GUI_ID_PLAYER2,
    GUI_ID_PLAYER3,
    GUI_ID_ONE_PLAYER,
    GUI_ID_TWO_PLAYERS,
    GUI_ID_THREE_PLAYERS,
    GUI_ID_CANCEL,
    GUI_ID_CANCEL_N,
    GUI_ID_CANCEL_P,
    GUI_ID_DIALOG,
    GUI_ID_SET_NAME_ONE,
    GUI_ID_SET_NAME_TWO,
    GUI_ID_SET_NAME_THREE,
    GUI_ID_CONTINUE,
    GUI_ID_BACK,
    GUI_ID_PAUSE_OPTION,
  };

//GAME

struct  Position
{
  int	x;
  int	y;
  Position(unsigned int x = 1, unsigned int y = 1);
};

struct  BombInfo
{
  Position      pos;
  unsigned int  range;
  bool          explosion;
};

#define BACKGROUND_MENU "./assets/file/background_menu.png"
#define	BACKGROUND_PAUSE "./assets/file/bric2.png"
#define GROUND "./assets/file/ground_2.jpeg"
#define	UNBREAKABLE_WALL "./assets/file/solid_block.jpg"
#define	BOMB_ASSET "assets/file/bomb.jpg"

#define SOUND_CLICK "./assets/sound/selection.wav"
#define SOUND_MENU "./assets/sound/intro.wav"
#define SOUND_MAIN "./assets/sound/peaceful_land.wav"

#define BOMB_UP_ASSET "assets/file/bomb_up_powerup.png"
#define RANGE_UP_ASSET "assets/file/range_up_powerup.png"
#define SPEED_UP_ASSET "assets/file/speed_up_powerup.png"
#define KICKBOMB_ASSET "assets/file/kickbomb_powerup.png"

#define SPEED_DOWN_ASSET "assets/file/speed_down_powerup.png"
#define RANGE_DOWN_ASSET "assets/file/range_down_powerup.png"
#define BOMB_DOWN_ASSET "assets/file/bomb_down_powerup.png"

#define SOLO_BUTTON "assets/file/buttons/solo_button.png"
#define TWO_PLAYERS_BUTTON "assets/file/buttons/2players_button.png"
#define THREE_PLAYERS_BUTTON "assets/file/buttons/3players_button.png"
#define CANCEL_BUTTON "assets/file/buttons/cancel_button.png"
#define LOAD_BUTTON "assets/file/buttons/load_button.png"
#define OPTIONS_BUTTON "assets/file/buttons/options_button.png"
#define PLAY_BUTTON "assets/file/buttons/play_button.png"
#define QUIT_BUTTON "assets/file/buttons/quit_button.png"
#define SAVE_BUTTON "assets/file/buttons/save_button.png"
#define UP_BUTTON "assets/file/buttons/up_button.png"
#define DOWN_BUTTON "assets/file/buttons/down_buttton.png"
#define LEFT_BUTTON "assets/file/buttons/left_buttton.png"
#define RIGHT_BUTTON "assets/file/buttons/right_buttton.png"
#define BOMB_BUTTON "assets/file/buttons/bomb_buttton.png"
#define CONTINU_BUTTON "assets/file/buttons/continue_buttton.png"
#define RESET_BUTTON "assets/file/buttons/reset_buttton.png"
#define CONTINUE_BUTTON "assets/file/buttons/continue_buttton.png"
#define PLAYER1_BUTTON "assets/file/buttons/player1_buttton.png"
#define PLAYER2_BUTTON "assets/file/buttons/player2_buttton.png"
#define PLAYER3_BUTTON "assets/file/buttons/player3_buttton.png"

#define PLAYER1_LABEL "assets/file/buttons/player1_label.png"
#define PLAYER2_LABEL "assets/file/buttons/player2_label.png"
#define PLAYER3_LABEL "assets/file/buttons/player3_label.png"
#define IA_BUTTON "assets/file/buttons/ia_button.png"
#define BREAKABLE_WALL "./assets/file/bric2.png"
#define FIRE_WALL "./assets/file/fire_wall.jpg"
#define SKYBOX "./assets/file/skybox.jpeg"
#define BACKGROUND_GAME "./assets/file/skybox.jpeg"
#define SIZE_BOMB 50
#define SIZE_POWERUP 50
#define SIZE_FIRE 50

#define X_IA_BUTTON 730
#define Y_IA_BUTTON 185
#define X_SIZE_IA_BUTTON 140
#define Y_SIZE_IA_BUTTON 75
#define X_IA_BUTTON_END X_IA_BUTTON + X_SIZE_IA_BUTTON
#define Y_IA_BUTTON_END Y_IA_BUTTON + Y_SIZE_IA_BUTTON

class Event;

struct Elem
{
  irr::scene::IAnimatedMeshSceneNode	*mesh;
  irr::video::IVideoDriver		*driver;
  irr::scene::ISceneManager		*smgr;
  Event					*event;
  irrMap_t				*irrMap;
  irr::IrrlichtDevice			*device;
  Sound					*sound;
};

# define mC(x, y) (((x) + (y)) / 50)

struct	Pos
{
  float	x;
  float	y;
};

enum class Direction : uint16_t
{
  RIGHT = 1,
    LEFT,
    UP,
    DOWN,
    NOP
};


enum class		Tile : uint16_t
{
    EMPTY	= 0,		// Empty cell
    BLOCK	= 1,		// BLOCK
    WALL	= 2,		// BOMB
    CHARACTER	= 3,		// EXPLOSION
    INTEL	= 4,		// IA
    BOMB	= 5,		// WALL
    EXPLOSION	= 6,		// CHARACTER
    EXPLOSION_POWERUP,		// CHARACTER
    INVINCIBLE,		// POWER UP INVINCIBLE
    KICKBOMB,		// POWER UP KICK BOMB
    SPEEDUP,		// POWER UP KICK BOMB
    SPEEDDOWN,		// POWER UP KICK BOMB
    GHOST,		// POWER UP GHOST
    RANGEDOWN,		// POWER UP RANGE UP
    RANGEUP,		// POWER UP RANGE DOWN
    BOMBUP,		// POWER UP BOMB UP
    LINEBOMB,		// POWER UP LINE BOMB
    BOMBDOWN,		// POWER UP BOMB DOWN
    NONE		// POWER UP BOMB DOWN
};

typedef std::vector<std::vector<Tile>> mapVector;

struct  keyMap
{
  irr::EKEY_CODE        UP;
  irr::EKEY_CODE        DOWN;
  irr::EKEY_CODE        RIGHT;
  irr::EKEY_CODE        LEFT;
  irr::EKEY_CODE        BOMB;
};

static const unsigned int timeToExplodeDefault = 4000;

// Irrlich typedef
typedef irr::scene::IAnimatedMeshSceneNode	irrAnimMesh;
typedef irr::scene::ISceneManager		irrSmgr;
typedef irr::video::IVideoDriver		irrDriver;
typedef irr::IrrlichtDevice			irrDevice;
typedef irr::scene::ISceneNode			irrNode;
typedef irr::core::vector3df			irrVector;

// STD typdef

//typedef std::string const			constString
#endif
