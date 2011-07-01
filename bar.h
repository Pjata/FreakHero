#ifndef INC_BAR_H
#define INC_BAR_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "note.h"
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

class bar
{
public:
	bar(float x,float y,std::string filename,int type,float w,float h);
	~bar(void);
	
	//1 blue | 2 red | 3 yellow | 4 green

	void	rendernote_down(int i,float x,float y);
	void	rendernote_up(int i,float x,float y);
	
	void renderbarbg_x(float x);
	void renderbar(int sec);
	
	int makemove_x(bool space_on,float x,bool KeyDown[4]);

	
	
	inline note* GetNote(int i) {return MyNotes[i];}
private:
	ALLEGRO_BITMAP *barbg_bottom;
	ALLEGRO_BITMAP *barbg_top;
	std::vector<note*> MyNotes;
	int song[840];
	int cur;
	int m_iBarLength;
	bool m_bNoteInHitZone;
	float m_fHeight;
	float m_fWidth;
	float m_fX;
	float m_fY;
	
	
};


#endif
