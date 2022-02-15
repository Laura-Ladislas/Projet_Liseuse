#include"appli.hpp"
#include "win.cpp"

IMPLEMENT_APP(Appli);

bool Appli::OnInit()
{
  /*ScrWindow *sw = new ScrWindow(wxT("ScrolledWindow"));
    sw->Show(true);*/

  SimpleMenu *menu = new SimpleMenu(wxT("Simple Menu"));
    menu->Show(true);

  return true;
}