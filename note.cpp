#include "note.h"

note::note()
{}


note::note(char* route,int dir)
{
	bmp = al_load_bitmap(route);
	
	m_iDir = dir;
	m_bMove=false;
	m_fX=686+49;
	m_fY=0;
	m_bHit=false;
	
}

note::note(char* route,char* route_down,int dir,float x,float y)
{
	bmp = al_load_bitmap(route);
	bmpdown = al_load_bitmap(route_down);
	m_iDir = dir;
	m_bMove=false;
	m_fX=x;
	m_fY=y;
	m_bHit=false;
	m_iType = NORMAL;
	 
/*	div_t result;

	//rács kiszámítása. biztos 49 * 49 es rácson lesz rajta a note
	result = div((x-414),49);
	int res_dived = result.quot;
	id[0]=res_dived;
	result = div(y,49);
	res_dived = result.quot;
	id[1]=res_dived; */

}


note::~note(void)
{
	al_destroy_bitmap(bmp);
	al_destroy_bitmap(bmpdown);
}

void note::DrawNote(int type)
{
	if(!m_bHit)
	{
		if(type == UP)
		{
		al_draw_bitmap(bmp,m_fX,m_fY,0);
		}
		else if(type == DOWN)
		{
			al_draw_bitmap(bmpdown,m_fX,m_fY,0);
		}
	}
}
int* note::IsHit(bool space_on,bool KeyDown[4],float w,float h)
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
			}
			 else if(!KeyDown[m_iDir] && !m_bHit)
			{
				scorex[0]=-1;
			}
			else 
			{
				scorex[0]=0;
			}
			
		 }
			

	return scorex;
}

int* note::GetProp()
{
		return NULL;	
}