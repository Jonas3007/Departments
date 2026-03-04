#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <Fl/Fl_Return_Button.H>
#include <iostream>
void button_cb(Fl_Widget *w, void *data)
{
    // 'w' ist der Button, der gedrückt wurde
    std::cout << "Button '" << w->label() << "' wurde gedrückt!" << std::endl;
}

int main(int argc, char **argv)
{

    Fl_Window *window = new Fl_Window(500, 500, "Taschenrechner");

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

    b1->callback(button_cb);
    b2->callback(button_cb);
    b3->callback(button_cb);
    b4->callback(button_cb);
    b5->callback(button_cb);
    b6->callback(button_cb);
    b7->callback(button_cb);
    b8->callback(button_cb);
    b9->callback(button_cb);
    b0->callback(button_cb);
    bPlus->callback(button_cb);
    bMinus->callback(button_cb);
    bMult->callback(button_cb);
    bDiv->callback(button_cb);
    bEqual->callback(button_cb);

    nmpad_grp->end();

    window->end();
    window->show(argc, argv);
    return Fl::run();
}