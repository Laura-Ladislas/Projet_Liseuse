#ifndef WIN_H
#define WIN_H

#include<wx/wx.h>
#include <wx/menu.h>

/*class ScrWindow: public wxFrame
{
public:
    ScrWindow(const wxString& title);
};*/

class SimpleMenu : public wxFrame
{
public:
    SimpleMenu(const wxString& title);

    void OnLire(wxCommandEvent& event);

    wxMenuBar *menubar;
    wxMenu *file;

};

#endif
