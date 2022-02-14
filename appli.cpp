#include"appli.hpp"
#include "win.cpp"

IMPLEMENT_APP(Appli)

bool Appli::OnInit()
{
  ScrWindow *sw = new ScrWindow(wxT("ScrolledWindow"));
    sw->Show(true);
  /*window=new Win(); // Création de notre fenêtre
  window->Show(TRUE);   // Rendre visible notre fenêtre
  SetTopWindow(window); // notre fenêtre est la fenêtre principale*/
  return true;
}