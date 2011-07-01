#include "Editor.h"
#include <fstream>
#include <iostream>
#include <string>
#include "RailNote.h"
#include "Player.h"
#include "DISPLAY_INFO.h"
#include <stdio.h>
using namespace std;

Editor::Editor(Player* MyPlayer,int ChoosedSong,float w,float h)
{
	//Deklarácitók
	barbg_bottom= NULL;
	barbg_bottom =  al_load_bitmap("./bar_bottom.png");
	
	barbg_top= NULL;
	barbg_top =  al_load_bitmap("./bar_top.png");

	

	m_fWidth = w;
	m_fHeight = h;

	// a note-ok bitmapjának  betöltese editorhoz elég csak az up
	notes[0] = al_load_bitmap("./blue_up.png");
	notes[1] = al_load_bitmap("./red_up.png");
	notes[2] = al_load_bitmap("./yellow_up.png");
	notes[3] = al_load_bitmap("./green_up.png");

	//a selection mikor a az egérrel kattintunk és kijelölünk bitmapja
	mouse_selection = al_create_bitmap(100,100);
	al_set_target_bitmap(mouse_selection);
	al_clear_to_color(al_map_rgb(30,30,130));
	//rail noteok helyezéséhez kel
	RailNoteStart = true;
	
	
	//OffSet = 686-49;
	OffSet = 0;
	//a Scroll bar, a szam eleje bar, es a szam vege bar betöltése
	ScrollBar = al_load_bitmap("./ScrollBar.png");
	start_bar = al_load_bitmap("./bottom_start.png");
	end_bar = al_load_bitmap("./song_end.png");
	// a szam vége barhoz a maximum (minimum valójában) koorditana, és a scroll X illetve y coord deklarásása
	MaxCoordY=1;
	ScrollX=m_fWidth-30;
	ScrollY=m_fHeight-49;
	 Scrolling=false;						// nem scrollolunk alapból
	 MySelection = new Selection();			// Selection deklarása
	 	char* str[4][2];

		//A fileból beolvassuk a note okat _______________________________________

	str[0][0]="./blue_up.png";
	str[1][0]="./red_up.png";
	str[2][0]="./yellow_up.png";
	str[3][0]="./green_up.png";

	str[0][1]="./blue_down.png";
	str[1][1]="./red_down.png";
	str[2][1]="./yellow_down.png";
	str[3][1]="./green_down.png";

	
	for(int i=0;i<4;i++)
	{

		std:string tmp = MyPlayer->GetSongs()->GetSongName(ChoosedSong);
		char* char_i = new char[16];
		itoa(i,char_i,10);
		tmp += char_i;
		SongNamesWithBrackets.push_back(tmp);
		delete char_i;
		
	}
	



	MaxCoordY = 0;
for (int i=0;i<4;i++)
{
		ifstream myfile(SongNamesWithBrackets[i]);
		int input_dir;
		int input_x;
		int input_y;
		int input_type;
	if(myfile.is_open())
	{
		
		while(!myfile.eof())
		{
			//getline(myfile,line);
			myfile >> input_type;
			if(input_type == NORMAL)
			{
			myfile >> input_dir;
			myfile >> input_x;
			myfile >> input_y;
			
			NoteBar[i].push_back(new note(str[input_dir][0],str[input_dir][1],input_dir,(m_fWidth/2)-(2*49)+(input_x*49),input_y)); // a vektorba szétválasztva tipus szerint kerülnek a note-ok
			}
			else if(input_type == RAIL)
			{
			myfile >> input_dir;
			myfile >> input_x;
			myfile >> input_y;
			int input_height;
			myfile >> input_height;
			NoteBar[i].push_back(new RailNote(str[input_dir][0],str[input_dir][1],input_dir,((m_fWidth/2)-(2*49))+(input_x*49),input_y,input_height));
			}
			if(input_y < MaxCoordY) 
			{
					MaxCoordY = input_y; // a song end barhoz kell
			}
		}
	}	
	
	}
int count = 0; 
for(int i=0;i<4;i++)
	{

		for(int j=0;j<NoteBar[i].size();j++)
		{
			for(int k=0;k<NoteBar[i].size();k++)
			{
				if(k != j && j<NoteBar[i].size() && k<NoteBar[i].size())
				{
					if(NoteBar[i][k]->GetX() == NoteBar[i][j]->GetX() && NoteBar[i][k]->GetY() == NoteBar[i][j]->GetY())
					{
						NoteBar[i].erase(NoteBar[i].begin()+k);
						count++;
					}
				}
			}
		}
	}
	
}


