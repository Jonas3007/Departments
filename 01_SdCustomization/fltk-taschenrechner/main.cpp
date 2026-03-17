#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <Fl/Fl_Return_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Round_Button.H>
#include <iostream>
#include "calculator.h"
#include <cmath>
#include <historyService.h>
#include <Fl/Fl_Multiline_Output.H>
#include <Fl/Fl_Check_Button.H>
#include <Fl/Fl_Choice.H>

using namespace std;
//structs
struct HistoryContext
{
	HistoryService *historyService;
	Fl_Input *filenameInput;
	Fl_Multiline_Output *historyOutput;
};

struct Context
{
	Calculator *calc;
	Fl_Input *input;
	Fl_Output *output;
	HistoryService *historyService;
};

//callbacks and helper functions
void button_cb(Fl_Widget *w, void *data)
{
	Context *ctx = static_cast<Context *>(data);

	if (!ctx->input)
		return;
	const char *label = w->label();
	const char *current = ctx->input->value();

	// asemble input string
	std::string new_input = current;
	new_input += label;
	ctx->input->value(new_input.c_str());
}

void chooseCalculator(string inputString, Context *ctx)
{
	if (inputString[0] == '+' || inputString[0] == '-' || inputString[0] == '*' || inputString[0] == '/')
	{
		ctx->calc->useResultForNextOperation(inputString);
	}
	else if (ctx->calc->checkForMultipleOperators(inputString) > 1)
	{
		ctx->calc->calculateTerm(inputString);
	}
	else if (inputString.find('^') != std::string::npos)
	{
		ctx->calc->calculateTerm(inputString);
	}
	else if (inputString.find('(') != std::string::npos || inputString.find(')') != std::string::npos)
	{
		ctx->calc->calculateTerm(inputString);
	}
	else
	{
		ctx->calc->splitInput(inputString);
		ctx->calc->chooseOperration();
	}
}

void calculateResult_cb(Fl_Widget *w, void *data)
{
	Context *ctx = static_cast<Context *>(data);
	std::string inputString = ctx->input->value();
	bool validInput = ctx->calc->checkForInvalidInput(inputString);

	if (validInput == false)
	{
		ctx->output->value("Invalid");
		ctx->historyService->AddtoTempHistory(inputString, "Invalid");
		return;
	}
	else
	{
		chooseCalculator(inputString, ctx);

		ctx->historyService->AddtoTempHistory(inputString, ctx->calc->Result);
	}

	std::string result = std::to_string(ctx->calc->Result);
	ctx->output->value(result.c_str());
}

void clear_cb(Fl_Widget *w, void *data)
{
	Context *ctx = static_cast<Context *>(data);
	ctx->input->value("");
}

void bracket_cb(Fl_Widget *w, void *data)
{
	Context *ctx = static_cast<Context *>(data);
	std::string inputString = ctx->input->value();
	int openBracketPos = inputString.find_last_of('(');
	int closeBracketPos = inputString.find_last_of(')');
	if (closeBracketPos > openBracketPos && closeBracketPos != std::string::npos)
	{
		ctx->input->value((inputString + "(").c_str());
	}
	else if (openBracketPos > closeBracketPos && openBracketPos != std::string::npos)
	{
		ctx->input->value((inputString + ")").c_str());
	}
	else
	{
		ctx->input->value((inputString + "(").c_str());
	}
}

void backspace_cb(Fl_Widget *w, void *data)
{
	Context *ctx = static_cast<Context *>(data);
	std::string currentInput = ctx->input->value();
	if (!currentInput.empty())
	{
		currentInput.pop_back();				 // Entfernt das letzte Zeichen
		ctx->input->value(currentInput.c_str()); // Aktualisiert das Eingabefeld
	}
}

void At_cb(Fl_Widget *w, void *data)
{
	Context *ctx = static_cast<Context *>(data);
	std::string inputString = ctx->input->value();
	const char *label = w->label();
	const char *current = ctx->input->value();

	// asemble input string
	std::string new_input = current;
	new_input += label;
	ctx->input->value(new_input.c_str());
}

