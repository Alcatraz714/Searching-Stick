#include "Sound/SoundService.h"
#include "Global/Config.h"

namespace Sound
{
	using namespace Global;

	void SoundService::initialize()
	{
		loadBackgroundMusicFromFile();
		loadSoundFromFile();
	}

	void SoundService::loadBackgroundMusicFromFile()
	{

	}

	void SoundService::loadSoundFromFile()
	{
		if (!buffer_button_click.loadFromFile(Config::button_click_sound_path))
			printf("Error loading button click sfx file");

		if (!buffer_compare_sfx.loadFromFile(Config::compare_sfx_path)) {
			printf("Error loading compare sfx file");
		}
	}

	void SoundService::playSound(SoundType soundType)
	{
		switch (soundType)
		{
		case SoundType::BUTTON_CLICK:
			sound_effect.setBuffer(buffer_button_click);
			break;
		case SoundType::COMPARE_SFX:
			sound_effect.setBuffer(buffer_compare_sfx);;
			break;
		default:
			printf("Invalid sound type");
			return;
		}

		sound_effect.play();
	}

	void SoundService::playBackgroundMusic()
	{
		background_music.setLoop(true);
		background_music.setVolume(background_music_volume);
		background_music.play();
	}
}