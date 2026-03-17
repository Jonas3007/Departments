#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Button.H>

#include "Appcontext.h"

class HistoryWindow : public Fl_Window
{
public:
    HistoryWindow(AppContext* ctx);

private:
    AppContext* ctx;

    Fl_Input* filenameInput;
    Fl_Multiline_Output* historyOutput;

    // interne Hilfsfunktionen
    void refresh();
    void save();

    // statische Callback-Wrapper
    static void cb_refresh(Fl_Widget*, void*);
    static void cb_save(Fl_Widget*, void*);
};

#endif // HISTORYWINDOW_H