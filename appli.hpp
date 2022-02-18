#ifndef APPLI_H
#define APPLI_H

#include<wx/wx.h>
#include"win.hpp"

//Classe qui permet la création de la fenêtre
class Appli: public wxApp
{
public:
     bool OnInit();
     
};

#endif
