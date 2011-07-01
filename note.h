#ifndef NOTE_H
#define NOTE_H
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
enum {UP,DOWN};
enum {NORMAL,RAIL};
class note
{
public:
	
	note();
	note(char* route,int dir);
	note(char* route,char* route_down,int dir,float x,float y);
	~note(void);
	
	inline	ALLEGRO_BITMAP* GetBMP() {return bmp;}
	inline	ALLEGRO_BITMAP* GetBMPDOWN() {return bmpdown;}
	
	inline void SetMove(bool m) {m_bMove=m;}
	inline void SetHit(bool h) {m_bHit=h;}
	inline void SetCoord(float x,float y) {m_fX=x;m_fY=y;}
	
	inline bool GetMove() {return m_bMove;} const
	inline float GetX() {return m_fX;}	const
	inline float GetY() {return m_fY;}	const
	inline int GetDir() {return m_iDir;}	const
	inline bool GetHit() {return m_bHit;}	const
	inline bool GetSelected() {return m_bSelected;} const
	inline int GetType() {return m_iType;} const
	
	inline void SetSelect(bool b) {m_bSelected = b;}
	
	virtual inline int* GetProp();
	virtual void  DrawNote(int type);
	virtual int* IsHit(bool space_on,bool KeyDown[4],float w,float h);

protected:
	ALLEGRO_BITMAP* bmp;
	ALLEGRO_BITMAP* bmpdown;
	int m_iDir;
	bool m_bMove;
	float m_fX,m_fY;
	bool m_bHit;
	int id[2];
	bool m_bSelected;
	int m_iType;
};
#endif
