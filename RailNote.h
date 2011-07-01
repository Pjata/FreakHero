#ifndef INC_RAILNOTE_H
#define INC_RAILNOTE_H
#include "note.h"

class RailNote : public note
{
public:
	RailNote(char* route,char* route_down,int dir,float x,float y,float height);
	~RailNote(void);
	void DrawNote(int type);
	int* IsHit(bool space_on,bool KeyDown[4],float w,float h);
	int* GetProp();
private:
	ALLEGRO_BITMAP* rail_up;
	ALLEGRO_BITMAP* rail_down;
	float m_fHeight;
	bool m_bRailing;

};

#endif

