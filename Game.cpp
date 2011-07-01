#include "Game.h"
#include <fstream>
#include <iostream>
#include "DISPLAY_INFO.h"
#include "Scroll.h"
Game::Game()
{
	 for(int i=0;i<4;i++)
	 {
		key[i]=false;
	 }
   redraw = true;
   doexit = false;
   
           
   
	   
	GameReadyToRun = false;
   secund=0;
   AllegroInitSuccess=Init_Allegro();
   if(AllegroInitSuccess)
   {
		GameResInitSuccess = Init_GameRes();
		
		
		if(GameResInitSuccess)
		{
			ChoosedSong = 0; // a kezdeti song választása;
			Choose = 2; //Game menu
			GameReadyToRun = true;
		}
   
   }
 
}
bool Game::Init_Allegro()
{
	if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }
   if(!al_init_image_addon())
   {
	fprintf(stderr,"failed to initialize the image adodn\n");
	return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   secundum = al_create_timer(60/49);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
   ALLEGRO_MONITOR_INFO info;
  al_get_monitor_info(0, &info);
  ScreenWidth = info.x2 - info.x1; 
  ScreenHeight = info.y2 - info.y1; 
  al_set_new_display_flags(ALLEGRO_FULLSCREEN);
   display = al_create_display(ScreenWidth,ScreenHeight);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
     return -1;
   } 
   
   if(!al_install_audio()) 
	{
		fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}
 
        if(!al_init_acodec_addon()) 
	{
		fprintf(stderr, "failed to initialize audio codecs!\n");
		return -1;
	}
		if (!al_reserve_samples(4)) 
	{
                fprintf(stderr, "failed to reserve samples!\n");
		return -1;
	}
		if(!al_install_joystick())
		{
			fprintf(stderr, "failed to init joystick");
		return -1;
		}
   return 1;
}

bool Game::Init_GameRes()
{
	bg = al_load_bitmap("./bg.png");
  if(!bg)
   {
	al_destroy_display(display);
	al_destroy_timer(timer);
	return -1;
  }
  start = al_load_bitmap("./start.png");
   if(!start)
   {
	al_destroy_display(display);
	al_destroy_timer(timer);
	return -1;
  }
   edit = al_load_bitmap("./edit.png");
   if(!edit)
   {
	al_destroy_display(display);
	al_destroy_timer(timer);
	return -1;
  }
   al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    font = al_load_ttf_font("font.ttf",72,0 ); // load the font | Font from Larabie Free Fonts

	
	event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
     
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   menu = al_load_bitmap("menu.png");
   // -------------------------Player init
   MyPlayer = new Player();
   //press ek false tétele
   space_press = false;
  
   return 1;
   
}

