#ifndef SOUND_HPP_
# define SOUND_HPP_

#include "irrKlang.h"

using namespace irrklang;

class Sound
{
public:
  Sound();
  ~Sound();
  void		getSoundMenu();
  void		getSoundMain();
  void		stopSoundMenu();
  void		stopSoundMain();
  void		getSoundExp();
  void		stopSoundExp();
  void		getSoundGame();
  void		stopSoundGame();
  void		getSoundPU();
  void		stopSoundPU();
  void		stopAllSounds();
private:
  irrklang::ISoundEngine	*engine;
  irrklang::ISound		*Smenu;
  irrklang::ISound		*Smain;
  irrklang::ISound		*Sgame;
  irrklang::ISound		*Sexp;
  irrklang::ISound		*Spu;
};


#endif /* SOUND_HPP_ */
