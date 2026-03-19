#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

// Forward-Declarations, damit der Header leichtgewichtig bleibt
class Calculator;
class HistoryService;
class Fl_Input;
class Fl_Output;
class Fl_Choice;
class Fl_Button;


struct AppContext {
	Calculator*      calc          = nullptr;
	HistoryService*  history       = nullptr;
	Fl_Input*        input         = nullptr;
	Fl_Output*       output        = nullptr;

	// File-Mode UI
	Fl_Choice*       fileChoice    = nullptr;
	Fl_Input*        newFileInput  = nullptr;
	Fl_Button*       addFileButton = nullptr; // NEU
	bool             fileMode      = false;
	bool             addFilePending = false;  // NEU
};

#endif // APP_CONTEXT_H
