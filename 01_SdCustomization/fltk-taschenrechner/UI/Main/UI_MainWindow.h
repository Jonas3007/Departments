#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <FL/Fl_Window.H>  // Wir brauchen hier den konkreten Typ zurückzugeben
#include "Appcontext.h"       // Für AppContext

// Baut das gesamte Hauptfenster und verdrahtet alle Callbacks.
// Gibt das besitzende Fl_Window* zurück (Besitz verbleibt beim Aufrufer).
Fl_Window* buildMainWindow(AppContext* ctx);

#endif // UI_MAINWINDOW_H