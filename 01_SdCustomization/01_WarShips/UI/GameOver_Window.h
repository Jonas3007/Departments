#pragma once
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Box.H>


class GameMaster;	
class GameOverWindow : public Fl_Window
{
	public:
		GameOverWindow();
		
	private:
		static void closewindow_cb(Fl_Widget *widget, void *data);	

		Fl_Box *displayWinnerBox;
		Fl_Box *continuePlaying;
		Fl_Button *yes;
		Fl_Button *no;
};