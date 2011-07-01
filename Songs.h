#ifndef INC_SONGS_H
#define INC_SONGS_H
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro.h>
#include <vector>
class Songs
{
public:
	Songs();
	~Songs();

//	inline ALLEGRO_SAMPLE* GetSong(int i) {return m_vSongs[i];}
	inline int Size() {return m_iSize;}
	inline char* GetSongName(int i) {return m_cSongNames[i];}


private:
//	std::vector<ALLEGRO_SAMPLE*> m_vSongs;
	int m_iSize;
	std::vector<char*> m_cSongNames;
};

#endif

