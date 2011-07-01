#ifndef INC_DISPLAY_INFO
#define INC_DISPLAY_INFO
#include <allegro5\allegro5.h>

inline float GetScreenWidth()
{
	 ALLEGRO_MONITOR_INFO info;
  al_get_monitor_info(0, &info);
  float ScreenWidth = info.x2 - info.x1; /* Assume this is 1366 */
  //ScreenHeight = info.y2 - info.y1; /* Assume this is 768 */
  return ScreenWidth;
}

inline float GetScreenHeight()
{
	 ALLEGRO_MONITOR_INFO info;
  al_get_monitor_info(0, &info);
  //ScreenWidth = info.x2 - info.x1; /* Assume this is 1366 */
 float ScreenHeight = info.y2 - info.y1; /* Assume this is 768 */
  return ScreenHeight;
}

const float BarWidth = 49;


#endif