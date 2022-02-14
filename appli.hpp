#ifndef APPLI_H
#define APPLI_H

#include<wx/wx.h>
#include"win.hpp"

class Appli: public wxApp
{
public:
     bool OnInit();

/*private:
     Win * window;       // Un pointeur vers notre fenêtre
     */
};

DECLARE_APP(Appli)

#endif
