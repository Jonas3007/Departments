#include "GameOver_Window.h"
#include "GameMaster.h"

GameOverWindow::GameOverWindow(GameMaster *gameMaster) : Fl_Window(350, 200, "Game Over")
{
	labelfont(FL_BOLD);
	displayWinnerBox = new Fl_Box(50, 20, 250, 50);
	if(gameMaster->Player1.AllShipsDestroyed)
	{
		displayWinnerBox->copy_label((gameMaster->Player2.Name + " wins!").c_str());
	}
	else if(gameMaster->Player2.AllShipsDestroyed)
	{
		displayWinnerBox->copy_label((gameMaster->Player1.Name + " wins!").c_str());
	}
	continuePlaying = new Fl_Box(50, 80, 250, 20, "Continue playing?");
	yes = new Fl_Button(50, 110, 100, 30, "Yes");
	no = new Fl_Button(200, 110, 100, 30, "No");
	continuePlaying->labelsize(14);
	continuePlaying->labelfont(FL_BOLD);
	yes->box(FL_PLASTIC_UP_BOX);
	no->box(FL_PLASTIC_UP_BOX);	
	yes->callback(continue_cb, gameMaster);
	no->callback(closewindow_cb, gameMaster);
	end();
	
}

void GameOverWindow::closewindow_cb(Fl_Widget *widget, void *data)
{
	exit(0);
}	