void saveHistory_cb(Fl_Widget *w, void *data)
{
	const char *label = w->label();
	HistoryContext *htx = static_cast<HistoryContext *>(data);
	string inputfield = htx->filenameInput->value();
	if (label == "QS")
	{
		htx->historyService->setCurrentFile("history");
		htx->historyService->SaveHistory();
		return;
	}
	if (!inputfield.empty())
	{
		htx->historyService->setCurrentFile(inputfield);
		htx->historyService->SaveHistory();
	}
	else
	{
		htx->historyService->setCurrentFile("history");
		htx->historyService->SaveHistory();
	}
}

void refresh_cb(Fl_Widget *w, void *data)
{
	HistoryContext *htx = static_cast<HistoryContext *>(data);

	string historyfile = htx->filenameInput->value();
	if (!historyfile.empty())
	{
		htx->historyService->setCurrentFile(historyfile);
		htx->historyOutput->value(htx->historyService->GetHistory().c_str());
	}
	else
	{
		htx->historyService->setCurrentFile("history");
		cout << htx->historyService->filePath << endl;
		htx->historyOutput->value(htx->historyService->GetHistory().c_str());
	}
}

void history_cb(Fl_Widget *w, void *data)
{
	HistoryContext *htx = static_cast<HistoryContext *>(data);
	HistoryService *service = htx->historyService;

	// Create a new window for history
	Fl_Window *historyWindow = new Fl_Window(245, 450, "History");

	// Inputfield to set filename for history. if left empty, default "history.txt" will be used
	Fl_Input *filenameInput = new Fl_Input(10, 10, 135, 35);
	filenameInput->box(FL_THIN_UP_BOX);
	htx->filenameInput = filenameInput;

	// Create an output widget to display history
	Fl_Multiline_Output *historyOutput = new Fl_Multiline_Output(10, 50, 220, 400);
	historyOutput->box(FL_THIN_UP_BOX);
	historyOutput->color(FL_WHITE);
	htx->historyOutput = historyOutput;

	// Button to save temp history to file
	Fl_Button *saveHistoryButton = new Fl_Button(145, 10, 45, 35, "Save");
	saveHistoryButton->box(FL_THIN_UP_BOX);
	saveHistoryButton->callback(saveHistory_cb, htx);

	// Refresh button to update history output after saving new history
	Fl_Button *refreshButton = new Fl_Button(190, 10, 35, 35, "⟳");
	refreshButton->box(FL_THIN_UP_BOX);
	refreshButton->callback(refresh_cb, htx);

	historyWindow->position(520, 30);
	historyWindow->show();
}

void checkBox_cb(Fl_Widget *w, void *data)
{
	Fl_Check_Button *checkButton = static_cast<Fl_Check_Button *>(w);
	Fl_Choice *fileChoice = static_cast<Fl_Choice *>(data);
	bool isChecked = checkButton->value();
	if (isChecked == true)
	{
		fileChoice->activate();
		fileChoice->show();
		cout << "Calculate from file: EIN" << endl;
	}
	else
	{
		fileChoice->deactivate();
		fileChoice->hide();
		cout << "Calculate from file: AUS" << endl;
	}
	
}


