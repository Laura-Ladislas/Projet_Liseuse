#include"appli.hpp"
#include "win.cpp"

IMPLEMENT_APP(Appli);

//Affiche la fenêtre complète
bool Appli::OnInit()
{

  Win *win = new Win(wxT("Liseuse"));
    win->Show(true);

  return true;
}