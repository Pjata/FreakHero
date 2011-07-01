#ifndef INC_SCROLL_H
#define INC_SCORLL_H
#include <allegro5\allegro5.h>
#include <allegro5\bitmap.h>
class Scroll
{
public:
	Scroll(float posmin,float posmaxy,float posx,float ScrollTerritoryY1,float ScrollTerritoryY2,float width,float height,int mertek);
	~Scroll(void);
	inline float const GetOffSet() {return OffSet;}
	void SetOffSet(float s) {OffSet=s;}
	void SetMouseDown(bool b) {mouse_down = b;}
	void HandleScroll(float mX,float mY,float dmY);
	void WheelScroll(int WheelScrollCount);
	void DrawScrollBar();

private:
	float minY,maxY,scrollY1,scrollY2,width,height,size,OffSet,pos_y,pos_x;
	int mertek;
	ALLEGRO_BITMAP* scroll_bg;
	bool Scrolling;
	float ScrollTerSize;
	bool mouse_down;
};

#endif
