#include "bar.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "RailNote.h"
using namespace std;

bar::bar(float x,float y,std::string filename,int type,float w,float h)
{
	barbg_bottom= NULL;
	barbg_bottom =  al_load_bitmap("./bar_bottom.png");
	
	barbg_top= NULL;
	barbg_top =  al_load_bitmap("./bar_top.png");

	cur = 0;
	m_bNoteInHitZone = false;
	m_fWidth = w;
	m_fHeight =  h;
	m_fX = x;
	m_fY = y;
	if(!barbg_bottom)
	{
		return;
	
	}
	if(!barbg_top)
	{
		return;
	}
	char* str[4][2];
	str[0][0]="./blue_up.png";
	str[1][0]="./red_up.png";
	str[2][0]="./yellow_up.png";
	str[3][0]="./green_up.png";

	str[0][1]="./blue_down.png";
	str[1][1]="./red_down.png";
	str[2][1]="./yellow_down.png";
	str[3][1]="./green_down.png";
	
	string line;
			int input_dir;
			int input_x;
			int input_y;
			int input_type;


	ifstream myfile(filename);
	try{

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
				MyNotes.push_back(new note(str[input_dir][0],str[input_dir][1],input_dir,(m_fWidth/2)-(2*49)+(input_x*49),input_y));
			}
			else if(input_type == RAIL)
			{
				myfile >> input_dir;
				myfile >> input_x;
				myfile >> input_y;
				int input_length;
				myfile >> input_length;
				if(input_length == 0)
				{
					input_length = 2;
				}
				
				MyNotes.push_back(new RailNote(str[input_dir][0],str[input_dir][1],input_dir,((m_fWidth/2)-(2*49))+(input_x*49),input_y,input_length));
			}
			else
			{
				throw "Nem ismert tipus beolvasaskor";
			}
		}
		
	
		m_iBarLength = MyNotes.size();	
	}
	}
	catch(char* szoveg)
	{
		std::cout << "Hiba: " << szoveg;
	}

}

bar::~bar(void)
{
	for(int i=0;i<MyNotes.size();i++)
	{
		MyNotes.erase(MyNotes.begin()+i);	
	}
	al_destroy_bitmap(barbg_top);
	al_destroy_bitmap(barbg_bottom);
}

void bar::rendernote_up(int i,float x,float y)
{
	al_draw_bitmap(MyNotes[i]->GetBMP(),x,y,0);
}
void bar::rendernote_down(int i,float x,float y)
{
	al_draw_bitmap(MyNotes[i]->GetBMPDOWN(),x,y,0);
}
void bar::renderbarbg_x(float x)
{
	al_draw_bitmap(barbg_bottom,x,(m_fHeight-al_get_bitmap_height(barbg_bottom)),0);
	 for(int i=m_fHeight-(al_get_bitmap_height(barbg_bottom)+al_get_bitmap_height(barbg_top));i>-100;i-=al_get_bitmap_height(barbg_top))
	{
		al_draw_bitmap(barbg_top,x,i,0);
	} 
}

int bar::makemove_x(bool space_on,float x,bool KeyDown[4])
{
	int scorex=0;
	int* HitResult;
	 renderbarbg_x(x);
	 for(int i=0;i<m_iBarLength;i++)
	 {
		 MyNotes[i]->SetCoord(MyNotes[i]->GetX(),MyNotes[i]->GetY()+(120/49));
		
			 if(KeyDown[MyNotes[i]->GetDir()])
			 {
				 MyNotes[i]->DrawNote(DOWN);
			 }
			 else
			 {
				 MyNotes[i]->DrawNote(UP);
			 }
		
		 HitResult = MyNotes[i]->IsHit(space_on,KeyDown,m_fWidth,m_fHeight); // a hibás ütés miatt ad vissza pointert 
		 if(HitResult[1])
		 {
			m_bNoteInHitZone = true;
		 }
		if(HitResult[0]==1)
		{
			scorex = 1;
		}
		else if(HitResult[0] == -1)
		{
			scorex = -1;
		}
	 }
		
		
	 if(!m_bNoteInHitZone && space_on &&  KeyDown[MyNotes[0]->GetDir()])
	 {
		scorex = -1;  // ha leütötte a barhoz megfelelõ key-t és a space-t is de nincsen note a hit zone ba akkor -1 hiba
	 }
	 m_bNoteInHitZone=false;
	 
	 
return scorex;
}


void bar::renderbar(int sec)
{
	
}