void Game::GameLoop()
{
	// MY BAR INITALIZÁLÁSA
	
	
	MyBar = new BarBracket(SongNamesWithBrackets[0],SongNamesWithBrackets[1],SongNamesWithBrackets[2],SongNamesWithBrackets[3],ScreenWidth,ScreenHeight);
	//_______________________
	

	float mouseX=300,mouseY=300;
	if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return;
   }
	 al_register_event_source(event_queue, al_get_mouse_event_source());
	  bool mouse_down=false;
	int score=0;
	char* cscore = new char[1280];
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue,al_get_joystick_event_source());
 
   al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
 
   al_start_timer(timer);
   al_start_timer(secundum);
	int key_press=5;
	bool game_running=true;
	bool song_started=false;
	
   while(game_running)
   {
	  
		
		 if(!song_started)
		 {
			 MyPlayer->PlaySong(ChoosedSong);	
			 song_started = true;
		   
		 }
	     
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if(key[KEY_UP]) {
            
		//	 MyBar->SetKeyDown(0,true);
         }
 
         if(key[KEY_DOWN] ) {
            
		//	MyBar->SetKeyDown(1,true);
         }
 
         if(key[KEY_LEFT]) {
         //  MyBar->SetKeyDown(2,true);
         }
 
         if(key[KEY_RIGHT]) {
           // MyBar->SetKeyDown(3,true);
         }
 
         redraw = true;
		
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_4:
			
               key[KEY_UP] = true;
			   MyBar->SetKeyDown(0,true);
               break;
 
            case ALLEGRO_KEY_5:
               key[KEY_DOWN] = true;
			   MyBar->SetKeyDown(1,true);
               break;
 
            case ALLEGRO_KEY_6: 
               key[KEY_LEFT] = true;
			   MyBar->SetKeyDown(2,true);
               break;
 
            case ALLEGRO_KEY_7:
               key[KEY_RIGHT] = true;
			   MyBar->SetKeyDown(3,true);
               break;
			case ALLEGRO_KEY_SPACE:
				space_press = true;
				break;
         }
	 
      }
	   else if(ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
	  {
		  switch(ev.joystick.button)
		  {
				case 0:
					key[KEY_UP] = true;
					MyBar->SetKeyDown(0,true);
				break;
				
				case 1:
					 key[KEY_DOWN] = true;
					 MyBar->SetKeyDown(1,true);
				break;
				
				case 3:
					key[KEY_LEFT] = true;
					MyBar->SetKeyDown(2,true);
				break;

				case 2:
					key[KEY_RIGHT] = true;
					MyBar->SetKeyDown(3,true);

				break;


		  }
	  }
	   else if(ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP)
	   {
			switch(ev.joystick.button)
		  {
				case 0:
					key[KEY_UP] = false;
					MyBar->SetKeyDown(0,false);
				break;
				
				case 1:
					 key[KEY_DOWN] = false;
					 MyBar->SetKeyDown(1,false);
				break;
				
				case 3:
					key[KEY_LEFT] = false;
					MyBar->SetKeyDown(2,false);
				break;

				case 2:
					key[KEY_RIGHT] = false;
					MyBar->SetKeyDown(3,false);

				break;


		  }

	   }
	   else if(ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS)
	   {
		   switch(ev.joystick.stick)
		   {
			case 0:
			case 1:
			case 2:
				switch(ev.joystick.axis)
				{
				case 0:
				case 1:
				case 2:
					if(ev.joystick.pos == 1 || ev.joystick.pos == -1)
					{
						space_press = true;
					}
					else if(ev.joystick.pos == 0)
					{
						space_press = false;
					}
					break;
				}

				break;
		   
		   }
	   }
	   
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_4:
               key[KEY_UP] = false;
			 MyBar->SetKeyDown(0,false);
               break;
 
            case ALLEGRO_KEY_5:
               key[KEY_DOWN] = false;
			  MyBar->SetKeyDown(1,false);
               break;
 
            case ALLEGRO_KEY_6: 
               key[KEY_LEFT] = false;
			   MyBar->SetKeyDown(2,false);
               break;
 
            case ALLEGRO_KEY_7:
               key[KEY_RIGHT] = false;
			   MyBar->SetKeyDown(3,false);
               break;
			
			case ALLEGRO_KEY_SPACE:
			//	space_press=false;
				break;
 
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }
	   else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
				  mouseX=ev.mouse.x;
				  mouseY=ev.mouse.y;
	  
	  }
	   else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	   {
				mouse_down=true;
	   }
	   else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	   {
				mouse_down=false;
	   }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
		if(mouseX > 0 && mouseX < 100)
			{
				if(mouseY > 0 && mouseY < 40)
				{
					Choose=1;
					game_running = true;
				}
				else if(mouseY > 40 && mouseY < 80)
				{
					Choose=0;
					game_running = false;
					
				}
				else if(mouseY > 80 && mouseY < 120)
				{
					Choose=2;
					game_running = false;
				}

				
			}
         al_clear_to_color(al_map_rgb(250,247,215));
		 
		 al_draw_scaled_bitmap(bg,0,0,800,686,0,0,ScreenWidth,ScreenHeight,0); //ScreenWidth/2-(al_get_bitmap_width(bg)/2),ScreenHeight-al_get_bitmap_height(bg),0);
		  secund++;
		  int ScoreToAdd = MyBar->MoveNotesInBrackets(space_press,0);
		  if(ScoreToAdd == -1)
		  {
			  al_set_sample_instance_gain(MyPlayer->GetSampleInstance(ChoosedSong),0.0f);
		  }
		  else
		  {
			  al_set_sample_instance_gain(MyPlayer->GetSampleInstance(ChoosedSong),1.0f);
			  score+=ScoreToAdd;
		  }

		 
		 

	
		_itoa(score,cscore,10);
		 
		 al_draw_text(font, al_map_rgb(0,0,0), ScreenWidth/2-2*49-200, ScreenHeight/2-72,0, cscore);// draw the text
     //    al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
		al_draw_bitmap(start,0,0,0);
 		al_draw_bitmap(edit,0,40,0);
         al_draw_bitmap(menu,0,80,0);
		al_flip_display();
      }
   }
   MyPlayer->StopSong(ChoosedSong);
      delete MyBar;
}
void Game::GameEditor()
{
	// MY EDITOR INITALIZÁLÁSA
		MyEditor = new Editor(MyPlayer,ChoosedSong,ScreenWidth,ScreenHeight);

	//___________________________
	int WheelChange=0;
	int MouseYChange=0;
	float mouseX,mouseY;

	
   
  
	if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return;
   }

	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	 al_register_event_source(event_queue, al_get_mouse_event_source());
   al_register_event_source(event_queue, al_get_keyboard_event_source());

	  al_flip_display();
 bool mouse_down=false;
 int mouse_button = 0;
 bool game_running=true;
   al_start_timer(timer);
   bool song_started = false;
   bool stop_song = false;
   bool selecting = false;
   bool select_starts = true;
   bool d_pressed = false;
   bool copy_pressed = false;
   bool shift_pressed = false;
	float select_x1,select_x2,select_y1,select_y2,select_y1_without_offset; // selection hez kellenek hogy legyen egy régi egy uj koordom ha lenyomva megy a selection
   al_set_target_bitmap(al_get_backbuffer(display));
    while(game_running)
   {
	     if(!song_started)
	   {
		   MyPlayer->PlaySong(ChoosedSong);
		   song_started = true;
		   
	   }
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
				  mouseX= ev.mouse.x;
				  mouseY= ev.mouse.y;
				WheelChange = ev.mouse.dz;
				MouseYChange = ev.mouse.dy;
				 
				  if(mouseY<20)
				  {
			//		  MyEditor->OutputToFiles();
				  }
				 MyEditor->SetM(mouseX,mouseY);
				 
				 // redraw=true;
	  }

	  if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	  {
		    
		  mouse_down=true;
		  mouse_button = ev.mouse.button;
		
			 
	  }
	 
	  else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	  {
		 mouse_down=false;
		  
		 // MyEditor->HandleScroll(mouseX,mouseY);
		  if(selecting)
		  {
			select_starts=false;
			select_x2 = mouseX;
			select_y2 = mouseY - MyEditor->GetOffSet();
			if(mouse_button == 1)
			{
				for(int i=0;i<4;i++)
				{
				MyEditor->GetSelect()->Select(select_x1,select_y1,select_x2,select_y2,MyEditor->GetNoteBar(i));
				}
			}
			else if(mouse_button == 2)
			{
				
				MyEditor->GetSelect()->Deselect(select_x1,select_y1,select_x2,select_y2);
				
			}
			  
		  }
		  select_starts = true;
		 MyEditor->SetScroll(false);
	  }
	    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) 
		{
			switch(ev.keyboard.keycode) 
			{
					case ALLEGRO_KEY_SPACE:
					if(!stop_song)
					{
						 stop_song = true;
					}
					else
					{
						stop_song = false;
					}
					break;

					case ALLEGRO_KEY_LCTRL:
					case ALLEGRO_KEY_RCTRL:
						selecting = true;
						
						break;
					case ALLEGRO_KEY_D:
						
						d_pressed = true;
						
						break;
					case ALLEGRO_KEY_C:
						if(selecting)
							{
								copy_pressed = true;
						}
						break;
					case ALLEGRO_KEY_DELETE:
						for(int i=0;i<4;i++)
						{
						MyEditor->GetSelect()->DeleteSelected(MyEditor->GetNoteBar(i));
						}
						break;
					case ALLEGRO_KEY_LSHIFT:
					case ALLEGRO_KEY_RSHIFT:
						shift_pressed = true;
						break;
			}
		 }
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_LCTRL:
			case ALLEGRO_KEY_RCTRL:
				selecting = false;
				break;
			case ALLEGRO_KEY_LSHIFT:
			case ALLEGRO_KEY_RSHIFT:
				shift_pressed = false;
				break;
			}
		}
      
 
      if(redraw && al_is_event_queue_empty(event_queue)) {

		   redraw = false;
 
         al_clear_to_color(al_map_rgb(0,0,0));
		  
		  al_draw_scaled_bitmap(bg,0,0,800,686,0,0,ScreenWidth,ScreenHeight,0);
		 MyEditor->DrawBars();
		 if(mouse_down)
		 {
			

					if(mouse_button == 1 )
					{
						if(copy_pressed)
						{
							for (int i=0;i<4;i++)
							{
								MyEditor->GetSelect()->Copy(mouseY,MyEditor->GetOffSet(),1,i,MyEditor->GetNoteBar(i));
							}
							copy_pressed = false;
						}
						if(selecting)
						{
							if(select_starts)
							{
								select_x1=mouseX;
								select_y1=mouseY - MyEditor->GetOffSet();
								select_y1_without_offset= mouseY;
								for(int i=0;i<4;i++)
								{
									MyEditor->GetSelect()->Select(select_x1,select_y1,MyEditor->GetNoteBar(i));
								}
							select_starts= false;
							}
							//Selection drawing
						MyEditor->MouseSelectionDraw(select_x1,select_y1_without_offset,mouseX,mouseY);
						}
						else 
						{
							if(shift_pressed)
							{
								MyEditor->PlaceNote(mouseX,mouseY,RAIL);
							}
							else
							{
								MyEditor->PlaceNote(mouseX,mouseY,NORMAL);
							}
							 mouse_button = 0;
						//	 mouse_down = false;
						}
					}
					else if(mouse_button == 2)
					{
						if(selecting)
						{
							if(select_starts)
							{
								select_x1=mouseX;
								select_y1=mouseY - MyEditor->GetOffSet();
								select_y1_without_offset= mouseY;
								select_starts= false;
								MyEditor->GetSelect()->Deselect(select_x1,select_y1);
							}
						//Selection drawing
							MyEditor->MouseSelectionDraw(select_x1,select_y1_without_offset,mouseX,mouseY);
						}
						else 
						{
							 MyEditor->RemoveNote(mouseX,mouseY);
							 mouse_button = 0;
							
						}
					}
					else if(mouse_button == 3)
					{
						MyPlayer->TrackSong(ChoosedSong,MyEditor->GetOffSet(),mouseY);
						MyPlayer->DrawSongBar(ChoosedSong,MyEditor->GetOffSet());
					}
		
					 MyEditor->HandleScroll(mouseX,mouseY,MouseYChange);
						if(mouseX > 0 && mouseX < 100)
						{
							if(mouseY > 0 && mouseY < 40)
							{
								Choose=1;
								game_running = false;
								MyEditor->OutputToFiles();
							}
							else if(mouseY > 40 && mouseY < 80)
							{
								Choose=0;
								game_running = true;
					
							}
							else if(mouseY > 80 && mouseY < 120)
							{
								Choose=2;
								game_running = false;
							}
			
				
						}
				

		 }
		 else if(selecting)
				{
					if(d_pressed)
					{
						MyEditor->GetSelect()->DeleteSelection();
						d_pressed = false;
					}
					
				}
		 
		 else if(copy_pressed)
		 {
			 MyEditor->GetSelect()->Copy(mouseY,MyEditor->GetOffSet(),0);
		 }


		 if(WheelChange)
		 {
			
			 MyEditor->WheelScroll(WheelChange);
			 WheelChange = 0;
		}
		if(stop_song)
		{
			if(al_get_sample_instance_playing(MyPlayer->GetSampleInstance(ChoosedSong)))
			{
				MyPlayer->PauseSong(ChoosedSong);
				
			}
		}
		else
		{
			if(!al_get_sample_instance_playing(MyPlayer->GetSampleInstance(ChoosedSong)))
			{
				MyPlayer->PlaySong(ChoosedSong);
			}
		}
		MyPlayer->DrawSongBar(ChoosedSong,MyEditor->GetOffSet());
		 MyEditor->DrawNotes();
		 MyEditor->GetSelect()->DrawSelection(MyEditor->GetOffSet());
		 
		 al_draw_bitmap(start,0,0,0);
		 al_draw_bitmap(edit,0,40,0);
		 al_draw_bitmap(menu,0,80,0);
		   al_flip_display();
	  }
	}
	MyPlayer->StopSong(ChoosedSong);
	delete MyEditor;
}

