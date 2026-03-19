#include <FL/Fl.H>
#include "Appcontext.h"
#include "UI_MainWindow.h"

// Deine bestehenden Klassen:
#include "calculator.h"
#include "historyService.h"

int main(int argc, char** argv)
{
    Calculator     calc;
    HistoryService history;

    AppContext ctx{};
    ctx.calc    = &calc;
    ctx.history = &history;

    Fl_Window* win = buildMainWindow(&ctx);
    win->show(argc, argv);

    return Fl::run();
}