int main(int argc, char **argv)
{
	// Insancing Calculator and HistoryService
	HistoryService historyService;
	Calculator calc;
	// Main Window
	Fl_Window *window = new Fl_Window(500, 500, "Taschenrechner");

	// Input Fields
	Fl_Input *input = new Fl_Input(160, 115, 180, 40);
	input->box(FL_THIN_UP_BOX);


	// Output

	Fl_Output *output = new Fl_Output(360, 115, 80, 40);
	output->box(FL_THIN_UP_BOX);
	output->color(FL_WHITE);
	output->value();

	HistoryContext htx;
	htx.historyService = &historyService;
	htx.filenameInput = nullptr;
	htx.historyOutput = nullptr;
	Context ctx;
	ctx.calc = &calc;
	ctx.input = input;
	ctx.output = output;
	ctx.historyService = &historyService;

	// History Button
	Fl_Button *bHistory = new Fl_Button(360, 160, 80, 45);
	bHistory->label("History");
	bHistory->box(FL_THIN_UP_BOX);
	bHistory->callback(history_cb, &htx);

	// Quckisave Button
	Fl_Button *qSave = new Fl_Button(110, 115, 45, 40, "QS");
	qSave->box(FL_THIN_UP_BOX);
	qSave->callback(saveHistory_cb, &htx);

	// Backspace Button
	Fl_Button *bBackspace = new Fl_Button(360, 250, 80, 45);
	bBackspace->label("⌫");
	bBackspace->box(FL_THIN_UP_BOX);
	bBackspace->labelfont(FL_BOLD);
	bBackspace->callback(backspace_cb, &ctx);

	// Clear Button
	Fl_Button *bClear = new Fl_Button(360, 205, 80, 45, "C");
	bClear->box(FL_THIN_UP_BOX);
	bClear->labelfont(FL_BOLD);
	bClear->labelcolor(FL_RED);

	bClear->callback(clear_cb, &ctx);

	// Equal Button
	Fl_Button *bEqual = new Fl_Return_Button(360, 295, 80, 45, "=");
	bEqual->box(FL_THIN_UP_BOX);
	bEqual->labelfont(FL_BOLD);
	bEqual->callback(calculateResult_cb, &ctx);

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
	Fl_Button *b1 = new Fl_Button(ngx, ngy, 45, 45, "7");
	Fl_Button *b2 = new Fl_Button(ngx + 45, ngy, 45, 45, "8");
	Fl_Button *b3 = new Fl_Button(ngx + 90, ngy, 45, 45, "9");
	Fl_Button *b4 = new Fl_Button(ngx, ngy + 45, 45, 45, "4");
	Fl_Button *b5 = new Fl_Button(ngx + 45, ngy + 45, 45, 45, "5");
	Fl_Button *b6 = new Fl_Button(ngx + 90, ngy + 45, 45, 45, "6");
	Fl_Button *b7 = new Fl_Button(ngx, ngy + 90, 45, 45, "1");
	Fl_Button *b8 = new Fl_Button(ngx + 45, ngy + 90, 45, 45, "2");
	Fl_Button *b9 = new Fl_Button(ngx + 90, ngy + 90, 45, 45, "3");
	Fl_Button *b0 = new Fl_Button(ngx + 45, ngy + 135, 45, 45, "0");
	Fl_Button *bBracket = new Fl_Button(ngx, ngy + 135, 45, 45, "()");
	Fl_Button *bAt = new Fl_Button(ngx + 90, ngy + 135, 45, 45, "^");
	Fl_Button *bPlus = new Fl_Button(ngx + 135, ngy, 45, 45, "+");
	Fl_Button *bMinus = new Fl_Button(ngx + 135, ngy + 45, 45, 45, "-");
	Fl_Button *bMult = new Fl_Button(ngx + 135, ngy + 90, 45, 45, "*");
	Fl_Button *bDiv = new Fl_Button(ngx + 135, ngy + 135, 45, 45, "/");

	// nmpad group begin and callbacks
	nmpad_grp->begin();

	b1->callback(button_cb, &ctx);
	b2->callback(button_cb, &ctx);
	b3->callback(button_cb, &ctx);
	b4->callback(button_cb, &ctx);
	b5->callback(button_cb, &ctx);
	b6->callback(button_cb, &ctx);
	b7->callback(button_cb, &ctx);
	b8->callback(button_cb, &ctx);
	b9->callback(button_cb, &ctx);
	b0->callback(button_cb, &ctx);
	bPlus->callback(button_cb, &ctx);
	bMinus->callback(button_cb, &ctx);
	bMult->callback(button_cb, &ctx);
	bDiv->callback(button_cb, &ctx);
	bBracket->callback(bracket_cb, &ctx);
	bAt->callback(At_cb, &ctx);

	nmpad_grp->end();
	
	// Dropdown Menu to choose history file for calculations
	Fl_Choice *fileChoice = new Fl_Choice(110, 390, 160, 35, "File:");
	fileChoice->add("history.txt");
	fileChoice->deactivate();
	fileChoice->hide();
	
	// Checkbutton: if true use calculations from file if false use normal calculations
	Fl_Check_Button *checkFileCalc = new Fl_Check_Button(110, 360, 160, 30, "Calculate from file");
	checkFileCalc->callback(checkBox_cb, fileChoice);
	
	
	
	
	

	window->end();
	window->show(argc, argv);
	return Fl::run();
}