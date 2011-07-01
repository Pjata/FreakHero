#include "Game.h"
int main(int argc, char **argv)
{
	Game* MyGame = new Game();
	if(MyGame->IsReady())
	{
		
		
		MyGame->ChosingWhatToDo();
	}
	delete MyGame;

}