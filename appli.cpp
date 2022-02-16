#include"appli.hpp"
#include "win.cpp"

IMPLEMENT_APP(Appli);

bool Appli::OnInit()
{

  Win *menu = new Win(wxT("Liseuse"));
    menu->Show(true);

  return true;
}