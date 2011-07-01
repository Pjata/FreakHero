#include "Player.h"
#include <string.h>
#include "DISPLAY_INFO.h"

Player::Player(void)
{
	MySongs = new Songs();
	musicbar = al_load_bitmap("./musicbar.png");
	 voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16,
      ALLEGRO_CHANNEL_CONF_2);
   if (!voice) {
      fprintf(stderr, "Could not create ALLEGRO_VOICE.\n");
      return ;
   }

   mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32,
      ALLEGRO_CHANNEL_CONF_2);
   if (!mixer) {
      fprintf(stderr, "al_create_mixer failed.\n");
      return ;
   }

   if (!al_attach_mixer_to_voice(mixer, voice)) {
      fprintf(stderr, "al_attach_mixer_to_voice failed.\n");
      return ;
   }
   /*
   for(int i=0;i<MySongs->Size();i++)
   {
	   m_vSampleInstance.push_back(al_create_sample_instance(MySongs->GetSong(i)));
		m_vSongPosition.push_back(0);	
	   if(!al_attach_sample_instance_to_mixer(m_vSampleInstance[i],mixer))
		{
			fprintf(stderr, "al_attach_sample_instance_to_mixer failed.\n");
         return ;
		}
   }
   */
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    font = al_load_ttf_font("font.ttf",72,0 ); // load the font | Font from Larabie Free Fonts
	old_song_number = -1;
}


Player::~Player(void)
{
	delete MySongs;
	al_destroy_bitmap(musicbar);
	al_destroy_sample_instance(m_vSampleInstance);
	al_destroy_mixer(mixer);
    al_destroy_voice(voice);
}

void Player::LoadSong(int song_number)
{
	if(old_song_number == -1)
	{
		ALLEGRO_SAMPLE* sample = al_load_sample(MySongs->GetSongName(song_number));
		m_vSampleInstance = al_create_sample_instance(sample);
		m_vSongPosition =0;
		old_song_number = song_number;
		 if(!al_attach_sample_instance_to_mixer(m_vSampleInstance,mixer))
		{
			fprintf(stderr, "al_attach_sample_instance_to_mixer failed.\n");
         return ;
		}
	}
	else if(old_song_number != song_number)
	{
		al_stop_sample_instance(m_vSampleInstance);
		al_destroy_sample_instance(m_vSampleInstance);
			

		ALLEGRO_SAMPLE* sample = al_load_sample(MySongs->GetSongName(song_number));
		m_vSampleInstance =al_create_sample_instance(sample);

		m_vSongPosition = 0;

		old_song_number = song_number;
		 if(!al_attach_sample_instance_to_mixer(m_vSampleInstance,mixer))
		{
			fprintf(stderr, "al_attach_sample_instance_to_mixer failed.\n");
         return ;
		}

	}
}
void Player::PlaySong(int song_number)
{
		LoadSong(song_number);
		al_set_sample_instance_position(m_vSampleInstance,m_vSongPosition);
		al_play_sample_instance(m_vSampleInstance);

}

void Player::PauseSong(int song_number)
{
	m_vSongPosition = al_get_sample_instance_position(m_vSampleInstance);
	al_stop_sample_instance(m_vSampleInstance);

}

void Player::StopSong(int song_number)
{
	m_vSongPosition = 0;
	al_stop_sample_instance(m_vSampleInstance);
}

void Player::DrawSongBar(int song_number,float OffSet)
{
	float length = al_get_sample_instance_length(m_vSampleInstance);
	float time = al_get_sample_instance_time(m_vSampleInstance);
	int pos=0;
	if(al_get_sample_instance_position(m_vSampleInstance))
	{
		pos = al_get_sample_instance_position(m_vSampleInstance);
	}
	else
	{
		pos = m_vSongPosition;
	}
	float time_spend = ((pos / length)) * time;
	float x = (GetScreenWidth() / 2 ) - BarWidth*2;
	float y = (time_spend  * ((120/49)*60)) * -1 + GetScreenHeight()-BarWidth + OffSet; // a megfelelõ x coordinataja a a song barnak
	al_draw_bitmap(musicbar,x,y,0);
	//______ a perc másodperc kijelzõ

	div_t result;
	result = div(time_spend,60);
	int min = result.quot;
	int sec = result.rem;
	char *cmin = new char[64];
	_itoa(min,cmin,10);
	char *csec = new char[64];
	_itoa(sec,csec,10);
	char* text = new char[130];
	
	strcpy(text,cmin);
	strcat(text,":");
	strcat(text,csec);
	al_draw_text(font,al_map_rgb(38,45,84),x+4*BarWidth,y-30,0,text);

}



void Player::TrackSong(int song_number,float OffSet,float mY)
{
	float length = al_get_sample_instance_length(m_vSampleInstance);
	float time = al_get_sample_instance_time(m_vSampleInstance);
	
	
 	float length_in_y = ((time) * ((120/49)*60));
	float y = mY;
	float pos = ((((y-649-OffSet)/-1)*length)/time)/((120/49)*60) ;
	
	m_vSongPosition = pos;
 	al_set_sample_instance_position(m_vSampleInstance,pos);



}