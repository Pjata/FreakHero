#ifndef INC_BARBRACKET_H
#define INC_BARBRACKET_H
#include "bar.h"
class BarBracket
{
public:
	BarBracket(std::string file_blue,std::string file_red, std::string file_yellow, std::string file_green,float w,float h);
	~BarBracket(void);
	bool GetKeyDown(int i) {return m_bKeyDown[i];}
	void SetKeyDown(int i,bool b) {m_bKeyDown[i]=b;}

	int MoveNotesInBrackets(bool space,float y);

private:
	bar* m_Bars[4];
	bool m_bKeyDown[4];
	float m_fWidth;
	float m_fHeight;
};

#endif

