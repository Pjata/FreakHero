#ifndef INC_EDITOR_H
#define INC_EDITOR_H
#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>
#include <vector>
#include "./note.h"
#include "Selection.h"
#include "Player.h"
class Editor
{
public:
	Editor(Player* MyPlayer,int ChoosedSong,float w,float h);
	~Editor(void);
	void DrawBars();
	void PlaceNote(float mX,float mY,float type);
	void OutputToFiles();
	void HandleScroll(float mX,float mY,float dmY);
	void DrawNotes();
	void WheelScroll(int WheelScrollCount);
	void RemoveNote(float mX,float mY);
	void MouseSelectionDraw(float x1,float y1,float x2,float y2); 

	inline	void SetM(float mX,float mY) {oldMX=mX;oldMY=mY;}
	inline	void SetScroll(bool scr) {Scrolling=scr;}
	inline float GetOffSet() {return OffSet;}
	inline bool GetScroll() {return Scrolling;}
	inline Selection* GetSelect() {return MySelection;}
	inline std::vector<note*>& GetNoteBar(int i) {return NoteBar[i];}

private:
	ALLEGRO_BITMAP* barbg_bottom;
	ALLEGRO_BITMAP* barbg_top;
	ALLEGRO_BITMAP* notes[4];
	ALLEGRO_BITMAP* ScrollBar;
	ALLEGRO_BITMAP* start_bar;
	ALLEGRO_BITMAP* end_bar;
	ALLEGRO_BITMAP* mouse_selection;
	float ScrollX;
	float ScrollY;
	float Add_To_X_Coord;
	float Add_To_Y_Coord;
	float oldScrollX;
	float oldScrollY;
	float oldMX;
	float oldMY;
	float OffSet;
	float MaxCoordY;
	float m_fWidth;
	float m_fHeight;
	bool Scrolling;
	
	int RailNoteStartY;
	int RailNoteX;
	int RailNoteEndY;
	bool RailNoteStart;

	std::vector<note*> NoteBar[4];
	std::vector<std::string> SongNamesWithBrackets;
	Selection* MySelection;
};
#endif
