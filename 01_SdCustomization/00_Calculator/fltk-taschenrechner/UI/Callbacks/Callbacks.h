#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <FL/Fl_Widget.H>

// Allgemeine Eingabe-/Rechen-Callbacks
void append_cb(Fl_Widget* w, void* data);
void bracket_cb(Fl_Widget* w, void* data);
void backspace_cb(Fl_Widget* w, void* data);
void clear_cb(Fl_Widget* w, void* data);
void calculateResult_cb(Fl_Widget* w, void* data);

// History
void history_cb(Fl_Widget* w, void* data);
void saveHistory_cb(Fl_Widget* w, void* data); // QuickSave (QS)
void refresh_cb(Fl_Widget* w, void* data);     // (Platzhalter, falls gebraucht)

// File-Mode
void checkBox_cb(Fl_Widget* w, void* data);
void addFile_cb(Fl_Widget* w, void* data);
void fileChoice_cb(Fl_Widget* w, void* data);

#endif // CALLBACKS_H