Editor::~Editor(void)
{
	for(int i=0;i<4;i++)
	{
		al_destroy_bitmap(notes[i]);
	
		NoteBar[i].clear();
	}
	al_destroy_bitmap(ScrollBar);
	al_destroy_bitmap(start_bar);
	al_destroy_bitmap(end_bar);
	al_destroy_bitmap(mouse_selection);
	al_destroy_bitmap(barbg_bottom);
	al_destroy_bitmap(barbg_top);
	SongNamesWithBrackets.clear();
	delete MySelection;
	
	

}


void Editor::DrawBars()
{
	//A notebar-ok és scroll bar rajzolása
	// a ciklusban annnyi bar-topot rajzol amennyi szükséges
	for(int i=0;i<4;i++)
	{
		float	x = (m_fWidth/2)-(al_get_bitmap_width(barbg_bottom)*2) + al_get_bitmap_width(barbg_bottom) *i ;
		al_draw_bitmap(barbg_bottom,x,(m_fHeight-al_get_bitmap_height(barbg_bottom)),0);
		for(int y=m_fHeight-(al_get_bitmap_height(barbg_bottom)+al_get_bitmap_height(barbg_top));y>-100;y-=al_get_bitmap_height(barbg_top))
		{
		al_draw_bitmap(barbg_top,x,y,0);
		} 
	
				
	}
	al_draw_bitmap(ScrollBar,ScrollX,ScrollY,0);
}

void Editor::PlaceNote(float mX,float mY,float type)
{
	char* str[4][2];
	str[0][0]="./blue_up.png";
	str[1][0]="./red_up.png";
	str[2][0]="./yellow_up.png";
	str[3][0]="./green_up.png";

	str[0][1]="./blue_down.png";
	str[1][1]="./red_down.png";
	str[2][1]="./yellow_down.png";
	str[3][1]="./green_down.png";
	
	for(int i=0;i<4;i++)
	{
		if(mX > 414+i*49 && mX < 414+((i+1)*49))
		{
			
			div_t divresult;                      //Hogy biztosan csak a megadott 49 el osztható koordinátákra kerüljün
												  //Igy tagolt lesz, fix helyekre kerülhetnek note-ok
			divresult = div (mY,49);
			float y = divresult.quot;
			
			
			
		//	al_draw_bitmap(notes[i],414+i*49,y*49,0);
			if(type == NORMAL)
			{
				NoteBar[i].push_back(new note(str[i][0],str[i][1],i,414+i*49,y*49-OffSet));
			}
			else if(type == RAIL)
			{
				RailNoteX=414+i*49;
				if(RailNoteStart)
				{
					RailNoteStartY = y*49 - OffSet;
					RailNoteStart = false;
				}
				else
				{
					RailNoteEndY = y*49 - OffSet;
					int height = abs(RailNoteStartY - RailNoteEndY) / 49;
					NoteBar[i].push_back(new  RailNote(str[i][0],str[i][1],i,RailNoteX,RailNoteStartY,height));
					RailNoteStart = true;
				}
			}
			if(y*49 - OffSet < MaxCoordY)
			{
				MaxCoordY = y*49 - OffSet; // A max szam hossz hoz kell ez valojaban minimum coordinata.
			}
			
		}
		
		
	}
	
	
	
}
void Editor::RemoveNote(float mX,float mY)
{
	
	
	for(int i=0;i<4;i++)
	{
		if(mX > 414+i*49 && mX < 414+((i+1)*49))
		{
			
			div_t divresult;
			divresult = div (mY,49);
			float y = divresult.quot;
			y = y*49-OffSet;
			float x = 414+i*49;
		
	
			for(int j=0;j<NoteBar[i].size();j++)
			{
				if(x==NoteBar[i][j]->GetX() && y==NoteBar[i][j]->GetY())
				{
					NoteBar[i].erase(NoteBar[i].begin()+j); //maga a törlés

				if(MaxCoordY==y) // ez azért kell hogy ha a végérõl leveszünk akkor a song end bar tovabb mozogjon
				{	

					MaxCoordY = 10000;
					for(int m_j=0;m_j<4;m_j++)
					{
						for(int m_i=0;m_i<NoteBar[m_j].size();m_i++)
						{
							if(NoteBar[m_j][m_i]->GetY() < MaxCoordY )
							{
								MaxCoordY = NoteBar[m_j][m_i]->GetY() ;
							}
						}
					}
				}
			
				
				}
			}
		}	
		
	}
	
	
}

