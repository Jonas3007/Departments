#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <Fl/Fl_Return_Button.H>
#include <FL/Fl_Output.H>
#include <iostream>
#include "calculator.h"

void opButton_cb(Fl_Widget *w, void *data)
{
	char op = w->label()[0];
	Calculator calc;
	if (op == '=')
	{
		try
		{
			double result = calc.chooseOperator();
		}
		catch (const std::exception &e)
		{
			std::cerr << "Fehler: " << e.what() << std::endl;
		}
		return;
	}
	calc.setOperator(op);
}

void button_cb(Fl_Widget *w, void *data)
{ 
	Calculator calc;
	Fl_Input *input = static_cast<Fl_Input *>(data);

	if (!input)
		return;
	const char *label = w->label();
	const char *current = input->value();

	// asemble input string
	std::string new_input = current;
	new_input += label;

	input->value(new_input.c_str());

	// 'w' ist der Button, der gedrückt wurde
	// std::cout << "Button '" << w->label() << "' wurde gedrückt!" << std::endl;
}

int main(int argc, char **argv)
{
	// Main Window
	Fl_Window *window = new Fl_Window(500, 500, "Taschenrechner");

	// Input Fields
	Fl_Input *input = new Fl_Input(160, 115, 180, 40);
	input->box(FL_THIN_UP_BOX);

	

	// Output

	Fl_Output *output = new Fl_Output(360, 115, 80, 40);
	output->box(FL_THIN_UP_BOX);
	output->color(FL_WHITE);

	// "=" Box
	Fl_Box *equal_box = new Fl_Box(345, 115, 10, 40, "=");
	equal_box->labelfont(FL_BOLD);
	equal_box->box(FL_NO_BOX);

	// Numpad Group
	int grp_w = 180;
	int grp_h = 180;
	int start_x = (window->w() - grp_w) / 2; // Zentriert die Gruppe horizontal
	int start_y = (window->h() - grp_h) / 2; // Zentriert die Gruppe vertikal
	Fl_Group *nmpad_grp = new Fl_Group(start_x, start_y, grp_w, grp_h);
	nmpad_grp->box(FL_ENGRAVED_FRAME);

	// Coordinates relative to nmpad_grp
	int ngx = nmpad_grp->x();
	int ngy = nmpad_grp->y();
	// Numpad Buttons
	Fl_Button *b1 = new Fl_Button(ngx, ngy, 45, 45, "1");
	Fl_Button *b2 = new Fl_Button(ngx + 45, ngy, 45, 45, "2");
	Fl_Button *b3 = new Fl_Button(ngx + 90, ngy, 45, 45, "3");
	Fl_Button *b4 = new Fl_Button(ngx, ngy + 45, 45, 45, "4");
	Fl_Button *b5 = new Fl_Button(ngx + 45, ngy + 45, 45, 45, "5");
	Fl_Button *b6 = new Fl_Button(ngx + 90, ngy + 45, 45, 45, "6");
	Fl_Button *b7 = new Fl_Button(ngx, ngy + 90, 45, 45, "7");
	Fl_Button *b8 = new Fl_Button(ngx + 45, ngy + 90, 45, 45, "8");
	Fl_Button *b9 = new Fl_Button(ngx + 90, ngy + 90, 45, 45, "9");
	Fl_Button *b0 = new Fl_Button(ngx + 90, ngy + 135, 45, 45, "0");
	Fl_Button *bPlus = new Fl_Button(ngx + 135, ngy, 45, 45, "+");
	Fl_Button *bMinus = new Fl_Button(ngx + 135, ngy + 45, 45, 45, "-");
	Fl_Button *bMult = new Fl_Button(ngx + 135, ngy + 90, 45, 45, "*");
	Fl_Button *bDiv = new Fl_Button(ngx + 135, ngy + 135, 45, 45, "/");
	Fl_Button *bEqual = new Fl_Return_Button(ngx, ngy + 135, 90, 45, "=");

	nmpad_grp->begin();

	b1->callback(button_cb, input);
	b2->callback(button_cb, input);
	b3->callback(button_cb, input);
	b4->callback(button_cb, input);
	b5->callback(button_cb, input);
	b6->callback(button_cb, input);
	b7->callback(button_cb, input);
	b8->callback(button_cb, input);
	b9->callback(button_cb, input);
	b0->callback(button_cb, input);
	bPlus->callback(opButton_cb);
	bMinus->callback(opButton_cb);
	bMult->callback(opButton_cb);
	bDiv->callback(opButton_cb);
	bEqual->callback(opButton_cb);

	nmpad_grp->end();

	window->end();
	window->show(argc, argv);
	return Fl::run();
}