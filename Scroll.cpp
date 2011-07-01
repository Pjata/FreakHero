#include "Scroll.h"



Scroll::Scroll(float posmin,float posmaxy,float posx,float ScrollTerritoryY1,float ScrollTerritoryY2,float width,float height,int mertek):
	minY(posmin),
	maxY(posmaxy),
	pos_x(posx),
	scrollY1(ScrollTerritoryY1),
	scrollY2(ScrollTerritoryY2),
	width(width),
	height(height),
	mertek(mertek),
	OffSet(0),
	Scrolling(false),
	mouse_down(false)
{
	scroll_bg = al_load_bitmap("scrollbar_bg.png");
	pos_y = minY+height;
	int tmp = scrollY1 - scrollY2;
	size = abs(tmp);
	
	ScrollTerSize = maxY-minY;
}


Scroll::~Scroll(void)
{
	al_destroy_bitmap(scroll_bg);
}

void Scroll::HandleScroll(float mX,float mY,float dmY)
{
	
	float oldScr = pos_y;
	if(!Scrolling)
	{
		if(mX > pos_x && mX < pos_x+width &&
		mY > pos_y && mY < pos_y+height )
			{
		
				Scrolling=true;
		
			}
	}
	else if(mouse_down)
	{
		float Valtozas_Merteke = (size-height)/((size-height)-mY);
		div_t result = div(ScrollTerSize/Valtozas_Merteke,mertek);
		OffSet = (result.quot*mertek) - (ScrollTerSize-height) ;
	
		pos_y = mY;
	}
}

void Scroll::WheelScroll(int WheelScrollCount)
{
	if((OffSet + WheelScrollCount*mertek)>=0)
	{
		float Valtozas_Merteke = mertek / ((size + ScrollTerSize) / ScrollTerSize);
				 //A dinamikusan valtozo szam hosszhoz van igazitva a scroll tolasanak merteke
		OffSet += WheelScrollCount*mertek;
		if(pos_y> 0 + Valtozas_Merteke && (WheelScrollCount > 0))
		{
			pos_y -= WheelScrollCount*Valtozas_Merteke;	              // A Scrollolas megoldasa: a wheel mozgasanal ha nem utkozik a két érték közé akkor scroll is mozog
																		  
		}
		if(pos_y < 686 - Valtozas_Merteke && (WheelScrollCount < 0))
		{
			pos_y -= WheelScrollCount*Valtozas_Merteke;
		} 
	}

}

void Scroll::DrawScrollBar()
{
	al_draw_bitmap(scroll_bg,pos_x,pos_y,0);

}