void Editor::OutputToFiles()
{

	
	
	std::ofstream MyFiles[4];
	for(int i=0;i<4;i++)
	{
		MyFiles[i].open(SongNamesWithBrackets[i]);
		int it;

		for(it = 0;it<NoteBar[i].size();it++)
		{
			if(NoteBar[i][it]->GetType() == NORMAL)
			{
				MyFiles[i] << NoteBar[i][it]->GetType() << " " <<  NoteBar[i][it]->GetDir() << " " << NoteBar[i][it]->GetX() << " " << NoteBar[i][it]->GetY() << "\n";
			}
			else if(NoteBar[i][it]->GetType() == RAIL)
			{
				int* Prop = NoteBar[i][it]->GetProp();
				MyFiles[i] << NoteBar[i][it]->GetType() << " " <<  NoteBar[i][it]->GetDir() << " " << NoteBar[i][it]->GetX() << " " << NoteBar[i][it]->GetY() << " " << Prop[0] << "\n";
			}
		}
	}
	
	
}

void Editor::HandleScroll(float mX,float mY,float dmY)
{
	float oldScr = ScrollY;
	if(!Scrolling)
	{
		if(mX > ScrollX && mX < ScrollX+10 &&
		mY > ScrollY && mY < ScrollY+30 )
			{
		
				Scrolling=true;
		
			}
	}
	else 
	{
		float Valtozas_Merteke = (m_fHeight-30)/((m_fHeight-30)-mY);
		div_t result = div((abs(MaxCoordY)+(m_fHeight-30))/Valtozas_Merteke,49);
		OffSet = result.quot*49;
		ScrollY = mY;
	}
	//ScrollY=mY;
	
	al_draw_bitmap(ScrollBar,ScrollX,ScrollY,0);
}
void Editor::WheelScroll(int WheelScrollCount)
{
	if((OffSet + WheelScrollCount*49)>=0)
	{
		float Valtozas_Merteke = 49 / ((abs(MaxCoordY) + m_fHeight) / m_fHeight);
				 //A dinamikusan valtozo szam hosszhoz van igazitva a scroll tolasanak merteke
		OffSet += WheelScrollCount*49;
		if(ScrollY > 0 + Valtozas_Merteke && (WheelScrollCount > 0))
		{
			ScrollY -= WheelScrollCount*Valtozas_Merteke;	              // A Scrollolas megoldasa: a wheel mozgasanal ha nem utkozik a két érték közé akkor scroll is mozog
																		  
		}
		if(ScrollY < 686 - Valtozas_Merteke && (WheelScrollCount < 0))
		{
			ScrollY -= WheelScrollCount*Valtozas_Merteke;
		} 
	}
	
}
void Editor::DrawNotes()
{
	for (int i=0;i<4;i++)
	{
		int it;

		for(it = 0;it<NoteBar[i].size();it++)
		{
			// OffSEttel eltolás majd vissza
			float y = NoteBar[i][it]->GetY() + OffSet;
			NoteBar[i][it]->SetCoord(NoteBar[i][it]->GetX(),y);
			NoteBar[i][it]->DrawNote(NoteBar[i][it]->GetType());
			y = NoteBar[i][it]->GetY() - OffSet;
			NoteBar[i][it]->SetCoord(NoteBar[i][it]->GetX(),y);
			
		}
	}
	if(RailNoteStart)
	{
		al_draw_bitmap(MySelection->GetBMPSELECTED(),RailNoteX,RailNoteStartY,0);
	}
	al_draw_bitmap(start_bar,m_fWidth/2-BarWidth*2,m_fHeight-49 + OffSet,0);
	al_draw_bitmap(end_bar,m_fWidth/2-BarWidth*2,MaxCoordY-49 + OffSet,0);
}

void Editor::MouseSelectionDraw(float x1,float y1,float x2,float y2)
{
	if(x2<x1) 
	{
		int tmp=x2;
		x2=x1;
		x1=tmp;
	}
	if(y2<y1)
	{
		int tmp=y2;
		y2=y1;
		y1=tmp;
		
	}
	
	al_draw_tinted_scaled_bitmap(mouse_selection,al_map_rgba_f(1,1,1,0.3),0,0,100,100,x1,y1,x2-x1,y2-y1,0);

}