void Game::ChosingWhatToDo()
{
	while(1)
	{
	if(Choose == 1) // 1 nel jatek 0 nal edit
		{
		
			GameLoop();
		}
	else if(Choose == 0)
		{
			GameEditor();
		}
	else if(Choose == 2)
		{
			GameMenu();
		}
	else if(Choose == 3)
		{
			GameEditor_RealTime();
		}
	}
}
void Game::GameMenu()
{
	if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return;
   }
	ALLEGRO_FONT* font = al_load_ttf_font("font.ttf",36,0 );
	ALLEGRO_BITMAP* menu_bg_light = al_load_bitmap("menu_bg_light.png");
	ALLEGRO_BITMAP* menu_bg_dark = al_load_bitmap("menu_bg_dark.png");
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	 al_register_event_source(event_queue, al_get_mouse_event_source());

	  al_flip_display();
	  bool NoSongSelected = true;
	  bool redraw = false;
	  float mouseX=0;
	  float mouseY=0;
	  float dmY=0;

	  Scroll *MyScrollBar = new Scroll(0,MyPlayer->GetSongs()->Size()*36,ScreenWidth-40,ScreenHeight-30,0+30,10,30,50);

	  while(NoSongSelected)
	  {
		 ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
			  if(ev.type == ALLEGRO_EVENT_TIMER) {
					  redraw = true;
				}
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
	  {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
              ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) 
	  {
				  mouseX = ev.mouse.x;
				  mouseY = ev.mouse.y;
				  dmY = ev.mouse.dy;
			redraw = true;
	  }	
	  else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	  {
		  if(ev.mouse.button == 1)
		  {
			  MyScrollBar->SetMouseDown(true);
			  for(int i=0;i<MyPlayer->GetSongs()->Size();i++)
			  {
				  if(mouseY>=i*36+MyScrollBar->GetOffSet() && mouseY<i*36+36+MyScrollBar->GetOffSet())
				{
					if( mouseX >= ((ScreenWidth/2)-150) && mouseX <= (ScreenWidth/2))
					{
					ChoosedSong = i;
					Choose = 1; // play
					NoSongSelected = false;
					}
					if(mouseX >= (ScreenWidth/2) && mouseX <=( (ScreenWidth/2)+100))
					{
						ChoosedSong = i;
						Choose = 0; // edit
						NoSongSelected = false;
					}
					if(mouseX >= (ScreenWidth/2+100) && mouseX <= ((ScreenWidth/2)+350))
					{
						ChoosedSong = i;
						Choose = 2; // real time edit
						NoSongSelected = false;
					}
				}
			  }
		  
		  
				  
		  }
		redraw = true;
	  }
	  else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	  {
		  if(ev.mouse.button == 1)
		  {
			  MyScrollBar->SetMouseDown(false);
			
		  }
	  }
		  
	  
				  
				  
			if( redraw &&  al_is_event_queue_empty(event_queue))
			{
				 MyScrollBar->HandleScroll(mouseX,mouseY,dmY);
				 al_clear_to_color(al_map_rgb(30,30,30));
				bool light = true;
				for(int i=0;i<MyPlayer->GetSongs()->Size();i++)
				{
					
					for(int x=0;x<ScreenWidth;x+=al_get_bitmap_width(menu_bg_light))
					{
						if(light)
						{
							al_draw_bitmap(menu_bg_light,x,i*36+10+MyScrollBar->GetOffSet(),0);
							
						}
						else
						{
							al_draw_bitmap(menu_bg_dark,x,i*36+10+MyScrollBar->GetOffSet(),0);
							
						}
						

					}
					if(light)
					{
						light = false;
					}
					else
					{
						light = true;
					}
					
						
					
					al_draw_text(font,al_map_rgb(240,184,75),40,i*36+MyScrollBar->GetOffSet(),0,MyPlayer->GetSongs()->GetSongName(i));
					al_draw_text(font,al_map_rgb(240,184,75),ScreenWidth/2-150,i*36+MyScrollBar->GetOffSet(),0,"Start");
					al_draw_text(font,al_map_rgb(240,184,75),ScreenWidth/2,i*36+MyScrollBar->GetOffSet(),0,"Edit");
					al_draw_text(font,al_map_rgb(240,184,75),ScreenWidth/2+100,i*36+MyScrollBar->GetOffSet(),0,"RealTime Edit");
					if(mouseY > i*36+MyScrollBar->GetOffSet() && mouseY < (i+1)*36+MyScrollBar->GetOffSet())
					{
					if(mouseX > ScreenWidth/2-150 && mouseX < ScreenWidth/2)
					{
						al_draw_text(font,al_map_rgb(243,43,43),ScreenWidth/2-150,i*36+MyScrollBar->GetOffSet(),0,"Start");
					}
					
					if(mouseX >  ScreenWidth/2 && mouseX < ScreenWidth/2+100)
					{
						al_draw_text(font,al_map_rgb(243,43,43),ScreenWidth/2,i*36+MyScrollBar->GetOffSet(),0,"Edit");
					}
					
					if(mouseX > ScreenWidth/2+100 && mouseX < ScreenWidth/2+350)
					{
						al_draw_text(font,al_map_rgb(243,43,43),ScreenWidth/2+100,i*36+MyScrollBar->GetOffSet(),0,"RealTime Edit");
					}
					
					}
				}
				 MyScrollBar->DrawScrollBar();
				 al_flip_display();
			}
	  }

	   for(int i=0;i<4;i++)
	{

		std:string tmp = MyPlayer->GetSongs()->GetSongName(ChoosedSong);
		char* char_i = new char[16];
		itoa(i,char_i,10);
		tmp += char_i;
		SongNamesWithBrackets.push_back(tmp);
		delete char_i;
		
	}

	   delete MyScrollBar;
	   al_destroy_bitmap(menu_bg_light);
	   al_destroy_bitmap(menu_bg_dark);
}

