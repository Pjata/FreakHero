#ifndef INC_GAME_H
#define INC_GAME_H
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include "Songs.h"
#include "BarBracket.h"
#include "Editor.h"
#include "Player.h"

const float FPS = 60;
const int SCREEN_W = 1024;
const int SCREEN_H = 686;

enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
class Game
{
public:
	Game();
	~Game();
	bool Init_Allegro();
	bool Init_GameRes();
	void GameLoop();
	void GameEditor();
	void GameMenu();
	void GameEditor_RealTime();
	inline bool IsReady() {return GameReadyToRun;}
	void ChosingWhatToDo();
	
private:
	 ALLEGRO_DISPLAY *display;
   ALLEGRO_EVENT_QUEUE *event_queue;
   ALLEGRO_TIMER *timer;
   ALLEGRO_TIMER *secundum;
   ALLEGRO_BITMAP *bg;
    ALLEGRO_FONT *font;
	ALLEGRO_BITMAP *start;
	ALLEGRO_BITMAP *edit;
	ALLEGRO_BITMAP *menu;
   bool AllegroInitSuccess;
	bool space_press;
	bool GameResInitSuccess;
	BarBracket* MyBar;
	bool key[4];
	bool redraw;
	bool doexit;
	int secund;
	bool GameReadyToRun;
	int Choose;
	int ChoosedSong;
	Editor* MyEditor;
	Player* MyPlayer;
	Editor* MyEditor_RealTime;
	std::vector<std::string> SongNamesWithBrackets;

	float ScreenWidth;
	float ScreenHeight;
};


#endif