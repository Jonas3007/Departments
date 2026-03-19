// UI_MainWindow.cpp
#include "UI_MainWindow.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <string>

#include "Callbacks.h"
#include "Appcontext.h"

// Hilfsfunktion: erzeugt den Numpad-Block dynamisch
static void build_numpad(Fl_Group *grp, AppContext *ctx)
{
	// Geometrie
	const int cell = 45;
	const int x0 = grp->x();
	const int y0 = grp->y();

	// 4x4 Grid (Labels)
	// Spalte 0..3, Zeile 0..3
	const char *grid[4][4] = {
		{"7", "8", "9", "+"},
		{"4", "5", "6", "-"},
		{"1", "2", "3", "*"},
		{"()", "0", "^", "/"}};

	grp->begin();
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			const char *lbl = grid[r][c];
			int bx = x0 + c * cell;
			int by = y0 + r * cell;

			Fl_Button *b = new Fl_Button(bx, by, cell, cell, lbl);

			// Besondere Behandlung für Klammer-Button
			if (std::string(lbl) == "()")
			{
				b->callback(bracket_cb, ctx);
			}
			else
			{
				b->callback(append_cb, ctx);
			}
				
		}
	}
	grp->end();
}

Fl_Window *buildMainWindow(AppContext *ctx)
{
	// --- Hauptfenster ---
	Fl_Window *window = new Fl_Window(500, 500, "Taschenrechner");

	// --- Eingabe ---
	Fl_Input *input = new Fl_Input(160, 115, 180, 40);
	input->box(FL_THIN_UP_BOX);

	// --- Ausgabe ---
	Fl_Output *output = new Fl_Output(360, 115, 80, 40);
	output->box(FL_THIN_UP_BOX);
	output->color(FL_WHITE);

	// "=" Box zwischen Ein- und Ausgabe
	Fl_Box *equal_box = new Fl_Box(345, 115, 10, 40, "=");
	equal_box->labelfont(FL_BOLD);
	equal_box->box(FL_NO_BOX);

	// --- Buttons rechts ---
	// History
	Fl_Button *bHistory = new Fl_Button(360, 160, 80, 45, "History");
	bHistory->box(FL_THIN_UP_BOX);
	bHistory->callback(history_cb, ctx);

	// Clear
	Fl_Button *bClear = new Fl_Button(360, 205, 80, 45, "C");
	bClear->box(FL_THIN_UP_BOX);
	bClear->labelfont(FL_BOLD);
	bClear->labelcolor(FL_RED);
	bClear->callback(clear_cb, ctx);

	// Backspace
	Fl_Button *bBackspace = new Fl_Button(360, 250, 80, 45, "⌫");
	bBackspace->box(FL_THIN_UP_BOX);
	bBackspace->labelfont(FL_BOLD);
	bBackspace->callback(backspace_cb, ctx);

	// Gleichheits-/Return-Button
	Fl_Return_Button *bEqual = new Fl_Return_Button(360, 295, 80, 45, "=");
	bEqual->box(FL_THIN_UP_BOX);
	bEqual->labelfont(FL_BOLD);
	bEqual->callback(calculateResult_cb, ctx);
	
	Fl_Button *bDot = new Fl_Button(110, 295, 45, 45, ".");
	bDot->box(FL_THIN_UP_BOX);
	bDot->callback(append_cb, ctx);

	// QuickSave (QS)
	Fl_Button *qSave = new Fl_Button(110, 115, 45, 40, "QS");
	qSave->box(FL_THIN_UP_BOX);
	qSave->callback(saveHistory_cb, ctx);

	// --- Numpad Group (zentriert) ---
	const int grp_w = 180;
	const int grp_h = 180;
	const int start_x = (window->w() - grp_w) / 2;
	const int start_y = (window->h() - grp_h) / 2;

	Fl_Group *nmpad_grp = new Fl_Group(start_x, start_y, grp_w, grp_h);
	nmpad_grp->box(FL_ENGRAVED_FRAME);
	build_numpad(nmpad_grp, ctx);

	// --- File-Mode / Berechnung aus Datei ---
	// Checkbox: "Calculate from file"
	Fl_Check_Button *checkFileCalc = new Fl_Check_Button(110, 360, 160, 30, "Calculate from file");
	checkFileCalc->callback(checkBox_cb, ctx);

	// Auswahlfeld (Dropdown)
	Fl_Choice *fileChoice = new Fl_Choice(110, 390, 160, 35, "File:");
	fileChoice->deactivate();
	fileChoice->hide();
	fileChoice->callback(fileChoice_cb, ctx);

	// Button zum Hinzufügen neuer Files
	Fl_Button *addFileButton = new Fl_Button(270, 390, 35, 35, "+");
	addFileButton->deactivate();
	addFileButton->hide();
	addFileButton->callback(addFile_cb, ctx);

	// Eingabefeld für neuen Dateinamen (erscheint beim ersten Klick auf "+")
	Fl_Input *fileInput = new Fl_Input(110, 390, 160, 35);
	fileInput->deactivate();
	fileInput->hide();

	// --- Kontext verbinden ---
	ctx->input = input;
	ctx->output = output;
	ctx->fileChoice = fileChoice;
	ctx->newFileInput = fileInput;
	ctx->addFileButton = addFileButton;
	// ctx->fileMode bleibt false bis die Checkbox aktiv ist

	window->end();
	return window;
}