void Game::GameEditor_RealTime()
{
	//MyEditor_RealTime = new Editor(MyPlayer,ChoosedSong);
	std::vector<note*> Notes[4];
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_joystick_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	float mouseX=300;
	float mouseY=300;
	bool game_running = true;
	bool redraw = false;
	 al_start_timer(timer);
	MyPlayer->PlaySong(ChoosedSong);
	float y = 0;
	 al_flip_display();
	 al_set_target_bitmap(al_get_backbuffer(display));
	 char* str[4][2];
	str[0][0]="./blue_up.png";
	str[1][0]="./red_up.png";
	str[2][0]="./yellow_up.png";
	str[3][0]="./green_up.png";

	str[0][1]="./blue_down.png";
	str[1][1]="./red_down.png";
	str[2][1]="./yellow_down.png";
	str[3][1]="./green_down.png";
	ALLEGRO_BITMAP* barbg_bottom = al_load_bitmap("bar_bottom.png");
	ALLEGRO_BITMAP* barbg_top = al_load_bitmap("bar_top.png");
	int ButtonDown[4] = {0,0,0,0};
	while(game_running)
	{
		 ALLEGRO_EVENT ev;
		 al_wait_for_event(event_queue, &ev);
		  if(ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
		 {
			 switch(ev.joystick.button)
			 {
			 case 0:
				 ButtonDown[0] = 1;
				break;
			 case 1:
				  ButtonDown[1] = 1;
			 break;

			 case 3:
				  ButtonDown[2] = 1;
			break;
			 case 2:
				  ButtonDown[3] = 1;
				 break;
			
			
			 }
			redraw = true;
		 }
		 if(ev.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP)
		 {
			 switch(ev.joystick.button)
			 {
			 case 0:
				 ButtonDown[0] = 0;
				break;
			 case 1:
				  ButtonDown[1] = 0;
			 break;

			 case 3:
				  ButtonDown[2] = 0;
				break;
			 case 2:
				  ButtonDown[3] = 0;
				 break;
			 }
			
			}
		if(ev.type == ALLEGRO_EVENT_JOYSTICK_AXIS)
	   {
		   switch(ev.joystick.stick)
		   {
			case 0:
			case 1:
			case 2:
				switch(ev.joystick.axis)
				{
				case 0:
				case 1:
				case 2:
					if(ev.joystick.pos == 1 || ev.joystick.pos == -1)
					{
						
							if(ButtonDown[0])
							{
								Notes[0].push_back(new note(str[0][0],str[0][1],0,0,y));
							}
							if(ButtonDown[1])
							{
								Notes[1].push_back(new note(str[1][0],str[0][1],1,1,y));
							}
							if(ButtonDown[2])
							{
								Notes[2].push_back(new note(str[2][0],str[2][1],2,2,y));
							}
							if(ButtonDown[3])
							{
								 Notes[3].push_back(new note(str[3][0],str[3][1],3,3,y));
							}
						
						
			
					}
					
					else if(ev.joystick.pos == 0)
					{
						//space_press = false;
					}
					break;
				}

				break;
		   
		   }
	   }
		
		 else if(ev.type == ALLEGRO_EVENT_TIMER)
		 {
			redraw = true;
		 }
		 else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
			 ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
		 {
			 mouseX = ev.mouse.x;
			 mouseY = ev.mouse.y;
			redraw = true;
		 }
		 else
		 {
			redraw =  true;
		 }
	
	
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
		if(mouseX > 0 && mouseX < 100)
			{
				if(mouseY > 0 && mouseY < 40)
				{
					Choose=1;
					game_running = false;
					
				}
				else if(mouseY > 40 && mouseY < 80)
				{
					Choose=0;
					game_running = false;
					
				}
					 
    		
			}
		al_clear_to_color(al_map_rgb(0,0,0));
		
		  al_draw_scaled_bitmap(bg,0,0,800,686,0,0,ScreenWidth,ScreenHeight,0);
		 
		for(int i=0;i<4;i++)
		{
			float	x = (ScreenWidth/2)-(al_get_bitmap_width(barbg_bottom)*2) + al_get_bitmap_width(barbg_bottom) *i ;
			al_draw_bitmap(barbg_bottom,x,(ScreenHeight-al_get_bitmap_height(barbg_bottom)),0);
			for(int y=ScreenHeight-(al_get_bitmap_height(barbg_bottom)+al_get_bitmap_height(barbg_top));y>-100;y-=al_get_bitmap_height(barbg_top))
			{
				al_draw_bitmap(barbg_top,x,y,0);
			} 
		}
		 for(int i=0;i<4;i++)
		{
			for(int j = 0;j<Notes[i].size();j++)
			{
				al_draw_bitmap(Notes[i][j]->GetBMP(),(ScreenWidth/2)-(BarWidth*2)+i*BarWidth,Notes[i][j]->GetY()-y,0);
			}
		}
		// MyEditor->DrawNotes();
		 y -= (120/49);
		 al_flip_display();
		 
		 
		}
	}
	MyPlayer->StopSong(ChoosedSong);
		std::ofstream MyFiles[4];
	for(int i=0;i<4;i++)
	{

		MyFiles[i].open(SongNamesWithBrackets[i]);
		int it;

		for(it = 0;it<Notes[i].size();it++)
		{
			if(Notes[i][it]->GetType() == NORMAL)
			{
				MyFiles[i] << Notes[i][it]->GetType() << " " <<  Notes[i][it]->GetDir() << " " << Notes[i][it]->GetX() << " " << Notes[i][it]->GetY() << "\n";
			}
			else if(Notes[i][it]->GetType() == RAIL)
			{
				int* Prop = Notes[i][it]->GetProp();
				MyFiles[i] << Notes[i][it]->GetType() << " " <<  Notes[i][it]->GetDir() << " " << Notes[i][it]->GetX() << " " << Notes[i][it]->GetY() << " " << Prop[0] << "\n";
			}
		}
	}

	
	
//	delete MyEditor_RealTime;
}

Game::~Game()
{
	 al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   al_destroy_bitmap(bg);
   al_destroy_bitmap(start);
   al_destroy_bitmap(edit);
   al_destroy_bitmap(menu);
   delete MyPlayer;
   

  
}