#include "RailNote.h"


RailNote::RailNote(char* route,char* route_down,int dir,float x,float y,float height)
{
	bmp = al_load_bitmap(route);
	bmpdown = al_load_bitmap(route_down);
	m_iDir = dir;
	m_bMove=false;
	m_fX=x;
	m_fY=y;
	m_bHit=false;
	m_fHeight = height;
	m_bRailing = false;
	rail_up = al_load_bitmap("./rail_up.png");
	rail_down = al_load_bitmap("./rail_down.png");
	m_iType = RAIL;
}


RailNote::~RailNote(void)
{
	al_destroy_bitmap(rail_up);
	al_destroy_bitmap(rail_down);
}

void RailNote::DrawNote(int type)
{
		if(m_bRailing)
		{
			for(int i=0;i<m_fHeight;i++)
			{
				al_draw_bitmap(rail_down,m_fX,m_fY-i*49,0);
			}
		}
		else if(!m_bHit)
		{
			for(int i=0;i<m_fHeight;i++)
			{
				al_draw_bitmap(rail_up,m_fX,m_fY-i*49,0);
			}
		}
	if(!m_bHit)
	{
		if(type == UP)
		{
	 
			for(int i=0;i<m_fHeight;i++)
			{
				al_draw_bitmap(rail_up,m_fX,m_fY-i*49,0);
			}
			al_draw_bitmap(bmp,m_fX,m_fY,0);
		}
		else if(type == DOWN)
		{
		
			al_draw_bitmap(bmpdown,m_fX,m_fY,0);
		}
	}

}
int* RailNote::IsHit(bool space_on,bool KeyDown[4],float w,float h)
{
	
int scorex[2];
	scorex[0]=0;
	scorex[1]=0;
	
	if(
			 (m_fY<=(h-49) && m_fY >= (h-90)) || 
			 ((m_fY)+40) <= (h-49) && ((m_fY)+49) >= (h-90)
		   )
		 {
			 scorex[1] = true;
			 if(KeyDown[m_iDir] && !m_bHit && space_on )
			{
				scorex[0]=1;
				m_bHit = true;
				m_bRailing = true;
			}
			 else if(!KeyDown[m_iDir] && !m_bHit)
			 {
				scorex[0] = -1;
			 }
			
			else
			{
				scorex[0]=0;
			}
			
		 }
	if(!space_on && m_bRailing)
	{
		m_bRailing = false;
	}
 	if((KeyDown[m_iDir] && space_on && m_bRailing && 
				(
	     		(m_fY-m_fHeight*49 <= h-49 && m_fY >= h-90)
				|| 
				(m_fY+40-m_fHeight*49 <= h-49 && m_fY+40 >= h-90)													
				)))
			
			{
     				scorex[0] = 1;
					scorex[1] = 1;
				if( m_fY+40 - m_fHeight*49 > h-90)
				{
					m_bRailing = false;
				} 
				
			}
	
		


			

	return scorex;

}

int*  RailNote::GetProp()
{
	int prop[1];
	prop[0] = m_fHeight;
	return prop;
}