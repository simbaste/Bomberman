//
// Sound.cpp for	Sound in /home/simomb_s/semestre4/rendu_4/cpp_indie_studio
//
// Made by stephanedarcy simomba
// Login   <simomb_s@epitech.net>
//
// Started on  Wed Jun  1 21:54:56 2016 stephanedarcy simomba
// Last update Wed Jun  8 11:01:01 2016 stephanedarcy simomba
//

#include <iostream>
#include "Sound.hpp"
#include "Tools.hpp"
#include "Excep.hpp"

Sound::Sound()
{
  engine = createIrrKlangDevice();
  Smenu = NULL;
  Sgame = NULL;
  Sexp = NULL;
  Spu = NULL;
  Smain = NULL;
}

Sound::~Sound()
{
  if (Smenu)
    Smenu->drop();
  if (Sgame)
    Sgame->drop();
  if (Sexp)
    Sexp->drop();
  if (Spu)
    Spu->drop();
  if (engine)
    engine->drop();
}

void		Sound::getSoundMenu()
{
  Smenu = engine->play2D(SOUND_MENU,
			 true, false, true, ESM_AUTO_DETECT, true);
}

void		Sound::getSoundMain()
{
  Smain = engine->play2D(SOUND_MAIN,
			 true, false, true, ESM_AUTO_DETECT, true);
}

void		Sound::stopSoundMain()
{
  if (Smain)
    Smain->stop();
}

void		Sound::stopSoundMenu()
{
  if (Smenu)
    Smenu->stop();
}

void		Sound::getSoundExp()
{
  if ((Sexp = engine->play2D("./assets/sound/sound.wav",
			     false, false, true, ESM_AUTO_DETECT, true)) == NULL)
    throw Excep("Impossible de charger une texture");
  Sexp->setVolume(0.3f);
}

void		Sound::stopSoundExp()
{
  if (Sexp)
    Sexp->stop();
}

void		Sound::getSoundGame()
{
  if ((Sgame = engine->play2D("./assets/sound/music.wav",
			      true, false, true, ESM_AUTO_DETECT, true)) ==NULL)
    throw Excep("Impossible de charger une texture");
  Sgame->setVolume(1);
}

void		Sound::stopSoundGame()
{
  if (Sgame)
    Sgame->stop();
}

void		Sound::getSoundPU()
{
  if ((Spu = engine->play2D("./assets/sound/powerup.wav",
			    false, false, true, ESM_AUTO_DETECT, true)) == NULL)
    throw Excep("Impossible de charger une texture");
}

void		Sound::stopSoundPU()
{
  if (Spu)
    Spu->stop();
}

void		Sound::stopAllSounds()
{
  if (engine)
    engine->stopAllSounds();
}
