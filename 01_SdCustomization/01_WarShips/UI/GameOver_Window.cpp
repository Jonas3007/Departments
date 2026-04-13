#include "GameOver_Window.h"


GameOverWindow::GameOverWindow() : Fl_Window(350, 200, "Game Over")
{
	labelfont(FL_BOLD);
	displayWinnerBox = new Fl_Box(50, 20, 250, 50);
	
	continuePlaying = new Fl_Box(50, 80, 250, 20, "Continue playing?");
	yes = new Fl_Button(50, 110, 100, 30, "Yes");
	no = new Fl_Button(200, 110, 100, 30, "No");
	continuePlaying->labelsize(14);
	continuePlaying->labelfont(FL_BOLD);
	yes->box(FL_PLASTIC_UP_BOX);
	no->box(FL_PLASTIC_UP_BOX);	

	end();
	
}

void GameOverWindow::closewindow_cb(Fl_Widget *widget, void *data)
{
	exit(0);
}	