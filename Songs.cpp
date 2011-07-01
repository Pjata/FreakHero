#include "Songs.h"
#include <iostream>
#include <fstream>

using namespace std;

Songs::Songs(void)
{
	fstream myfile("./songlist.txt");
	
	
if(myfile.is_open())
{
	while(!myfile.eof())
	{
		char* tmp = new char[64];
		myfile >> tmp;
		
		m_cSongNames.push_back(tmp);
	}
	
/*	for(int i=0;i<m_cSongNames.size();i++)
	{
	//	ALLEGRO_SAMPLE* sample = al_load_sample(SongNames[i]);
		m_vSongs.push_back(al_load_sample(m_cSongNames[i]));
//		delete sample;
	}
	*/
	m_iSize = m_cSongNames.size();
}
}


Songs::~Songs(void)
{
//	m_vSongs.clear();
	m_cSongNames.clear();
}
