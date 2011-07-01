#include "BarBracket.h"


BarBracket::BarBracket(std::string file_blue,std::string file_red, std::string file_yellow, std::string file_green,float w,float h)
{
	m_Bars[0] = new bar(414,0,file_blue,0,w,h);
	m_Bars[1] = new bar(414+49,0,file_red,0,w,h);
	m_Bars[2] = new bar(414+98,0,file_yellow,0,w,h);
	m_Bars[3] = new bar(414+147,0,file_green,0,w,h);
	m_fWidth = w;
	m_fHeight = h;
	for (int i=0;i<4;i++)
	{
		m_bKeyDown[i]=false;
	}
}


BarBracket::~BarBracket(void)
{
	for(int i=0;i<4;i++)
	{
		delete m_Bars[i];
	}
}

int BarBracket::MoveNotesInBrackets(bool space,float y)
{
	int score[4];
	for(int i=0;i<4;i++)
	{
		score[i]=0;
	}
	for(int i=0;i<4;i++)
	{
		// a kozepére rendeleli a bar-t
		score[i]=m_Bars[i]->makemove_x(space,(m_fWidth/2)-(2*49)+i*49,m_bKeyDown);
	}
	int scorex=0; // a score def
	int i=0;
	while(i<4 && score[i] != -1 )
	{
										//keresés ha van -1 vagyis hibás leütés akkor nem kap pontot
		if(score[i] == 1)
		{
			scorex += score[i];
		}				             // de addig is adjuk szépen a pontokat találat esetén
		i++;
	}
	
	if(i<4)
	{
		scorex = -1; // pont levonás tesztelés miatt
	}
	
	return scorex;
}

