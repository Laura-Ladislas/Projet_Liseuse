#ifndef WIN_H
#define WIN_H

#include<wx/wx.h>
#include <wx/menu.h>


class Win : public wxFrame
{
public:
    Win(const wxString& title);

    void OnLire(wxCommandEvent& event);
    void OnDezip(wxCommandEvent& event);
    void OnPrec(wxCommandEvent& event);
    void OnSuiv(wxCommandEvent& event);
    void OnZoom(wxCommandEvent& event);

    wxMenuBar *menubar;
    wxMenu *file;

};

enum
    {
    ID_Lire = 1,
    ID_Dezip=100
    };
#endif
