#ifndef WIN_H
#define WIN_H

#include<wx/wx.h>
#include <wx/menu.h>

//Classe représentant la fenêtre d'affichage
class Win : public wxFrame
{
public:
    Win(const wxString& title);

    void OnLire(wxCommandEvent& event);
    void OnDezip(wxCommandEvent& event);
    void OnPrec(wxCommandEvent& event);
    void OnSuiv(wxCommandEvent& event);
    void OnZoom(wxCommandEvent& event);
    void OnDezoom(wxCommandEvent& event);

    wxMenuBar *menubar;
    wxMenu *menu;                         
    wxScrolledWindow *sw;                //Fenêtre où s'affiche l'image
    wxStaticBitmap *sb;                  //Bitmap statique dans lequel sont chargées les images

};
#endif
