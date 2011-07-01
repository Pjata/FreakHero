#include "Selection.h"


Selection::Selection(void)
{
	selected = al_load_bitmap("./selected.png");
}


Selection::~Selection(void)
{
	al_destroy_bitmap(selected);
	m_vSelection.clear();

}


void Selection::Select(float x,float y,vector<note*> &From)
{
	for(int i=0;i<From.size();i++)
	{
		if((From[i]->GetX() <= x && From[i]->GetY() <= y) &&
			((From[i]->GetX()+49) >= x && (From[i]->GetY()+49) >= y))
		{
			m_vSelection.push_back(From[i]);
		}
	}
}

void Selection::Select(float x1,float y1,float x2,float y2,vector<note*> &From)
{
	if(x1>x2) 
	{
		int tmp=x2; x2=x1; x1=tmp;
	}
	if(y2>y1) 
	{
		int tmp=y2; y2=y1; y1=tmp;
	} 
	for(int i=0;i<From.size();i++)
	{
		if(((From[i]->GetX() >= x1 ||From[i]->GetX() >= x1-28) && (From[i]->GetX() <= x2 || From[i]->GetX() <= x2-28)) &&  
			((From[i]->GetY() <= y1 || From[i]->GetY() <= y1-28) && (From[i]->GetY() >= y2 || From[i]->GetY() >= y2-28)) 
		// &&	(From[i]->GetSelected() == false)
			)
		{
			m_vSelection.push_back(From[i]);
		//	From[i]->SetSelect(true);
		}
	}
}

void Selection::Deselect(float x,float y)
{
	for(int i=0;i<m_vSelection.size();i++)
	{
		if((m_vSelection[i]->GetX() <= x && m_vSelection[i]->GetY() <= y) &&
			((m_vSelection[i]->GetX()+49) >= x && (m_vSelection[i]->GetY()+49) >= y))
		{
			m_vSelection.erase(m_vSelection.begin()+i);
		}
	}
}

void Selection::Deselect(float x1,float y1,float x2,float y2)
{
	if(x1>x2) 
	{
		int tmp=x2; x2=x1; x1=tmp;
	}
	if(y2>y1) 
	{
		int tmp=y2; y2=y1; y1=tmp;
	} 
	for(int i=0;i<m_vSelection.size();i++)
	{
	if(((m_vSelection[i]->GetX() >= x1 ||m_vSelection[i]->GetX() >= x1-28) && (m_vSelection[i]->GetX() <= x2 || m_vSelection[i]->GetX() <= x2-28)) &&  
			((m_vSelection[i]->GetY() <= y1 || m_vSelection[i]->GetY() <= y1-28) && (m_vSelection[i]->GetY() >= y2 || m_vSelection[i]->GetY() >= y2-28))) 
		{
			m_vSelection.erase(m_vSelection.begin()+i);
			i--;
		}
	}
}

void Selection::DeleteSelection()
{
	m_vSelection.clear();
}

void Selection::DrawSelection(float OffSet)
{
	for(int i=0;i<m_vSelection.size();i++)
	{
		al_draw_bitmap(selected,m_vSelection[i]->GetX(),m_vSelection[i]->GetY()+OffSet,0);
	}
}

void Selection::DeleteSelected(std::vector<note*> &NoteBar)
{
	for(int i=0;i<NoteBar.size();i++)
	{
		for(int j=0;j<m_vSelection.size();j++)
		{
			if(i<NoteBar.size() && j<m_vSelection.size() && NoteBar[i]->GetX() ==  NoteBar[j]->GetX() &&
				NoteBar[i]->GetY() == m_vSelection[j]->GetY())
			{
				NoteBar.erase(NoteBar.begin()+i);
				m_vSelection.erase(m_vSelection.begin()+j);
			}
		}
	}

}

void Selection::Copy(float mY,float OffSet,bool CopyFinished,int type,std::vector<note*> &NoteBar)
{
	if(!CopyFinished)
	{
		int min_y=10000;
		for(int i=0;i<m_vSelection.size();i++)
		{
			if(min_y>m_vSelection[i]->GetY()) 
			{
				min_y = m_vSelection[i]->GetY();
			}
			div_t result = div(mY,49);
			float y = (abs(min_y - m_vSelection[i]->GetY())) + result.quot*49;
			al_draw_bitmap(selected,m_vSelection[i]->GetX(),y,0);
		}
	}
	else
	{
		int min_y=10000;
		int size = m_vSelection.size();
		for(int i=0;i<size;i++)
		{
			if(min_y>m_vSelection[i]->GetY()) 
			{
				min_y = m_vSelection[i]->GetY();
			}
		}
		for(int i=0;i<size;i++)
		{
			
			div_t result = div(mY,49);
			float y = (abs(min_y - m_vSelection[i]->GetY())) + result.quot*49 - OffSet;
			
			char* str[4][2];
	str[0][0]="./blue_up.png";
	str[1][0]="./red_up.png";
	str[2][0]="./yellow_up.png";
	str[3][0]="./green_up.png";

	str[0][1]="./blue_down.png";
	str[1][1]="./red_down.png";
	str[2][1]="./yellow_down.png";
	str[3][1]="./green_down.png";
			int dir = (m_vSelection[i]->GetX()-414) / 49;
			int x = m_vSelection[i]->GetX();
			if(dir == type)
			{
			NoteBar.push_back(new note(str[dir][0],str[dir][1],dir,x,y));
		
			}
		}
	}
}


void Selection::Copy(float mY,float OffSet,bool CopyFinished)
{
	if(!CopyFinished)
	{
		int min_y=10000;
		for(int i=0;i<m_vSelection.size();i++)
		{
		if(min_y>m_vSelection[i]->GetY()) 
			{
				min_y = m_vSelection[i]->GetY();
			}
		}
		for(int i=0;i<m_vSelection.size();i++)
		{
			
			div_t result = div(mY,49);
			float y = (abs(min_y - m_vSelection[i]->GetY())) + result.quot*49;
			al_draw_bitmap(selected,m_vSelection[i]->GetX(),y,0);
		}
	}
	
}

