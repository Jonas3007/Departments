#include "UI_HistoryWindow.h"
#include "Appcontext.h"
#include <string>
#include "historyService.h"
using namespace std;	

HistoryWindow::HistoryWindow(AppContext* ctx)
	: Fl_Window(245, 450, "History"), ctx(ctx)
{
	// Dateiname
	filenameInput = new Fl_Input(10, 10, 135, 30);
	filenameInput->box(FL_THIN_UP_BOX);

	// Save Button
	Fl_Button* saveBtn = new Fl_Button(150, 10, 40, 30, "Save");
	saveBtn->box(FL_THIN_UP_BOX);
	saveBtn->callback(cb_save, this);

	// Refresh Button
	Fl_Button* refreshBtn = new Fl_Button(195, 10, 35, 30, "⟳");
	refreshBtn->box(FL_THIN_UP_BOX);
	refreshBtn->callback(cb_refresh, this);

	// History-Ausgabe
	historyOutput = new Fl_Multiline_Output(10, 50, 220, 390);
	historyOutput->box(FL_THIN_UP_BOX);
	historyOutput->color(FL_WHITE);

	// Start: Default-History laden
	refresh();

	end();
}

// ----------------------------
// interne Funktionen
// ----------------------------

void HistoryWindow::refresh()
{
	string file = filenameInput->value();
	if (file.empty())
	{
		 file = "history";
	}
	   

	ctx->history->setCurrentFile(file);
	historyOutput->value(ctx->history->GetHistory().c_str());
}

void HistoryWindow::save()
{
	string file = filenameInput->value();
	if (file.empty())
		file = "history";

	ctx->history->setCurrentFile(file);
	ctx->history->SaveHistory();

	refresh();
}

// ----------------------------
// statische Callback-Wrapper
// ----------------------------

void HistoryWindow::cb_refresh(Fl_Widget*, void* data)
{
	auto* self = static_cast<HistoryWindow*>(data);
	self->refresh();
}

void HistoryWindow::cb_save(Fl_Widget*, void* data)
{
	auto* self = static_cast<HistoryWindow*>(data);
	self->save();
}