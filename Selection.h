#ifndef INC_SELECTION_H
#define INC_SELECTION_H

#include "note.h"
#include <vector>
using namespace std;

class Selection
{
public:
	Selection(void);
	~Selection(void);
	
	inline ALLEGRO_BITMAP* GetBMPSELECTED() const {return selected;}

	void Select(float x,float y,vector<note*> &From);
	void Select(float x1,float y1,float x2,float y2,vector<note*> &From);
	void Deselect(float x,float y);
	void Deselect(float x1,float y1,float x2,float y2);

	void DeleteSelection();
	void Copy(float mY,float OffSet,bool CopyFinished,int type,std::vector<note*> &NoteBar);
	void Copy(float mY,float OffSet,bool CopyFinished);
	void Cut(vector<note*>  &CutFrom);
	void Paste(float y);
	void DeleteSelected(std::vector<note*> &NoteBar);

	void DrawSelection(float OffSet);

private:
	std::vector<note*> m_vSelection;
	ALLEGRO_BITMAP* selected;
	

};

#endif