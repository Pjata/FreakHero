#ifndef INC_PLAYER_H
#define INC_PLAYER_H
#include "Songs.h"
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <vector>
class Player
{
public:
	Player(void);
	~Player(void);
	inline Songs* GetSongs() {return MySongs;}
	void PlaySong(int song_number);
	void StopSong(int song_number);
	void PauseSong(int song_number);
	void LoadSong(int song_number);

	void DrawSongBar(int song_number,float OffSet);
	inline ALLEGRO_SAMPLE_INSTANCE* GetSampleInstance (int song_number) {return m_vSampleInstance;}
	void TrackSong(int song_number,float OffSet,float mY);
	
private:
	ALLEGRO_BITMAP* musicbar;
	Songs* MySongs;
	ALLEGRO_VOICE *voice;
   ALLEGRO_MIXER *mixer;
   ALLEGRO_SAMPLE_INSTANCE* m_vSampleInstance;
   int m_vSongPosition;
   ALLEGRO_FONT *font;
   int old_song_number;
};

#endif

